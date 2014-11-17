typedef struct node node;

struct node {
  char * data;
  node * next;
};

// construct a new node
node * node_new(char * data);

// free the memory for all parts of the node
void node_free(node * node);

// update the next pointer of a node
void node_update_next(node * this, node * next);

// returns the next pointer of a node
node * node_next(node * node);

// returns the string contained in a node
char * node_get_string(node * node);

// compares the data in a node to a string
int node_compare(node * node, char * str);
