#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int strend(char *s, char *t){

    int length_s, length_t;
    length_s = strlen(s);
    length_t = strlen(t);
    char *sub_str = malloc(length_s * sizeof(char));

    if (length_s < length_t){ // if s is less than t
        return 0;
    }

    for (int i = 0; i < length_s; i++){
        sub_str[i] = s[length_s - length_t + i];
    }

    if (strcmp(sub_str, t) == 0){
        free(sub_str);
        return 1;
    }

    free(sub_str);
    return 0;
}

int main(void){

    char s[] = "HelloWord";
    char t[] = "Wor";

    int a = strend(s, t);

    printf("%i", a);

    return 0;
}


