#include <bson.h>

bson_t * bson_query1_create()
{
    bson_t *bson_query = bson_new();
    bson_t *bson1, *bson2;

    bson1 = bson_new();
    bson_append_double(bson1, "0", -1, 21.020);
    bson_append_double(bson1, "1", -1, 52.259);

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

bson_t * bson_query2_create()
{
    bson_t *bson_query = bson_new();
    bson_t *bson1, *bson2;

    bson1 = bson_new();
    bson_append_double(bson1, "0", -1, 18.639);
    bson_append_double(bson1, "1", -1, 54.360);

    bson2 = bson_new();
    bson_append_utf8(bson2, "type", -1, "Point", -1);
    bson_append_array(bson2, "coordinates", -1, bson1);

    bson1 = bson_new();
    bson_append_document(bson1, "$geometry", -1, bson2);
    bson_append_int32(bson1, "$minDistance", -1, 100000);
    bson_append_int32(bson1, "$maxDistance", -1, 300000);

    bson2 = bson_new();
    bson_append_document(bson2, "$near", -1, bson1);

    bson_append_document(bson_query, "geometry", -1, bson2);

    return bson_query;
}
