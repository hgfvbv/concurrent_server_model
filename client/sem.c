#include "sem.h"

union semun
{
	unsigned short *array;
};
int sem_create(int nsems, unsigned short valuse[])
{
	key_t key;
	key = ftok(SEM_PATHNAME, SEM_PROJID);
	if(-1 == key){
		perror("[ERROR] : ftok_sem()");
		return -1;
	}
	int semid = semget(key, nsems, IPC_CREAT | 0644);
	if(-1 == semid){
		perror("[ERROR] : semget()");
		return -1;
	}
	union semun s;
	s.array = valuse;
	int ret;
	ret = semctl(semid, 0, SETALL, s);
	if(-1 == ret){
		perror("[ERROR] : semctl()");
		return -1;
	}
	return semid;
}

int sem_p(int semid, int semnum)
{
	struct sembuf sops;
	sops.sem_num = semnum;
	sops.sem_op = -1;
	// sops.sem_flg = SEM_UNDO;
	return semop(semid, &sops, 1);
}

int sem_v(int semid, int semnum)
{
	struct sembuf sops;
	sops.sem_num = semnum;
	sops.sem_op = 1;
	// sops.sem_flg = SEM_UNDO;
	return semop(semid, &sops, 1);
}

int sem_del(int semid)
{
	return semctl(semid, 0, IPC_RMID, NULL);
}
