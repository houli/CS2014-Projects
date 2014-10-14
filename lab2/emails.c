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
  int state = 0;
  int length = strlen(address);
  int i = 0;

  while (i < length) {
    char next = address[i];
    
    switch (state) {

      case 0:
      if (is_alpha_or_digit(next)) {
        state = 1;
      } else {
        return 0;
      }
      break;

      case 1:
      if (is_alpha_or_digit(next)) {
        state = 1;
      } else if (next == '@') {
        state = 2;
      } else if (next == '.') {
        state = 3;
      } else {
        return 0;
      }
      break;

      case 2:
      if(is_alpha_or_digit(next)) {
        state = 4;
      } else {
        return 0;
      }
      break;

      case 3:
      if (is_alpha_or_digit(next)) {
        state = 1;
      } else {
        return 0;
      }
      break;

      case 4:
      if (is_alpha_or_digit(next)) {
        state = 4;
      } else if (next == '.') {
        state = 5;
      } else {
        return 0;
      }
      break;

      case 5:
      if (is_alpha_or_digit(next)) {
        state = 6;
      } else {
        return 0;
      }
      break;

      case 6:
      if (is_alpha_or_digit(next)) {
        state = 6;
      } else if (next == '.') {
        state = 5;
      } else {
        return 0;
      }
      break;

      default:
      return 0;
    }
    i++;
  }

  if (state == 6) {
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

  terminators[0] = "com";
  terminators[1] = "net";
  terminators[2] = "edu";
  terminators[3] = "ie";
  terminators[4] = "tv";

  // Valid
  print_validity("santa.claus@north.pole.com", terminators, length);
  print_validity("houli.houli.houli.houli@tcd.tcd.tcd.ie", terminators, length);
  print_validity("92323.233ga.f4@s24.com", terminators, length);

  printf("\n");

  // Invalid
  print_validity("I.am@fish", terminators, length);
  print_validity(".asd.sds@tcd.com", terminators, length);
  print_validity("ehoulih@tcd@tcd.ie", terminators, length);

  return 0;
}
