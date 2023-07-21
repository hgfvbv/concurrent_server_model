#include "msg.h"

int msg_create()
{
	int msgid;
	key_t key = ftok(PATHNAME, PRO_ID);
	msgid = msgget(key, 0);
	if(-1 == msgid){
		msgid = msgget(key, IPC_CREAT | 0644);
		if(-1 == msgid){
			perror("[ERROR] : msgget()");
			return -1;
		}
	}
	return msgid;
}

int msg_send(int msgid, long mtype, char *buf)
{
	int ret;
	struct msgbuf msg;
	msg.mtype = mtype;
	strcpy(msg.mtext, buf);
	return msgsnd(msgid, (const void*)&msg, strlen(msg.mtext) + 1, 0);
}

int msg_recv(int msgid, long mtype, char *buf, int len)
{
	struct msgbuf msg;
	int ret;
	ret = msgrcv(msgid, (void*)&msg, len, mtype, 0);
	if(-1 == ret){
		perror("[ERROR] msgrcv()");
		return -1;
	}
	strcpy(buf, msg.mtext);
	return ret;
}

int msg_del(int msgid)
{
	return msgctl(msgid, IPC_RMID, NULL);
}
