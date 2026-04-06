#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "buscar.h"
#include "fornecidas.h"

// Funcionalidade de deletar.
// 
// arquivoBIN: Nome do arquivo binario
// n: Quantidade de vezes que ocorre a deleção
int DELETE(char *arquivoBIN, int n){
    // Abrindo o arquivo
    FILE *escrever;
    escrever = fopen(arquivoBIN,"rb+");
    if(escrever == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return -1;
    }
    // Mudando o status do arquivo para instável.
    fwrite(&c_zero,sizeof(char),1,escrever);
    fseek(escrever,1,SEEK_SET); //de acordo com o padrão do C não pode dar um fread e um fwrite seguidos.
    
    int topo;
    fread(&topo,sizeof(int),1,escrever); // Topo da pilha

    for(int i = 0; i < n; i++) { // Loop para cada deleção
        int *lista; // Lista de inteiros dos RRN das estações a serem removidas
        int m;
        estacao temp;
        nulifica_estacao(&temp); // Presente em util.c
        scanf("%d",&m);
        pegar_info_estacao(&temp,m); // Presente em util.c

        int tam = buscar_estacao(&temp, &lista, escrever, false); // Presente em util.c
        for(int i = 0; i < tam; i++){
            fseek(escrever, 17 + (80) * lista[i], SEEK_SET); // Cabeçalho tem 17 bytes, cada registro tem tamanho 80.
            fwrite(&c_um,sizeof(char),1,escrever); // Troca o removidos para 1
            // Atualiza o campo "próximo" para o último registro removido (armazenado em topo)
            fwrite(&topo,sizeof(int),1,escrever);
            // Atualiza o topo da pilha de removidos para o registro atual.
            topo = lista[i];
        }
        // Desalocando memória
        if(temp.nomeEstacao != NULL) free(temp.nomeEstacao);
        if(temp.nomeLinha != NULL) free(temp.nomeLinha);
    }
    int novoTamEstacao = conta_estacao(escrever);
    int novoTamPar = conta_par_estacao(escrever);
    
    // Reescrevendo o cabeçalho
    fseek(escrever,9,SEEK_SET);
    fwrite(&novoTamEstacao,sizeof(int),1,escrever);
    fwrite(&novoTamPar,sizeof(int),1,escrever);
    fseek(escrever,0,SEEK_SET);
    fwrite(&c_um,sizeof(char),1,escrever); // Marca como arquivo estavel
    fwrite(&topo,sizeof(int),1,escrever);
    fclose(escrever);

    BinarioNaTela(arquivoBIN);
}