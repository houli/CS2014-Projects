#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "stack.h"

const char OPERATORS[] = {'+', '-', 'x', '/', '%'};
const int NUM_OPERATORS = 5;

int is_operator(char * str) {
  if (strlen(str) > 1) {
    return 0;
  }

  char c = str[0];
  int i;
  for (i = 0; i < NUM_OPERATORS; i++) {
    if (c == OPERATORS[i]) {
      return 1;
    }
  }
  return 0;
}

void operate(stack * stack, char * op_str) {
  char operator = op_str[0];
  double operand2 = stack_pop(stack);
  double operand1 = stack_pop(stack);

  double result;
  switch (operator) {
    case '+':
    result = operand1 + operand2;
    break;

    case '-':
    result = operand1 - operand2;
    break;

    case 'x':
    result = operand1 * operand2;
    break;

    case '/':
    result = operand1 / operand2;
    break;

    case '%':
    result = fmod(operand1, operand2);
    break;
  }

  stack_push(stack, result);
}

int main(int argc, char * argv[]) {
  stack * calc_stack = stack_new(100);
  int i;
  for (i = 1; i < argc; i++) {
    if (is_operator(argv[i])) {
      operate(calc_stack, argv[i]);
    } else {
      stack_push(calc_stack, atof(argv[i]));
    }
  }
  printf("Result: %.4f\n", stack_pop(calc_stack));
  return 0;
}
