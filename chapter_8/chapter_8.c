//
// Created by oneapm on 2019-09-15.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void createthread();

int *thread(void *arg) {
    pthread_t newthid;

    newthid = pthread_self();
    printf("this is a new thread, thread ID = %d\n", newthid);
    return NULL;
}

int main(int argc, char *argv[], char **environ) {
    createthread();
}

void createthread() {
    pthread_t thid;

    printf("main thread ,ID is %d\n", pthread_self());
    if (pthread_create(&thid, NULL, (void *) thread, NULL) != 0) {
        printf("thread creation failed\n");
        exit(1);
    }
}




