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

bson_t * create_query_bson(int id)
{
    bson_t *bson = bson_new();
    bson_append_int32(bson, "id", -1, id);
    
    return bson;
}

bson_t * create_update_bson(char **tags)
{
    bson_t *bson_update = bson_new();
    bson_t *bson_array  = bson_new();
    bson_t *bson_set    = bson_new();
    
    char array_key[16];
    int count = 0;
    
    while (*tags != NULL)
    {
        sprintf(array_key, "%d", count);
        bson_append_utf8(bson_array, array_key, -1, *tags, -1);
        
        count += 1;
        tags  += 1;
    }
    
    bson_append_array(bson_set, "string", -1, bson_array);
    bson_append_document(bson_update, "$set", -1, bson_set);
    
    bson_destroy(bson_array);
    bson_destroy(bson_set);
    
    return bson_update;
}

int main()
{
    char uri_string[]      = "mongodb://localhost:27017/";
    char db_name[]         = "test";
    char collection_name[] = "test";
    
    mongoc_client_t     *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t     *cursor;
    
    const bson_t *document;
    bson_t *query;
    bson_t *update;
    
    json_object *json;
    enum json_type json_type;
    
    size_t len;
    
    char *str;
    char *tags;
    
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
            if (strcmp(key, "string") == 0)
            {
                json_type = json_object_get_type(val);
                
                if (json_type == json_type_string)
                {
                    tags = strdup(json_object_get_string(val));
                    strings = split(tags, " ");
                    free(tags);
                    
                    update = create_update_bson(strings);
                    //printf("%s\n", bson_as_json(update, NULL));
                    
                    bson_destroy(update);
                    free(strings);
                    /*
                    pointer = strings;
                    
                    while (*pointer != NULL)
                    {
                        printf("%s:", *pointer);
                        
                        pointer++;
                    }
                    
                    putchar(10);
                    */
                }
            }
        }
        
        bson_free(str);
        json_object_put(json);
    }
    
    bson_destroy(query);
    mongoc_cursor_destroy(cursor);
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    
    return 0;
}
