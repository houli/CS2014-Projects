#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitset.h"

#define CHAR_UNIVERSE 256

void print_charset(bitset * set) {
  printf("{");
  int is_first = 1;
  int i;
  for (i = 0; i < CHAR_UNIVERSE; i++) {
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
  bitset * set1 = bitset_new(CHAR_UNIVERSE);
  int i;
  for (i = 0; i < len; i++) {
    bitset_add(set1, (int)str1[i]);
  }

  printf("\nType in some more characters:\n");
  char * str2 = malloc(buf_size * sizeof(char));
  scanf("%[^\n]%*c", str2);
  len = strlen(str2);
  bitset * set2 = bitset_new(CHAR_UNIVERSE);
  for (i = 0; i < len; i++) {
    bitset_add(set2, (int)str2[i]);
  }

  printf("\nFirst character set:\n");
  print_charset(set1);

  printf("\nSecond character set:\n");
  print_charset(set2);

  bitset * union_set = bitset_new(CHAR_UNIVERSE);
  bitset_union(union_set, set1, set2);
  printf("\nUnion of first two character sets:\n");
  print_charset(union_set);

  bitset * intersect_set = bitset_new(CHAR_UNIVERSE);
  bitset_intersect(intersect_set, set1, set2);
  printf("\nIntersection of first two character sets:\n");
  print_charset(intersect_set);

  return 0;
}
