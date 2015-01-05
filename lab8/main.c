#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "huffman.h"
#include "bitfile.h"

const int CHARACTER_SET_SIZE = 128;
const char * error_string = "Usage: huff[de]code <training file> <input file> <output file>";

int main(int argc, char ** argv) {
  if (argc != 4) {
    fprintf(stderr, "%s\n", error_string);
    exit(1);
  } else {
    int c;
    FILE * file;
    int freqs[CHARACTER_SET_SIZE] = {};

    file = fopen(argv[1], "r");
    assert(file != NULL);
    while ((c = fgetc(file)) != EOF) {
      freqs[c]++;
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
    int ** encodings = malloc(sizeof(int *) * CHARACTER_SET_SIZE);
    huffman_tree_walk(tree, encodings);

    if (strcmp(argv[0], "./huffcode") == 0) {
      FILE * in_file = fopen(argv[2], "r");
      bitfile * out_file = bitfile_new(fopen(argv[3], "w"));
      while ((c = fgetc(in_file)) != EOF) {
        int * encoding = encodings[c];
        int length = encoding[0];
        for (i = 1; i < length + 1; i++) {
          bitfile_write(out_file, encoding[i]);
        }
      }
      fclose(in_file);
      bitfile_close(out_file);
    } else if (strcmp(argv[0], "./huffdecode") == 0) {
      // decode the file
    } else {
      fprintf(stderr, "%s\n", error_string);
      exit(1);
    }
    huffman_tree_free(tree);
  }
  return 0;
}
