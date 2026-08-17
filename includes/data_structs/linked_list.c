#include "./linked_list.h"
#include <stdlib.h>

/*
Funcion: create_list
Argumentos: void
Objetivo: Crea y devuelve una lista vacia.
*/
LinkedList *create_list(void)
{
   LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
   if (!list)
      return NULL;

   list->head = NULL;
   list->tail = NULL;
   list->length = 0;

   return list;
}

/*
Funcion: LinkedList *_list: Indica la lista en la que se agregara en nodo
         Node *_node: Indica el nodo a agregar.
Objetivo: Guarda en una lista vacia un nodo recibido.
*/
void add_node_emp(LinkedList *_list, Node *_node)
{
   if (!_list || !_node)
      return;

   _list->head = _node;
   _list->tail = _node;

   _list->length++;
   return;
}

/*
Funcion: add_node_end
Argumentos: LinkedList *_list: Indica la lista donde se agregara el nodo.
            Node *_node: Indica el nodo a agregar.
Objetivo: Agregar al final de una lista un nodo recibido.
*/
void add_node_end(LinkedList *_list, Node *_node)
{
   if (!_list || !_node)
      return;

   if (!_list->head)
      add_node_emp(_list, _node);
   else
   {
      _list->tail->next = _node;
      _node->prev = _list->tail;
      _list->tail = _node;
      _list->length++;
   }
   return;
}

/*
Funcion: free_list
Argumentos: LinkedList *_list: Indica la lista a liberar.
Objetivo: Liberar la memoria ocupada por un lista.
*/
void free_list(LinkedList *_list)
{
   if (!_list)
      return;
   if (!_list->head) // Como no existen elementos en la lista, simplemente liberamos la referencia a la lista
   {
      free(_list);
      return;
   }

   Node *next = NULL; // Guardamos una referencia al elemento siguiente del actual, para liberaralo luego
   Node *current_element = _list->head;
   while (current_element != NULL)
   {
      next = current_element->next;
      free(current_element);
      current_element = next;
   }

   free(_list);
   return;
}

/*
Funcion: add_node
Argumentos: LinkedList *_list: Indica la lista en donde se guardara el nodo.
            Node *_node: Indica el nodo a guardar.
Objetivo: Guardar al principio de una lista un nodo recibido.
*/
void add_node(LinkedList *_list, Node *_node)
{
   if (!_list || !_node)
      return;

   if (!_list->head)
   {
      add_node_emp(_list, _node);
      return;
   }
   _list->head->prev = _node;
   _node->next = _list->head;
   _list->head = _node;

   _list->length++;
   return;
}

/*
Funcion: create_node
Argumentos: int _data: Indica el dato a almacenar en el nodo.
Objetivo: Crear un nuevo nodo que almacene el dato recibido.
*/
Node *create_node(int _data)
{
   Node *new_node = (Node *)malloc(sizeof(Node));
   if (!new_node)
      return NULL;

   new_node->data = _data;
   new_node->next = NULL;
   new_node->prev = NULL;

   return new_node;
}

/*
Funcion: get_node_by_index
Argumentos: LinkedList _list: Indica la lista en la que se buscara
            int _index: Indica el indice que se buscara.
Objetivo: Busca y retorna un elemento de la lista cuyo indice corresponda con el recibido.
*/
Node *get_node_by_index(LinkedList _list, int _index)
{
   if (_index < 0 || !_list.head || _index >= _list.length)
      return NULL;

   int count = 0;
   Node *current_node = _list.head;
   while (count < _index && current_node)
   {
      current_node = current_node->next;
      count++;
   }

   return current_node;
}