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

void jointhread_test();

void tsd();

int *thread(void *arg) {
    pthread_t newthid;

    newthid = pthread_self();
    printf("this is a new thread, thread ID = %d\n", newthid);
    return NULL;
}

void assisthread(void *arg) {
    printf("I am helping to do some jobs\n");
    sleep(3);
    pthread_exit(0);
}

int main(int argc, char *argv[], char **environ) {
//    createthread();
//    oncerun();
//    jointhread_test();
    tsd();
}

pthread_key_t key;

void *thread200(void *arg) {
    int tsd = 5;

    printf("thread %d is running\n", pthread_self());
    pthread_setspecific(key, (void *) tsd);
    printf("thread %d returns %d\n", pthread_self(), pthread_getspecific(key));
}

void *thread100(void *arg) {
    int tsd = 0;
    pthread_t thid2;

    printf("thread %d is running\n", pthread_self());
    pthread_setspecific(key, (void *) tsd);
    pthread_create(&thid2, NULL, thread200, NULL);
    sleep(5);
    printf("thread %d returns %d\n", pthread_self(), pthread_getspecific(key));
}

void tsd() {
    pthread_t thid1;
    printf("main thread begins running\n");
    pthread_key_create(&key, NULL);
    pthread_create(&thid1, NULL, thread100, NULL);
    sleep(300);
    pthread_key_delete(key);
    printf("main thread exit\n");
}

void jointhread_test() {
    pthread_t assistthid;
    int status;

    pthread_create(&assistthid, NULL, (void *) assisthread, NULL);
    pthread_join(assistthid, (void *) &status);
    printf("assistthread's exit is caused %d\n", status);
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




