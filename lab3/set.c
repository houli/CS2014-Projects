#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE 16

typedef struct {
  int * array;
  int max_elements;
  int current_elements;
} int_set;

// create a new, empty set
int_set * int_set_new() {
  // create set
  int_set * new_set = malloc(sizeof(int_set));

  // populate fields
  new_set->array = malloc(sizeof(int) * MIN_SIZE);
  new_set->max_elements = MIN_SIZE;
  new_set->current_elements = 0;

  return new_set;
}

void increase_set(int_set * this) {
  int new_array_size = (this->max_elements * 7) / 4;
  int * new_array = malloc(sizeof(int) * new_array_size);

  int i;
  for (i = 0; i < this->max_elements; i++) {
    new_array[i] = this->array[i];
  }

  free(this->array);
  this->array = new_array;
  this->max_elements = new_array_size;
}

void decrease_set(int_set * this) {

}

// get the index of an item in the set
// returns -1 if not found
int index_of(int_set * this, int item) {
  int i;
  for (i = 0; i < this->current_elements; i++) {
    if (this->array[i] == item) {
      return i;
    }
  }
  return -1;
}

// check to see if an item is in the set
// returns 1 for true, 0 for false
int int_set_lookup(int_set * this, int item) {
  int i;
  for (i = 0; i < this->current_elements; i++) {
    if (this->array[i] == item) {
      return 1;
    }
  }
  return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
int int_set_add(int_set * this, int item) {
  if (this->current_elements == this->max_elements) {
    increase_set(this);
  }
  if (!int_set_lookup(this, item)) {
    this->array[this->current_elements++] = item;
    return 1;
  }
  return 0;
}

// remove an item with number 'item' from the set
// has no effect if the items is not in the set
int int_set_remove(int_set * this, int item) {
  int index = index_of(this, item);
  if (index != -1) {
    this->array[this->current_elements--] = this->array[index];
    return 1;
  }
  return 0;
}

// place the union of src1 and src2 into dest
void int_set_union(int_set * dest, int_set * src1, int_set * src2) {

}

// place the intersection of src1 and src2 into dest
void int_set_intersect(int_set * dest, int_set * src1, int_set * src2) {

}

void int_set_print(int_set * set) {
  printf("{");
  int is_first = 1;

  int i;
  for (i = 0; i < set->current_elements; i++) {
    if (!is_first) {
      printf(", ");
    } else {
      is_first = 0;
    }
    printf("%d", set->array[i]);
  }

  printf("}\n");
}

int main() {
  int_set  * set = int_set_new();
  int_set_add(set, 1);
  int_set_print(set);
  int_set_add(set, 2);
  int_set_print(set);
  int_set_add(set, 3);
  int_set_print(set);
  int_set_add(set, 235);
  int_set_print(set);
  int_set_add(set, 12);
  int_set_print(set);
  int_set_add(set, 124124);
  int_set_print(set);
  return 0;
}
