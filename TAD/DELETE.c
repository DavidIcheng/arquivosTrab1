#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

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


int DELETE(char *arquivoBIN, int n){
    int um = 1;
    int zero = 0;
    char czero = '0';
    char c_um = '1';
    char cifrao = '$';
    
    FILE *escrever;
    escrever = fopen(arquivoBIN,"rb+");
    // fseek(escrever, 1, SEEK_SET);
    fwrite(&czero,sizeof(char),1,escrever);

    int topo;
    fread(&topo,sizeof(int),1,escrever);
    for(int i = 0; i < n; i++){
        int *lista;
        int m;
        estacao temp;
        temp.codEstacao = -1;
        temp.codLinha = -1;
        temp.codProxEstacao = -1;
        temp.distProxEstacao = -1;
        temp.codLinhaIntegra = -1;
        temp.codEstIntegra = -1;
        temp.tamNomeEstacao = -1;
        temp.nomeEstacao = NULL;
        temp.tamNomeLinha = -1;
        temp.nomeLinha = NULL;
        scanf("%d",&m);
        for(int j = 0; j < m; j++){
            char s[20];
            scanf(" %s",s);
            if(strcmp(s, "codEstacao") == 0) {
                scanf(" %d",&temp.codEstacao);
            } else if(strcmp(s,"codLinha" == 0)) {
                scanf(" %d",&temp.codLinha);
            } else if(strcmp(s,"codProxEstacao") == 0) {
                scanf(" %d",&temp.codProxEstacao);
            } else if(strcmp(s,"distProxEstacao") == 0) {
                scanf(" %d",&temp.distProxEstacao);
            } else if(strcmp(s,"codLinhaIntegra") == 0) {
                scanf(" %d",&temp.codLinhaIntegra);
            } else if(strcmp(s,"codEstIntegra") == 0) {
                scanf(" %d",&temp.codEstIntegra);
            } else if(strcmp(s,"tamNomeEstacao") == 0) {
                scanf(" %d",&temp.tamNomeEstacao);
            } else if(strcmp(s,"nomeEstacao") == 0) {
                temp.nomeEstacao = malloc(sizeof(char) * 30);
                scanf(" %s",temp.nomeEstacao);
            } else if(strcmp(s,"tamNomeLinha") == 0) {
                scanf(" %d",&temp.tamNomeLinha);
            } else if(strcmp(s,"nomeLinha") == 0) {
                temp.nomeLinha = malloc(sizeof(char) * 30);
                scanf(" %s",temp.nomeLinha);
            } else {
                printf("Campo invalido");
            }
        }
        //buscar(lista,temp);
        for(int i = 1; i < lista[0] + 1; i++){ //primeiro elemento da lista determina o tamanho da lista
            fseek(escrever, 17 + (80) * lista[i], SEEK_SET);
            fwrite(&czero,sizeof(char),1,escrever);
            fwrite(topo,sizeof(int),1,escrever);
            topo = lista[i];
        }
    }
    fseek(escrever,0,SEEK_SET);
    fwrite(&c_um,sizeof(char),1,escrever);
    fwrite(&topo,sizeof(int),1,escrever);
    fclose(escrever);
}