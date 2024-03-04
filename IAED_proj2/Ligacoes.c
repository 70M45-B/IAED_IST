/*Ficheiro que contém as funções utilizadas para o correto funcionamento
das ligações entre paragens para cada carreira */

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

/*****************************************************************************/


/*Função que inicializa os valores de uma lista de ligações*/

listaLigacoes * cria_listaLigacoes()
{
    listaLigacoes *lista = NULL;
    lista = (listaLigacoes*) mallocTrue(sizeof(listaLigacoes));
    lista->head = NULL;
    lista->last = NULL;
    return lista;
}   

/*****************************************************************************/


/**/

void adicionaCarreiraParagem(Paragem *head, char *CarreiraAadicionar,
char *NomeParagem)
{   
    Paragem * paragem = NULL;
    CarreiraParagem *novaCarreira_p = criaCarreiraParagem(CarreiraAadicionar);

    /*encontra a paragem à qual a carreira será adicionada*/
    paragem = encontraParagem(head,NomeParagem);
    if(paragem->CarreirasParagem != NULL) {

        /*no caso de ainda não haverem carreiras na paragem*/
        if(paragem->CarreirasParagem->head == NULL){
            /*A primeira carreira adicionada será tanto a primeira como 
            a última da lista*/
            paragem->CarreirasParagem->head = novaCarreira_p;
            paragem->CarreirasParagem->last = novaCarreira_p;    
        } 
        else /*No caso de não ser a primeira carreira*/
            if(paragem->CarreirasParagem->last != NULL){

                /*Atualizam-se os ponteiros do anterior, do seguinte e da
                novaCarreira de modo a ficarem corretamente interligados*/
                paragem->CarreirasParagem->last->next = novaCarreira_p;
                novaCarreira_p->prev = paragem->CarreirasParagem->last;
                paragem->CarreirasParagem->last = novaCarreira_p;
        }
    }
    /*Incrementação do número de carreiras da paragem*/
    paragem->numCarreiras++;
}

/*****************************************************************************/


/*Cria uma ligação ao alocar memória para tal estrutura e ao inicializar
 todos os seus valores*/

Ligacao * criaLigacao(char * ParagemOrigem, char * ParagemDestino,
double custo, double duracao)
{
    size_t tamanho_P_origem = strlen(ParagemOrigem)+1;
    size_t tamanho_P_destino = strlen(ParagemDestino)+1;
    Ligacao * nova_ligacao = NULL;

    /*Aloca memória para a nova ligação*/
    nova_ligacao = (Ligacao*) mallocTrue(sizeof(Ligacao));
    
    nova_ligacao->p_Origem = NULL;
    /*Aloca memória para a paragem origem da nova ligação*/
    nova_ligacao->p_Origem = (char*) mallocTrue(sizeof(char)*tamanho_P_origem);
    
    nova_ligacao->p_Destino = NULL;
    /*Aloca memória para a paragem destino da nova ligação*/
    nova_ligacao->p_Destino =(char*)mallocTrue(sizeof(char)*tamanho_P_destino);
    
    /*Copia as strings recebidas como input para as paragens da ligação*/
    strcpy(nova_ligacao->p_Origem, ParagemOrigem);
    strcpy(nova_ligacao->p_Destino, ParagemDestino);

    /*inicializa os valores e ponteiros*/
    nova_ligacao->custo = custo;
    nova_ligacao->duracao = duracao;
    nova_ligacao->next = NULL;
    nova_ligacao->prev = NULL;

    return nova_ligacao;
}

/*****************************************************************************/


/*Adiciona uma ligação no início da lista, criando uma nova cabeça*/

void adicionaLigacaoInicio(listaLigacoes **lista,char * ParagemOrigem,
char * ParagemDestino,double custo, double duracao)
{
    Ligacao *novaLigacao = 
    criaLigacao(ParagemOrigem,ParagemDestino,custo,duracao);
    /*No caso da lista ser nula, é só adicionar o elemento e atualizar
    os ponteiros head e last*/
    if((*lista)->head == NULL){
        (*lista)->head = novaLigacao;
        (*lista)->last = novaLigacao;
    }
    /*A cabeça passa a ser o segundo elemento e é anexada uma 
    nova cabeça*/
    else{ 
        novaLigacao->next = (*lista)->head;
        (*lista)->head->prev = novaLigacao;
        (*lista)->head = novaLigacao;
    } 
}

/*****************************************************************************/


/*Adiciona uma ligação ao final da lista*/

void adicionaLigacaoFim(listaLigacoes **lista,char * ParagemOrigem,
char * ParagemDestino,double custo, double duracao) {

    Ligacao *novaLigacao = 
    criaLigacao(ParagemOrigem,ParagemDestino,custo,duracao);

    /*no caso de ainda não haverem ligações*/
    if((*lista)->head == NULL){ 
        (*lista)->head = novaLigacao;
        (*lista)->last = novaLigacao;    
    }
    /*Se só houver um elemento*/
    else if((*lista)->head == (*lista)->last) {
        /*Atualiza os ponteiros de modo a que a nova ligação passe a ser
        a última ligação*/
        (*lista)->head->next = novaLigacao;
        novaLigacao->prev = (*lista)->head;
        (*lista)->last = novaLigacao;
    }
    else {
        /*Atualiza os ponteiros de modo a que a nova ligação passe a ser
        a última ligação*/
            (*lista)->last->next = novaLigacao;
            novaLigacao->prev = (*lista)->last;
            (*lista)->last = novaLigacao;
        }
}

/*****************************************************************************/


/*Esta função adiciona uma ligação num determinado sítio da lista de ligações
 de uma carreira*/

void adicionaLigacao(Carreira * carreira, Paragem * head, char * ParagemOrigem,
char * ParagemDestino,double custo, double duracao)
{   
    listaLigacoes * lista = carreira->ligacoes;
    /*No caso de não existirem ligações*/
    if(carreira->numLigacoes == 0)
    {   /*Se a paragem Origem não existe na carreira, então pode-se adicionar
        a carreira à paragem */
        if(encontraParagemCarreira(carreira,ParagemOrigem) == NAO_EXISTE)
            adicionaCarreiraParagem(head,carreira->nome,ParagemOrigem);

        if(encontraParagemCarreira(carreira,ParagemDestino) == NAO_EXISTE)
            /*se as paragens destino e origem não forem idênticas adiciona-se
            a carreira à paragem destino*/
            if(strcmp(ParagemOrigem,ParagemDestino) != 0)
                adicionaCarreiraParagem(head,carreira->nome,ParagemDestino);

        /*adiciona-se a primeira ligação à lista das ligações da carreira*/
        adicionaLigacaoInicio(&lista,ParagemOrigem,ParagemDestino,custo,
        duracao);

        /*incrementa os campos numéricos da carreira em questão*/
        incrementaCamposCarreira(carreira,custo,duracao);
    }
    else {
        /*Caso em que acrescenta a ligação no final
        Mesma lógica do processo quando o numLigacoes = 0
        Se a paragem origem recebida ser igual à paragem destino da carreira*/
        if(strcmp(ParagemOrigem,lista->last->p_Destino) == 0) {
            if(encontraParagemCarreira(carreira,ParagemDestino) == NAO_EXISTE)
                adicionaCarreiraParagem(head,carreira->nome,ParagemDestino);

            adicionaLigacaoFim(&lista,ParagemOrigem,ParagemDestino,custo,duracao);
            incrementaCamposCarreira(carreira,custo,duracao);
        }

        /*Se a paragem destino recebida ser igual à paragem origem da carreira*/
        else if(strcmp(ParagemDestino,lista->head->p_Origem) == 0){
            if(encontraParagemCarreira(carreira,ParagemOrigem) == NAO_EXISTE)
                adicionaCarreiraParagem(head,carreira->nome,ParagemOrigem);
            adicionaLigacaoInicio(&lista,ParagemOrigem,ParagemDestino,custo,duracao);
            incrementaCamposCarreira(carreira,custo,duracao);
        }
        else 
            printf("link cannot be associated with bus line.\n");
    }
}

/*****************************************************************************/


/* Lê os nomes de uma carreira e paragens de uma ligação (Origem e destino) */

void leNomesComando(char **nomeCarreira, char **nomeOrigem, char **nomeDestino) {
    
    leEspacos();
    leNome(nomeCarreira);

    leEspacos();
    leNome(nomeOrigem);

    leEspacos();
    leNome(nomeDestino);
}

/*****************************************************************************/


/*Função que trata do comando 'l'*/

void ligacoes(listaParagens *lista_paragens, listaCarreiras *lista_carreiras) {
    char *nomeCarreira = NULL, *nomeOrigem= NULL, *nomeDestino= NULL;
    double custo, duracao;
    Carreira * carreira_i = NULL;

    /*Lê todos os nomes adjacentes ao comando 'l'*/
    leNomesComando(&nomeCarreira, &nomeOrigem, &nomeDestino);

    /*recebe o custo e duração da ligação*/
    scanf("%lf%lf", &custo, &duracao);

    /*guarda a carreira com o nome lido*/
    carreira_i = encontraCarreira(lista_carreiras->head,nomeCarreira);

    /*levantamento de erros(Se algum dos nomes não for encontrado)*/
    if (carreira_i == NAO_ENCONTRADO)
        printf("%s: no such line.\n", nomeCarreira);
    else {
        if (encontraParagem(lista_paragens->head,nomeOrigem) == NAO_ENCONTRADO) 
	    printf("%s: no such stop.\n", nomeOrigem);
	else {
	    if (encontraParagem(lista_paragens->head,nomeDestino) == NAO_ENCONTRADO)
	        printf("%s: no such stop.\n", nomeDestino);
        /*Se o custo ou a duração forem negativos*/
	    else if (custo < 0.0 || duracao < 0.0)
	            printf("negative cost or duration.\n");
		else 
            /*Se não der erro adiciona a ligação com os dados de entrada*/
		    adicionaLigacao(carreira_i, lista_paragens->head, nomeOrigem,
            nomeDestino, custo, duracao);
	    }
    }
    /*Os nomes já foram utilizados e são agora libertados*/
    free(nomeCarreira), free(nomeDestino), free(nomeOrigem);
}

/*****************************************************************************/