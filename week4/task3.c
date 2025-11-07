#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *stringCopy(char *s)
{
    int length_of_str;

    length_of_str = strlen(s);
    char *ptr = (char *)malloc(length_of_str * sizeof(char));
    strcpy(ptr, s);
    return ptr;
}

int main(void)
{
    char test[] = "Hello";
    char *result = stringCopy(test);

    if (result != NULL)
    {
        printf("Original: %s\n", test);
        printf("Copy: %s\n", result);
        free(result);
    }

    return 0;
}