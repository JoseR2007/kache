#include "./linked_list.h"

void free_list(Node *head)
{
   if (!head)
      return;

   Node *next = NULL; // Guardamos una referencia al elemento siguiente del actual, para liberaralo luego
   Node *current_element = head;
   while (current_element != NULL)
   {
      next = current_element->next;
      free(current_element);
      current_element = next;
   }

   free(head);
   return;
}

Node *create_node(kvstore *data)
{
   Node *new_node = (Node *)malloc(sizeof(Node));
   if (!new_node)
      return NULL;

   new_node->data = data;
   new_node->next = NULL;
   new_node->prev = NULL;

   return new_node;
}

Node *get_node_by_index(Node *head, int index)
{
   if (index < 0)
      return NULL;

   int ind = 0;
   Node *current_node = head;
   while (ind < index && current_node->next)
   {
      current_node = current_node->next;
      ind++;
   }
   if (index > ind)
      current_node = NULL;

   return current_node;
}

Node *get_node_by_key(Node *head, char *key)
{
   Node *current_node = head;
   int find = 0;
   while (!find && current_node->next)
   {
      if (strcmp(current_node->data->key, key))
      {
         find = 1;
         continue;
      }
      current_node = current_node->next;
   }

   if (!find)
      current_node = NULL;
   return current_node;
}