#include <json/json.h>
#include <string.h>
#include <stdlib.h>
#include <mongoc.h>
#include <alloca.h>
#include <stdio.h>
#include <bson.h>

#include "linked-list-tag.h"
#include "queries.h"

linked_list_tag_t ** tags_split(char *string, char *delimiter)
{
    char *tag;
    char *substring;
    
    linked_list_tag_t **tags = linked_list_tag_create();
    
    while ((substring = strsep(&string, delimiter)) != NULL)
    {
        tag = malloc(strlen(substring));
        strcpy(tag, substring);
        
        linked_list_tag_add_last(tags, tag);
    }
    
    return tags;
}


int main()
{
    char uri_string[]      = "mongodb://localhost:27017/";
    char db_name[]         = "test";
    char collection_name[] = "test";
    
    mongoc_client_t     *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t     *cursor;
    
    linked_list_tag_t **tags;
    
    const bson_t *document;
    bson_t *query;
    bson_t *update;
    
    json_object *json;
    enum json_type json_type;
    
    size_t len;
    
    char *str;
    char *tags_str;
    
    char **strings;
    char **pointer;
    
    //
    
    
    mongoc_init();
    
    client = mongoc_client_new(uri_string);
    collection = mongoc_client_get_collection(client, db_name, collection_name);
    
    query = bson_new();
    
    cursor = mongoc_collection_find(collection, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);
    
    while (mongoc_cursor_next(cursor, &document))
    {
        str  = bson_as_json(document, NULL);
        json = json_tokener_parse(str);
        
        json_object_object_foreach(json, key, val)
        {
            if (strcmp(key, "tags") == 0)
            {
                json_type = json_object_get_type(val);
                
                if (json_type == json_type_string)
                {
                    tags_str = strdup(json_object_get_string(val));
                    tags = tags_split(tags_str, " ");
                    free(tags_str);
                    
                    //linked_list_tag_print(tags);
                    
                    update = create_bson_update(tags);
                    
                    //printf("%s\n", bson_as_json(update, NULL));
                    
                    linked_list_tag_clear(tags);
                    free(tags);
                }
            }
            else if (strcmp(key, "id") == 0)
            {
                query = create_bson_selector(json_object_get_int(val));
                
                printf("%s\n", bson_as_json(query, NULL));
            }
        }
        
        mongoc_collection_update(collection, MONGOC_QUERY_NONE, query, update, NULL, NULL);
        
        bson_destroy(update);
        bson_destroy(query);
        bson_free(str);
        json_object_put(json);
    }
    
    mongoc_cursor_destroy(cursor);
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    
    return 0;
}
