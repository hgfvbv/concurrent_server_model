#include "shm.h"

enum shm_creat_status shm_create(size_t size, int *pshmid)
{
	key_t key;
	key = ftok(SHM_PATHNAME, SHM_PROJID);
	if(-1 == key){
		perror("[ERROR] : ftok_shm()");
		return SHM_CREAT_ERROR;
	}
	int shmid;
	shmid = shmget(key, size, 0);
	if(-1 == shmid){
		shmid = shmget(key, size, IPC_CREAT | 0644);
		if(-1 == shmid){
			perror("[ERROR] : shmget()");
			return SHM_CREAT_ERROR;
		}
		*pshmid = shmid;
		return SHM_CREAT_NEW;
	}else{
		*pshmid = shmid;
		return SHM_HAS_EXIST;
	}
}

void *shm_at(int shmid)
{
	void *addr = NULL;
	addr = shmat(shmid, NULL, 0);
	if((void*)-1 == addr)
	{
		perror("[ERROR] : shmat()");
		return NULL;
	}
	return addr;
}

int shm_dt(const void *addr)
{
	return shmdt(addr);
}

int shm_del(int shmid)
{
	return shmctl(shmid, IPC_RMID, NULL);
}
