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
      FILE * out = fopen(argv[3], "w");
      bitfile * out_file = bitfile_new(out);

      // Making room for a header to store the character length of the original file
      for (i = 0; i < 4; i++) {
        fputc(0, out);
      }

      int count = 0;
      while ((c = fgetc(in_file)) != EOF) {
        int * encoding = encodings[c];
        int length = encoding[0];
        for (i = 1; i < length + 1; i++) {
          bitfile_write(out_file, encoding[i]);
        }
        count++;
      }
      fclose(in_file);
      bitfile_close(out_file);
      out = fopen(argv[3], "r+");

      // Write header information now we know the length of the file
      // Shifts used to write one byte at a time
      for (i = 3; i >= 0; i--) {
        fputc((count >> (i * 8)) & 0xFF, out);
      }
      fclose(out);
    } else if (strcmp(argv[0], "./huffdecode") == 0) {
      FILE * out_file = fopen(argv[3], "w");
      FILE * in = fopen(argv[2], "r");
      bitfile * in_file = bitfile_new(in);

      // Get length of character sequence from 4 byte header
      unsigned char bytes[4];
      for (i = 0; i < 4; i++) {
        bytes[i] = fgetc(in);
      }
      int length = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];

      int chars_decoded = 0;
      symbol * root = tree->table[0];
      symbol * current = root;
      while (chars_decoded < length) {
        if (current->is_leaf) {
          fputc(current->data.c, out_file);
          chars_decoded++;
          current = root;
        } else {
          int bit = bitfile_read(in_file);
          if (chars_decoded == 0) {
          }
          if (bit == 0) {
            current = current->data.children.left;
          } else {
            current = current->data.children.right;
          }
        }
      }
      fclose(out_file);
    } else {
      fprintf(stderr, "%s\n", error_string);
      exit(1);
    }
    huffman_tree_free(tree);
  }
  return 0;
}
