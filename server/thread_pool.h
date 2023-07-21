#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct tpool_task
{
	void(*function)(void *arg);
	void *arg;
}tpool_task_t;

typedef struct tpool
{
	tpool_task_t *tp_task;
	int tp_qcapacity;
	int tp_qsize;
	int tp_qfront;
	int tp_qrear;
	pthread_t *tp_work_threads_ids;
	int tp_number_of_threads;
	pthread_mutex_t tp_mutex_pool;
	pthread_cond_t tp_cond_empty;
	pthread_cond_t tp_cond_full;
	bool tp_shutdown;
}tpool_t;

extern tpool_t *thread_pool_init(int cnt, int queuesize);
extern void thread_pool_add_task(tpool_t *pool, void (*task)(void *arg), void *arg);
extern int thread_pool_destroy(tpool_t *pool);
void *tp_worker(void *arg);
#endif
