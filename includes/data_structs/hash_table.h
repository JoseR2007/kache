#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "linked_list.h"
#include <pthread.h>
#include <stdatomic.h>

#define INIT_CAPACITY 64
#define N_LOCKS 16

typedef struct hash_table
{
  atomic_int numOfElements;
  int capacity;
  Node **arr;
  pthread_mutex_t *locks;
} hash_table;

int hash_fn(char *, int);
hash_table *creat_hash_table(void);
void ht_destroy(hash_table *);
void hash_insert(kvstore *, hash_table *);
kvstore *search(char *, hash_table *);
void delete_key(char *, hash_table *);
int modif_key(hash_table *, char *, char *);

int lock_index(int);
int bucket_index(int);

#endif