#include <stdio.h>
#include <stdlib.h>

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

  set->array = malloc(set->size * sizeof(unsigned int));

  int i;
  for (i = 0; i < set->size; i++) {
    set->array[i] = 0;
  }
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
  int index = item / (this->size * INT_SIZE);
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
  int index = item / (this->size * INT_SIZE);
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
  int index = item / (this->size * INT_SIZE);
  int bit_offset = item % INT_SIZE;

  this->array[index] &= (!(1 << bit_offset));
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

int main() {
  bitset * set = bitset_new(300);
  bitset_add(set, 20);
  if (bitset_lookup(set, 20)) {
    printf("In there!\n");
  } else {
    printf("Not in there!\n");
  }
  return 0;
}
