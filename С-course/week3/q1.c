#include <stdio.h>
#include <math.h>

int per(int a, int b, int c)
{
    return a + b + c;
}

double ar(int a, int b, int c)
{
    double s = (a + b + c) / 2.0;
    double area_sq = s * (s - a) * (s - b) * (s - c);
    if (area_sq <= 0.0)
    {
        return 0.0;
    }
    return sqrt(area_sq);
}

int main(void)
{
    int a, b, c;
    printf("Input variables: \n");
    if (scanf("%d %d %d", &a, &b, &c) != 3)
    {
        fprintf(stderr, "Invalid input. Expected three integers.\n");
        return 1;
    }

    /* Validate inputs: non-zero, positive and satisfy triangle inequality */
    if (a <= 0 || b <= 0 || c <= 0)
    {
        printf("BROSKI 3 VARIABLES\n");
        return 0;
    }

    if ((a + b <= c) || (a + c <= b) || (b + c <= a))
    {
        printf("Not a valid triangle\n");
        return 0;
    }

    printf("\nPerimeter : %d", per(a, b, c));
    printf("\nArea : %f\n", ar(a, b, c));

    return 0;
}