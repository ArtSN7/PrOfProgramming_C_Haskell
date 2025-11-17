#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int count_digits(long number)
{
    int count = 0;
    if (number == 0)
        return 1; // Special case for 0
    if (number < 0)
        number = -number; // Handle negative numbers

    while (number != 0)
    {
        number /= 10;
        count++;
    }
    return count;
}

int calc_fact(int num)
{
    if (num == 0)
    {
        return 0;
    }
    if (num == 1)
    {
        return 1;
    }
    return num * calc_fact(num - 1);
}

int upPower(int a, int b)
{
    int count = 1;

    if (b == 0)
    {
        return 1;
    }

    for (int i = 0; i < b; i++)
    {
        count *= a;
    }

    return count;
}

bool isStrong(int number)
{

    int length = count_digits(number);
    int count = 0;
    int a;

    for (int i = 0; i < length; i++)
    {
        a = number % upPower(10, i + 1) / upPower(10, i);
        count += calc_fact(a);
    }

    if (count == number)
    {
        return true;
    }

    return false;
}

int main(void)
{
    int low, high;
    int result = scanf("%d %d", &low, &high);

    if (result != 2 || low >= high)
    {
        return 0;
    }

    for (int i = low; i <= high; i++)
    {
        if (isStrong(i))
        {
            printf("%d - strong\n", i);
        }
    }
    return 0;
}