#include "client.h"
#include "shmfifo.h"
#include "msg.h"
#include <pthread.h>

static shm_fifo_t *g_shmfifo = NULL;
static int g_msgid = 0;
void client_init()
{
	g_shmfifo = shmfifo_init(BLOCK_CNT, sizeof(packet_t));	
	g_msgid = msg_create();
}

void subscribe(char *topic)
{
	packet_t packet;
	int err;
	pthread_t tid;
	err = pthread_create(&tid, NULL, do_client_subscribe, NULL);
	if(err != 0){
		fprintf(stderr, "[ERROR] : pthread_create(): %s\n", strerror(err));
		return;
	}
	pthread_detach(tid);
	strcpy(packet.topic, topic);
	packet.pid = getpid();
	packet.mode = SUBSCRIBE;
	shmfifo_put(g_shmfifo, &packet);
}

void publish(char *topic, const char *content)
{
	packet_t packet;
	strcpy(packet.topic, topic);
	strcpy(packet.content, content);
	packet.pid = getpid();
	packet.mode = PUBLISH;
	shmfifo_put(g_shmfifo, &packet);
}

void *do_client_subscribe(void *arg)
{
	char buffer[64] = {0};
	while(1){
		memset(buffer, 0, sizeof(buffer));
		msg_recv(g_msgid, getpid(), buffer, 64);
	       	printf("< message > : %s\n", buffer);
	}	
}
