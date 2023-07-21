#ifndef __CLIENT_H__
#define __CLIENT_H__
#include "shmfifo.h"
#define TOPIC_SZ 64
#define CONTENT_SZ 64
#define BLOCK_CNT 10
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
extern void client_init();
extern void subscribe(char *topic);
extern void publish(char *topic, const char *content);
extern void *do_client_subscribe(void *arg);
#endif
