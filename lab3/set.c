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

void resize_set(int_set * this, int new_size) {
  int * new_array = malloc(sizeof(int) * new_size);

  int i;
  for (i = 0; i < this->current_elements; i++) {
    new_array[i] = this->array[i];
  }

  // free memory from old array and point at the new array
  free(this->array);
  this->array = new_array;
  this->max_elements = new_size;
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
  if (!int_set_lookup(this, item)) {
    if (this->current_elements == this->max_elements) {
      // increase set size when full
      resize_set(this, this->max_elements * 2);
    }
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
    // decrease set size when half full
    if (this->current_elements == this->max_elements / 2) {
      resize_set(this, this->max_elements / 2);
    }
    this->array[index] = this->array[--this->current_elements];
    return 1;
  }
  return 0;
}

// place the union of src1 and src2 into dest
void int_set_union(int_set * dest, int_set * src1, int_set * src2) {
  // add all elements of both sets. elements won't be added if they already exist
  int i;
  for (i = 0; i < src1->current_elements; i++) {
    int_set_add(dest, src1->array[i]);
  }
  for (i = 0; i < src2->current_elements; i++) {
    int_set_add(dest, src2->array[i]);
  }
}

// place the intersection of src1 and src2 into dest
void int_set_intersect(int_set * dest, int_set * src1, int_set * src2) {
  int i;
  for (i = 0; i < src1->current_elements; i++) {
    if (int_set_lookup(src2, src1->array[i])) {
      // if the elements of src1 are in src2 they are added to dest
      int_set_add(dest, src1->array[i]);
    }
  }
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
  int i;
  for (i = 5; i <= 300; i += 5) {
    int_set_add(set, i);
  }
  int_set_print(set);

  int_set * set2 = int_set_new();
  for (i = 3; i <= 300; i += 3) {
    int_set_add(set2, i);
  }
  int_set_print(set2);

  int_set * intersect = int_set_new();
  int_set_intersect(intersect, set, set2);
  int_set_print(intersect);

  int_set * union_set = int_set_new();
  int_set_union(union_set, set, set2);
  int_set_print(union_set);

  for (i = 5; i <= 300; i += 5) {
    int_set_remove(union_set, i);
    if (int_set_lookup(union_set, 0)) {
      printf("%d\n", i);
    }
  }
  int_set_print(union_set);

  for (i = 3; i <= 300; i += 3) {
    int_set_remove(union_set, i);
  }
  int_set_print(union_set);
  return 0;
}
