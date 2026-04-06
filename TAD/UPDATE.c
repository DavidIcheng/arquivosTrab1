#include "UPDATE.h"

void UPDATE_ONE(FILE *arquivo,estacao* mudar, estacao* mudanca){
    int menosum = -1;
    if(mudanca->codEstacao != -1){
        mudar->codEstacao = mudanca->codEstacao;
    }
    if(mudanca->codLinha != -1){
        mudar->codLinha = mudanca->codLinha;
    }
    if(mudanca->codProxEstacao != -1){
        mudar->codProxEstacao = mudanca->codProxEstacao;
    }
    if(mudanca->distProxEstacao != -1){
        mudar->distProxEstacao = mudanca->distProxEstacao;
    }
    if(mudanca->codLinhaIntegra != -1){
        if(mudanca->codLinhaIntegra == -2){
            mudar->codLinhaIntegra = -1;
        }else{
            mudar->codLinhaIntegra = mudanca->codLinhaIntegra;
        }
    }
    if(mudanca->codEstIntegra != -1){
        if(mudanca->codEstIntegra == -2){
            mudar->codEstIntegra = -1;
        }else{
            mudar->codEstIntegra = mudanca->codEstIntegra;
        }
    }
    if(mudanca->tamNomeEstacao != -1){
        mudar->tamNomeEstacao = mudanca->tamNomeEstacao;
        mudar->nomeEstacao = mudanca->nomeEstacao;
    }
    if(mudanca->tamNomeLinha != -1){
        mudar->tamNomeLinha = mudanca->tamNomeLinha;
        mudar->nomeLinha = mudanca->nomeLinha;
    }
}

void UPDATE(char *arquivoBIN,int vezes){
    FILE *arquivo = fopen(arquivoBIN,"rb+");
    if(arquivo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    fwrite(&c_zero,sizeof(char),1,arquivo);
    for(int i = 0; i < vezes; i++){
        int *lista;
        int m;
        estacao temp;
        nulifica_estacao(&temp);
        scanf("%d",&m);
        pegar_info_estacao(&temp,m);
        int tam = buscar_estacao(&temp, &lista, arquivo, false);
        scanf("%d",&m);
        nulifica_estacao(&temp);
        pegar_info_estacao(&temp,m);
        for(int j = 0; j < tam; j++){
            estacao mudar;
            binario_para_estacao(&mudar,lista[j],arquivo);
            UPDATE_ONE(arquivo,&mudar,&temp);
            estacao_para_binario(&mudar,lista[j],arquivo);
        }
        if(temp.nomeEstacao != NULL) free(temp.nomeEstacao);
        if(temp.nomeLinha != NULL) free(temp.nomeLinha);
    }
    fseek(arquivo, 0, SEEK_SET);
    fwrite(&c_um,sizeof(char),1,arquivo);
    fclose(arquivo);
    BinarioNaTela(arquivoBIN);
}