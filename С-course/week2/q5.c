#include <stdio.h>

int main(void)
{

    for (int i = 0; i < 6; i++)
    {
        for (int k = 0; k < i; k++)
        {
            printf(" ");
        }
        for (int j = 0; j < 6 - i; j++)
        {
            printf("*");
        }

        printf("\n");
    }

    return 0;
}