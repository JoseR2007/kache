#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <string.h>

typedef struct kvstore
{
   char *key;
   char *value;
} kvstore;

typedef struct Node
{
   kvstore *data;
   struct Node *next;
   struct Node *prev;
} Node;

void free_list(Node *);
Node *get_node_by_index(Node *, int);
Node *create_node(kvstore *);
Node *get_node_by_key(Node *, char *);

#endif