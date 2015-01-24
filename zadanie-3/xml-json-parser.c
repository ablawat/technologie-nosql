#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

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
    char file_name[] = "plwiki-test-head.xml";
    
    xmlDoc *doc = NULL;
    
    xmlNode *root_node;
    xmlNode *current_node;
    xmlNode *node_tmp;
    
    xmlChar *text;
    
    int32_t result;
    
    LIBXML_TEST_VERSION
    
    doc = xmlReadFile(file_name, NULL, 0);
    
    root_node = xmlDocGetRootElement(doc);
    
    for (current_node = root_node -> children; current_node != NULL; current_node = current_node -> next)
    {
        if (current_node -> type == XML_ELEMENT_NODE)
        {
            result = strcmp(current_node -> name, "page");
            
            if (result == 0)
            {
                node_tmp = find_node(current_node, "revision");
                
                if (node_tmp != NULL)
                {
                    node_tmp = find_node(node_tmp, "text");
                    
                    text = xmlNodeGetContent(node_tmp);
                    printf("%s", text);
                    xmlFree(text);
                }
            }
        }
    }
    
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return 0;
}
