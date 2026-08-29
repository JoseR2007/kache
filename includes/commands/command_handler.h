#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "hash_table.h"

#define GET_KEY "GET"
#define SET_KEY "SET"
#define DEL_KEY "DEL"
#define SAV_KEY "SAV"

// Partes clave de las solicitudes
#define DIVISION_MASK "/r/n"
#define CLOSE_MASK "/r/c"

#define LEN_MASK 4
#define LEN_TYPE 3

typedef enum
{
  get_type,
  set_type,
  del_type,
  sav_type,
  unknown_type
} type_request;

type_request get_type_req(const char *);
int is_valid_req(const char *);
int is_valid_feild(const char *);
kvstore *get_data(const char *, type_request); // <- asume que la request se valido antes
char *normalize_req(const char *);
void *req_handle(const char *);
char *get_feild_value(const char *);

#endif