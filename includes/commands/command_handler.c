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

  char *delimitation = strchr(normalize_req(req), DIVISION_MASK);
  if (!delimitation || strlen(*(delimitation + 1)) == 0)
    return 0;

  if (type == get_type || type == del_type)
  {
    char *buf = strchr(delimitation, ":");
    char buf_len[strcspn(buf, ":") + 1];
    strncpy(buf_len, buf + 1, strcspn(buf, ":"));
    buf_len[strcspn(buf, ":")] = '\0';

    int len_key = atoi(buf_len);
    if (len_key == 0)
      return 0;
    int ind = strcspn(buf, ":") + 2, count = 0;
    while (buf[ind] != '\"' && buf[ind] != '\0')
    {
      ind++;
      count++;
    }
    if (count != len_key)
      return 0;
  }
  else if (type == set_type)
  {
  }

  free(delimitation);
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