/****************************************************************************
**
**  Copyright (C) 2017 liushixiongcpp@163.com
**  All rights reserved.
**
****************************************************************************/

#include "sharememory.h"

#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

// void *mmap(void *addr, size_t length, int prot, int flags,
//                        int fd, off_t offset);
// int munmap(void *addr, size_t length);

typedef struct stu
{
    char name[4];
    int age;
} STU;

int read_mmap(const char *filename);
int creat_mmap(const char *filename);

int main(int argc, char *argv[])
{

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return -1;
    }

    int opt     = -1;
    int iscreat = -1;
    int isread  = -1;
    int isdel   = -1;
    char filebuf[1024] = {0};
    while (1) {
        // c create r read d delte f send message 
        opt = getopt(argc, argv, "c:r:df:");
        if (opt == '?') {
            exit(EXIT_FAILURE);
        } else if (opt == -1) {
            break;
        }

        switch (opt) {
            case 'c':
                iscreat = 0;
                if (NULL != optarg) {
                    sscanf(optarg, "%s", filebuf);
                }
                break;
            case 'r':
                isread  = 0;
                if (NULL != optarg) {
                    sscanf(optarg, "%s", filebuf);
                }
                break;
            case 'f':
                if (NULL != optarg) {
                    sscanf(optarg, "%s", filebuf);
                }
                break;
            case 'd':
                isdel = 0;
                break;
            default:
                break;
        }
    }

    if (0 == iscreat) {
        creat_mmap(filebuf);
    }

    if (0 == isread) {
        read_mmap(filebuf);
    }

    if (0 == isdel) {
        unlink("./test.mmap");
    }

    return 0;
}

int read_mmap(const char *filename)
{
    if (NULL == filename) {
        return -1;
    }

    int fd = open(filename, O_RDWR);
    if (fd < 0) {
        ERR_EXIT("open");
    }

    STU *p = mmap(NULL, sizeof(STU)*5
                        , PROT_READ | PROT_WRITE
                        , MAP_SHARED
                        , fd
                        , 0);    

    if (NULL == p) {
        ERR_EXIT("mmap");
    }

    int i = 0;
    for (; i<10; ++i) {
        printf("name:%s, age:%d\n", (p+i)->name, (p+i)->age);
    }
   
    munmap(p, sizeof(STU)*5); 

    return 0;
}

int creat_mmap(const char *filename)
{
    int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0666);
    if (fd < 0) {
        ERR_EXIT("open");
    }

    lseek(fd, sizeof(STU)*5-1, SEEK_SET);
    write(fd, "", 1);

    STU *p = (STU *)mmap(NULL, sizeof(STU)*5
                , PROT_READ | PROT_WRITE
                , MAP_SHARED
                , fd, 0);

    if (NULL == p) {
        ERR_EXIT("mmap");
    }

    int i   = 0;
    char ch = 'a';
    // 如果文件没有关闭，超过文件的大小，读端还是可以读取比文件大小大的数据
    // 这是因为内存分配是以一个页为单位（一般为4k）不足一页还是分配一页大小
    for (; i<10; ++i) {
        memcpy((p+i)->name, &ch, 1);
        (p+i)->age = 20+i;
        ++ch;
    }

    printf("initalize over\n");

    sleep(10);
    munmap(p, sizeof(STU)*5);

    printf("exit\n");

    return 0;
}
