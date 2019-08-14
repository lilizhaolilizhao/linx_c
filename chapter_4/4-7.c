//
// Created by oneapm on 2019-08-12.
//

#include <stdio.h>

void function_401();

void function_402();

void function_403();

void function_404();

void function_405();

void function_406();

int main() {
//    function_401();
//    function_402();
//    function_403();
//    function_404();
//    function_405();
    function_406();

    return 0;
}

void function_406() {
    int a[2][5] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    int (*p)[5], i;

    p = a;
    for (i = 0; i < 5; i++)
        printf("%d ", (*p)[i]);
    printf("\n");

    p++;
    for (i = 0; i < 5; i++)
        printf("%d ", (*p)[i]);
    printf("\n");
}

void function_405() {
    int a[5] = {1, 3, 5, 7, 9};
    int *p[5], i;
    int **pp = p;

    for (i = 0; i < 5; i++)
        p[i] = &a[i];

    for (i = 0; i < 5; i++)
        printf("%d ", *p[i]);
    printf("\n");

    for (i = 0; i < 5; i++, pp++)
        printf("%d ", **pp);
}

void function_404() {
    int a[10], i, *p = NULL;

    for (i = 0; i < 10; i++)
        a[i] = i;

    for (i = 0; i < 10; i++)
        printf("%d ", a[i]);
    printf("\n");

    for (i = 0; i < 10; i++)
        printf("%d ", *(a + i));
    printf("\n");

    for (p = a; p < a + 10;)
        printf("%d ", *p++);
    printf("\n");
}

void function_403() {
    int a = 100, b = 200;
    int *p1 = &a, *p2 = &b;

    printf("%d,%d\n", a, b);
    printf("%d,%d\n", *p1, *p2);
    printf("%x,%x\n", &a, &b);
    printf("%x,%x\n\n", p1, p2);

    *p1 = *p1 * 3;
    printf("%d\n", a);
    printf("%d\n\n", *p1);

    p1 = &b;
    printf("%x\n", p1);
    printf("%x\n", p2);
}

void function_402() {
    int a[2][4] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8}};
    int b[4][2], i, j;

    printf("array a:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            printf("%5d", a[i][j]);
            b[j][i] = a[i][j];
        }
        printf("\n");
    }

    printf("array b:\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            printf("%5d", b[i][j]);
        }
        printf("\n");
    }
}

void function_401() {
    int a[2][4] = {{1, 2, 3, 4},
                   {5, 6, 7, 8}};
    int b[4][2], i, j;

    printf("array a:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            printf("%5d", a[i][j]);
            b[j][i] = a[i][j];
        }
        printf("\n");
    }

    printf("array b:\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            printf("%5d", b[i][j]);
        }
        printf("\n");
    }
}