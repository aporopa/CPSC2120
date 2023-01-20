#include <iostream>
#include "review.h"

int Fibonacci(int a){
    int fibonacci[a];
    fibonacci[0] = 0;
    fibonacci[1] = 1;

    for(int i = 2; i <= a; i++){
        fibonacci[i] = fibonacci[i-2] + fibonacci[i-1];
    }

    return fibonacci[a];
}