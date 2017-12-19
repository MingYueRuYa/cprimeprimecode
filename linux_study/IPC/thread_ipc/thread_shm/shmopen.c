#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>
#include <fcntl.h>           /* For O_* constants */

#include "common.h"

typedef struct student {
	char name[32];
	int  age;
} Student;

int main(int argc, char *argv[])
{
	int shmid = shm_open("/abc", O_CREAT | O_RDWR, 0666);
	if (shmid == -1) {
		ERR_EXIT("shm_open");
	}
	printf("open shm successful\n");
	
	if (-1 == ftruncate(shmid, sizeof(Student))) {
		ERR_EXIT("ftruncate");
	}

	struct stat buf;
	if (-1 == fstat(shmid, &buf)) {
		ERR_EXIT("fstat");
	}
	printf("size=%ld, mode=%o\n", buf.st_size, buf.st_mode & 0777);
	close(shmid);
	return 0;
}
