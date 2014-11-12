typedef struct {
  double * array;
  int top;
  int size;
} stack;

// Creates a new stack of a given size.
stack * stack_new(int size);

// Pushes a value on to the stack. Returns 1 if successful, 0 otherwise.
int stack_push(stack * stack, double number);

// Pops a value off the stack.
double stack_pop(stack * stack);

// Returns 1 if the stack is empty, 0 otherwise.
int stack_is_empty(stack * stack);
