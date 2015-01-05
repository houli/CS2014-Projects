#include <stdlib.h>
#include "symbol.h"

symbol * symbol_new_char(int frequency, char c) {
  symbol * new_symbol = malloc(sizeof(symbol));

  new_symbol->data.c = c;

  new_symbol->frequency = frequency;
  new_symbol->is_leaf = true;
  return new_symbol;
}

symbol * symbol_new_children(int frequency, symbol * left, symbol * right) {
  symbol * new_symbol = malloc(sizeof(symbol));

  new_symbol->data.children.left = left;
  new_symbol->data.children.right = right;

  new_symbol->frequency = frequency;
  new_symbol->is_leaf = false;
  return new_symbol;
}

void symbol_free(symbol * symbol) {
  free(symbol);
}
