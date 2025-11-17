#include <stdio.h>
#include <stdbool.h>

int IsPrime(long number)
{
    for (int i = 2; i < number; i++)
    {
        if (number % i == 0 && i != number)
            return false;
    }
    return true;
}

int main(void){
    long number;
    int result;

    while (true){

        result = scanf("%ld", &number);

        if (result == 1){
            break;
        }

        print("\nInput just value: \n");

    }
    

    if (IsPrime(number)){
        print("PRIME");
    }else{
        print("NOT PRIME");
    }

    return 0;
}