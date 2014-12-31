#ifndef LINKED_LIST_TAG_H
#define LINKED_LIST_TAG_H

typedef struct linked_list_tag
{
    char                    *value;
    struct linked_list_tag  *next;
}
linked_list_tag_t;

linked_list_tag_t ** linked_list_tag_create();

int   linked_list_tag_add_first  (linked_list_tag_t **list, char *tag);
int   linked_list_tag_add_last   (linked_list_tag_t **list, char *tag);

void  linked_list_tag_clear      (linked_list_tag_t **list);
void  linked_list_tag_destroy    (linked_list_tag_t **list);

void  linked_list_tag_print      (linked_list_tag_t **list);

#endif
