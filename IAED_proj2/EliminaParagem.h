#ifndef _ELIMINAPARAGEM_
#define _ELIMINAPARAGEM_

/*importe das estruturas de dados*/

#include "EstruturasDados.h"

/*Declarações das funções para a eliminação das paragens do sistema*/

void removeParagemDaLista(listaParagens *lista, char *nomeParagem);

void eliminaParagemFinalCarreira(Carreira *carreira);

void eliminaParagemInicioCarreira(Carreira *carreira);

void colapsaLigacoesCarreira(char *nomeParagem, Carreira *carreira);

void eliminaParagem(listaParagens *lista_p, listaCarreiras *lista_c);

/*****************************************************************************/

#endif