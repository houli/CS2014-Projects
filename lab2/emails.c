#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// Enum used to give nicer names to the states rather than 0, 1, 2 etc.
enum State {
  initial,
  alphaNum,
  at,
  dot,
  alphaNumAfterAt,
  dotAfterAt,
  alphaNumAfterDotAfterAt
};

void string_copy(char * dst, char * src, int length) {
  int i;
  for (i = 0; i < length; i++) {
    dst[i] = src[i];
  }
  dst[i] = '\0';
}

int string_length(char * string) {
  int len = 0;
  while (string[len] != '\0') {
    len++;
  }
  return len;
}

int string_compare(char * s1, char * s2) {
  int len = string_length(s1);
  if (len != string_length(s2)) {
    return 0;
  }

  int i;
  for (i = 0; i < len; i++) {
    if (s1[i] != s2[i]) {
      return 0;
    }
  }
  return 1;
}

/*
*  A function to find the index of the last
*  occurrence of a specfic character in a string.
*  Returns the index if it's found. Otherwise
*  it returns -1.
*/
int last_char_occurrence(char * string, char c) {
  int length = string_length(string);

  while (length >= 0) {
    if (string[length] == c) {
      return length;
    }
    length--;
  }
  return -1;
}

int check_terminator(char * address, char** terminators, int num_terminators) {
  int length = string_length(address);
  int dot_index = last_char_occurrence(address, '.') + 1;

  char terminator[length - dot_index];
  string_copy(terminator, address + dot_index, length - dot_index + 1);

  int i;
  for (i = 0; i < num_terminators; i++) {
    if (string_compare(terminator, terminators[i])){
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
  enum State state = initial;
  int length = string_length(address);
  int i;

  for (i = 0; i < length; i++) {
    char next = address[i];
    
    // A state machine based on the next character. Anything other than alphanum, @, . is invalid and goes straight to false
    switch (state) {

      case initial:
      if (isalpha(next)) { // first char must be alpha
        state = alphaNum;
      } else {
        return 0;
      }
      break;

      case alphaNum:
      if (is_alpha_or_digit(next)) { // all other characters in identifer can be alphanum
        state = alphaNum;
      } else if (next == '@') {
        state = at;
      } else if (next == '.') {
        state = dot;
      } else {
        return 0;
      }
      break;

      case at:
      if(isalpha(next)) {
        state = alphaNumAfterAt;
      } else {
        return 0;
      }
      break;

      case dot:
      if (isalpha(next)) {
        state = alphaNum;
      } else {
        return 0;
      }
      break;

      case alphaNumAfterAt:
      if (is_alpha_or_digit(next)) {
        state = alphaNumAfterAt;
      } else if (next == '.') {
        state = dotAfterAt;
      } else {
        return 0;
      }
      break;

      case dotAfterAt:
      if (isalpha(next)) {
        state = alphaNumAfterDotAfterAt;
      } else {
        return 0;
      }
      break;

      case alphaNumAfterDotAfterAt:
      if (is_alpha_or_digit(next)) {
        state = alphaNumAfterDotAfterAt;
      } else if (next == '.') {
        state = dotAfterAt;
      } else {
        return 0;
      }
      break;

      default:
      return 0;
    }
  }

  if (state == alphaNumAfterDotAfterAt) {
    // If in this state after the loop there has been at least one alpha after a '.' after an '@' so we can check the terminator
    return check_terminator(address, terminators, num_terminators);
  }
  // Any other state is incorrect for checking the terminator
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
  print_validity("a92323.g233a.f4@s24.com", terminators, length);

  printf("\n");

  // Invalid
  print_validity("I.am@fish", terminators, length); // No terminator
  print_validity(".asd.sds@tcd.com", terminators, length); // Begins with '.'
  print_validity("ehoulih@tcd@tcd.ie", terminators, length); // Two @ symbols
  print_validity("", terminators, length); // Empty string
  print_validity("@tcd.ie", terminators, length); // Begins with '@'
  print_validity("ehoulih@tcd.es", terminators, length); // Invalid terminator

  return 0;
}
