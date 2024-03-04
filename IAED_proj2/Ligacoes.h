#ifndef _LIGACOES_
#define _LIGACOES_

/*Importe das estruturas de dados necessárias*/

#include "EstruturasDados.h"

/*Declarações das funções*/

listaLigacoes * cria_listaLigacoes();

void adicionaCarreiraParagem(Paragem *head, char *CarreiraAadicionar,char *NomeParagem); 

Ligacao * criaLigacao(char * ParagemOrigem, char * ParagemDestino,double custo, double duracao);

void adicionaLigacaoInicio(listaLigacoes **lista,char * ParagemOrigem,
char * ParagemDestino,double custo, double duracao);

void adicionaLigacaoFim(listaLigacoes **lista,char * ParagemOrigem,
char * ParagemDestino,double custo, double duracao);

void adicionaLigacao(Carreira * carreira, Paragem * head, char * ParagemOrigem,
char * ParagemDestino,double custo, double duracao);

void leNomesComando(char **nomeCarreira, char **nomeOrigem, char **nomeDestino);

void ligacoes(listaParagens *lista_paragens, listaCarreiras *lista_carreiras);

/*****************************************************************************/

#endif
