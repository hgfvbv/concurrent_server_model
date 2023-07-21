#ifndef __MSG_H__
#define __MSG_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PATHNAME "../msg"
#define PRO_ID 10
#define MSG_SZ 64
struct msgbuf{
	long mtype;
	char mtext[MSG_SZ];
};
extern int msg_create();
extern int msg_send(int msgid, long mtype, char *buf);
extern int msg_recv(int msgid, long mtype, char *buf, int len);
extern int msg_del(int msgid);
#endif
