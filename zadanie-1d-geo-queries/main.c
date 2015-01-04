#include <string.h>
#include <stdlib.h>
#include <mongoc.h>
#include <stdio.h>
#include <bson.h>
#include "queries.h"

typedef struct query
{
    bson_t  *query;
    char    out_file[64];
}
query_t;

int main()
{
    char uri_string[]      = "mongodb://localhost:27017/";
    char db_name[]         = "test";
    char collection_name[] = "places";
    
    query_t queries[3];
    point_t points[7];
    
    mongoc_client_t     *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t     *cursor;
    
    FILE *file_geojson;
    
    const bson_t *document;
    
    bson_t *query;
    bson_t *geojson;
    bson_t *array;
    
    char str_buffer[16];
    
    int32_t i, counter;
    
    char *str;
    
    
    points[0].longitude = 17.970;
    points[0].latitude  = 54.130;
    
    points[1].longitude = 18.779;
    points[1].latitude  = 54.099;
    
    points[2].longitude = 18.930;
    points[2].latitude  = 53.740;
    
    points[3].longitude = 18.440;
    points[3].latitude  = 53.400;
    
    points[4].longitude = 17.030;
    points[4].latitude  = 53.359;
    
    points[5].longitude = 16.689;
    points[5].latitude  = 53.710;
    
    points[6].longitude = 17.970;
    points[6].latitude  = 54.130;
    
    queries[0].query = bson_query1_create();
    strcpy(queries[0].out_file, "../data/query-1.geojson");
    
    queries[1].query = bson_query2_create();
    strcpy(queries[1].out_file, "../data/query-2.geojson");
    
    queries[2].query = bson_query3_create(points, 7);
    strcpy(queries[2].out_file, "../data/query-3.geojson");
    
    
    mongoc_init();
    
    client = mongoc_client_new(uri_string);
    collection = mongoc_client_get_collection(client, db_name, collection_name);
    
    for (i = 0; i < 3; i++)
    {
        query = queries[i].query;
        
        array   = bson_new();
        geojson = bson_new();
        
        bson_append_utf8(geojson, "type", -1, "FeatureCollection", -1);
        
        cursor = mongoc_collection_find(collection, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);
        
        counter = 0;
        
        while (mongoc_cursor_next(cursor, &document))
        {
            sprintf(str_buffer, "%d", counter);
            bson_append_document(array, str_buffer, -1, document);
            
            counter += 1;
        }
        printf("%d\n", counter);
        bson_append_array(geojson, "features", -1, array);
        
        str = bson_as_json(geojson, NULL);
        
        file_geojson = fopen(queries[i].out_file, "w");
        
        fputs(str, file_geojson);
        fclose(file_geojson);
        
        bson_free(str);
        bson_free(query);
    
        mongoc_cursor_destroy(cursor);
    }
    
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    
    return 0;
}
