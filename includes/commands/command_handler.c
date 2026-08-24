#include "command_handler.h"

type_request get_type_req(const char *req)
{
  if (strncmp(req, GET_KEY, LEN_TYPE) == 0)
    return get_type;
  else if (strncmp(req, SET_KEY, LEN_TYPE) == 0)
    return set_type;
  else if (strncmp(req, DEL_KEY, LEN_TYPE) == 0)
    return del_type;
  else if (strncmp(req, SAV_KEY, LEN_TYPE) == 0)
    return sav_type;
  return unknown_type;
}

int is_valid_feild(const char *feild)
{
}

int is_valid_req(const char *req)
{
  if (!req)
    return 0;

  type_request type = get_type_req(req);
  if (type == unknown_type)
    return 0;

  char *normalized = normalize_req(req);
  if (!normalized)
    return 0;

  if (!strstr(normalized, CLOSE_MASK) || !strstr(normalized, DIVISION_MASK) || !strchr(normalized, ':'))
    return 0;

  char *division_buf = strstr(normalized, DIVISION_MASK);
  if (!division_buf)
    return 0;

  if (type == GET_KEY || type == DEL_KEY)
  {
  }
  else if (type == SAV_KEY || type == SET_KEY)
  {
  }

  free(normalized);
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
  int ind = 0, sup = 0, j = 0;

  result = (char *)malloc((strlen(req) + 1) * sizeof(char));
  if (!result)
    return NULL;

  while (req[ind] != '\0')
  {
    if (req[ind] == '\"')
    {
      sup = !sup;
      result[j] = req[ind];
      j++;
    }
    else if (req[ind] != ' ' || sup)
    {
      result[j] = req[ind];
      j++;
    }
    ind++;
  }
  result[j] = '\0';
  return result;
}