#include "command_handler.h"

type_request get_type_req(const char *req)
{
  if (strncmp(req, GET_KEY, LEN_TYPE))
    return get_type;
  else if (strncmp(req, SET_KEY, LEN_TYPE))
    return set_type;
  else if (strncmp(req, DEL_KEY, LEN_TYPE))
    return del_type;
  return unknown_type;
}

int is_valid_req(const char *req)
{
  if (!req)
    return 0;

  type_request type = get_type_req(req);
  if (type == unknown_type)
    return 0;

  if (type == get_type || type == del_type)
  {
  }
  else if (type == set_type)
  {
  }

  return 1;
}

kvstore *get_data(const char *req)
{
  kvstore *store = (kvstore *)calloc(1, sizeof(kvstore));
  if (!store)
    return NULL;

  char *normalized_req = normalize_req(req);
}

char *normalize_req(const char *req)
{
  char *result = NULL;
  int ind = 0, sup = 0;
  while (req[ind] != '\0')
  {
    if (req[ind] == '\"')
      sup = !sup;
    else if (req[ind] != ' ' || sup)
    {
      result = (char *)calloc(result, (ind + 1) * sizeof(char));
      result[ind] = req[ind];
    }
    ind++;
  }
  result = (char *)calloc(result, (ind + 1) * sizeof(char));
  result[ind] = '\0';
  return result;
}