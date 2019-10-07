//
// Created by oneapm on 2019-10-06.
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

#define FIFO_READ    "readfifo"
#define FIFO_WRITE    "writefifo"
#define BUF_SIZE    1024

void server();

void client();

void ftok_test();

int main(int argc, char *argv[], char **environ) {
//    server();
//    client();
    ftok_test();
}

void ftok_test() {
    int i;
    for ( i = 1; i <= 5; i++ )
        printf( "key[%d] =  %ul \n", i, ftok( ".", i) );
}

void client() {
    int wfd, rfd;
    char buf[BUF_SIZE];
    int len;

    umask(0);
    if (mkfifo(FIFO_WRITE, S_IFIFO | 0666)) {
        printf("Can't create FIFO %s because %s", FIFO_WRITE, strerror(errno));
        exit(1);
    }

    while ((rfd = open(FIFO_READ, O_RDONLY)) == -1) {
        sleep(1);
    }

    wfd = open(FIFO_WRITE, O_WRONLY);
    if (wfd == -1) {
        printf("Fail to open FIFO %s: %s", FIFO_WRITE, strerror(errno));
        exit(-1);
    }

    while (1) {
        len = read(rfd, buf, BUF_SIZE);
        if (len > 0) {
            buf[len] = '\0';
            printf("Server: %s\n", buf);
        }

        printf("Client: ");
        fgets(buf, BUF_SIZE, stdin);
        buf[strlen(buf) - 1] = '\0';
        if (strncmp(buf, "quit", 4) == 0) {
            close(wfd);
            unlink(FIFO_WRITE);
            close(rfd);
            exit(0);
        }
        write(wfd, buf, strlen(buf));
    }
}

void server() {
    int wfd, rfd;
    char buf[BUF_SIZE];
    int len;

    umask(0);
    if (mkfifo(FIFO_WRITE, S_IFIFO | 0666)) {
        printf("Can't create FIFO %s because  %s", FIFO_WRITE, strerror(errno));
        exit(1);
    }
    umask(0);
    wfd = open(FIFO_WRITE, O_WRONLY);
    if (wfd == -1) {
        printf("open FIFO %s error: %s", FIFO_WRITE, strerror(errno));
        exit(1);
    }

    while ((rfd = open(FIFO_READ, O_RDONLY)) == -1) {
        sleep(1);
    }

    while (1) {
        printf("Server: ");
        fgets(buf, BUF_SIZE, stdin);
        buf[strlen(buf) - 1] = '\0';
        if (strncmp(buf, "quit", 4) == 0) {
            close(wfd);
            unlink(FIFO_WRITE);
            close(rfd);
            exit(0);
        }
        write(wfd, buf, strlen(buf));

        len = read(rfd, buf, BUF_SIZE);
        if (len > 0) {
            buf[len] = '\0';
            printf("Client: %s\n", buf);
        }
    }
}
