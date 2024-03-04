/*
iaed-23
File: project1.c
Autor: Tomas Bernardino
ID: ist1107052
Descrição: Programa para gestão de uma rede de transportes públicos
*/

/*Ficheiro que contém as funções utilizadas para o correto funcionamento
do comando 'a' e da interpretação dos comandos rebidos no input*/

/*inclusão dos ficheiros necessários às funções presentes abaixo*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constantes.h"
#include "le_input.h"
#include "le_input.c"
#include "Paragens.h"
#include "Paragens.c"
#include "Carreiras.h"
#include "Carreiras.c"
#include "Ligacoes.h"
#include "Ligacoes.c"
#include "Intersecoes.h"
#include "Intersecoes.c"
#include "EstruturasDados.h"
#include "ComandoR.h"
#include "ComandoR.c"
#include "EliminaParagem.h"
#include "EliminaParagem.c"


/*Comando que liberta toda a memória do sistema ao libertar todas as carreiras
(e consecutivamente todas as ligações) e todas as paragens e suas carreiras*/

void comando_a(listaParagens *lista_p,listaCarreiras * lista_c)
{
    freeParagens(lista_p);
    freeCarreiras(lista_c);
    
}

/*****************************************************************************/

void comando_f(listaCarreiras *lista_c, listaParagens *lista_p)
{
    Carreira *temp = lista_c->head;
    char *nome = NULL;
    int controlo = 0;
    leEspacos();
    leNome(&nome);

    if(encontraParagem(lista_p->head,nome) == NULL) {
        free(nome);
        printf("%s: no such stop.\n", nome);
        return;
    }
    while(temp != NULL)
    {   
        if(temp->ligacoes != NULL && temp->ligacoes->last != NULL) {
            if(strcmp(temp->ligacoes->last->p_Destino,nome) == 0) {
                if(controlo == 0){
                    printf("%s",temp->nome);
                    controlo = 1;
                }
                else
                    printf(" %s",temp->nome);
            }
        }
        temp = temp->next;
    }
    if(controlo == 1) putchar('\n');
    free(nome);
    
}

/*Interpreta os comandos do projeto 1*/

void comandosProj1(char c, listaCarreiras *lista_c, listaParagens *lista_p)
{
    switch(c) {
        case 'c':
            carreiras(lista_c);
            break;
        case 'p':
            paragens(lista_p);
            break;
        case 'l':
            ligacoes(lista_p,lista_c);
            break;
        case 'i':
            intersecoes(lista_p->head);
            break;
        case 'q':
            comando_a(lista_p,lista_c);
	        break;
        }
}

/*****************************************************************************/

/*Interpreta os comandos do projeto 2*/

void comandosProj2(char c, listaCarreiras *lista_c, listaParagens *lista_p)
{   
    switch(c) {
        case 'r':
            removeCarreira(lista_c,lista_p->head);
            break;
        case 'e':
            eliminaParagem(lista_p,lista_c);
            break;
        case 'a':
            comando_a(lista_p, lista_c);
            break;
        }
}

/*****************************************************************************/


/*Função MAIN*/

int main() {
    int c;
    /*Cria as listas vazias de paragens e carreiras do sistema*/
    listaParagens *lista_paragens = cria_listaParagens();
    listaCarreiras *lista_carreiras = cria_listaCarreiras();
    do {
        c = getchar();

        if(c == 'c'|| c == 'p'|| c == 'l' || c == 'i' || c == 'q')
            comandosProj1(c,lista_carreiras,lista_paragens);

        else if (c == 'r'|| c == 'e')
            comandosProj2(c,lista_carreiras,lista_paragens);

        else if (c == 'a')
        {
            comandosProj2(c,lista_carreiras,lista_paragens);
            lista_paragens = cria_listaParagens();
            lista_carreiras = cria_listaCarreiras();
        }
        else if(c == 'f')
            comando_f(lista_carreiras,lista_paragens);

    } while (c != 'q');
    return 0;
}

/*****************************************************************************/

