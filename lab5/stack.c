#include <stdlib.h>
#include "stack.h"

stack * stack_new(int size) {
  stack * stack = malloc(sizeof(stack));
  stack->top = 0;
  stack->size = size;
  stack->array = malloc(size * sizeof(double));
  return stack;
}

int stack_push(stack * stack, double number) {
  if (stack->top >= stack->size) {
    return 0;
  }
  stack->array[stack->top++] = number;
  return 1;
}

double stack_pop(stack * stack) {
  if (stack_is_empty(stack)) {
    return 0.0;
  }
  return stack->array[--stack->top];
}

int stack_is_empty(stack * stack) {
  return stack->top == 0;
}
