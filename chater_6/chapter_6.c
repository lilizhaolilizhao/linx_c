//
// Created by oneapm on 2019-08-22.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <zconf.h>
#include <errno.h>

void my_chomod(int argc, char **argv);

void my_create();

void my_rwl();

int my_read(int fd);

void my_err(const char *err_string, int line);

int main(int argc, char **argv) {
//    my_chomod(argc, argv);
//    my_create();
    my_rwl();
}

void my_rwl() {
    int fd;
    char write_buf[32] = "Hello World!";

    /*在当前目录下创建文件example_63.c*/
    if ((fd = open("example_63.c", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) == -1) {
        my_err("open", __LINE__);
    } else {
        printf("create file success\n");
    }

    /*写数据*/
    if (write(fd, write_buf, strlen(write_buf)) != strlen(write_buf)) {
        my_err("write", __LINE__);
    }

    my_read(fd);

    /*演示文件的间隔*/
    printf("/*--------------------*/\n");
    if (lseek(fd, 10, SEEK_END) == -1) {
        my_err("lseek", __LINE__);
    }
    if (write(fd, write_buf, strlen(write_buf)) != strlen(write_buf)) {
        my_err("write", __LINE__);
    }

    my_read(fd);

    close(fd);
}

/*自定义的错误处理函数*/
void my_err(const char *err_string, int line) {
    fprintf(stderr, "line:%d  ", line);
    perror(err_string);
    exit(1);
}

/*自定义的读数据函数*/
int my_read(int fd) {
    int len;
    int ret;
    int i;
    char read_buf[64];

    if (lseek(fd, 0, SEEK_END) == -1) {
        my_err("lseek", __LINE__);
    }
    if ((len = lseek(fd, 0, SEEK_CUR)) == -1) {
        my_err("lseek", __LINE__);
    }
    if ((lseek(fd, 0, SEEK_SET)) == -1) {
        my_err("lseek", __LINE__);
    }

    printf("len:%d\n", len);
    /*读数据*/
    if ((ret = read(fd, read_buf, len)) < 0) {
        my_err("read", __LINE__);
    }

    for (i = 0; i < len; i++) {
        printf("%c", read_buf[i]);
    }
    printf("\n");

    return ret;
}

void my_create() {
    int fd;

    if ((fd = open("lilizhao.c", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR)) == -1) {
        perror("open");
        exit(1);
    } else {
        printf("create file success\n");
    }

    close(fd);
}

void my_chomod(int argc, char **argv) {
    int mode;    // 权限
    int mode_u;    // 所有者的权限
    int mode_g;    // 所属组的权限
    int mode_o;    // 其他用户的权限
    char *path;

    /*检查参数个数的合法性*/
    if (argc < 3) {
        printf("%s <mode num> <target file>\n", argv[0]);
        exit(0);
    }

    /*获取命令行参数*/
    mode = atoi(argv[1]);
    if (mode > 777 || mode < 0) {
        printf("mode num error!\n");
        exit(0);
    }

    mode_u = mode / 100;
    mode_g = (mode - (mode_u * 100)) / 10;
    mode_o = mode - (mode_u * 100) - (mode_g * 10);
    mode = (mode_u * 8 * 8) + (mode_g * 8) + mode_o;    // 八进制转换
    path = argv[2];

    if (chmod(path, mode) == -1) {
        perror("chmod error");
        exit(1);
    }
}
