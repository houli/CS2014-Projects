#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int INT_SIZE = sizeof(unsigned int) * 8;

typedef struct {
  unsigned int * array;
  int size;
  int universe_size;
} bitset;

// create a new, empty bit vector set of 'size' items
bitset * bitset_new(int size) {
  bitset * set = malloc(sizeof(bitset));
  set->universe_size = size;

  set->size = size / INT_SIZE;
  if (size % INT_SIZE != 0) {
    set->size++;
  }

  set->array = calloc(set->size, sizeof(unsigned int));

  return set;
}

// check to see if an item is out of bounds
// returns 1 if the item is out of bounds, 0 otherwise
int out_of_bounds(bitset * this, int item) {
  if (item >= this->universe_size || item < 0) {
    return 1;
  } else {
    return 0;
  }
}

// check to see if an item is in the set
// returns 1 if in the set, 0 if not, and -1 if 'item' is out of bounds
int bitset_lookup(bitset * this, int item) {
  if (out_of_bounds(this, item)) {
    return -1;
  }
  int index = item / INT_SIZE;
  int bit_offset = item % INT_SIZE;

  return this->array[index] & (1 << bit_offset);
}

// add an item, with number 'item' to the set
// (returns 0 if item is out of bounds, 1 otherwise)
// has no effect if the item is already in the set
int bitset_add(bitset * this, int item) {
  if (out_of_bounds(this, item)) {
    return 0;
  }
  int index = item / INT_SIZE;
  int bit_offset = item % INT_SIZE;

  this->array[index] |= (1 << bit_offset);
  return 1;
}

// remove an item with number 'item' from the set
// (returns 0 if item is out of bounds, 1 otherwise)
int bitset_remove(bitset * this, int item) {
  if (out_of_bounds(this, item)) {
    return 0;
  }
  int index = item / INT_SIZE;
  int bit_offset = item % INT_SIZE;

  this->array[index] &= (~(1 << bit_offset));
  return 1;
}

// place the union of src1 and src2 into dest
void bitset_union(bitset * dest, bitset * src1, bitset * src2) {
  int i;
  for (i = 0; i < src1->size; i++) {
    dest->array[i] = src1->array[i] | src2->array[i];
  }
}

// place the intersection of src1 and src2 into dest
void bitset_intersect(bitset * dest, bitset * src1, bitset * src2) {
  int i;
  for (i = 0; i < src1->size; i++) {
    dest->array[i] = src1->array[i] & src2->array[i];
  }
}

void print_charset(bitset * set) {
  printf("{");
  int is_first = 1;
  int i;
  for (i = 0; i < 256; i++) {
    if (bitset_lookup(set, i)) {
    if (!is_first) {
      printf(", ");
    } else {
      is_first = 0;
    }
      printf("\"%c\"", i);
    }
  }
  printf("}\n");
}

int main() {
  printf("Type in some characters:\n");
  int buf_size = 1024;
  char * str1 = malloc(buf_size * sizeof(char));
  scanf("%[^\n]%*c", str1);
  int len = strlen(str1);
  bitset * set1 = bitset_new(256);
  int i;
  for (i = 0; i < len; i++) {
    bitset_add(set1, (int)str1[i]);
  }

  printf("\nType in some more characters:\n");
  char * str2 = malloc(buf_size * sizeof(char));
  scanf("%[^\n]%*c", str2);
  len = strlen(str2);
  bitset * set2 = bitset_new(256);
  for (i = 0; i < len; i++) {
    bitset_add(set2, (int)str2[i]);
  }

  printf("\nFirst character set:\n");
  print_charset(set1);

  printf("\nSecond character set:\n");
  print_charset(set2);

  bitset * union_set = bitset_new(256);
  bitset_union(union_set, set1, set2);
  printf("\nUnion of first two character sets:\n");
  print_charset(union_set);

  bitset * intersect_set = bitset_new(256);
  bitset_intersect(intersect_set, set1, set2);
  printf("\nIntersection of first two character sets:\n");
  print_charset(intersect_set);

  return 0;
}
