
#ifndef _LE_INPUT_
#define _LE_INPUT_

/*Declaração das funções usadas para ler o input*/

int leEspacos();

void * mallocTrue(size_t size);

void * reallocTrue(void *ptr, size_t size);

void leNome(char **nome);

void leAteFinalLinha(char s[]);

/************************************************/

#endif