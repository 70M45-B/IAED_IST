#ifndef _CARREIRAS_
#define _CARREIRAS_

/*importe das estruturas de dados, nomeadamente as carreiras e ligações*/

#include "EstruturasDados.h"


/*Declarações das funções das carreiras*/

int eh_inverso(char *word);

listaCarreiras * cria_listaCarreiras();

void mostraCarreiras(Carreira *head);

void mostraLigacoesCarreira(Carreira *carreira, int inverso);

Carreira * encontraCarreira(Carreira *head, char *nomeCarreira);

int encontraParagemCarreira(Carreira *carreira, char *nomeParagem);

Carreira * criaCarreira(char *nomeCarreira);

void adiciona_carreira(listaCarreiras *lista,char *nome);

void incrementaCamposCarreira( Carreira *carreira, double custo, double duracao);

void carreiras(listaCarreiras *lista_carreiras);

void freeCarreira(Carreira *carreira);

void freeCarreiras(listaCarreiras *lista);

/*****************************************************************************/

#endif
