#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "buscar.h"

void SELECT(char *arquivoBIN, int n){
    FILE *arquivo;
    arquivo = fopen(arquivoBIN,"rb+");
    // fseek(escrever, 1, SEEK_SET);
    fwrite(&c_zero,sizeof(char),1,arquivo);

    for(int i = 0; i < n; i++){
        int *lista;
        int m;
        estacao temp;
        nulifica_estacao(&temp);
        scanf("%d",&m);
        for(int j = 0; j < m; j++){
            char s[20];
            scanf(" %s",s);
            if(strcmp(s, "codEstacao") == 0){
                scanf(" %d",&temp.codEstacao);
            }else if(strcmp(s,"codLinha") == 0){
                scanf(" %d",&temp.codLinha);
            }else if(strcmp(s,"codProxEstacao") == 0){
                scanf(" %d",&temp.codProxEstacao);
            }else if(strcmp(s,"distProxEstacao") == 0){
                scanf(" %d",&temp.distProxEstacao);
            }else if(strcmp(s,"codLinhaIntegra") == 0){
                scanf(" %d",&temp.codLinhaIntegra);
            }else if(strcmp(s,"codEstIntegra") == 0){
                scanf(" %d",&temp.codEstIntegra);
            }else if(strcmp(s,"tamNomeEstacao") == 0){
                scanf(" %d",&temp.tamNomeEstacao);
            }else if(strcmp(s,"nomeEstacao") == 0){
                temp.nomeEstacao = malloc(sizeof(char) * 30);
                scanf(" %s",temp.nomeEstacao);
            }else if(strcmp(s,"tamNomeLinha") == 0){
                scanf(" %d",&temp.tamNomeLinha);
            }else if(strcmp(s,"nomeLinha") == 0){
                temp.nomeLinha = malloc(sizeof(char) * 30);
                scanf(" %s",temp.nomeLinha);
            }else{
                printf("Campo invalido");
            }
        }
        int tam = buscar_estacao(&temp, &lista, arquivo, true);
        printf("ALOUUUU");
    }
    fseek(arquivo,0,SEEK_SET);
    fwrite(&c_um,sizeof(char),1,arquivo);
    fclose(arquivo);

    return;
}