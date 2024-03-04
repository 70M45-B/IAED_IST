/*Ficheiro que contém as funções utilizadas para o bom funcionamento
do fluxo de carreiras do programa*/

/*inclusão dos ficheiros necessários às funções das carreiras*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constantes.h"
#include "le_input.h"
#include "EstruturasDados.h"
#include "Paragens.h"
#include "Carreiras.h"
#include "Ligacoes.h"
/*****************************************************************************/

/* Verifica se a string é um prefixo de tamanho pelo menos 3 da
palavra inverso. */

int eh_inverso(char * word)
{
    int len_s = strlen(word);
    int len_inv = strlen("inverso");
    /*Restringe a abreviatura de 3 a 7 letras*/
    if(len_s >= 3 && len_s <= len_inv) 
    {
    /*Se a palavra word for igual às n(len_s) primeiras letras de inverso,
    retorna verdade*/
        if(strncmp("inverso", word, len_s) == 0)
            return VERDADE;
    }
    return FALSO;
}
/*****************************************************************************/


/*Cria a lista de Carreiras e incializa os seus campos*/

listaCarreiras * cria_listaCarreiras()
{
    listaCarreiras *lista = NULL;
    lista = (listaCarreiras*) mallocTrue(sizeof(listaCarreiras));
    lista->head = NULL;
    lista->last = NULL;
    lista->num_Carreiras = 0;
    return lista;
}
/*****************************************************************************/


/*Mostra todas as carreiras já fornecidas pelo input*/

void mostraCarreiras(Carreira *head) {
    Carreira *temp = NULL;
    size_t numLigacoes = 0;

    for(temp = head; temp != NULL; temp = temp->next)
    {   /*teste prático*/
        if(strlen(temp->nome) < 6) {
            numLigacoes= temp->numLigacoes;
            printf("%s ", temp->nome);
            /*Só se numLigacoes > 1 é que existem paragem de origem e de destino*/
            if (numLigacoes > 0) {
                if(temp->ligacoes->head != NULL)   
                    printf("%s %s ", temp->ligacoes->head->p_Origem,
                    temp->ligacoes->last->p_Destino);
                printf("%ld ", numLigacoes+1);
                printf("%.2f ", temp->custoTotal);
                printf("%.2f\n", temp->duracaoTotal);
            }
            else 
                printf("%ld %.2f %.2f\n",numLigacoes, 0.0, 0.0);
        }
    }
}
/*****************************************************************************/


/*Lista todas as paragens de uma carreira através das suas ligações*/

void mostraLigacoesCarreira(Carreira * carreira, int inverso)
{   
    Ligacao *temp;
    int numLigacoes = carreira->numLigacoes;
/*No caso de não haverem paragens a mostrar (0 ligações)*/
    if (numLigacoes == 0) 
        return;
    if (inverso == FALSO) { /*Lista as paragens em que a carreira pára*/
        
        for(temp = carreira->ligacoes->head; temp != NULL; temp = temp->next)
            printf("%s, ",temp->p_Origem);

        printf("%s\n", carreira->ligacoes->last->p_Destino);
        
    }
    else { /*Lista as paragens em que a carreira para*/
        for(temp = carreira->ligacoes->last; temp != NULL; temp = temp->prev)
            printf("%s, ",temp->p_Destino);
        printf("%s\n", carreira->ligacoes->head->p_Origem);
    }
}
/*****************************************************************************/


/*Função que encontra uma carreira na lista das carreiras*/

Carreira * encontraCarreira(Carreira * head, char * nomeCarreira) 
{    
    Carreira * temp = head;
    while (temp != NULL)
    {   
        /*Se o nomeCarreira for igual ao nome da carreira para o qual temp 
        aponta, devolve essa carreira*/
        if (strcmp(nomeCarreira, temp->nome) == 0) return temp;
        temp = temp->next;
    }
    /*Se não encontrar devolve NULL*/
    return NAO_ENCONTRADO;
}
/*****************************************************************************/


/*Verifica se uma determinada paragem existe no percurso de uma carreira*/

int encontraParagemCarreira(Carreira * carreira, char * nomeParagem) 
{
    Ligacao *temp = NULL;
/*Se não existirem ligações não existem paragens, sai da função*/
    if (carreira->numLigacoes == 0) 
        return NAO_EXISTE;
    /*De modo a evitar o loop, se a última paragem corresponder à procurada
    devolve logo 1*/
    if(strcmp(carreira->ligacoes->last->p_Destino,nomeParagem) == 0)
        return EXISTE;
    temp = carreira->ligacoes->head;
    while(temp != NULL){
        if(strcmp(nomeParagem,temp->p_Origem) == 0)
            return EXISTE;
        temp = temp->next;
        }
    return NAO_EXISTE;        
}
/*****************************************************************************/


/*Função que inicializa todos os valores de uma estrutura carreira e atribui
 o nome recebido ao campo nome da estrutura*/

Carreira * criaCarreira(char *nomeCarreira) 
{
    size_t length_nome = strlen(nomeCarreira)+1;
    Carreira *nova_carreira = NULL;
    /*Alocação do espaço para a estrutura Carreira*/
    nova_carreira = (Carreira*) mallocTrue(sizeof(Carreira));

    nova_carreira->nome = NULL;
    nova_carreira->nome = (char*) mallocTrue(length_nome);
    strcpy(nova_carreira->nome, nomeCarreira);
    /*inicialização das variáveis numéricas*/
    nova_carreira->custoTotal = 0.0;
    nova_carreira->duracaoTotal = 0.0;
    nova_carreira->numLigacoes = 0;

    /*inicialização dos ponteiros da nova carreira*/
    nova_carreira->prev = NULL;
    nova_carreira->next = NULL;
    /*Criação da lista das ligações da carreira*/
    nova_carreira->ligacoes = cria_listaLigacoes();

    return nova_carreira;
}
/*****************************************************************************/

/*Adiciona uma carreira à lista das carreiras*/

void adiciona_carreira(listaCarreiras * lista,char *nome)
{
    Carreira *novaCarreira = criaCarreira(nome);

    if(lista != NULL)
    {   
        /*no caso de ainda não haverem paragens*/
        if (lista->head == NULL) { 
            lista->head = novaCarreira;
            
        }
        /*adiciona a carreira depois do último elemento da lista e atualiza
        o ponteiro anterior*/
        else { 
            lista->last->next = novaCarreira;
            novaCarreira->prev = lista->last;
            
        }
        /*atualiza o ponteiro last*/
        lista->last = novaCarreira;
    }
    lista->num_Carreiras++;
}
/*****************************************************************************/

/*Função auxiliar que incrementa os campos numéricos de uma carreira*/

void incrementaCamposCarreira( Carreira * carreira, double custo, double duracao)
{
        carreira->numLigacoes++;
        carreira->custoTotal += custo;
        carreira->duracaoTotal += duracao;
}
/*****************************************************************************/


/* Função para tratar do comando 'c'. */

void carreiras(listaCarreiras * lista_carreiras) {

    char *nome = NULL, *palavra = NULL;
    Carreira *temp = NULL;
    int fimLinha = leEspacos();
    /*No caso de não haverem argumentos depois do c*/
    if (!fimLinha) {
        
        if(lista_carreiras->num_Carreiras > 0){
            if(lista_carreiras->head != NULL) 
            mostraCarreiras(lista_carreiras->head);
        }
        return;
    }

    leNome(&nome);
    fimLinha = leEspacos();
    /*No caso de haver um argumento*/
    if (!fimLinha) {
        /*Se a carreira com o nome não existir, é adicionada*/
        if ((temp = encontraCarreira(lista_carreiras->head,nome)) == NAO_ENCONTRADO)
            adiciona_carreira(lista_carreiras,nome);
        else /*Senão mostra as paragens da carreira por ordem*/
            mostraLigacoesCarreira(temp, FALSO);
    }
    /*No caso de haverem 3 argumentos*/
    else {

        if ((temp = encontraCarreira(lista_carreiras->head,nome))){
            
            leNome(&palavra);
            /*Se a palavra for uma abreviatura de "inverso"*/
            if (eh_inverso(palavra)){
                mostraLigacoesCarreira(temp, VERDADE);
                free(palavra);
            }
            /*Caso contrário levanta erro*/
            else{ 
                printf("incorrect sort option.\n");
                free(palavra);
            }
        }
    }
    free(nome); 
}
/*****************************************************************************/


/*Função que liberta toda a memória associada a uma carreira*/

void freeCarreira(Carreira *carreira)
{   
    /*Ponteiro provisório*/
    Ligacao *ptr_l;

    if(carreira != NULL) {
        
        if(carreira->ligacoes != NULL){
            /*Se a carreira e a lista de ligações não for nula*/
            ptr_l = carreira->ligacoes->head;
            while (ptr_l != NULL){
                /*ponteiro que vai guardar o ponteiro seguinte de ptr_l de modo
                a ser possível percorrer a lista depois do free do ptr_l*/
                Ligacao *ptr_l_next = ptr_l->next;
                /*Para cada ligação vai apagar os nomes das paragens
                origem e destino*/
                free(ptr_l->p_Destino);
                free(ptr_l->p_Origem);
                free(ptr_l);
                /*ptr_l passa à próxima ligação*/
                ptr_l = ptr_l_next;
            }
            /*Liberta a lista das ligações da carreira*/
            free(carreira->ligacoes);
        }
        /*liberta o nome da carreira e a carreira*/
        free(carreira->nome);
        free(carreira);
    }
}
/*****************************************************************************/

/*Função geral para remover todos os dados de todas as carreiras recorrendo à 
função particular freeCarreira para a liberação dos dados de cada carreira*/

void freeCarreiras(listaCarreiras *lista)
{   
    Carreira *ptr = NULL;
    if(lista != NULL){
        ptr = lista->head;
        while(ptr != NULL){
            /* salva o ponteiro para a próxima carreira*/
            Carreira *ptr_next = ptr->next;
            freeCarreira(ptr);
            ptr = ptr_next;
        }
        /*liberta a lista depois de ter libertado tudo o resto*/
        free(lista);
    }
}
/*****************************************************************************/
