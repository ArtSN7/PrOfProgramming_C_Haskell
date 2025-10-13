#include <stdio.h>
#include <math.h>
#include <stdbool.h>



bool isPrime(int n)
{
    // Numbers less than 2 are not prime
    if (n < 2)
    {
        return false;
    }

    // Check for divisibility up to the square root of n
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return false; // n is divisible by i, so not prime
        }
    }

    return true; // n is prime
}

void squaresNum()
{
    for (int i = 1; i <= 100; i++)
    {
        printf("%d * %d = %d\n", i, i, i * i);
    }
}

void squaredEvenNum()
{
    for (int i = 1; i <= 100; i++)
    {
        if (i % 2 == 0)
        {
            printf("%d * %d = %d\n", i, i, i * i);
        }
    }
}




int main(void){


    squaresNum();
    squaredEvenNum();

    for (int i = 1; i <= 100; i++)
    {
        if (isPrime(i))
        {
            printf("%d is a prime number.\n", i);
        }
    }

    return 0;
}