#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}


int* sort(int *n, int size){

    bool swapped;

    int* array = malloc(size * sizeof(int));

    if (!array)
    {
        return NULL;
    }

    for (int i = 0; i < size; i++){
        array[i] = n[i];
    }

    for (int i = 0; i < size - 1; i++){
        swapped = false;

        for (int j = 0; j < size - i - 1; j++){
            if (array[j] > array[j + 1])
            {
                swap(&array[j], &array[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }

    return array;
}



int main(void){
    int array[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int size = sizeof(array) / sizeof(int);

    printf("Initial array: ");
    for (int i = 0; i < size; i++){
        printf("%d, ", array[i]);
    }

    int* array_sorted = sort(array, size);

    printf("Sorted array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d, ", array_sorted[i]);
    }

    free(array_sorted);
    return 0;
}