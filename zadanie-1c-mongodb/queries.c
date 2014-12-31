#include <stdlib.h>
#include <bson.h>
#include "linked-list-tag.h"

bson_t * create_bson_selector(int id)
{
    bson_t *bson = bson_new();
    bson_append_int32(bson, "id", -1, id);
    
    return bson;
}

bson_t * create_bson_update(linked_list_tag_t **tags)
{
    bson_t *bson_update = bson_new();
    bson_t *bson_array  = bson_new();
    bson_t *bson_set    = bson_new();
    
    linked_list_tag_t *list_item = tags[0];
    
    char array_key[16];
    int count = 0;
    
    while (list_item != NULL)
    {
        sprintf(array_key, "%d", count);
        bson_append_utf8(bson_array, array_key, -1, list_item -> value, -1);
        
        count += 1;
        
        list_item = list_item -> next;
    }
    
    bson_append_array(bson_set, "tags", -1, bson_array);
    bson_append_document(bson_update, "$set", -1, bson_set);
    
    bson_destroy(bson_array);
    bson_destroy(bson_set);
    
    return bson_update;
}
