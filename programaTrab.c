#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "TAD/CREATE.h"
#include "TAD/SELECT.h"
#include "TAD/DELETE.h"
#include "TAD/fornecidas.h"
#include "TAD/util.h"
#include "TAD/SELECT_ALL.h"

// typedef struct Cabecalho {
//     char status;
//     int topo;
//     int proxRRN;
//     int nroEstacoes;
//     int nroParesEstacao;
// } cabecalho;

int main(void) {
    int comando;
    scanf("%d",&comando);
    // printf("%d", comando);
    if(comando == 1) {
        char entrada[40];
        char saida[40];
        scanf(" %s",entrada);
        scanf(" %s",saida);
        CREATE_TABLE(entrada,saida);
    }else if(comando == 2){
        char entrada[40];
        scanf(" %s",entrada);
        SELECT_ALL(entrada);
        //printar(entrada);
    }else if(comando == 3){
        char entrada[40];
        scanf(" %s",entrada);
        int n;
        scanf(" %d",&n);
        SELECT(entrada,n);
    }else if(comando == 4){
        char entrada[40];
        scanf(" %s",entrada);
        int n;
        scanf(" %d",&n);
        DELETE(entrada,n);
    }else if(comando == 5){
        //insercao
    }else if(comando == 6){
        //depoois nois le o 6
    }else{
        printf("Comando Inválido\n");
    }
}