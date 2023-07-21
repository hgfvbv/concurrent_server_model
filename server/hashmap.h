#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HTABLE_LEN 7

typedef struct datatype{
	char topic[32];
	pid_t pid;
}datatype_t;
typedef struct node{
	datatype_t data;
	struct node *next;
}hashtable_t;

extern hashtable_t **create_hashtable();
extern void insert_data_hash(hashtable_t **h, char *key, datatype_t value);
extern int hashcode(const char *string);
extern void printf_hash_table(hashtable_t **h);
extern int search_hash_table(hashtable_t **h, char *key, pid_t result[]);
#endif
