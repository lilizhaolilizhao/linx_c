//
// Created by oneapm on 2019-08-20.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PI 3.1415926
#define  MAX(x, y)  (x>y?x:y)

void function_5_001();

void function_5_002();

int main() {
//    function_5_001();
    function_5_002();

    return 0;
}

void function_5_002() {
    int a = 5, b = 10, max;

    max = MAX(a, b);
    printf("The max between(%d,%d) is %d\n", a, b, max);
}

void function_5_001() {
    int r = 100;
    double length = 2 * PI * r;

    printf("The circumference is %f\n", length);
}
