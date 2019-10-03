//
// Created by oneapm on 2019-10-02.
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

void my_signal_test();

void my_sigaction();

void wrong_return();

void right_return();

void my_kill();

void simulate_ping();

void test_setitimer();

void sig_mask();

void sig_suspend();

/*信号处理函数*/
void handler_sigint(int signo) {
    printf("recv SIGINT\n");
}

/*自定义的错误处理函数*/
void my_err(const char *err_string, int line) {
    fprintf(stderr, "line:%d  ", line);
    perror(err_string);
    exit(1);
}

int main(int argc, char *argv[], char **environ) {
//    my_signal_test();
//    my_sigaction();
//    wrong_return();
//    right_return();
//    my_kill(argc, argv, environ);
//    simulate_ping();
//    test_setitimer();
//    sig_mask();
    sig_suspend();
}

void sig_suspend() {
    sigset_t newmask, oldmask, zeromask;    // 定义信号集

    /*安装信号处理函数*/
    if (signal(SIGINT, handler_sigint) == SIG_ERR) {
        my_err("signal", __LINE__);
    }

    sigemptyset(&newmask);
    sigemptyset(&zeromask);
    sigaddset(&newmask, SIGINT);

    /*屏蔽信号SIGINT*/
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        my_err("sigprocmask", __LINE__);
    } else {
        printf("SIGINT blocked\n");
    }

    /*临界区*/

    /*使用sigsuspend取消所有信号的屏蔽并等待信号的触发*/
    if (sigsuspend(&zeromask) != -1) {  // sigsuspend总是返回-1
        my_err("sigsuspend", __LINE__);
    } else {
        printf("recv a signo, return from sigsuspend\n");
    }

/*-----------------------------------------
// 如果使用sigprocmask 加上 pause可能会出现错误
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		my_err("sigprocmask", __LINE__);
	}
	pause();
-----------------------------------------*/

    /*将信号屏蔽字恢复*/
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        my_err("sigprocmask", __LINE__);
    }

    while (1);
}

/*自定义的错误处理函数*/
void my_err(const char *err_string, int line) {
    fprintf(stderr, "line:%d  ", line);
    perror(err_string);
    exit(1);
}

/*SIGINT的处理函数*/
void hander_sigint(int signo) {
    printf("recv SIGINT\n");
}

void sig_mask() {
    sigset_t newmask, oldmask, pendmask;    // 定义信号集

    /*安装信号处理函数*/
    if (signal(SIGINT, hander_sigint) == SIG_ERR) {
        my_err("signal", __LINE__);
    }

    /*睡眠10秒*/
    sleep(10);

    /*初始化信号集newmask并将SIGINT添加进去*/
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    /*屏蔽信号SIGINT*/
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        my_err("sigprocmask", __LINE__);
    } else {
        printf("SIGINT blocked\n");
    }

    sleep(10);

    /*获取未决信号队列*/
    if (sigpending(&pendmask) < 0) {
        my_err("sigpending", __LINE__);
    }

    /*检查未决信号队列里面是否有SIGINT*/
    switch (sigismember(&pendmask, SIGINT)) {
        case 0:
            printf("SIGINT is not in pending queue\n");
            break;
        case 1:
            printf("SIGINT is in pending queue\n");
            break;
        case -1:
            my_err("sigismember", __LINE__);
            break;
        default:
            break;
    }

    /*解除对SIGINT的屏蔽*/
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        my_err("sigprocmask", __LINE__);
    } else {
        printf("SIGINT unblocked\n");
    }

    while (1);
}

/*信号处理程序*/
void handler_sigtime(int signo) {
    switch (signo) {
        case SIGALRM:
            printf("recv SIGALRM\n");
            break;
        case SIGPROF:
            printf("recv SIGPROF\n");
            break;
        default:
            break;
    }
}

void test_setitimer() {
    struct itimerval value;

    /*安装信号处理函数*/
    signal(SIGALRM, handler_sigtime);
    signal(SIGPROF, handler_sigtime);

    /*初始化value结构*/
    value.it_value.tv_sec = 1;            // 第一次1秒触发信号
    value.it_value.tv_usec = 0;
    value.it_interval.tv_sec = 5;        // 第二次开始每5秒触发信号
    value.it_interval.tv_usec = 0;

    /*设置定时器*/
    setitimer(ITIMER_REAL, &value, NULL);
    setitimer(ITIMER_PROF, &value, NULL);

    while (1);
}

void send_ip() {
    /*发送回送请求报文，这里只是打印消息*/
    printf("send a icmp echo request packet\n");
}

void handler_sigalarm(int signo) {
    send_ip();
    alarm(2);
}

void recv_ip() {
    /*挂起在套接字上等待数据并解析报文，这里只是使用死循环*/
    while (1);
}

void simulate_ping() {
    /*安装信号处理程序*/
    signal(SIGALRM, handler_sigalarm);

    /*触发一个SIGALRM信号给本进程*/
    raise(SIGALRM);
    recv_ip();
}

void my_kill(int argc, char *argv[], char **environ) {
    int i, j;
    int signum = SIGTERM;    // 默认发送SIGTERM
    pid_t pid;

    /*首先检查参数个数*/;
    if (argc != 2 && argc != 4) {
        printf("Usage: ./my_kill <-s signum> [PID]\n");
        exit(0);
    }

    /*从命令行参数解析出信号编号*/
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-s")) {
            signum = atoi(argv[i + 1]);
            break;
        }
    }

    /*解析出进程号*/
    if (argc == 2) {
        pid = atoi(argv[1]);
    } else {
        for (j = 1; j < argc; j++) {
            if (j != i && j != i + 1) {
                pid = atoi(argv[j]);
                break;
            }
        }
    }

    if (kill(pid, signum) < 0) {
        perror("kill");
        exit(1);
    }
}

void right_return() {
//    /*设置返回点*/
//    switch (sigsetjmp(env, 1)) {	// sigsetjmp的第二个参数只要非0即可
//        case 0:
//            printf("return 0\n");
//            flag_saveenv = ENV_SAVED;
//            break;
//        case 1:
//            printf("return from SIGRTMIN+15\n");
//            break;
//        default:
//            printf("return else\n");
//            break;
//    }
//
//    /*捕捉信号，安装信号处理函数*/
//    signal(SIGRTMIN+15, handler_sigrtmin15);
//
//    while (1)
//        ;
}

jmp_buf env;     // 保存待跳转位置的栈信息

void wrong_return() {
//    /*设置返回点*/
//    switch (setjmp(env)) {
//        case 0:
//            break;
//        case 1:
//            printf("return from SIGRTMIN+15\n");
//            break;
//        case 2:
//            printf("return from SIGRTMAX-15\n");
//            break;
//        default:
//            break;
//    }
//
//    /*捕捉信号，安装信号处理函数*/
//    signal(SIGRTMIN+15, handler_sigrtmin15);
//    signal(SIGRTMAX-15, handler_sigrtmax15);
//
//    while (1)
//        ;
}

int temp = 0;

/*信号处理函数*/
void handler_sigint100(int signo) {
    printf("recv SIGINT\n");
    sleep(5);
    temp += 1;
    printf("the value of temp is: %d\n", temp);
    printf("in handler_sigint, after sleep\n");
}

void my_sigaction() {
    struct sigaction act;

    /*赋值act结构*/
    act.sa_handler = handler_sigint100;
    act.sa_flags = SIGTERM;
    /*安装信号处理函数*/
    sigaction(SIGINT, &act, NULL);

    while (1);
}

void my_signal_test() {
    /*安装信号处理函数*/
    signal(SIGINT, handler_sigint);

    while (1);
}

