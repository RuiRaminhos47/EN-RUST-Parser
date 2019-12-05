#ifndef __hash_h__
#define __hash_h__
#include "ast.h"
#define HASH_SIZE 7

typedef struct record { // hashtable com o valor das variaveis
	char *variavel; 
	int valor;
	struct record *next;
} *RECORD;

RECORD table[HASH_SIZE]; // HAST TABLE 

unsigned int hash(char *s); // ir ver onde ta a variavel
RECORD lookup(char *s); // procura e retorna a posiçao na lista onde se encontra a string
void insert(char *s, int value); // insere variavel/valor na hastable
void init_table(); // limpa table

#endif