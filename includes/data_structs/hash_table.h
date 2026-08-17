#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "linked_list.h"

#define INIT_CAPACITY 10

typedef struct hash_table
{
  int numOfElements, capacity;
  Node **arr;
} hash_table;

int hash_fn(char *, int);
hash_table *creat_hash_table(void);
void hash_insert(kvstore *, hash_table *);
kvstore *search(char *, hash_table *);
void delete_key(char *, hash_table *);

#endif