#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char ** argv) {
  unsigned char c;
  FILE * file;
  int freqs[128] = {};

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
  int i;
  for (i = 0; i < 128; i++) {
    printf("%c: %d\n", i, freqs[i]);
  }
  fclose(file);

  return 0;
}
