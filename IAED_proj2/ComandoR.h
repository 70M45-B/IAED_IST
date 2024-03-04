#ifndef _COMANDOR_
#define _COMANDOR_

/*importe das estruturas de dados, nomeadamente as carreiras e ligações*/

#include "EstruturasDados.h"

/*Declarações das funções para a remoção das carreiras do sistema*/

void removeCarreiraDaLista(listaCarreiras *lista, Carreira *carreiraAremover);

CarreiraParagem * encontraCarreiraParagem(CarreiraParagem * head,
char * nomeCarreira);

void removeCarreiraDaParagem(CarreirasParagem *lista,
CarreiraParagem *carreira);

void removeCarreiraParagens(Paragem *head ,char *nomeCarreira);

void removeCarreira(listaCarreiras *lista,Paragem *head);

/*****************************************************************************/

#endif