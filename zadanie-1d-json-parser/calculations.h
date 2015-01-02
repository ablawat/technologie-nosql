#ifndef CALCULATIONS_H
#define CALCULATIONS_H

typedef struct transmitter
{
    char *value_longitude;
    char *value_latitude;
    char *value_name;
}
transmitter_t;

transmitter_t *  transmitter_create  (char *csv_line, char *delimiter);
json_object *    json_create         (transmitter_t *transmitter);

#endif
