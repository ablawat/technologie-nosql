#include <string.h>
#include <stdlib.h>
#include <mongoc.h>
#include <stdio.h>
#include <bson.h>

int main()
{
    char uri-string[]      = "";
    char db-name[]         = "";
    char collection-name[] = "";
    
    mongoc_client_t     *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t     *cursor;
    
    bson_t *doc;
    bson_t *query;
    
    char *str;
    
    
    mongoc_init();
    
    client = mongoc_client_new(uri-string);
    collection = mongoc_client_get_collection(client, db-name, collection-name);
    
    return 0;
}
