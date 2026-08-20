#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

#define GET_KEY "GET"
#define SET_KEY "SET"
#define DEL_KEY "DEL"

// Partes clave de las solicitudes
#define DIVISION_MASK "/r/n"
#define SUBDIVISION_MASK "/r"
#define CLOSE_MASK "/r/c"
#define LEN_TYPE 3

typedef enum
{
  get_type,
  set_type,
  del_type,
  unknown_type
} type_request;

type_request get_type_req(const char *);
int is_valid_req(const char *);
kvstore *get_data(const char *);
char *normalize_req(const char *);

#endif