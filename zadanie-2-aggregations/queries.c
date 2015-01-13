#include <bson.h>
#include "queries.h"

bson_t * bson_pipeline_query1_create()
{
    bson_t *bson_pipeline_query = bson_new();
    bson_t *bson1, *bson2, *bson3, *bson4;
    
    bson1 = bson_new();
    
    bson2 = bson_new();
    bson3 = bson_new();
    
    bson_append_utf8(bson3, "_id", -1, "$action", -1);
    
    bson4 = bson_new();
    bson_append_int32(bson4, "$sum", -1, 1);
    bson_append_document(bson3, "count", -1, bson4);
    bson_append_document(bson2, "$group", -1, bson3);
    bson_append_document(bson1, "0", -1, bson2);
    
    
    bson2 = bson_new();
    bson3 = bson_new();
    
    bson_append_int32(bson3, "count", -1, -1);
    bson_append_document(bson2, "$sort", -1, bson3);
    bson_append_document(bson1, "1", -1, bson2);
    
    
    bson_append_array(bson_pipeline_query, "pipeline", -1, bson1);
    
    return bson_pipeline_query;
}
bson_t * bson_pipeline_query2_create()
{
    bson_t *bson_pipeline_query = bson_new();
    bson_t *bson1, *bson2, *bson3, *bson4;
    
    bson1 = bson_new();
    
    bson2 = bson_new();
    bson3 = bson_new();
    
    bson_append_utf8(bson3, "_id", -1, "$userId", -1);
    
    bson4 = bson_new();
    bson_append_int32(bson4, "$sum", -1, 1);
    bson_append_document(bson3, "count", -1, bson4);
    bson_append_document(bson2, "$group", -1, bson3);
    bson_append_document(bson1, "0", -1, bson2);
    
    
    bson2 = bson_new();
    bson3 = bson_new();
    
    bson_append_int32(bson3, "count", -1, -1);
    bson_append_document(bson2, "$sort", -1, bson3);
    bson_append_document(bson1, "1", -1, bson2);
    
    
    bson2 = bson_new();
    bson_append_int32(bson2, "$limit", -1, 20);
    
    bson_append_document(bson1, "2", -1, bson2);
    
    
    bson_append_array(bson_pipeline_query, "pipeline", -1, bson1);
    
    return bson_pipeline_query;
}

bson_t * bson_pipeline_query3_create()
{
    bson_t *bson_pipeline_query = bson_new();
    bson_t *bson1, *bson2, *bson3, *bson4;
    
    bson1 = bson_new();
    
    bson2 = bson_new();
    bson3 = bson_new();
    
    bson_append_utf8(bson3, "modelName", -1, "movies", -1);
    bson_append_document(bson2, "$match", -1, bson3);
    bson_append_document(bson1, "0", -1, bson2);
    
    
    bson2 = bson_new();
    bson3 = bson_new();
    
    bson_append_utf8(bson3, "_id", -1, "$title", -1);
    
    bson4 = bson_new();
    bson_append_int32(bson4, "$sum", -1, 1);
    bson_append_document(bson3, "count", -1, bson4);
    bson_append_document(bson2, "$group", -1, bson3);
    bson_append_document(bson1, "1", -1, bson2);
    
    
    bson2 = bson_new();
    bson3 = bson_new();
    
    bson_append_int32(bson3, "count", -1, -1);
    bson_append_document(bson2, "$sort", -1, bson3);
    bson_append_document(bson1, "2", -1, bson2);
    
    
    bson2 = bson_new();
    bson_append_int32(bson2, "$limit", -1, 10);
    
    bson_append_document(bson1, "3", -1, bson2);
    
    
    bson_append_array(bson_pipeline_query, "pipeline", -1, bson1);
    
    return bson_pipeline_query;
}

bson_t * bson_pipeline_query4_create()
{
    bson_t *bson_pipeline_query = bson_new();
    bson_t *bson1, *bson2, *bson3, *bson4;
    
    bson1 = bson_new();
    
    bson2 = bson_new();
    bson3 = bson_new();
    
    bson_append_utf8(bson3, "modelName", -1, "movies", -1);
    bson_append_document(bson2, "$match", -1, bson3);
    bson_append_document(bson1, "0", -1, bson2);
    
    
    bson2 = bson_new();
    bson3 = bson_new();
    
    bson_append_utf8(bson3, "action", -1, "Liked", -1);
    bson_append_document(bson2, "$match", -1, bson3);
    bson_append_document(bson1, "1", -1, bson2);
    bson2 = bson_new();
    bson3 = bson_new();
    
    bson_append_utf8(bson3, "_id", -1, "$title", -1);
    
    bson4 = bson_new();
    bson_append_int32(bson4, "$sum", -1, 1);
    bson_append_document(bson3, "count", -1, bson4);
    bson_append_document(bson2, "$group", -1, bson3);
    bson_append_document(bson1, "2", -1, bson2);
    
    
    bson2 = bson_new();
    bson3 = bson_new();
    
    bson_append_int32(bson3, "count", -1, -1);
    bson_append_document(bson2, "$sort", -1, bson3);
    bson_append_document(bson1, "3", -1, bson2);
    
    
    bson2 = bson_new();
    bson_append_int32(bson2, "$limit", -1, 15);
    
    bson_append_document(bson1, "4", -1, bson2);
    
    
    bson_append_array(bson_pipeline_query, "pipeline", -1, bson1);
    
    return bson_pipeline_query;
}
