#ifndef _ESTRUTURASDADOS_
#define _ESTRUTURASDADOS_


/*Definição das estruturas das paragens*/
typedef struct CarreiraParagem{
    char *nome;
    struct CarreiraParagem *next, *prev;
}CarreiraParagem;


typedef struct CarreirasParagem{
    CarreiraParagem *head, *last;
}CarreirasParagem;


typedef struct Paragem{
    char *nome;
    double latitude, longitude;
    CarreirasParagem *CarreirasParagem;
    size_t numCarreiras;
    struct Paragem *prev;
    struct Paragem *next;
}Paragem;


typedef struct listaParagens{
    Paragem *head, *last;
}listaParagens;

/****************************************/


/*Definição das estruturas das Ligações*/

typedef struct Ligacao{
    char *p_Origem, *p_Destino;
    double custo, duracao;
    struct Ligacao *prev;
    struct Ligacao *next;
} Ligacao;

typedef struct listaligacoes{
    Ligacao *head, *last;
}listaLigacoes;

/****************************************/


/*Definição das estruturas das carreiras*/

typedef struct Carreira{
    char *nome;
    double custoTotal;
    double duracaoTotal;
    listaLigacoes *ligacoes;
    size_t numLigacoes;
    struct Carreira *prev;
    struct Carreira *next;
}Carreira;


typedef struct listaCarreiras{
    size_t num_Carreiras;
    Carreira *head, *last;
}listaCarreiras;

/****************************************/


#endif