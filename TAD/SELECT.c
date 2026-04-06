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
        pegar_info_estacao(&temp,m);
        
        int tam = buscar_estacao(&temp, &lista, arquivo, true);
        // tem q printar uma quebra de linha no final
        printf("\n");

        if(temp.nomeEstacao != NULL) free(temp.nomeEstacao);
        if(temp.nomeLinha != NULL) free(temp.nomeLinha);
    }
    fseek(arquivo,0,SEEK_SET);
    fwrite(&c_um,sizeof(char),1,arquivo);
    fclose(arquivo);

    return;
}