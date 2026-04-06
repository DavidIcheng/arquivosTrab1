#include "util.h"
#include "buscar.h"

// Imprime todos os registros não removidos do arquivo.

// arquivoBin: Nome do arquivo a ser lido.
void SELECT_ALL(char *arquivoBIN) {
    // Abrindo o arquivo
    FILE *arquivo;
    arquivo = fopen(arquivoBIN,"rb+");
    // Tratamento de erro
    if(arquivo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Marca o arquivo como instável
    fwrite(&c_zero,sizeof(char),1,arquivo);

    int *lista; // Lista com todos os RRNs. Não será usado, é só para o argumento do buscar_estacao
    estacao temp;
    nulifica_estacao(&temp);
    int tam = buscar_estacao(&temp, &lista, arquivo, true);
    
    // Desalocando memória
    free(lista);
    lista = NULL;
    
    // Marca o arquivo como estável e o fecha.
    fseek(arquivo,0,SEEK_SET);
    fwrite(&c_um,sizeof(char),1,arquivo);
    fclose(arquivo);

    return;
}