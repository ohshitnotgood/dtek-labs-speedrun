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
    int array_size = n - 1;                                // we ignore the number 1, so 1 less than arg
    int *primes = (int *)malloc(array_size * sizeof(int)); // allocate memory on the heap

    if (primes == NULL)
    {
        printf("Memory allocation failed.\n");
        return; // handle allocation failure
    }

    for (int i = 0; i < array_size; i++)
    {
        primes[i] = 1; // at first, all are prime
    }

    double root = sqrt(n); // only need to check up to the root of n

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

    free(primes); // release the memory allocated on the heap
}

int main(int argc, char *argv[])
{
    if (argc == 2)
        print_sieves(atoi(argv[1]));
    else
        printf("Please state an integer number.\n");
    return 0;

    // max number in 2 seconds: 85000
}