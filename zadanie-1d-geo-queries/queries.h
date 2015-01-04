#ifndef QUERIES_H
#define QUERIES_H

typedef struct point
{
    double longitude;
    double latitude;
}
point_t;

bson_t * bson_query1_create();
bson_t * bson_query2_create();
bson_t * bson_query3_create(point_t *point, size_t point_num);

#endif
