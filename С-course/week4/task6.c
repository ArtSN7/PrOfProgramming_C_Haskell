#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int** allocation(int num_rows, int sizes[]){
    int i, j;

    int** ragged_array = malloc(num_rows * sizeof(int*)); // allocate the memory of array of pointers to another array of pointers

    for (i = 0; i < num_rows; i++){
        ragged_array[i] = malloc(sizes[i] * sizeof(int)); // for each pointer we add an array
        for (j = 0; j < sizes[i]; j++){
            ragged_array[i][j] = j + 1;
        }
    }

    return ragged_array;
}


int main(void){
    int i, j;
    int num_of_rows = 4;
    int array[] = {4, 6, 4, 8};
    int **response = allocation(num_of_rows, array);

    for (i = 0; i < num_of_rows ; i++)
    {
        int* inner_array = response[i];
        for (j = 0; j < array[i]; j++)
        {
            printf("%d ", inner_array[j]);
        }
        free(inner_array);
        printf("\n");
    }

    free(response);

    return 0;
}