#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>
#include <fcntl.h>           /* For O_* constants */
#include <string.h>

#include "common.h"

typedef struct student {
	char name[32];
	int  age;
} Student;

int main(int argc, char *argv[])
{
	int shmid = shm_open("/abc", O_RDWR, 0);
	if (shmid == -1) {
		ERR_EXIT("shm_open");
	}

    struct stat buf;
    if (-1 == fstat(shmid, &buf)) {
        ERR_EXIT("fstat");
    }

    Student *stu = mmap(NULL, buf.st_size, PROT_WRITE, MAP_SHARED, shmid, 0);
    if (stu == MAP_FAILED) {
        ERR_EXIT("mmap");
    }

    strcpy(stu->name, "test");
    stu->age = 20;

	close(shmid);
	return 0;
}
