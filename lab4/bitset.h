typedef struct {
  unsigned int * array;
  int size;
  int universe_size;
} bitset;

bitset * bitset_new(int size);

int out_of_bounds(bitset * this, int item);

int bitset_lookup(bitset * this, int item);

int bitset_add(bitset * this, int item);

int bitset_remove(bitset * this, int item);

void bitset_union(bitset * dest, bitset * src1, bitset * src2);

void bitset_intersect(bitset * dest, bitset * src1, bitset * src2);
