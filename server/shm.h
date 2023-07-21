#ifndef __SHM_H__ 
#define __SHM_H__ 
#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_PATHNAME "../shm"
#define SHM_PROJID 10
enum shm_creat_status{
	SHM_HAS_EXIST = 0,
	SHM_CREAT_NEW,
	SHM_CREAT_ERROR,
};

extern enum shm_creat_status shm_create(size_t size, int *pshmid);
extern void *shm_at(int shmid);
extern int shm_dt(const void *shmaddr);
extern int shm_del(int shmid);
#endif
