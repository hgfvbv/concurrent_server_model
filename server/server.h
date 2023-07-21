#ifndef __SERVER_H__
#define __SERVER_H__

#include "shmfifo.h"
#include "thread_pool.h"
#include "hashmap.h"
#define TOPIC_SZ 64
#define CONTENT_SZ 64
#define BLOCK_CNT 10
#define THREAD_CNT 10
#define TASK_CNT 10
#define RESULT_SZ 10
enum work_mode{
	PUBLISH = 0,
	SUBSCRIBE,
};
typedef struct packet{
	char topic[TOPIC_SZ];
	pid_t pid;
	enum work_mode mode;
	char content[CONTENT_SZ];
}packet_t;

extern void server_init();
extern void runloop();
extern void task_handler(void *arg);
extern void do_subscribe(char *topic, pid_t pid);
extern void do_publish(char *topic, pid_t pid, char *content);
#endif
