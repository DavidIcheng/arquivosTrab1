#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "buscar.h"

void SELECT_ALL(char *arquivoBIN) {
    FILE *arquivo;
    arquivo = fopen(arquivoBIN,"rb+");
    // fseek(escrever, 1, SEEK_SET);
    fwrite(&c_zero,sizeof(char),1,arquivo);

    int *lista;
    estacao temp;
    nulifica_estacao(&temp);
    int tam = buscar_estacao(&temp, &lista, arquivo, true);
    
    fseek(arquivo,0,SEEK_SET);
    fwrite(&c_um,sizeof(char),1,arquivo);
    fclose(arquivo);

    return;
}