#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "hash.h"
#define MULTIPLIER 32
#define maxSize 20

unsigned int hash(char *s) { 
	unsigned int h;
	unsigned char *p;
	h=0;

	for(p=(unsigned char *)s; *p != '\0'; p++) {
		h = MULTIPLIER*h + *p;
	}

	return h%HASH_SIZE;
}

RECORD lookup(char *s) { 
	int index;
	RECORD p;
	index = hash(s);

	for( p=table[index]; p!=NULL; p=p->next) {
		if(strcmp(s, p->variavel)==0) return p;
	}

	return NULL;
}

void insert(char *s, int value) { 
	int index;
	RECORD p;
	p = (RECORD)malloc(sizeof(struct record));
	index = hash(s);

	p->variavel = s; 
	p->valor = value;
	p->next = table[index];
	table[index] = p;
}

void init_table() { 
	for(int i=0; i<HASH_SIZE; i++) {
		table[i] = NULL;
	}
}
