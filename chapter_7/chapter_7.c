//
// Created by oneapm on 2019-08-25.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <zconf.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <limits.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/param.h>
#include <syslog.h>

void fork_test1();

void fork_test2();

void fork_test3();

void difffork();

int init_daemon();

void init_daemon_main();

void env();

void processimage(int argc, char *argv[], char **environ);

void execve_test();

int globVar = 5;

int main(int argc, char *argv[], char **environ) {
//    fork_test1();
//    fork_test2();
//    fork_test3();
//    difffork();
//    init_daemon_main();
//    env(argc, argv);
//    processimage(argc, argv, environ);
    execve_test();
}

void execve_test(int argc, char *argv[], char **environ) {
    pid_t pid;
    int stat_val;

    printf("Exec example!\\n");
    pid = fork();
    switch (pid) {
        case -1:
            perror("Process Creation failed\n");
            exit(1);
        case 0:
            printf("Child process is running\n");
            printf("My pid = %d ,parentpid = %d\n", getpid(), getppid());
            printf("uid = %d,gid =%d\n", getuid(), getgid());
            execve("processimage", argv, environ);
            printf("process never go to here!\n");
            exit(0);
        default:
            printf("Parent process is running\n");
            break;
    }

    wait(&stat_val);
    exit(0);
}

void processimage(int argc, char *argv[], char **environ) {
    int i;

    printf("I am a process image!\n");
    printf("My pid = %d, parentpid = %d\n", getpid(), getppid());
    printf("uid = %d,gid = %d\n", getuid(), getgid());

    for (i = 0; i < argc; i++)
        printf("argv[%d]:%s\n", i, argv[i]);
}

extern char **environ;

//使用env查看环境变量信息
void env(int argc, char *argv[]) {
    int i;

    printf("Argument:\n");
    for (i = 0; i < argc; i++) {
        printf("argv[%d] is %s\n", i, argv[i]);
    }
    printf("Environment:\n");

    for (i = 0; environ[i] != NULL; i++)
        printf("%s\n", environ[i]);
}

void init_daemon_main() {
    time_t now;
    init_daemon();
    syslog(LOG_USER | LOG_INFO, "测试守护进程! \n");

    while (1) {
        sleep(8);
        time(&now);
        syslog(LOG_USER | LOG_INFO, "系统时间: \t%s\t\t\n", ctime(&now));
    }
}

int init_daemon(void) {
    int pid;
    int i;

    /*忽略终端I/O信号，STOP信号*/
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    pid = fork();
    if (pid > 0) {
        exit(0); /*结束父进程，使得子进程成为后台进程*/
    } else if (pid < 0) {
        return -1;
    }

    /*建立一个新的进程组,在这个新的进程组中,子进程成为这个进程组的首进程,以使该进程脱离所有终端*/
    setsid();

    /*再次新建一个子进程，退出父进程，保证该进程不是进程组长，同时让该进程无法再打开一个新的终端*/
    pid = fork();
    if (pid > 0) {
        exit(0);
    } else if (pid < 0) {
        return -1;
    }

    /*关闭所有从父进程继承的不再需要的文件描述符*/
    for (i = 0; i < NOFILE; close(i++));

    /*改变工作目录，使得进程不与任何文件系统联系*/
    chdir("/");

    /*将文件当时创建屏蔽字设置为0*/
    umask(0);

    /*忽略SIGCHLD信号*/
    signal(SIGCHLD, SIG_IGN);
}

void difffork() {
    pid_t pid;
    int var = 1, i;

    printf("fork is diffirent with vfrok \n");

//    pid = fork();
    pid = vfork();
    switch (pid) {
        case 0:
            i = 3;
            while (i-- > 0) {
                printf("Child process is running\n");
                globVar++;
                var++;
                sleep(1);
            }
            printf("Child's globVar = %d,var = %d\n", globVar, var);
            break;
        case -1:
            perror("Process creation failed\n");
            exit(0);
        default:
            i = 5;
            while (i-- > 0) {
                printf("Parent process is running\n");
                globVar++;
                var++;
                sleep(1);
            }
            printf("Parent's globVar = %d ,var = %d\n", globVar, var);
            exit(0);
    }
}

void fork_test3() {
    pid_t pid;

    pid = fork();
    switch (pid) {
        case 0:
            while (1) {
                printf("A background process, PID:%d\n, ParentID: %d\n", getpid(), getppid());
                sleep(3);
            }
        case -1:
            perror("Process creation failed\n");
            exit(-1);
        default:
            printf("I am parent process,my pid is %d\n", getpid());
            exit(0);
    }
}

void fork_test2() {
    pid_t pid;
    char *msg;
    int k;

    printf("Process Creation Study\n");

    pid = fork();

    switch (pid) {
        case 0:
            msg = "Child process is running";
            k = 3;
            break;
        case -1:
            perror("Process creation failed\n");
            break;
        default:
            msg = "Parent process is running";
            k = 5;
            break;
    }

    while (k > 0) {
        puts(msg);
        sleep(1);
        k--;
    }
}

void fork_test1() {
    pid_t pid;

    printf("Process Creation Study\n");
    pid = fork();

    switch (pid) {
        case 0:
            printf("Child process is running,CurPid is %d, ParentPid is %d\n", pid, getppid());
            break;
        case -1:
            perror("Process creation failed\n");
            break;
        default:
            printf("Parent process is running,ChildPid is %d, ParentPid is %d\n", pid, getpid());
            break;
    }
}
