#include "node.h"

typedef struct {
  int size;
  node ** table;
} hashtable;

// construct a new hash table with size elements
hashtable * hashtable_new(int size);

// free the memory for all parts of the hashtable
void hashtable_free(hashtable * this);

// insert string into the hash table, no effect if it's already there
void hashtable_insert(hashtable * this, char * item);

// remove string from the hash table, no effect if not in table
void hashtable_remove(hashtable * this, char * item);

// return 1 if string is already in table, 0 otherwise
int hashtable_lookup(hashtable * this, char * item);

// print out each entry in the hash table and the values
// stored at that entry
void hashtable_print(hashtable * this);

// compute the hash for a given string
unsigned hash_string(char * str);
