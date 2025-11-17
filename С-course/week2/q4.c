#include <stdio.h>

int main(void)
{

    for (int i = 1; i <= 4; i++)
    {

        if (i == 1 || i == 4)
        {
            for (int j = 1; j <= 5; j++)
            {
                printf("*");
            }
        }
        else
        {
            for (int j = 1; j <= 5; j++)
            {
                if (j == 1 || j == 5)
                {
                    printf("*");
                }else{
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    return 0;
}
