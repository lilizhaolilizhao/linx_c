//
// Created by oneapm on 2019-08-04.
//

#include <stdio.h>

#define PI 3.1415926

void function_2_1();

void function_2_2();

void function_2_3();

void function_2_4();

void function_2_5();

void function_2_6();

void function_2_7();

void function_2_8();

void function_2_9();

void function_2_10();

void function_2_11();

//int main() {
////    function_2_1();
////    function_2_2();
////    function_2_3();
////    function_2_4();
////    function_2_5();
////    function_2_6();
////    function_2_7();
////    function_2_8();
////    function_2_9();
////    function_2_10();
//    function_2_11();
//}

void function_2_11() {
    int a, b, c, d;

    a = 10;
    b = a++;
    c = ++a;
    d = 10 * a++;

    printf("b, c, d:%d, %d, %d\n", b, c, d);
}

void function_2_10() {
    int i;
    char c;
    float f;

    scanf("%d%c%f", &i, &c, &f);
    printf("%d %c %f\n", i, c, f);
    scanf("%d,%c,%f", &i, &c, &f);
    printf("%d %c %f\n", i, c, f);
}

void function_2_9() {
    char c = 'a';
    int i = 1234;
    float f = 12.123456;
    double d = 12.5;

    printf("%d %o %x\n", i, i, i);
    printf("%c %d\n", c, c);
    printf("%s\n", "hello");
    printf("%f %e %g\n", f, f, f);

    printf("123456789012345678901234567890\n");
    printf("%5c%5d%10.5f%10.5f\n", c, i, f, d);
    printf("123456789012345678901234567890\n");
    printf("%-5c%-5d%-10.5f%-10.5f\n", c, i, f, d);
}

void function_2_8() {
    char c;
    c = getchar();
    putchar(c);
    putchar('\n');
}

void function_2_7() {
    char a, b;

    a = 'H';
    b = 'i';

    putchar(a);
    putchar(b);
    putchar('\n');
    putchar(97);
    putchar('b');
}

void function_2_6() {
    int i = 3, j, k;

    j = i++;
    k = ++i;

    printf("i=%d,j=%d,k=%d\n", i, j, k);
    printf("%d\n", -i++);
    printf("%d,%d,%d", i, i++, i++);
}

void function_2_5() {
    float r = 2.56;
    float l, s;

    l = 2 * PI * r;
    s = PI * r * r;
    printf("l=%f\n", l);
    printf("s=%f\n", s);
}

void function_2_4() {
    int c1, c2;
    char c3;

    c1 = 'a' - 'A';
    c2 = 'b' - 'B';
    c3 = 'c' - 32;

    printf("c1 is %d and c2 is %d\n", c1, c2);
    printf("c3 is %d and %c\n", c3, c3);
}

void function_2_3() {
    float a = 88888.88888;            /*整数部分5位，小数部分5位*/
    double b = 8888888888.888888888;   /*整数部分10位，小数部分9位*/

    printf("a is %f\n", a);
    printf("b is %f\n", b);
}

void function_2_2() {
    short int i;
    int j;
    long int k;
    int a, b, c;

    a = sizeof(i);
    b = sizeof(j);
    c = sizeof(k);

    printf("a is %d\n", a);
    printf("b is %d\n", b);
    printf("c is %d\n", c);
}

void function_2_1() {
    int x, y, sum;

    x = 100;
    y = 200;
    sum = x + y;
    printf("sum is %d", sum);
}
