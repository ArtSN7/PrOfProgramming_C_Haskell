#include <stdio.h>


int main(void){
    int i = 0;
    do {
        i++;
        printf("13 * %d = %d\n", i, 13 * i);
    } while ( i < 13 );

    return 0;

}