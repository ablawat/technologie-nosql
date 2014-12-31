#ifndef QUERIES_H
#define QUERIES_H

#include "linked-list-tag.h"

bson_t *  create_bson_selector  (int id);
bson_t *  create_bson_update    (linked_list_tag_t **list);

#endif
