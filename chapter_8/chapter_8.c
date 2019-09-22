//
// Created by oneapm on 2019-09-15.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void createthread();

pthread_once_t once = PTHREAD_ONCE_INIT;

void run(void) {
    printf("Fuction run is running in thread %d\n", pthread_self());
}

void oncerun();

int *thread(void *arg) {
    pthread_t newthid;

    newthid = pthread_self();
    printf("this is a new thread, thread ID = %d\n", newthid);
    return NULL;
}

int main(int argc, char *argv[], char **environ) {
//    createthread();
    oncerun();
}

void *thread1(void *arg) {
    pthread_t thid = pthread_self();
    printf("Current thread's ID is %d\n", thid);
    pthread_once(&once, run);
    printf("thread1 ends\n");
}

void *thread2(void *arg) {
    pthread_t thid = pthread_self();
    printf("Current thread's ID is %d\n", thid);
    pthread_once(&once, run);
    printf("thread2 ends\n");
}

void oncerun() {
    pthread_t thid1, thid2;

    pthread_create(&thid1, NULL, thread1, NULL);
    pthread_create(&thid2, NULL, thread2, NULL);
    sleep(3);
    printf("main thread exit! \n");
    exit(0);
}

void createthread() {
    pthread_t thid;

    printf("main thread ,ID is %d\n", pthread_self());
    if (pthread_create(&thid, NULL, (void *) thread, NULL) != 0) {
        printf("thread creation failed\n");
        exit(1);
    }
}




