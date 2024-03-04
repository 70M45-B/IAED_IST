/*Ficheiro que contém as funções utilizadas para o correto funcionamento
das Paragens */

/*inclusão dos ficheiros necessários às funções presentes abaixo*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constantes.h"
#include "le_input.h"
#include "EstruturasDados.h"
#include "Paragens.h"



listaParagens * cria_listaParagens()
{
    listaParagens *lista = NULL;
    lista = (listaParagens*) mallocTrue(sizeof(listaParagens));
    lista->head = NULL;
    lista->last = NULL;
    return lista;
}    

/*****************************************************************************/

/*Aloca e inicializa a lista de carreiras de uma paragem*/

CarreirasParagem * criaListaCarreirasParagem()
{
    CarreirasParagem *lista = NULL;
    lista = (CarreirasParagem*) mallocTrue(sizeof(CarreirasParagem));
    lista->head = NULL;
    lista->last = NULL;
    return lista;
}   

/*****************************************************************************/


/*Função que cria uma estrutura do tipo CarreiraParagem para adicionar a uma
paragem consecutivamente */

CarreiraParagem * criaCarreiraParagem(char *nomeCarreira) 
{
    size_t length_nome = strlen(nomeCarreira)+1;
    CarreiraParagem *nova_carreira = NULL;
    nova_carreira = (CarreiraParagem*) mallocTrue(sizeof(CarreiraParagem));

    nova_carreira->nome = NULL;
    nova_carreira->nome = (char*) mallocTrue(length_nome);

    strcpy(nova_carreira->nome, nomeCarreira);
    
    /*inicialização dos ponteiros da nova carreira*/
    nova_carreira->next = NULL;
    nova_carreira->prev = NULL;
    return nova_carreira;
}

/*****************************************************************************/


/*Mostra todas as paragens.*/

void mostraParagens(Paragem *head) {
    Paragem *temp = head;
    while (temp != NULL)
    {
        printf("%s: %16.12f %16.12f %ld\n", temp->nome, temp->latitude, 
        temp->longitude, temp->numCarreiras);
        temp = temp->next;
    }
}

/*****************************************************************************/


/* Verifica se existe uma paragem com um determinado nome.
   Se existir devolve a paragem. Caso contrário, devolve NAO_ENCONTRADO. */

Paragem * encontraParagem(Paragem * head, char * nomeParagem) {
    Paragem * temp = head;

    while (temp != NULL)
    {
        if (strcmp(nomeParagem, temp->nome) == 0) return temp;
        temp = temp->next;
    }
    return NAO_ENCONTRADO;
}

/*****************************************************************************/


/* Cria uma nova paragem. */

Paragem * criaParagem(char *nome, double latitude, double longitude)
{   
    size_t length_s_nome = strlen(nome)+1;
    Paragem *nova_paragem = NULL;
    nova_paragem = (Paragem*) mallocTrue(sizeof(Paragem));

    nova_paragem->nome = NULL;
    nova_paragem->nome = (char*) mallocTrue(length_s_nome);

    /*Atribui os valores aos respetivos campos da paragem*/
    strcpy(nova_paragem->nome, nome);
    nova_paragem->latitude = latitude;
    nova_paragem->longitude = longitude;

    /*inicializa valores*/
    nova_paragem->numCarreiras = 0;
    nova_paragem->CarreirasParagem = criaListaCarreirasParagem();

    return nova_paragem;
}

/*****************************************************************************/


/*adiciona uma paragem no final lista de paragens*/
void adiciona_paragem(listaParagens * lista,char *nome, double latitude,
double longitude)
{
    Paragem *novaParagem = criaParagem(nome,latitude,longitude);
    /*inicialização dos ponteiros da nova paragem*/
    novaParagem->next = NULL;
    novaParagem->prev = lista->last;
    
    /*teste prático*/
    if(latitude < -90 || latitude > 90 || longitude < -180 || longitude > 180) {
        printf("invalid location.\n");
        free(novaParagem->CarreirasParagem);
        free(novaParagem->nome);
        free(novaParagem);
        return;
    }
    /*no caso de ainda não haverem paragens*/
    if (lista->head == NULL) 
        lista->head = novaParagem; 
    /*adiciona a paragem depois do último elemento da lista*/
    if(lista->last != NULL) 
        lista->last->next = novaParagem;
    lista->last = novaParagem;
}

/*****************************************************************************/


/*Função para tratar o comando 'p'.*/

void paragens(listaParagens * lista_paragens)
{
    char *nome = NULL;
    Paragem *temp = NULL;
    int fimLinha = leEspacos();

    /*No caso de receber 0 arguementos*/
    if (!fimLinha) {
        mostraParagens(lista_paragens->head);
        return;
    }
    leNome(&nome);
    fimLinha = leEspacos();

    /*No caso de receber 1 arguementos*/
    if (!fimLinha) {
        if ((temp = encontraParagem(lista_paragens->head,nome)) 
        == NAO_ENCONTRADO) {
            printf("%s: no such stop.\n", nome);
        }
        else   
            printf("%16.12f %16.12f\n", temp->latitude, temp->longitude);
    }
    /*No caso de receber 3 argumentos*/
    else {
        double latitude, longitude;
        scanf("%lf%lf", &latitude, &longitude);
        if ((temp = encontraParagem(lista_paragens->head,nome)) 
        == NAO_ENCONTRADO)
        /*Se ainda não existir é criada uma nova com os valores de input*/
            adiciona_paragem(lista_paragens,nome,latitude,longitude);

        else
            printf("%s: stop already exists.\n", temp->nome);

    }
    free(nome); 
}

/*****************************************************************************/

/*Liberta toda a informação contida por uma estrutura do tipo Paragem*/

void freeParagem(Paragem *paragem)
{
    CarreiraParagem *ptr_c = NULL;
    if(paragem != NULL) {
        if(paragem->CarreirasParagem != NULL) {
                ptr_c = paragem->CarreirasParagem->head;
                while(ptr_c != NULL){
                    CarreiraParagem *ptr_c_next = ptr_c->next;

                    /*liberta os dados da carreira da paragem ptr_c*/
                    free(ptr_c->nome);
                    free(ptr_c);
                    ptr_c = ptr_c_next;
                }
                free(paragem->CarreirasParagem);
            }
    
            free(paragem->nome);
            free(paragem);
        }
}

/*****************************************************************************/

/*Função que, recorrendo à função freeParagem, liberta toda a informação 
associada à lista de paragens do sistema */

void freeParagens(listaParagens * lista)
{   
    Paragem *ptr;
    
    if(lista != NULL){
        ptr = lista->head;
        while(ptr != NULL){
            Paragem *ptr_next = ptr->next;
            freeParagem(ptr);
            ptr = ptr_next;
        }
     free(lista);
    }
}

/*****************************************************************************/


