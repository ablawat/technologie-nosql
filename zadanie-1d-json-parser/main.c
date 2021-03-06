#include <json/json.h>
#include <stdio.h>
#include <string.h>
#include "calculations.h"

int main()
{
    char in_file_name[]  = "../data/radiopolska_obiekty.csv";
    char out_file_name[] = "../data/stations.json";
    
    transmitter_t *transmitter;
    
    char line_buffer[2 * 1024];
    
    FILE *in_file;
    FILE *out_file;
    
    json_object *json;
    
    const char *json_str;
    char *read_result;
    
    
    in_file = fopen(in_file_name, "r");
    
    if (in_file == NULL)
    {
        fputs("Input/Output error.", stderr);
        return -1;
    }
    
    out_file = fopen(out_file_name, "w");
    
    if (out_file == NULL)
    {
        fputs("Input/Output error.", stderr);
        return -1;
    }
    
    
    do
    {
        read_result = fgets(line_buffer, 2 * 1024, in_file);
        
        if (read_result != NULL)
        {
            line_buffer[strlen(line_buffer) - 2] = '\0';
            
            transmitter = transmitter_create(line_buffer, ",");
            
            json = json_create(transmitter);
            
            json_str = json_object_to_json_string(json);
            
            fputs(json_str, out_file);
            fputc(10, out_file);
            
            json_object_put(json);
            free(transmitter);
        }
    }
    while (read_result != NULL);
    
    fclose(in_file);
    fclose(out_file);
    
    return 0;
}
