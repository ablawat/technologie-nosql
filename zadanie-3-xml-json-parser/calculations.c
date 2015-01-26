#include <json/json.h>
#include <string.h>
#include <stdio.h>
#include "calculations.h"

json_object *  json_page_create  (int32_t page_id, char *page_text)
{
    json_object *json_page = json_object_new_object();
    json_object *json;
    
    json = json_object_new_int(page_id);
    json_object_object_add(json_page, "id", json);
    
    json = json_object_new_string(page_text);
    json_object_object_add(json_page, "text", json);
    
    return json_page;
}
