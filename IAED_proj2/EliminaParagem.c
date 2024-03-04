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
#include "EliminaParagem.h"

/*****************************************************************************/

/*Função que remove uma Paragem da lista de paragens do sistema*/

void removeParagemDaLista(listaParagens *lista,char *nomeParagem)
{   
    Paragem *ParagemAremover = NULL;
    /*No caso de não haver lista ou o nome ser nulo*/
    if(lista == NULL || nomeParagem == NULL) {
        printf("%s: no such stop.\n",nomeParagem);
        return;
    }
    ParagemAremover = encontraParagem(lista->head,nomeParagem);

    /*Se a paragem não existir*/
    if(ParagemAremover == NAO_ENCONTRADO) {
        printf("%s: no such stop.\n",nomeParagem);
        return;
    }
    else {
    /*Se houver um elemento anterior ao que vamos remover atualizamos o seu 
    ponteiro next para o ponteiro next da paragem a remover de modo a saltar a paragem*/
    if(ParagemAremover->prev != NULL)
        ParagemAremover->prev->next = ParagemAremover->next;

    /*Se não tem anterior é porque é a cabeça, logo atualiza-se a cabeça*/
    else 
        lista->head = ParagemAremover->next;
    
    /*mesma lógica mas para o elemento seguinte seguinte*/
    if(ParagemAremover->next != NULL)
        ParagemAremover->next->prev = ParagemAremover->prev;

    /*Se não houver seguinte é porque é o último*/
    else 
        lista->last = ParagemAremover->prev;
    }
    freeParagem(ParagemAremover);
}

/*****************************************************************************/


/*Função que elimina a última paragem, encurtando o percurso*/

void eliminaParagemFinalCarreira(Carreira *carreira)
{
    Ligacao *noAremover = NULL;
    noAremover = carreira->ligacoes->last;

    /*Retira o tempo e custo da ligação, por ser um dos extremos*/
    
    carreira->custoTotal -= noAremover->custo;
    carreira->duracaoTotal -= noAremover->duracao;

    /*No caso da ligação ser a única da lista,a lista é libertada e fica nula*/
    if(noAremover->prev == NULL) {
        carreira->ligacoes->last = NULL;
        free(carreira->ligacoes);
        carreira->ligacoes = NULL;
    }

    
    else {
        /*atualiza o último da lista para o anterior ao nó a remover*/
        carreira->ligacoes->last = noAremover->prev;
        carreira->ligacoes->last->next = NULL; /*o seguinte ao último é nulo*/
    }
    /*liberta o espaço da ligação*/
    free(noAremover->p_Destino);
    free(noAremover->p_Origem);
    free(noAremover);
}

/*****************************************************************************/

/*Função que elimina a pimeira paragem da carreira*/

void eliminaParagemInicioCarreira(Carreira *carreira)
{   
        Ligacao *newHead = carreira->ligacoes->head->next;
        /*O nó anterior à nova cabeça passa a ser nulo*/
        if(newHead != NULL)     
            newHead->prev = NULL;

        /*Retira o custo e duração da ligação removida*/
        carreira->custoTotal -= carreira->ligacoes->head->custo;
        carreira->duracaoTotal -= carreira->ligacoes->head->duracao;

        /*liberta memória da antiga cabeça*/
        free(carreira->ligacoes->head->p_Origem);
        free(carreira->ligacoes->head->p_Destino);
        free(carreira->ligacoes->head); 

        /*atualiza o ponteiro da cabeça para o novo nó da cabeça */
        carreira->ligacoes->head = newHead;

}

/*****************************************************************************/

/*Função que transforma duas ligações numa ao passar o nome da paragem de 
destino da ligação a remover para o nome da paragem de destino da ligação 
anterior*/

void colapsaLigacoesCarreira(char *nomeParagem,Carreira *carreira)
{   
    /*servirão de ligação atual e seguinte no loop*/
    Ligacao *temp = NULL, *temp_next = NULL; 

    for(temp = carreira->ligacoes->head; temp != NULL; temp = temp_next) { 
        temp_next = temp->next;
        /*Se a paragem origem da ligação for a paragem a remover*/
        if(strcmp(nomeParagem,temp->p_Origem) == 0){
            if(temp == carreira->ligacoes->head) 
                eliminaParagemInicioCarreira(carreira);
            else {
                /*Se for a ligação a ser removida for a última, a penúltima
                passa a ser a última */
                if(temp == carreira->ligacoes->last)
                    carreira->ligacoes->last = temp->prev;

                /*Atualiza os ponteiros para "saltar" a ligação atual*/    
                temp->prev->next = temp->next;
                if (temp->next != NULL)
                    temp->next->prev = temp->prev;

                /*A paragem destino da ligação prev, igual à paragem origem do
                elemento temp, será substituída pela paragem destino da ligação*/
                temp->prev->p_Destino = reallocTrue(temp->prev->p_Destino,
                (sizeof(char)*(strlen(temp->p_Destino)+1)));
                strcpy(temp->prev->p_Destino,temp->p_Destino);
                /*Soma o custo e duração da ligação removida à ligação anterior*/
                temp->prev->custo += temp->custo;
                temp->prev->duracao += temp->duracao;
                /*Toda a informação da ligação a remover é libertada*/
                free(temp->p_Destino);
                free(temp->p_Origem);
                free(temp);
            }
        /*diminui o número de ligações da carreira*/
        carreira->numLigacoes --;
        }
    } 
}

/*****************************************************************************/


/*Função que trata do comando 'e' usando as restantes funções já declaradas*/

void eliminaParagem(listaParagens *lista_p, listaCarreiras *lista_c)
{   
    char *nomeParagem = NULL;
    Carreira *temp = NULL;
    
    leEspacos();
    leNome(&nomeParagem);

    /*Começa por remover a Paragem da lista das paragens*/
    removeParagemDaLista(lista_p,nomeParagem);

    /*Se não houver nada para remover dá free ao nome e sai da função*/
    if(lista_c == NULL || lista_c->head == NULL){
        free(nomeParagem);
        return;
    }
    for(temp = lista_c->head; temp != NULL; temp = temp->next) {

        /*Se  houver pelo menos uma ligação*/
        if(temp->ligacoes != NULL && temp->ligacoes->head != NULL){ 
            /*No caso do nome da paragem ser igual à última paragem*/
            if(strcmp(nomeParagem,temp->ligacoes->last->p_Destino) == 0) {
                eliminaParagemFinalCarreira(temp);
                temp->numLigacoes--;
            }
            /*Se a paragem ainda existir na carreira*/
            if(temp->ligacoes != NULL) {
                if(temp->ligacoes->head != NULL)
                    colapsaLigacoesCarreira(nomeParagem,temp);
            }
        }
    }
    free(nomeParagem);
}

/*****************************************************************************/