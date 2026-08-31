#include "hash_table.h"

// Hash e indices de la tabla

int hash_fn(char *key, int size)
{
  int current_c, total = 0;
  for (int ind = 0; key[ind] != '\0'; ind++)
  {
    current_c = (int)key[ind];
    total += current_c * (ind + 1);
  }

  return total / size;
}

int lock_index(int bucket)
{
  return (bucket % N_LOCKS);
}

// Creacion y destruccion de tablas

hash_table *creat_hash_table(void)
{
  hash_table *table = (hash_table *)malloc(sizeof(hash_table));
  pthread_mutex_t *locks = (pthread_mutex_t *)malloc(N_LOCKS * sizeof(pthread_mutex_t));
  if (!table || !locks)
    return NULL;

  table->capacity = INIT_CAPACITY;
  table->numOfElements = 0;
  table->arr = (Node *)calloc(table->capacity, sizeof(Node));
  table->locks = locks;
  return table;
}

void ht_destroy(hash_table *table)
{
  if (!table)
    return;

  for (int ind = 0; ind < table->numOfElements; ind++)
  {
    Node *head;
    if ((head = table->arr[ind]) != NULL)
    {
      Node *current_node = head;
      Node *next_node = current_node->next;
      while (next_node != NULL)
      {
        free(current_node->data->key);
        free(current_node->data->value);
        free(current_node->data);
        free(current_node);
        current_node = next_node;
        next_node = next_node->next;
      }
    }
  }

  for (int ind = 0; ind < N_LOCKS; ind++)
    pthread_mutex_unlock(&table->locks[ind]);

  free(table->locks);
  free(table);
  return;
}

void hash_insert(kvstore *kv, hash_table *table)
{
  int index = hash_fn(kv->key, table->capacity);
  Node *node = (Node *)calloc(1, sizeof(Node));
  if (!node)
    return;

  if (table->arr[index] == NULL)
    table->arr[index] = node;
  else // Colision
  {
    node->prev = table->arr[index]->next;
    table->arr[index]->next = node;
  }
  table->numOfElements++;

  return;
}

kvstore *search(char *key, hash_table *table)
{
  int index = hash_fn(key, table->capacity);
  Node *node_head_found = table->arr[index];

  if (node_head_found != NULL)
    return get_node_by_key(node_head_found, key)->data;

  return NULL;
}

void delete_key(char *key, hash_table *table)
{
  int index = hash_fn(key, table->capacity);

  Node *current_node = NULL;
  if ((current_node = get_node_by_key(table->arr[index], key)) != NULL)
  {
    if (current_node->prev == NULL)
      current_node = current_node->next;
    else
    {
      current_node->prev->next = current_node->next;
      current_node->next->prev = current_node->prev;
    }
    free(current_node);
    table->numOfElements--;
  }
  return;
}

int modif_key(hash_table *table, char *key, char *new_value)
{
  kvstore *kv = search(key, table);
  if (kv == NULL)
    return -1;

  kv->value = new_value;
  return 0;
}
