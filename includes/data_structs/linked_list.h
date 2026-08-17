#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

typedef struct Node
{
   int data;
   struct Node *next;
   struct Node *prev;
} Node;

typedef struct
{
   Node *head;
   Node *tail;
   int length;
} LinkedList;

LinkedList *create_list(void);
void add_node_end(LinkedList *, Node *);
void add_node_emp(LinkedList *, Node *);
void free_list(LinkedList *);
void add_node(LinkedList *, Node *);
Node *get_node_by_index(LinkedList, int);
Node *create_node(int);

#endif