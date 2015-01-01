#include <json/json.h>
#include <string.h>
#include <stdio.h>
#include "calculations.h"

transmitter_t * transmitter_create(char *csv_line, char *delimiter)
{
    transmitter_t *transmitter;
    
    char *substring;
    char *fields[3];
    
    int32_t i;
    
    for (i = 0; i < 3; i++)
    {
        substring = strsep(&csv_line, delimiter);
        fields[i] = substring;
    }
    
    transmitter = malloc(sizeof(transmitter_t));
    
    transmitter -> value_longitude = fields[0];
    transmitter -> value_latitude  = fields[1];
    transmitter -> value_name      = fields[2];
    
    return transmitter;
}

json_object * geojson_create(transmitter_t *transmitter)
{
    json_object *geojson = json_object_new_object();
    json_object *json1, *json2, *json3;
    double coordinate;
    
    json1 = json_object_new_string("Feature");
    json_object_object_add(geojson, "type", json1);
    
    json1 = json_object_new_object();
    json2 = json_object_new_string("Point");
    json_object_object_add(json1, "type", json2);
    
    json2 = json_object_new_array();
    
    coordinate  = strtod(transmitter -> value_longitude, NULL);
    json3 = json_object_new_double(coordinate);
    json_object_array_add(json2, json3);
    
    coordinate = strtod(transmitter -> value_latitude, NULL);
    json3 = json_object_new_double(coordinate);
    json_object_array_add(json2, json3);
    
    json_object_object_add(json1, "coordinates", json2);
    
    json_object_object_add(geojson, "geometry", json1);
    
    json1 = json_object_new_object();       
    json2 = json_object_new_string(transmitter -> value_name);
    json_object_object_add(json1, "name", json2);
    
    json_object_object_add(geojson, "properties", json1);
    
    return geojson;
}
