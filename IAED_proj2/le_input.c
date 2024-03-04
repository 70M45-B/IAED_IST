/*Ficheiro que contém as funções utilizadas para uma correta leitura de input*/

/*inclusão dos ficheiros necessários às funções presentes abaixo*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Constantes.h"
#include "le_input.h"


/********************* Funções para tratamento do input *********************/

/* Lê espaços: Retorna 0 se chegou ao final de linha ou 1 caso contrário. */

int leEspacos() {
    int c;
    /*Enquanto o inteiro c corresponder ao código ASCII de um espaço ou '\t'
    vai lendo*/
    while ((c = getchar()) == ' ' || c == '\t');
    if (c == '\n') /*Sai da função com valor 0 se chegar a um '\n'*/
        return 0; 
    ungetc(c, stdin); /*Se chegar a uma letra, volta a introduzi-la no standard
    input para poder ser lida novamente*/
    return 1;
}

/*****************************************************************************/


/*Função que substituirá o malloc de modo a garantir que o programa termina
controladamente no caso de não existir mais memória disponível*/

void * mallocTrue(size_t size) {

    /*Tenta alocar memória para um ponteiro*/
    void* ptr = malloc(size);

    /*Se o malloc returnar NULL, significa que não existe memória disponível*/
    if(ptr == NULL) {
        printf("No memory.\n");
        exit(1);
    }
    /*Se chegou aqui é porque existe memória e retorna o ponteiro
    já alocado*/
    return ptr; 
}

/*****************************************************************************/

/*Semelhante ao mallocTrue, esta função irá garantir que o programa termina
controladamente no caso de não existir mais memória disponível*/

void * reallocTrue(void *ptr, size_t size) {
    void *novo_ptr = realloc(ptr,size);
    if(novo_ptr == NULL) {
        printf("No memory.\n");
        exit(1);
    }
    return novo_ptr;
}

/*****************************************************************************/

/* Lê um nome para a string que recebe como parâmetro. */

void leNome(char **nome) {

    char c;
    size_t tamanho = 0;
    
    char *s = NULL, *nova_str = NULL;

    /*Aloca memória para a string 's'*/
    s = (char*) mallocTrue(BUFFER);
    
    *s = getchar(); /*lê o primeiro caracter de s*/
    /* Se o primeiro elemento não ser uma aspa*/
    if (*s != '"') { 
        tamanho = 1;

        /*lê até encontrar qualquer tipo de espaço branco*/
        while (!isspace(c = getchar()))
            s[tamanho++] = c;
        ungetc(c, stdin);
    }
    /*Se o primeiro elemento for uma aspa, então considera todos os
    caracteres até à próxima aspa como parte da string*/
    else { 
        while((c = getchar()) != '"')
            s[tamanho++] = c;
    }
    s[tamanho] = '\0'; /*adiciona o limitador de strings*/
    
    /*Realoca a memória para o tamanho da string*/
    nova_str = (char*) reallocTrue(*nome, sizeof(char)*(strlen(s)+1));

    strcpy(nova_str, s);
    /*Altera o ponteiro nome de modo a apontar para a nova string*/
    *nome = nova_str;
    free(s);
}

/**************************************************************/


/* Le todo o texto até ao final de linha. */

void leAteFinalLinha(char s[]) {
    char c;
    int i = 0;
    while ((c = getchar()) != '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
}

/******************************************/