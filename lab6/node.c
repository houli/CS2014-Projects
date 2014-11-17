#include <stdlib.h>
#include <string.h>
#include "node.h"

node * node_new(char * data) {
  node * node = malloc(sizeof(node));
  node->data = strdup(data);
  node->next = NULL;
  return node;
}

void node_free(node * node) {
  free(node->data);
  free(node);
}

void node_update_next(node * this, node * next) {
  this->next = next;
}

node * node_next(node * node) {
  return node->next;
}

char * node_get_string(node * node) {
  return node->data;
}
