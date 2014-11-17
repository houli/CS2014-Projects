#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

hashtable * hashtable_new(int size) {
  hashtable * table = malloc(sizeof(hashtable));
  table->size = size;
  table->table = malloc(sizeof(node *) * size);
  int i;
  for (i = 0; i < size; i++) {
    table->table[i] = NULL;
  }
  return table;
}

void hashtable_free(hashtable * this) {
  int i;
  for (i = 0; i < this->size; i++) {
    node * next = this->table[i];
    while (next != NULL) {
      node * temp = node_next(next);
      node_free(next);
      next = temp;
    }
  }
  free(this->table);
  free(this);
}

void hashtable_insert(hashtable * this, char * item) {
  if (!hashtable_lookup(this, item)) {
    unsigned hash = hash_string(item);
    node * node = node_new(item);
    node_update_next(node, this->table[hash % this->size]);
    this->table[hash % this->size] = node;
  }
}

void hashtable_remove(hashtable * this, char * item) {
  if (hashtable_lookup(this, item)) {
    unsigned hash = hash_string(item);
    node * current = this->table[hash % this->size];
    if (strcmp(item, node_get_string(current)) == 0) {
      this->table[hash % this->size] = node_next(current);
      node_free(current);
    } else {
      while (!strcmp(item, node_get_string(node_next(current))) == 0) {
        current = node_next(current);
      }
      node * next = node_next(current);
      node_update_next(current, node_next(next));
      node_free(next);
    }
  }
}

int hashtable_lookup(hashtable * this, char * item) {
  unsigned hash = hash_string(item);
  if (this->table[hash % this->size] == NULL) {
    return 0;
  } else {
    node * node = this->table[hash % this->size];
    while (node != NULL) {
      if (strcmp(item, node_get_string(node)) == 0) {
        return 1;
      }
      node = node_next(node);
    }  
    return 0;
  }
}

void hashtable_print(hashtable * this) {
  int i;
  for (i = 0; i < this->size; i++) {
    printf("%d: ", i);
    if (this->table[i] == NULL) {
      printf("<empty>");
    } else {
      int is_first = 1;
      node * node = this->table[i];
      while (node != NULL) {
        if (!is_first) {
          printf(", ");
        } else {
          is_first = 0;
        }
        printf("%s", node_get_string(node));
        node = node_next(node);
      }
    }
    printf("\n");
  }
}

unsigned hash_string(char * str) {
  unsigned hash = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    hash = hash * 37 + str[i];
  }
  return hash;
}
