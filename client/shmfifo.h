#ifndef __SHMFIFO_H__
#define __SHMFIFO_H__
#include <string.h>
#include <sys/wait.h>
#include "shm.h"
#include "sem.h"
#define SEM_EMPTY_ID 0
#define SEM_FULL_ID 1
#define SEM_MUTEX_ID 2

typedef struct shm_head{
	int rpos;
	int wpos;
	int blocks;
	int blksz;
	int semid;
}shm_head_t;
typedef struct shm_fifo{
	shm_head_t *p_head;
	char *p_payload;
}shm_fifo_t;

extern shm_fifo_t *shmfifo_init(int blocks, int blksz);
extern void shmfifo_destroy(shm_fifo_t *fifo);
extern void shmfifo_put(shm_fifo_t *fifo, const void *buf);
extern void shmfifo_get(shm_fifo_t *fifo, void *buf);
#endif
