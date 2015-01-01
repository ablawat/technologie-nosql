#include <json/json.h>
#include <string.h>
#include <stdlib.h>
#include <mongoc.h>
#include <alloca.h>
#include <stdio.h>
#include <bson.h>

bson_t * bson_query_create()
{
    bson_t *bson_query = bson_new();
    bson_t *bson1, *bson2;
    
    bson1 = bson_new();
    bson_append_double(bson1, "0", -1, 21.000366);
    bson_append_double(bson1, "1", -1, 52.231163);
    
    bson2 = bson_new();
    bson_append_utf8(bson2, "type", -1, "Point", -1);
    bson_append_array(bson2, "coordinates", -1, bson1);
    
    bson1 = bson_new();
    bson_append_document(bson1, "$geometry", -1, bson2);
    bson_append_int32(bson1, "$maxDistance", -1, 100000);
    
    bson2 = bson_new();
    bson_append_document(bson2, "$near", -1, bson1);
    
    bson_append_document(bson_query, "geometry", -1, bson2);
    
    return bson_query;
}

int main()
{
    char uri_string[]      = "mongodb://localhost:27017/";
    char db_name[]         = "test";
    char collection_name[] = "places";
    
    char out_file_name[]   = "../data/query-1.geojson";
    
    mongoc_client_t     *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t     *cursor;
    
    FILE *file_geojson;
    
    const bson_t *document;
    
    bson_t *query;
    bson_t *geojson;
    bson_t *array;
    
    char str_buffer[16];
    
    json_object *json;
    enum json_type json_type;
    
    int32_t counter;
    
    char *str;
    char *tags_str;
    
    char **strings;
    char **pointer;
    
    //
    
    
    file_geojson = fopen(out_file_name, "w");
    
    mongoc_init();
    
    client = mongoc_client_new(uri_string);
    collection = mongoc_client_get_collection(client, db_name, collection_name);
    
    query = bson_query_create();
    
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
    
    bson_append_array(geojson, "features", -1, array);
    
    str = bson_as_json(geojson, NULL);
    
    fputs(str, file_geojson);
    fclose(file_geojson);
    
    bson_free(str);
    
    mongoc_cursor_destroy(cursor);
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    
    return 0;
}
