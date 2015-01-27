#include <json/json.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "calculations.h"

xmlNode * find_node(xmlNode *parent, char *node_name)
{
    xmlNode *current_node = parent;
    xmlNode *result_node  = NULL;
    int32_t result;
    
    for (current_node = current_node -> children; current_node != NULL; current_node = current_node -> next)
    {
        if (current_node -> type == XML_ELEMENT_NODE)
        {
            result = strcmp(current_node -> name, node_name);
            
            if (result == 0)
            {
                result_node = current_node;
                break;
            }
        }
    }
    
    return result_node;
}

int main()
{
    char in_file_name[]  = "../data/plwiki-20150116-pages-articles-multistream.xml";
    char out_file_name[] = "../data/wikipedia.json";
    
    const char *json_str;
    
    xmlDoc *doc = NULL;
    
    xmlNode *root_node;
    xmlNode *current_node;
    xmlNode *node_found;
    
    FILE *out_file;
    
    json_object *json;
    
    xmlChar *text;
    
    int32_t  page_id;
    char    *page_text;
    
    int32_t result;
    
    
    out_file = fopen(out_file_name, "w");

    if (out_file == NULL)
    {
        fputs("Input/Output error.", stderr);
        return -1;
    }
    
    LIBXML_TEST_VERSION
    
    doc = xmlReadFile(in_file_name, NULL, 0);
    
    root_node = xmlDocGetRootElement(doc);
    
    for (current_node = root_node -> children; current_node != NULL; current_node = current_node -> next)
    {
        if (current_node -> type == XML_ELEMENT_NODE)
        {
            result = strcmp(current_node -> name, "page");
            
            if (result == 0)
            {
                node_found = find_node(current_node, "id");
                
                if (node_found != NULL)
                {
                    text = xmlNodeGetContent(node_found);
                    page_id = (int32_t)strtol(text, NULL, 10);
                    xmlFree(text);
                }
                
                node_found = find_node(current_node, "revision");
                
                if (node_found != NULL)
                {
                    node_found = find_node(node_found, "text");
                    
                    text = xmlNodeGetContent(node_found);
                    page_text = text;
                }
                
                json = json_page_create(page_id, page_text);
                
                json_str = json_object_to_json_string(json);
                
                fputs(json_str, out_file);
                fputc(10, out_file);
                
                json_object_put(json);
                xmlFree(text);
            }
        }
    }
    
    fclose(out_file);
    
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return 0;
}
