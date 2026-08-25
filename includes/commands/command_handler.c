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
  if (!feild || strlen(feild + 1) == 0)
    return 0;

  char *buf = strchr(feild, ':');

  int len_char = strcspn(feild, ":");
  char buf_leng[len_char + 1];
  strncpy(buf_leng, buf + 1, len_char);
  buf_leng[len_char + 1] = '\0';

  int len = atoi(buf_leng);
  if (len == 0)
    return 0;

  int ind = 0, limit = strcspn(buf, DIVISION_MASK);
  while ((buf + len_char + 1)[ind] != '\"' || ind < limit)
    ind++;

  if (ind != len)
    return 0;

  return 1;
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
    return is_valid_feild(division_buf);
  }
  else if (type == SAV_KEY || type == SET_KEY)
  {
    int key_feild = is_valid_feild(division_buf);
    char *sec_division = strstr(normalized, DIVISION_MASK);
    if (!sec_division)
      return 0;
    if (!is_valid_feild(sec_division) || !key_feild)
      return 0;
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