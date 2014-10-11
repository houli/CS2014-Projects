#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_terminator(char * address, char** terminators, int num_terminators) {
  int length = strlen(address);
  char *last_dot = strrchr(address, '.');
  int dot_index = (last_dot - address) + 1;

  char terminator[length - dot_index];
  memcpy(terminator, &address[dot_index], length - dot_index);
  terminator[length - dot_index] = '\0';

  int i;
  for (i = 0; i < num_terminators; i++) {
    if (strcmp(terminator, terminators[i]) == 0){
      return 1;
    }
  }
  return 0;
}

int is_alpha_or_digit(char c) {
  if (isalpha(c) || isdigit(c)) {
    return 1;
  }
  return 0;
}

int is_valid_email_address(char * address, char ** terminators, int num_terminators)
{
  int state = 1;
  int length = strlen(address);
  int i = 0;

  while (i < length) {
    char next = address[i];
    
    switch (state) {

      case 1:
      if (is_alpha_or_digit(next)) {
        state = 2;
      } else {
        return 0;
      }
      break;

      case 2:
      if (is_alpha_or_digit(next)) {
        state = 2;
      } else if (next == '@') {
        state = 3;
      } else if (next == '.') {
        state = 4;
      } else {
        return 0;
      }
      break;

      case 3:
      if(is_alpha_or_digit(next)) {
        state = 5;
      } else {
        return 0;
      }
      break;

      case 4:
      if (is_alpha_or_digit(next)) {
        state = 2;
      } else {
        return 0;
      }
      break;

      case 5:
      if (is_alpha_or_digit(next)) {
        state = 5;
      } else if (next == '.') {
        state = 6;
      } else {
        return 0;
      }
      break;

      case 6:
      if (is_alpha_or_digit(next)) {
        state = 7;
      } else {
        return 0;
      }
      break;

      case 7:
      if (is_alpha_or_digit(next)) {
        state = 7;
      } else if (next == '.') {
        state = 6;
      } else {
        return 0;
      }
      break;

      default:
      return 0;
    }
    i++;
  }

  if (state == 7) {
    return check_terminator(address, terminators, num_terminators);
  }
  return 0;
}

void print_validity(char * address, char** terminators, int length)
{
  printf("The string %s is ", address);
  if (!is_valid_email_address(address, terminators, length)) {
    printf("not ");
  }
  printf("a valid email address\n");
}

int main()
{
  const int length = 5;
  char * terminators[length];
  char * address1, * address2;

  terminators[0] = "com";
  terminators[1] = "net";
  terminators[2] = "edu";
  terminators[3] = "ie";
  terminators[4] = "tv";

  address1 = "santa.claus@north.pole.com";
  address2 = "I.am@fish";

  print_validity(address1, terminators, length);
  print_validity(address2, terminators, length);

  return 0;
}