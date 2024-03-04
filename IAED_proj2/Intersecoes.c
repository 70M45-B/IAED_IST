/*Ficheiro que contém as funções utilizadas para o correto funcionamento
das interseções entre carreiras para cada paragem */

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
#include "Intersecoes.h"

/*****************************************************************************/


/*Função que ordena uma lista de carreiras pelo nome*/

void insertionSortLista(CarreirasParagem **lista) {

    /*Ponteiro para ajudar na inicialização dos restantes*/
    CarreiraParagem *inicial = NULL;
    /*Ponteiro para o nó que vai ser mudado se for necessário*/
    CarreiraParagem *atual = NULL;
    atual = (*lista)->head;
    
    inicial = (CarreiraParagem*) mallocTrue(sizeof(CarreiraParagem));
    inicial->prev = inicial->next = NULL;

    while (atual != NULL) {

        /*Guarda o ponteiro seguinte do atual pois este vai ser atualizado*/
        CarreiraParagem *temp = atual->next;

        /*prev vai guardar o último comparado com valor menor do que o atual*/
        CarreiraParagem *prev = inicial;

        /*Ponteiro para o nó que está a ser comparado com o nó 'atual'. 
        Este é atualizado e acaba por apontar para o primeiro nó cujo valor é
        maior do que o valor de 'atual'*/
        CarreiraParagem *Comparado = inicial->next;

        while (Comparado != NULL && strcmp(Comparado->nome,atual->nome) < 0) {
            prev = Comparado;
            /*Passa ao próximo para comparar se não tiver chegado ao fim*/    
            Comparado = Comparado->next;
        }
        /*Inserção do nó atual no local correto*/
        atual->next = Comparado;
        prev->next = atual;

        /*Incremento do ponteiro*/
        atual = temp;
    }
    /*Atualização da cabeça*/
    (*lista)->head = inicial->next;
    free(inicial);
}

/*****************************************************************************/

/*Função que trata do comando 'i'*/

void intersecoes(Paragem *head) {
    Paragem *temp = NULL;

    for(temp = head; temp != NULL; temp = temp->next){
        /*No caso de haverem pelo menos duas carreiras para ordenar*/
        if(temp->numCarreiras > 1){
            CarreiraParagem *ptr = NULL;
            printf("%s %ld:",temp->nome,temp->numCarreiras);

            /*Ordena a lista de carreiras da paragem apontada por 'temp'*/
            insertionSortLista(&(temp->CarreirasParagem));

            /*O loop vai imprimir todos os elementos da lista ordenada*/
            for(ptr = temp->CarreirasParagem->head;ptr != NULL; ptr = ptr->next)
                printf(" %s",ptr->nome);   

            putchar('\n');
        }  
    }
}

/*****************************************************************************/

