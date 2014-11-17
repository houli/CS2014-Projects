#include <stdio.h>
#include "hashtable.h"

int main(int argc, char * argv[]) {
  hashtable * table = hashtable_new(80);
  int i;
  for (i = 1; i < argc; i++) {
    hashtable_insert(table, argv[i]);
  }

  hashtable_insert(table, "fish");

  if (hashtable_lookup(table, "porridge")) {
    hashtable_remove(table, "porridge");
  }
  hashtable_print(table);

  hashtable_free(table);
  return 0;
}
