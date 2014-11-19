#include <json/json.h>
#include <string.h>
#include <stdlib.h>
#include <mongoc.h>
#include <alloca.h>
#include <stdio.h>
#include <bson.h>

char ** split(char *string, char *delimiter)
{
    char **strings;
    char **pointer;
    
    char *substring;
    
    strings = malloc(100);
    pointer = strings;
    
    while ((substring = strsep(&string, delimiter)) != NULL)
    {
        *pointer = malloc(strlen(substring));
        strcpy(*pointer, substring);
        
        pointer++;
    }       
    
    *pointer = NULL;
    
    return strings;
}

int main()
{
    char uri_string[]      = "";
    char db_name[]         = "";
    char collection_name[] = "";
    
    mongoc_client_t     *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t     *cursor;
    
    bson_t *document;
    bson_t *query;
    
    json_object *json;
    enum json_type json_type;
    
    size_t len;
    
    char *str;
    char *tags;
    
    char **strings;
    char **pointer;
    
    
    mongoc_init();
    
    client = mongoc_client_new(uri_string);
    collection = mongoc_client_get_collection(client, db_name, collection_name);
    
    query = bson_new();
    
    cursor = mongoc_collection_find(collection, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);
    
    while (mongoc_cursor_next(cursor, &document))
    {
        str = bson_as_json(document, NULL);
        json = json_tokener_parse(str);
        
        json_object_object_foreach(json, key, val)
        {
            if (strcmp(key, "string") == 0)
            {
                json_type = json_object_get_type(val);
                
                if (json_type == json_type_string)
                {
                    tags = strdupa(json_object_get_string(val));
                    
                    //puts(tags);
                    
                    strings = split(tags, " ");
                    
                    pointer = strings;
                    
                    while (*pointer != NULL)
                    {
                        pointer++;
                    }
                }
            }
        }
        
        bson_free(str);
    }
    
    bson_destroy(query);
    mongoc_cursor_destroy(cursor);
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    
    return 0;
}
