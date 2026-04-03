#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "TAD/CREATE.h"
#include "TAD/fornecidas.h"

// typedef struct Cabecalho {
//     char status;
//     int topo;
//     int proxRRN;
//     int nroEstacoes;
//     int nroParesEstacao;
// } cabecalho;

typedef struct Estacao {
    char removido;
    int proximo;
    int codEstacao;
    int codLinha;
    int codProxEstacao;
    int distProxEstacao;
    int codLinhaIntegra;
    int codEstIntegra;
    int tamNomeEstacao;
    char* nomeEstacao;
    int tamNomeLinha;
    char* nomeLinha;
} estacao;

int main(void) {
    int comando;
    scanf("%d",&comando);
    // printf("%d", comando);
    if(comando == 1) {
        char entrada[40];
        char saida[40];
        scanf(" %s",entrada);
        scanf(" %s",saida);
        //printf("%s %s", entrada, saida);
        CREATE_TABLE(entrada,saida);
    }else if(comando == 2){
        char entrada[40];
        scanf(" %s",entrada);
        //printar(entrada);
    }else if(comando == 3){
        char entrada[40];
        scanf(" %s",entrada);
        int n;
        scanf(" %d",&n);
        for(int i = 0; i < n; i++){
            //busca(entrada);
        }
    }else if(comando == 4){
        char entrada[40];
        scanf(" %s",entrada);
        int n;
        scanf(" %d",&n);
        for(int i = 0; i < n; i++){
            //remocao(entrada);
        }
    }else if(comando == 5){
        //insercao
    }else if(comando == 6){
        //depoois nois le o 6
    }else{
        printf("Comando Inválido\n");
    }
}