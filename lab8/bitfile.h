#include <stdio.h>

typedef struct {
  int buffer_index;
  FILE * file;
  char buffer;
} bitfile;

bitfile * bitfile_new(FILE * file);

void bitfile_close();

int bitfile_read(bitfile * this);

void bitfile_write(bitfile * this, int bit);
