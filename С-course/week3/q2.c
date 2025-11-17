#include <stdio.h>


int rec_method(int a, int b){
    if (b == 0){
        return 1;
    }

    return rec_method(a, b - 1) * a;
}

int loop_method(int a, int b){
    int count = 1;
    for (int i = b; i > 0; i--){

        count *= a;

    }

    return count;
}


int main(void){
    int a, b;
    printf("Input numbers:\n");

    if (scanf("%d %d", &a, &b) != 2){
        fprintf(stderr, "Invalid number of args");
        return 0;
    }

    if (b <= 0){
        fprintf(stderr, "Invalid number of args");
        return 0;
    }

    printf("Recursive method: %d\n", rec_method(a, b));
    printf("Loop method: %d\n", loop_method(a, b));
    return 0;
}