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

void fork_test1();

void fork_test2();

void fork_test3();

void difffork();

int globVar = 5;

int main() {
//    fork_test1();
//    fork_test2();
//    fork_test3();
    difffork();
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
