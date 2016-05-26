/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef ipc_shm_h
#define ipc_shm_h

//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

int IPC_CreateShm(char *fileseedfile, int shmsize, int *shmhdl);

int IPC_MapShm(int shmhdl, void **mapaddr);

int IPC_UnMapShm(void *unmapaddr);

int IPC_DelShm(int shmhdl);

#ifdef __cplusplus
}
#endif

#endif //ipc_shm_h


