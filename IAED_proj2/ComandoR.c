/*Ficheiro que contém as funções utilizadas para o correto funcionamento
da remoção de carreiras do programa*/

/*inclusão dos ficheiros necessários às funções presentes abaixo*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constantes.h"
#include "le_input.h"
#include "EstruturasDados.h"
#include "Paragens.h"
#include "Carreiras.h"
#include "Ligacoes.h"
#include "ComandoR.h"

/*****************************************************************************/




/*Função que remove uma determinada carreira da lista de carreiras*/

void removeCarreiraDaLista(listaCarreiras *lista, Carreira *carreiraAremover)
{   
    /*No caso de não haver nada a remover*/
    if(lista == NULL || carreiraAremover == NULL)
        return;
    /*No caso de existir um elemento anterior, atualiza o seu ponteiro next de
    modo a "saltar" a carreira a remover*/
    if(carreiraAremover->prev != NULL)
        carreiraAremover->prev->next = carreiraAremover->next;
    /*Senão é porque é a cabeça, basta atualizá-la*/
    else
        lista->head = carreiraAremover->next;
    /*No caso de existir um elemento seguinte, atualiza o seu ponteiro prev de
    modo a "saltar" a carreira a remover*/
    if(carreiraAremover->next != NULL)
        carreiraAremover->next->prev = carreiraAremover->prev;

    /*Senão é porque é a cabeça, basta atualizá-la*/
    else
        lista->last = carreiraAremover->prev;
}

/*****************************************************************************/

/*Função que encontra uma Carreira que para numa paragem recebendo a lista de 
carreiras que passam na paragem e o nome da carreira*/

CarreiraParagem * encontraCarreiraParagem(CarreiraParagem * head, char * nomeC) 
{    
    CarreiraParagem * temp = head;
    while (temp != NULL)
    {
        if (strcmp(nomeC, temp->nome) == 0) return temp;
        temp = temp->next;
    }
    return NAO_ENCONTRADO;
}

/*****************************************************************************/


/*Função que remove uma carreira da lista de carreiras da paragem*/

void removeCarreiraDaParagem(CarreirasParagem *lista,CarreiraParagem *carreira)
{   
    /*No caso de não haver nada a remover*/
    if(lista == NULL || carreira == NULL)
        return; 
    /*Atualiza o ponteiro next do elemento anterior*/
    if(carreira->prev != NULL)
        carreira->prev->next = carreira->next;
    /*No caso de o nó a remover ser a cabeça da lista, a cabeça passa 
    a ser o elemento seguinte*/
    else 
        lista->head = carreira->next;

    /*No caso de a carreira seguinte não ser nula, atualiza o seu ponteiro
    anterior para saltar a carreira a remover*/
    if(carreira->next != NULL)
        carreira->next->prev = carreira->prev;

    /*No caso de ser a última carreira basta apontar o last para a anterior*/
    else
        lista->last = carreira->prev;
    /*Liberta a informação da carreira removida*/
    free(carreira->nome);
    free(carreira);
}

/*****************************************************************************/


/*Função que remove a carreira com nome 'nomeCarreira' de todas as paragens*/

void removeCarreiraParagens(Paragem *head ,char *nomeCarreira)
{   
    Paragem *temp = NULL;
    CarreiraParagem * carreiraParagem = NULL;
    for(temp = head; temp != NULL; temp = temp->next)
    {   /*Para cada paragem passada por temp, vai remover a carreira se 
        esta existir, decrementando o seu valor*/
        if((carreiraParagem 
        = encontraCarreiraParagem(temp->CarreirasParagem->head,nomeCarreira))
        != NAO_ENCONTRADO) {
            removeCarreiraDaParagem(temp->CarreirasParagem,carreiraParagem);
            temp->numCarreiras--;
        }
    }
}

/*****************************************************************************/



/*Função que trata do comando 'r' ao recorrer a todas as funções acima 
definidas para remover a presença de uma carreira no sistema*/

void removeCarreira(listaCarreiras *lista,Paragem *head)
{   char *nomeCarreira = NULL;
    Carreira * carreira = NULL;
    
    leEspacos();
    leNome(&nomeCarreira);
    /*No caso de não haver carreira sai da função com erro e liberta o nome*/
    if((carreira = encontraCarreira(lista->head,nomeCarreira)) == NULL) {
        printf("%s: no such line.\n",nomeCarreira);
        free(nomeCarreira);
        return;
    }
    /*Remove a carreira da lista de carreiras do sistema*/
    removeCarreiraDaLista(lista,carreira);
    freeCarreira(carreira);
    /*Decrementa o número de carreiras*/
    lista->num_Carreiras--;
    
    /*Remove a carreira da lista de carreiras de cada paragem*/
    removeCarreiraParagens(head,nomeCarreira);
    free(nomeCarreira);
}

/*****************************************************************************/