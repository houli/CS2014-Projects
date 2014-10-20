#include <stdio.h>

typedef struct {
  int * array;
  int max_elements;
  int current_elements;
} int_set;

// create a new, empty set
int_set * int_set_new() {

}

// check to see if an item is in the set
// returns 1 for true, 0 for false
int int_set_lookup(int_set * this, int item) {

}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
int int_set_add(int_set * this, int item) {

}

// remove an item with number 'item' from the set
// has no effect if the items is not in the set
int int_set_remove(int_set * this, int item) {

}

// place the union of src1 and src2 into dest
void int_set_union(int_set * dest, int_set * src1, int_set * src2) {

}

// place the intersection of src1 and src2 into dest
void int_set_intersect(int_set * dest, int_set * src1, int_set * src2) {

}

int main() {

}
