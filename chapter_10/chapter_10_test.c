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
#include <sys/ipc.h>
#include <sys/msg.h>

#define FIFO_READ    "readfifo"
#define FIFO_WRITE    "writefifo"
#define BUF_SIZE    1024

#define BUF_SIZE    256
#define PROJ_ID        32
#define PATH_NAME    "."

#define BUF_SIZE    256
#define PROJ_ID        32
#define PATH_NAME    "/tmp"
#define SERVER_MSG    1
#define CLIENT_MSG    2

void server();

void client();

void ftok_test();

void sendmsg_test();

void rcvmsg_test();

void opmsg_test();

void getmsgattr(int msgid, struct msqid_ds msq_info);

void server2();

void client2();

//int main(int argc, char *argv[], char **environ) {
////    server();
////    client();
////    ftok_test();
////    sendmsg_test();
////    rcvmsg_test();
////    opmsg_test();
////    server2();
////    client2();
//
//}

void client2() {
/*用户自定义消息缓冲区*/
    struct mymsgbuf {
        long msgtype;
        char ctrlstring[BUF_SIZE];
    } msgbuffer;
    int qid;    /*消息队列标识符*/
    int msglen;
    key_t msgkey;

    /*获取键值*/
    if ((msgkey = ftok(PATH_NAME, PROJ_ID)) == -1) {
        perror("ftok error!\n");
        exit(1);
    }

    if ((qid = msgget(msgkey, IPC_CREAT | 0660)) == -1) {
        perror("msgget error!\n");
        exit(1);
    }

    while (1) {
        if (msgrcv(qid, &msgbuffer, BUF_SIZE, SERVER_MSG, 0) == -1) {
            perror("Server msgrcv error!\n");
            exit(1);
        }

        printf("server: %s\n", msgbuffer.ctrlstring);
        printf("client: ");
        fgets(msgbuffer.ctrlstring, BUF_SIZE, stdin);
        if (strncmp("exit", msgbuffer.ctrlstring, 4) == 0) {
            break;
        }
        msgbuffer.ctrlstring[strlen(msgbuffer.ctrlstring) - 1] = '\0';
        msgbuffer.msgtype = CLIENT_MSG;
        if (msgsnd(qid, &msgbuffer, strlen(msgbuffer.ctrlstring) + 1, 0) == -1) {
            perror("client msgsnd error!\n");
            exit(1);
        }
    }
}

void server2() {
    /*用户自定义消息缓冲区*/
    struct mymsgbuf {
        long msgtype;
        char ctrlstring[BUF_SIZE];
    } msgbuffer;

    int qid; /*消息队列标识符*/
    int msglen;
    key_t msgkey;

    /*获取键值*/
    if ((msgkey = ftok(PATH_NAME, PROJ_ID)) == -1) {
        perror("ftok error!\n");
        exit(1);
    }

    if ((qid = msgget(msgkey, IPC_CREAT | 0660)) == -1) {
        perror("msgget error!\n");
        exit(1);
    }

    while (1) {
        printf("server: ");
        fgets(msgbuffer.ctrlstring, BUF_SIZE, stdin);
        if (strncmp("exit", msgbuffer.ctrlstring, 4) == 0) {
            msgctl(qid, IPC_RMID, NULL);
            break;
        }
        msgbuffer.ctrlstring[strlen(msgbuffer.ctrlstring) - 1] = '\0';
        msgbuffer.msgtype = SERVER_MSG;
        if (msgsnd(qid, &msgbuffer, strlen(msgbuffer.ctrlstring) + 1, 0) == -1) {
            perror("Server msgsnd error!\n");
            exit(1);
        }


        if (msgrcv(qid, &msgbuffer, BUF_SIZE, CLIENT_MSG, 0) == -1) {
            perror("Server msgrcv error!\n");
            exit(1);
        }
        printf("Client: %s\n", msgbuffer.ctrlstring);
    }
}

void opmsg_test() {
    /*用户自定义消息缓冲区*/
    struct mymsgbuf {
        long msgtype;
        char ctrlstring[BUF_SIZE];
    } msgbuffer;
    int qid;    /*消息队列标识符*/
    int msglen;
    key_t msgkey;
    struct msqid_ds msq_attr;

    /*获取键值*/
    if ((msgkey = ftok(PATH_NAME, PROJ_ID)) == -1) {
        perror("ftok error!\n");
        exit(1);
    }

    /*获取消息队列标识符*/
    if ((qid = msgget(msgkey, IPC_CREAT | 0660)) == -1) {
        perror("msgget error!\n");
        exit(1);
    }

    getmsgattr(qid, msq_attr); /*输出消息队列的属性*/

    /*发送一条消息到消息队列*/
    msgbuffer.msgtype = 2;
    strcpy(msgbuffer.ctrlstring, "Aother message");
    msglen = sizeof(struct mymsgbuf) - 4;
    if (msgsnd(qid, &msgbuffer, msglen, 0) == -1) {
        perror("msgget error!\n");
        exit(1);
    }
    getmsgattr(qid, msq_attr); /*再输出消息队列的属性*/

    /*设置消息队列的属性*/
    msq_attr.msg_perm.uid = 3;
    msq_attr.msg_perm.gid = 2;
    if (msgctl(qid, IPC_SET, &msq_attr) == -1) {
        perror("msg set error!\n");
        exit(1);
    }
    getmsgattr(qid, msq_attr);/*修改后再观察其属性*/
    if (msgctl(qid, IPC_RMID, NULL) == -1) {
        perror("delete msg error!\n");
        exit(1);
    }
    getmsgattr(qid, msq_attr);/*删除后再观察其属性*/
}

void getmsgattr(int msgid, struct msqid_ds msg_info) {
    if (msgctl(msgid, IPC_STAT, &msg_info) == -1) {
        perror("msgctl error!\n");
        return;
    }
    printf("****information of message queue %d****\n", msgid);
    printf("last msgsnd to msq time is %s\n", ctime(&(msg_info.msg_stime)));
    printf("last msgrcv time from msg is %s\n", ctime(&(msg_info.msg_rtime)));
    printf("last change msq time is %s\n", ctime(&(msg_info.msg_ctime)));
    printf("current number of bytes on queue is %d\n", msg_info.msg_cbytes);
    printf("number of messages in queue is %d\n", msg_info.msg_qnum);
    printf("max number of bytes on queue is %d\n", msg_info.msg_qbytes);
    printf("pid of last msgsnd is %d\n", msg_info.msg_lspid);
    printf("pid of last msgrcv is %d\n", msg_info.msg_lrpid);

    printf("msg uid is %d\n", msg_info.msg_perm.uid);
    printf("msg gid is %d\n", msg_info.msg_perm.gid);
    printf("******information end!**********\n", msgid);
}

void rcvmsg_test() {
/*用户自定义消息缓冲区*/
    struct mymsgbuf {
        long msgtype;
        char ctrlstring[BUF_SIZE];
    } msgbuffer;
    int qid;     /*消息队列标识符*/
    int msglen;
    key_t msgkey;

    /*获取键值*/
    if ((msgkey = ftok(PATH_NAME, PROJ_ID)) == -1) {
        perror("ftok error!\n");
        exit(1);
    }

    /*获取消息队列标识符*/
    if ((qid = msgget(msgkey, IPC_CREAT | 0660)) == -1) {
        perror("msgget error!\n");
        exit(1);
    }

    msglen = sizeof(struct mymsgbuf) - 4;
    if (msgrcv(qid, &msgbuffer, msglen, 3, 0) == -1)  /*读取数据*/
    {
        perror("msgrcv error!\n");
        exit(1);
    }
    printf("Get message %s\n", msgbuffer.ctrlstring);
}

void sendmsg_test() {
    /*用户自定义消息缓冲*/
    struct mymsgbuf {
        long msgtype;
        char ctrlstring[BUF_SIZE];
    } msgbuffer;
    int qid;    /*消息队列标识符*/
    int msglen;
    key_t msgkey;

    /*获取键值*/
    if ((msgkey = ftok(PATH_NAME, PROJ_ID)) == -1) {
        perror("ftok error!\n");
        exit(1);
    }

    /*创建消息队列*/
    if ((qid = msgget(msgkey, IPC_CREAT | 0660)) == -1) {
        perror("msgget error!\n");
        exit(1);
    }

    /*填充消息结构，发送到消息队列*/
    msgbuffer.msgtype = 3;
    strcpy (msgbuffer.ctrlstring, "Hello,message queue");
    msglen = sizeof(msgbuffer) - 4;
    if (msgsnd(qid, &msgbuffer, msglen, 0) == -1) {
        perror("msgget error!\n");
        exit(1);
    }
}

void ftok_test() {
    int i;
    for (i = 1; i <= 5; i++)
        printf("key[%d] =  %ul \n", i, ftok(".", i));
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
