/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6

int counter = 0;

int is_prime(int n)
{
  double root = sqrt(n);
  for (int i = 2; i <= root; i++)
  {
    if (n % i == 0)
      return 0;
  }
  return 1;
}

int count_digits(int n)
{
  int count = 0;
  do
  {
    n /= 10; // integer division rounds towards 0
    ++count;
  } while (n != 0);

  return count;
}

// prime numbers aren't expected to be negative
void print_number(int n)
{
  int blank_spaces = 12 - count_digits(n); // account for digit length

  // spaces first
  for (int i = 0; i < blank_spaces; i++)
  {
    printf(" ");
  }
  printf("%d", n);
  counter++;
  // count no of columns
  if (counter == COLUMNS)
  {
    printf("\n");
    counter = 0;
  }
}

void print_primes(int n)
{
  for (int i = 2; i < n; i++)
  {
    if (is_prime(i) == 1)
    {
      print_number(i);
    }
  }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[])
{
  if (argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an integer number.\n");
  return 0;

  // Max no in 2 seconds: 83000
}