#include <stdlib.h>
#include "bitfile.h"

bitfile * bitfile_new(FILE * file) {
  bitfile * new = malloc(sizeof(bitfile));
  new->file = file;
  new->buffer = 0;
  new->buffer_index = 8;
  new->init = 0;
  return new;
}

void bitfile_close(bitfile * this) {
  if (this->buffer_index != 8) {
    fputc(this->buffer, this->file);
  }
  fclose(this->file);
}

int bitfile_read(bitfile * this) {
  if (!this->init) {
    this->init = 1;
    this->buffer = fgetc(this->file);
  }
  int result;
  if (this->buffer_index == 0) {
    this->buffer = fgetc(this->file);
    this->buffer_index = 8;
  }
  result = (this->buffer >> --this->buffer_index) & 1;
  return result;
}

void bitfile_write(bitfile * this, int bit) {
  if (this->buffer_index == 0) {
    fputc(this->buffer, this->file);
    this->buffer = 0;
    this->buffer_index = 8;
  }
  if (bit == 0) {
    this->buffer &= ~(1 << (--this->buffer_index));
  } else {
    this->buffer |= bit << (--this->buffer_index);
  }
}
