//
// Created by oneapm on 2019-08-11.
//

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void function_001();

void function_002();

void function_003();

void function_004();

void function_005();

void function_006();

void function_007();

main() {
//    function_001();
//    function_002();
//    function_003();
//    function_004();
//    function_005();
//    function_006();
    function_007();
}

void function_007() {
    int number, guess, i = 8;

    srand(time(NULL));
    number = rand() % 100 + 1;

    printf("Please guess a number:\n");

    while (i > 0) {
        scanf("%d", &guess);

        if (guess == number) {
            printf("Wonderful,you are right!\n\n");
        } else if (guess > number) {
            printf("Sorry,your are wrong.");
            printf("too high\n");
        } else {
            printf("Sorry,your are wrong.");
            printf("too low\n");
        }
        i--;
    }

    printf("Game over!\n\n");
}

void function_006() {
    int i, sum = 0, flag = 0;
    char killer;

    for (i = 1; i <= 4; i++) {
        killer = 64 + i;

        sum = (killer != 'A') + (killer == 'C') + (killer == 'D') + (killer != 'D');

        if (sum == 3) {
            flag = 1;
            printf("%c is the killer.\n", killer);
            break;
        }
    }

    if (flag == 0)
        printf("Can not find\n");
}

void function_005() {
    int i, j;
    long sum = 0;

    for (i = 1; i <= 10; i++) {
        int total = 1;
        for (j = 1; j <= i; j++)
            total = total * j;
        sum = sum + total;
    }

    printf("1!+2!+3!+...+10!=%d\n", sum);
}

void function_004() {
    int number;

    for (number = 1; number <= 100; number++) {
        if (number % 13 == 0)
            continue;
        printf("%d ", number);
    }

    printf("\n");
}

void function_003() {
    int sum = 0, i = 1;

    do {
        sum = sum + i;
        i = i + 1;
    } while (i <= 100);

    printf("%d\n", sum);
}

void function_002() {
    int sum = 0, i = 1;

    while (i <= 100) {
        sum += i;
        i += 1;
    }

    printf("%d\n", sum);
}

void function_001() {
    float a, b, c, temp;

    scanf("%f,%f,%f", &a, &b, &c);
    if (a > b) {
        temp = a;
        a = b;
        b = temp;
    }
    if (a > c) {
        temp = a;
        a = c;
        c = temp;
    }
    if (b > c) {
        temp = b;
        b = c;
        c = temp;
    }

    printf("%f,%f,%f\n", a, b, c);
}