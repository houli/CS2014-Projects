#include "symbol.h"

typedef struct {
  symbol ** table;
  int size;
} huffman_tree;

huffman_tree * huffman_tree_new(int size);

void huffman_tree_insert(huffman_tree * tree, int index, symbol * s);

void huffman_tree_merge(huffman_tree * tree);

void find_smallest(huffman_tree * tree, int * smallest, int * next_smallest, int end);

void huffman_tree_walk(huffman_tree * tree);

void huffman_tree_free(huffman_tree * tree);
