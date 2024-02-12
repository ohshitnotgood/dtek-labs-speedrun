#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6

int counter = 0;

int count_digits(int n)
{
    int count = 0;
    do
    {
        n /= 10;
        ++count;
    } while (n != 0);

    return count;
}

void print_number(int n)
{

    int blank_spaces = 12 - count_digits(n);

    for (int i = 0; i < blank_spaces; i++)
    {
        printf(" ");
    }
    printf("%d", n);
    counter++;
    if (counter == COLUMNS)
    {
        printf("\n");
        counter = 0;
    }
}

void print_sieves(int n)
{
    int array_size = n - 1;
    int primes[array_size]; // 1 if is prime, 0 if not

    for (int i = 0; i < array_size; i++)
    {
        primes[i] = 1; // at first, all are prime
    }

    double root = sqrt(n);

    for (int i = 2; i <= root; i++)
    {
        if (primes[i - 2] == 1)
        { // if number is prime
            for (int j = i * i; j <= n; j += i)
            {
                primes[j - 2] = 0; // if multiple of the prime, it is not a prime
            }
        }
    }

    // go through array and print corresponding numbers to the elements marked 1
    for (int i = 0; i < array_size; i++)
    {
        if (primes[i] == 1)
        {
            print_number(i + 2);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2)
        print_sieves(atoi(argv[1]));
    else
        printf("Please state an integer number.\n");
    return 0;

    // max no: 82000 in 2 seconds
}