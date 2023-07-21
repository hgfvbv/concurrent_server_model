#include "server.h"
#include "shmfifo.h"
#include "thread_pool.h"
#include "hashmap.h"
#include "msg.h"

static shm_fifo_t *g_shmfifo = NULL;
static tpool_t *g_tpool = NULL;
static hashtable_t **g_hashtable = NULL;
static int g_msgid = 0;
void server_init()
{
	g_shmfifo = shmfifo_init(BLOCK_CNT, sizeof(packet_t));
	g_tpool = thread_pool_init(THREAD_CNT, TASK_CNT); 
	g_hashtable = create_hashtable();
	g_msgid = msg_create();
}
void runloop()
{
	packet_t *packet = NULL;
	while(1)
	{
		packet = (packet_t*)malloc(sizeof(packet_t));
		memset(packet, 0, sizeof(packet_t));
		shmfifo_get(g_shmfifo, packet);
		printf("topic: %s, pid : %d,content:%s mode : %d\n", packet->topic, packet->pid, packet->content, packet->mode);	
		thread_pool_add_task(g_tpool, task_handler, (void*)packet);
	}
}

void do_subscribe(char *topic, pid_t pid)
{
	datatype_t value;
	strcpy(value.topic, topic);
	value.pid = pid;
	insert_data_hash(g_hashtable, topic, value);
	printf_hash_table(g_hashtable);
}

void do_publish(char *topic, pid_t pid, char *content)
{
	pid_t result[RESULT_SZ];
	int ret;
	ret = search_hash_table(g_hashtable, topic, result);
	if(ret != 0){
		printf("ret = %d\n", ret);	
		for(int i = 0; i < ret; ++i){
			msg_send(g_msgid, result[1], content);
		}
	}
}

void task_handler(void *arg)
{
	packet_t *packet = (packet_t*)arg;
	if(PUBLISH == packet->mode){
		printf("publish\n");
		do_publish(packet->topic, packet->pid, packet->content);
	}else if(SUBSCRIBE == packet->mode){
		printf("subscribe\n");
		do_subscribe(packet->topic, packet->pid);
	}
}
