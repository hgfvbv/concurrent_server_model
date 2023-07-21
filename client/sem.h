#ifndef __SEM_H__
#define __SEM_H__
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#define SEM_PATHNAME "."
#define SEM_PROJID 10
extern int sem_create(int nsems, unsigned short values[]);
extern int sem_p(int semid, int semnum);
extern int sem_v(int semid, int semnum);
extern int sem_del(int semid);
#endif
