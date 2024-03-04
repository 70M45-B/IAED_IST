#ifndef _PARAGENS_
#define _PARAGENS_

#include "EstruturasDados.h"


/*Declaração das funções que trabalham com paragens*/

listaParagens * cria_listaParagens();

CarreirasParagem * criaListaCarreirasParagem();

void mostraParagens(Paragem *head);

Paragem * encontraParagem(Paragem * head, char * nomeParagem);

Paragem * criaParagem(char *nome, double latitude, double longitude);

void adiciona_paragem(listaParagens * lista,char *nome, double latitude, double longitude);

void paragens(listaParagens * lista);

void freeParagem(Paragem *paragem);

void freeParagens(listaParagens * lista);

CarreiraParagem * criaCarreiraParagem(char *nomeCarreira);

/*****************************************************************************/

#endif

