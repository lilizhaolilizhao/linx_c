//
// Created by oneapm on 2019-08-12.
//

#include <stdio.h>

void function_001();

int main() {
    function_001();

    return 0;
}

void function_001() {
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