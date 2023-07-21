#include "hashmap.h"

hashtable_t **create_hashtable()
{
	hashtable_t **h = NULL;
	h = (hashtable_t**)malloc(HTABLE_LEN * sizeof(hashtable_t*));
	memset(h, 0, sizeof(HTABLE_LEN * sizeof(hashtable_t*)));
	for(int i = 0; i < HTABLE_LEN; ++i){
		h[i] = NULL;
	}
	return h;	
}

void insert_data_hash(hashtable_t **h, char *key, datatype_t value)
{
	hashtable_t *temp = NULL;
	hashtable_t **p = NULL;
	int index = 0;
	int code = 0;
	code = hashcode(key);
	index = code % HTABLE_LEN;
	for(p = &p[index]; *p != NULL; p = &((*p)->next)){
		if((*p)->data.pid > value.pid)
			break;
	}
	temp = (hashtable_t*)malloc(sizeof(hashtable_t));
	temp->data = value;
	temp->next = *p;
	*p = temp;
}

void printf_hash_table(hashtable_t **h)
{
	hashtable_t **p = NULL;
	for(int i = 0; i < HTABLE_LEN; ++i){
		printf("index = %d : ", i);
		for(p = &p[i]; p != NULL; p = &((*p)->next)){
			printf("%s\n", (*p)->data.topic);
		}
		putchar('\n');
	}
}

int search_hash_table(hashtable_t **h, char *key, pid_t result[])
{
	int code = hashcode(key);
	int cnt = 0;
	int index = code % HTABLE_LEN;
	hashtable_t **p = NULL;
	printf("index = %d\n", index);
	for(p = &p[index]; p != NULL; p = &((*p)->next)){
		printf("key : %s, (*p)->data.topic : %s\n", key, (*p)->data.topic);
		if(strcmp(key, (*p)->data.topic) == 0)
			result[cnt++] = (*p)->data.pid;
	}
	return cnt;
}

int hashcode(const char *string)
{
	int hashcode = 0;
	while(*string)
		hashcode += *string++;
	return hashcode;
}
