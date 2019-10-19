//
// Created by oneapm on 2019-10-09.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "my_recv.h"    // 自定义的头文件

#define    SERV_PORT        4507    // 服务器端的端口
#define    LISTENQ            12    // 连接请求队列的最大长度

#define    INVALID_USERINFO    'n'    // 用户信息无效
#define    VALID_USERINFO        'y'    // 用户信息有效

#define    USERNAME        0    // 接收到的是用户名
#define    PASSWORD        1    // 接收到的是密码

struct userinfo {    // 保存用户名和密码的结构体
    char username[32];
    char password[32];
};
struct userinfo users[] = {
        {"linux", "unix"},
        {"4507",  "4508"},
        {"clh",   "clh"},
        {"xl",    "xl"},
        {" ",     " "}        // 以只含一个空格的字符串作为数组的结束标志
};

// 查找用户名是否存在，存在返回该用户名的下标,不存在则返回-1，出错返回-2
int find_name(const char *name) {
    int i;

    if (name == NULL) {
        printf("in find_name, NULL pointer");
        return -2;
    }
    for (i = 0; users[i].username[0] != ' '; i++) {
        if (strcmp(users[i].username, name) == 0) {
            return i;
        }
    }

    return -1;
}

void test_address();

void test_select();

void display_time(const char *string);

void my_server();

void my_strcpy();

char *my_strcpy222(char *strDest, const char *strSrc);

void my_scaner();

int main(int argc, char *argv[], char **environ) {
//    test_address();
//    test_select();
//    my_server();
//    my_strcpy();
    my_scaner(argc, argv);
}

// 定义一个端口区间信息
typedef struct _port_segment {
    struct in_addr dest_ip;    // 目标IP
    unsigned short int min_port;    // 起始端口
    unsigned short int max_port;    // 最大端口
} port_segment;

/*
 * 命令行参数：-m 最大端口， -a 目标主机的IP地址,  -n 最大线程数
 */
void my_scaner(int argc, char **argv) {
    pthread_t *thread;              // 指向所有的线程ID
    int max_port;                   // 最大端口号
    int thread_num;                 // 最大线程数
    int seg_len;                    // 端口区间长度
    struct in_addr dest_ip;         // 目标主机IP
    int i;

    // 检查参数个数
    if (argc != 7) {
        printf("Usage: [-m] [max_port] [-a] [serv_address] [-n] [thread_number]\n");
        exit(1);
    }

    // 解析命令行参数
    for (i = 1; i < argc; i++) {
        if (strcmp("-m", argv[i]) == 0) {
            max_port = atoi(argv[i + 1]);   // 将字符串转化为对应的整数
            if (max_port < 0 || max_port > 65535) {
                printf("Usage:invalid max dest port\n");
                exit(1);
            }
            continue;
        }

        if (strcmp("-a", argv[i]) == 0) {
            if (inet_aton(argv[i + 1], &dest_ip) == 0) {
                printf("Usage:invalid dest ip address\n");
                exit(1);
            }
            continue;
        }

        if (strcmp("-n", argv[i]) == 0) {
            thread_num = atoi(argv[i + 1]);
            if (thread_num <= 0) {
                printf("Usage:invalid thread_number\n");
                exit(1);
            }
            continue;
        }
    }

    // 如果输入的最大端口号小于线程数，则将线程数设为最大端口号
    if (max_port < thread_num) {
        thread_num = max_port;
    }

    seg_len = max_port / thread_num;
    if ((max_port % thread_num) != 0) {
        thread_num += 1;
    }
    // 分配存储所有线程ID的内存空间
    thread = (pthread_t *) malloc(thread_num * sizeof(pthread_t));

    // 创建线程，根据最大端口号和线程数分配每个线程扫描的端口区间
    for (i = 0; i < thread_num; i++) {
        port_segment portinfo;
        portinfo.dest_ip = dest_ip;
        portinfo.min_port = i * seg_len + 1;
        if (i == thread_num - 1) {
            portinfo.max_port = max_port;
        } else {
            portinfo.max_port = portinfo.min_port + seg_len - 1;
        }
        // 创建线程
        if (pthread_create(&thread[i], NULL, scaner, (void *) &portinfo) != 0) {
            my_err("pthread_create", __LINE__);
        }
        // 主线程等待子线程结束
        pthread_join(thread[i], NULL);
    }
}

void my_strcpy() {
    char string1[32];
    char string2[32];
    int c;
    int i = 0;

    printf("please input your string:");
    // 对输入字符串的长度进行检查
    while (i < 31 && (c = getchar()) != '\n') {
        string2[i] = c;
        i++;
    }
    string2[i] = '\0';

    // 对返回值也进行合法性检查
    // 对返回值也进行合法性检查
    if (my_strcpy222(string1, string2) == NULL) {
        fprintf(stderr, "return from my_strcpy");
        exit(1);
    }

    printf("string1:%s\n", string1);
    printf("string2:%s\n", string2);
}

char *my_strcpy222(char *strDest, const char *strSrc) {
    char *p_return = strDest;

    // 检查参数指针是否为空
    if (strDest == NULL || strSrc == NULL) {
        fprintf(stderr, "NULL POINT!");
        return NULL;
    }

    while ((*strDest++ = *strSrc++) != '\0');
    return p_return;
}

void test_select() {
    fd_set readfds;
    struct timeval timeout;
    int ret;

    /*监视文件描述符0是否有数据输入，即文件描述符0表示标准输入即键盘输入*/
    FD_ZERO(&readfds);  // 开始使用一个描述符集合前一般要将其清空
    FD_SET(0, &readfds);

    /*设置阻塞时间为10秒*/
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    while (1) {
        display_time("before select");
        ret = select(1, &readfds, NULL, NULL, &timeout);
        display_time("after select");

        switch (ret) {
            case 0:
                printf("No data in ten seconds.\n");
                exit(0);
                break;
            case -1:
                perror("select");
                exit(1);
                break;
            default:
                getchar();     // 将数据读入，否则标准输入上将一直为读就绪
                printf("Data is available now.\n");
        }
    }
}

void display_time(const char *string) {
    int seconds;

    seconds = time((time_t *) NULL);
    printf("%s, %d\n", string, seconds);
}

void test_address() {
    char buffer[32];
    int ret = 0;
    int host = 0;
    int network = 0;
    unsigned int address = 0;
    struct in_addr in;

    in.s_addr = 0;

    /*输入一个以"."分隔的字符串形式的IP地址*/
    printf("please input your ip address:");
    fgets(buffer, 31, stdin);
    buffer[31] = '\0';

    /*示例使用inet_aton()函数*/
    if ((ret = inet_aton(buffer, &in)) == 0) {
        printf("inet_aton: \t invalid address\n");
    } else {
        printf("inet_aton:\t0x%x\n", in.s_addr);
    }

    /*示例使用inet_addr()函数*/
    if ((address = inet_addr(buffer)) == INADDR_NONE) {
        printf("inet_addr: \t invalid address\n");
    } else {
        printf("inet_addr:\t0x%lx\n", address);
    }

    /*示例使用inet_network()函数*/
    if ((address = inet_network(buffer)) == -1) {
        printf("inet_network: \t invalid address\n");
    } else {
        printf("inet_network:\t0x%lx\n", address);
    }

    /*示例使用inet_ntoa()函数*/
    if (inet_ntoa(in) == NULL) {
        printf("inet_ntoa: \t invalid address\n");
    } else {
        printf("inet_ntoa:\t%s\n", inet_ntoa(in));
    }

    /*示例使用inet_lnaof()与inet_netof()函数*/
    host = inet_lnaof(in);
    network = inet_netof(in);
    printf("inet_lnaof:\t0x%x\n", host);
    printf("inet_netof:\t0x%x\n", network);

    in = inet_makeaddr(network, host);
    printf("inet_makeaddr:0x%x\n", in.s_addr);
}

