//
// Created by oneapm on 2019-08-12.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void function_401();

void function_402();

void function_403();

void function_404();

void function_405();

void function_406();

void function_407();

void change(int a, int *pInt);

void function_408();

char *week(int day);

void function_409();

void function_410();

void function_4_18();

void copy_string1(char a[16], char b[20]);

void copy_string2(char a[16], char string[20]);

void function_char_test();

void function_4_32();

void function_4_33();

void function_4_34();

void test1();

void test2();

void test3();

void function_4_35();

int sum(int a);

void function_4_36();

int fun(int pInt[6], size_t i);

int fun22_22(int a[], int n);

void function_4_37();

char *RetMemory();

void function_4_38();

int findnumstring(char *p, char string[27]);

void function_4_39();

char *name[7] = {"Monday", "Tuesday", "Wednesday", "Thursday",
                 "Friday", "Saturday", "Sunday"};
char *message = "wrong input";

#define  GET_MAX    0
#define  GET_MIN    1

int get_max(int i, int j) {
    return i > j ? i : j;
}

int get_min(int i, int j) {
    return i > j ? j : i;
}

int compare(int i, int j, int flag) {
    int ret;
    int (*p)(int, int);

    if (flag == GET_MAX)
        p = get_max;
    else
        p = get_min;

    ret = p(i, j);

    return ret;
}

//int main() {
////    function_401();
////    function_402();
////    function_403();
////    function_404();
////    function_405();
////    function_406();
////    function_407();
////    function_408();
////    function_409();
////    function_410();
////    function_4_18();
////    function_char_test();
////    function_4_32();
////    function_4_33();
////    function_4_34();
////    function_4_35();
////    function_4_36();
////    function_4_37();
////    function_4_38();
//    function_4_39();
//
//    return 0;
//}

void function_4_39() {
    char str[] = "ABCD1234efgh";
    int length = strlen(str);
    char *p1 = str;            // p1指向字符串的第一个字符
    char *p2 = str + length - 1;    // p2指向字符串的最后一个字符

    // 逐个对调第一个和最后一个字符、第二个和倒数第二字符
    // 如此下去，直到达到字符串的中间
    while (p1 < p2) {
        // 对调字符
        char c = *p1;
        *p1 = *p2;
        *p2 = c;
        // 移动指针
        ++p1;
        --p2;
    }

    printf("string now is  %s\n", str);
}

void function_4_38() {
    // 主函数测试findnumstring函数是否正常工作
    char string[] = "abcd12345eee125ss123456789";
    char *p = (char *) malloc(strlen(string) + 1);
    int count = findnumstring(p, string);
    printf("%s\nnumber string length = %d\n", p, count);
}

int findnumstring(char *outputstr, char *inputstr) {
    /* temp用于指向正在搜索中的数字子串
           final用于指向最终的最长的数字子串
     */
    char *in = inputstr, *out = outputstr, *temp, *final;
    int count = 0, maxlen = 0;
    int i;

    while (*in != '\0')   //该循环用于找到最长的数字串，初始in指向输入串
    {
        // 如果in所指向的字符串的第一个字符为数字
        // 就获取以此数字字符开始的数字串的长度
        // 如果不是数字字符，in指向输入串的下一个字符
        if (*in > 47 && *in < 58) {
            // 注意in指针在变化
            for (temp = in; *in > 47 && *in < 58; in++)
                count++;
        } else
            in++;

        // 如果temp所指向数字串的长度比上一次找到的长
        // 则把当前找到的最长数字串长度和地址分别赋给maxlen和final
        if (maxlen < count) {
            maxlen = count;
            final = temp;
        }

        // 把count清零
        count = 0;
    }

    // while循环结束后，最长的数字串已经找到。
    // 把找到的最长数字串存储到out所指的存储空间
    for (i = 0; i < maxlen; i++) {
        *out = *final;
        out++;
        final++;
    }
    *out = '\0';

    return maxlen;
}

void function_4_37() {
    char *str = "NULL";

    //指向函数内部变量的指针
    str = RetMemory();
    printf("%s", str);
}

char *RetMemory() {
    char p[] = "hello world";
    return p;
}

void function_4_36() {
    int a[] = {1, 2, 3, 4, 5, 6};
    int b[] = {1, 2, 3, 4, 6, 5};

    if (fun22_22(a, sizeof(a) / sizeof(a[0])) == 1)
        printf("a:ok\n");
    else
        printf("a:no\n");

    if (fun22_22(b, sizeof(a) / sizeof(a[0])) == 1)
        printf("b:ok\n");
    else
        printf("b:no\n");
}

int fun22_22(int a[], int n) {
    if (n == 1)
        return 1;
    if (n == 2)
        return (a[n - 1] >= a[n - 2]);
    return (fun22_22(a, n - 1) && (a[n - 1] >= a[n - 2]));
}

void function_4_35() {
    int i;
    int a = 2;
    for (i = 0; i < 5; i++) {
        printf("%d,", sum(a));
    }
}

int sum(int a) {
    auto int c = 0;
    static int b = 3;
    c += 1;
    b += 2;
    return (a + b + c);
}

void function_4_34() {
//    test1();
//    test2();
//    test3();
}

void test3(char *str1) {
    char string[10];
    if (strlen(str1) <= 10) {
        strcpy(string, str1);
    }
}

void test2() {
    char string[10], str1[10];
    for (int i = 0; i < 9; i++) {
        str1[i] = 'a';
        str1[9] = '\0';
        strcpy(string, str1);
    }

    printf("%s\n%s", string, str1);
}

//detected buffer overflow
void test1() {
    char string[11];
    char *str1 = "0123456789";
    strcpy(string, str1);

    printf("%s\n%s", string, str1);
}

void reverse(char *p) {
    if (*p == '\0')
        return;
    reverse(p + 1);
    printf("%c", *p);
}

void function_4_33() {
    reverse("abcd");

    printf("\n");
}

void function_4_32() {
    int **p, *q;
    int arr[100];
    q = arr;
    p = &q;
}

void function_char_test() {
//    char a[] = "Welcome to ";
//    char *p = "Linux C Program";
//
//    puts(a);
//    puts(p);
//    char string[20];
//    gets(string);
//    puts(string);

    //字符串拷贝
//    char *s = "Hello World!!!!!!!";
//    char d1[20], d2[20];
//    strcpy(d1, s);
//    strncpy(d2, s, strlen(s));
//
//    printf("%s\n%s\n", d1, d2);

    //字符串连接
//    char d[20] = "Hello ";
//    char *s = "Word";
//    strcat(d, s);
//
//    printf("%s\n", d);

//    //字符串比较
//    char *s1 = "compare";
//    char *s2 = "computer";
//    if (strcmp(s1, s2) == 0) {
//        printf("0000000000");
//    } else if (strcmp(s1, s2) > 0) {
//        printf("1111111111");
//    } else {
//        printf("22222222222");
//    }

//    //字符串长度
//    char string[10] = "China";
//    printf("%d\n", strlen(string));

    //查找字串
    char *s1 = "Linux C Program", *s2 = "nux", *p;

    p = strstr(s1, s2);
    if (p != NULL) {
        printf("%s\n", p);
    } else {
        printf("Not Found!");
    }

    p = strchr(s1, 'C');
    if (p != NULL) {
        printf("%s\n", p);
    } else {
        printf("Not Found!");
    }
}

void function_4_18() {
    char a[] = "Linux C Program", b[20], c[20];

    copy_string1(a, b);
    copy_string2(a, c);

    printf("%s\n%s\n%s\n", a, b, c);
}

void copy_string2(char *psrc, char *pdst) {
    for (; *psrc != '\0'; psrc++, pdst++) {
        *pdst = *psrc;
    }

    *pdst = '\0';
}

void copy_string1(char src[], char dst[]) {
    int i;

    for (i = 0; src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';
}

void function_410() {
    char a[] = "Linux C Program", b[20], c[20];
    int i;

    for (i = 0; *(a + i) != '\0'; i++) {
        *(b + i) = *(a + i);
    }
    *(b + i) = '\0';

    char *p1, *p2;
    p1 = a;
    p2 = c;

    for (; *p1 != '\0'; p1++, p2++)
        *p2 = *p1;
    *p2 = '\0';

    printf("%s\n", a);
    printf("%s\n", b);
    printf("%s\n", c);
}

void function_409() {
    int i = 5, j = 10, ret;

    ret = compare(i, j, GET_MAX);
    printf("The MAX is %d\n", ret);
}

void function_408() {
    int day;
    char *p;

    printf("Input a number of a week:\n");
    scanf("%d", &day);

    p = week(day);
    printf("%s\n", p);
}

char *week(int day) {
    if (day < 0 || day > 7)
        return message;
    else
        return name[day - 1];
}

void function_407() {
    int a = 5, b = 10;

    change(a, &b);
    printf("a=%d b=%d\n", a, b);
}

void change(int i, int *p) {
    i++;

    if (p != NULL) {
        (*p)++;
    }
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