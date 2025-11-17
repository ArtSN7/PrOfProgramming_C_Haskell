#include <stdio.h>
#include <stdbool.h>

bool isPrime(int num)
{

    for (int i = 2; i < num; i++)
    {
        if (num % i == 0 && i != num)
        {
            return false;
        }
    }
    return true;
}

int main(void)
{
    int low, high;
    int result = scanf("%d %d", &low, &high);

    if (result != 2)
    { // Fixed: Check for two successful reads
        return 0;
    }

    if (low < 2 || low >= high)
    {
        return 0;
    }

    int prev_prime = -1; // Track the previous prime found
    for (int i = low; i <= high; i++)
    {
        if (isPrime(i))
        {
            if (prev_prime != -1 && i - prev_prime <= 2)
            {
                printf("%d %d\n", prev_prime, i); // Print the pair (smaller first)
            }
            prev_prime = i; // Update for next iteration
        }
    }

    return 0;
}