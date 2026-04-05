#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "buscar.h"
#include "fornecidas.h"

int DELETE(char *arquivoBIN, int n){
    
    FILE *escrever;
    escrever = fopen(arquivoBIN,"rb+");
    // fseek(escrever, 1, SEEK_SET);
    fwrite(&c_zero,sizeof(char),1,escrever);
    fseek(escrever,1,SEEK_SET); //de acordo com o padrão do C não pode dar um fread e um fwrite seguidos.
    int topo;
    fread(&topo,sizeof(int),1,escrever);
    for(int i = 0; i < n; i++){
        int *lista;
        int m;
        estacao temp;
        nulifica_estacao(&temp);
        scanf("%d",&m);
        pegar_info_estacao(&temp,m);
        //printar_estacao(&temp);
        int tam = buscar_estacao(&temp, &lista, escrever, false,false);
        for(int i = 0; i < tam; i++){
            fseek(escrever, 17 + (80) * lista[i], SEEK_SET);
            fwrite(&c_um,sizeof(char),1,escrever);
            fwrite(&topo,sizeof(int),1,escrever);
            topo = lista[i];
        }
        if(temp.nomeEstacao != NULL) free(temp.nomeEstacao);
        if(temp.nomeLinha != NULL) free(temp.nomeLinha);
    }
    int novoTamEstacao = conta_estacao(escrever);
    int novoTamPar = conta_par_estacao(escrever);
    fseek(escrever,9,SEEK_SET);
    fwrite(&novoTamEstacao,sizeof(int),1,escrever);
    fwrite(&novoTamPar,sizeof(int),1,escrever);
    fseek(escrever,0,SEEK_SET);
    fwrite(&c_um,sizeof(char),1,escrever);
    fwrite(&topo,sizeof(int),1,escrever);
    fclose(escrever);

    BinarioNaTela(arquivoBIN);
}