#include <mongoc.h>
#include <stdio.h>
#include <bson.h>
#include "queries.h"

int main()
{
    char uri_string[]      = "mongodb://localhost:27017/";
    char db_name[]         = "test";
    char collection_name[] = "imdb";
    
    mongoc_client_t     *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t     *cursor;
    
    const bson_t *document;
    
    bson_t *pipeline_queries[4];
    bson_t *query;
    
    char *str;
    
    int32_t i;
    
    
    pipeline_queries[0] = bson_pipeline_query1_create();
    pipeline_queries[1] = bson_pipeline_query2_create();
    pipeline_queries[2] = bson_pipeline_query3_create();
    pipeline_queries[3] = bson_pipeline_query4_create();
    
    mongoc_init();
    
    client = mongoc_client_new(uri_string);
    collection = mongoc_client_get_collection(client, db_name, collection_name);
    
    for (i = 0; i < 4; i++)
    {
        query = pipeline_queries[i];
        
        cursor = mongoc_collection_aggregate(collection, MONGOC_QUERY_NONE, query, NULL, NULL);
        
        printf("Aggregation %d result:\n", i + 1);
        
        while (mongoc_cursor_next(cursor, &document))
        {
            str = bson_as_json(document, NULL);
            puts(str);
            
            bson_free(str);
        }
        
        bson_free(query);
        mongoc_cursor_destroy(cursor);
    }
    
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    
    return 0;
}
