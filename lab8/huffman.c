#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"

huffman_tree * huffman_tree_new(int size) {
  huffman_tree * tree = malloc(sizeof(huffman_tree));
  tree->table = malloc(sizeof(symbol *) * size);
  tree->size = size;
  return tree;
}

void huffman_tree_insert(huffman_tree * tree, int index, symbol * s) {
  tree->table[index] = s;
}

void find_smallest(huffman_tree * tree, int * smallest, int * next_smallest, int end) {
  int i;
  *smallest = 0;
  *next_smallest = 1;
  if (tree->table[*next_smallest]->frequency < tree->table[*smallest]->frequency) {
    *smallest = 1;
    *next_smallest = 0;
  }
  for (i = 2; i <= end; i++) {
    if (tree->table[i]->frequency < tree->table[*smallest]->frequency) {
      *next_smallest = *smallest;
      *smallest = i;
    } else if (tree->table[i]->frequency < tree->table[*next_smallest]->frequency) {
      *next_smallest = i;
    }
  }
}

void huffman_tree_merge(huffman_tree * tree) {
  int i, smallest, next_smallest;
  for (i = 0; i < tree->size - 1; i++) {
    find_smallest(tree, &smallest, &next_smallest, tree->size - 1 - i);
    int new_frequency = tree->table[smallest]->frequency + tree->table[next_smallest]->frequency;
    symbol * merged = symbol_new_children(new_frequency, tree->table[smallest], tree->table[next_smallest]);
    tree->table[smallest] = merged;
    tree->table[next_smallest] = tree->table[tree->size - 1 - i];
  }
}

static void _huffman_tree_walk(symbol * sym, int * path, int depth, int ** encodings) {

  if (sym->is_leaf) {
    int * encoding = malloc(sizeof(int) * (depth + 1));
    encoding[0] = depth;
    int i;
    for (i = 0; i < depth; i++) {
      encoding[i + 1] = path[i];
    }
    encodings[sym->data.c] = encoding;
  } else {
    path[depth] = 0;
    _huffman_tree_walk(sym->data.children.left, path, depth + 1, encodings);

    path[depth] = 1;
    _huffman_tree_walk(sym->data.children.right, path, depth + 1, encodings);
  }

}

void huffman_tree_walk(huffman_tree * tree, int ** encodings) {
  int * path = malloc(sizeof(int) * 40);
  _huffman_tree_walk(tree->table[0], path, 0, encodings);
  free(path);
}

static void _huffman_tree_free(symbol * sym) {
  if (sym->is_leaf) {
    symbol_free(sym);
  } else {
    _huffman_tree_free(sym->data.children.left);
    _huffman_tree_free(sym->data.children.right);
    symbol_free(sym);
  }
}

void huffman_tree_free(huffman_tree * tree) {
  _huffman_tree_free(tree->table[0]);
  free(tree->table);
  free(tree);
}
