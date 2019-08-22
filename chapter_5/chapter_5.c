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

void function_5_003();

void function_5_004();

void function_5_005();

void function_5_011();

//int main() {
////    function_5_001();
////    function_5_002();
////    function_5_003();
////    function_5_004();
////    function_5_005();
//    function_5_011();
//
//    return 0;
//}

void function_5_011() {
    struct data {
        long l;
        char *s;
        short int i;
        char c;
        short int a[5];
    } d;

    struct data *p = &d;

    printf("%d\n", sizeof(d));
    printf("%x\t%x\n", p, p + 1);
    printf("%x\t%x\n", p, (char *) p + 1);
    printf("%x\t%x\n", p, (long *) p + 1);
}

struct student {
    int number;
    char name[20];
    char sex;
    int age;
    char addr[30];
};

void print_struct2(struct student *p) {
    p->age++;
    printf("%d,%s,%c,%d,%s\n", p->number, p->name, p->sex, p->age, p->addr);
}

void function_5_005() {
    struct student s[3] = {{10000, "Zhang", 'm', 21, "Shang Hai"},
                           {10001, "Li",    'f', 20, "Bei Jing"},
                           {10002, "Liu",   'm', 22, "Guang Dong"}};
    printf("%d,%d,%d\n", s[0].age, s[1].age, s[2].age);
    struct student *p;
    for (p = s; p < s + 3; p++)
        print_struct2(p);
    printf("%d,%d,%d\n", s[0].age, s[1].age, s[2].age);
}


void function_5_004() {
    struct student {
        int number;
        char name[20];
        char sex;
        int age;
        char addr[30];
    };
    struct student s[3] = {{10000, "Zhang", 'm', 21, "Shang Hai"},
                           {10001, "Li",    'f', 20, "Bei Jing"},
                           {10002, "Liu",   'm', 22, "Guang Dong"}};
    struct student *p;
    for (p = s; p < s + 3; p++) {
        printf("%d,%s,%c,%d,%s\n", p->number, p->name, p->sex, p->age, p->addr);
    }
}

void function_5_003() {
    struct student {
        int number;
        char name[20];
        char sex;
        int age;
        char addr[30];
    };
    struct student s[3] = {{10000, "Zhang", 'm', 21, "Shang Hai"},
                           {10001, "Li",    'f', 20, "Bei Jing"}};
    struct student *p;
    s[2].number = 10002;
    s[2].sex = 'm';
    s[2].age = 22;

    strcpy(s[2].name, "Liu");
    strcpy(s[2].addr, "Guang Dong");

    p = &s[0];
    printf("%d,%s,%c,%d,%s\n", s[0].number, s[0].name, s[0].sex, s[0].age, s[0].addr);
    printf("%d,%s,%c,%d,%s\n", p->number, p->name, p->sex, p->age, p->addr);
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
