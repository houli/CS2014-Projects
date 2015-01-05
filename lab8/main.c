#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "huffman.h"

const int CHARACTER_SET_SIZE = 256;

int main(int argc, char ** argv) {
  unsigned char c;
  FILE * file;
  int freqs[CHARACTER_SET_SIZE] = {};

  if (argc != 2) {
    fprintf(stderr, "Usage: huffman <filename>\n");
    exit(1); // exit with error code
  }

  file = fopen(argv[1], "r");
  assert(file != NULL);
  c = fgetc(file);
  while (!feof(file)) {
    freqs[c]++;
    c = fgetc(file);
  }
  fclose(file);

  huffman_tree * tree = huffman_tree_new(CHARACTER_SET_SIZE);
  int i;
  for (i = 0; i < CHARACTER_SET_SIZE; i++) {
    if (freqs[i] == 0) {
      freqs[i] = 1;
    }
    symbol * char_symbol = symbol_new_char(freqs[i], i);
    huffman_tree_insert(tree, i, char_symbol);
  }

  huffman_tree_merge(tree);
  huffman_tree_walk(tree);
  huffman_tree_free(tree);

  return 0;
}
