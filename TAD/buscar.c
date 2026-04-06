#include "buscar.h"

bool satisfazBase(estacao* base, estacao* temp) {
    if(base->codEstacao != -1 && base->codEstacao != temp->codEstacao) {
        return false; 
    }
    if(base->codLinha != -1 && base->codLinha != temp->codLinha) {
        return false;
    }
    if(base->codProxEstacao != -1 && base->codProxEstacao != temp->codProxEstacao) {
        return false;
    }
    if(base->distProxEstacao != -1 && base->distProxEstacao != temp->distProxEstacao) {
        return false;
    }
    if(base->codLinhaIntegra != -1) {
        if(base->codLinhaIntegra == -2){
            if(temp->codLinhaIntegra != -1) return false;
        }else{
            if(temp->codLinhaIntegra != base->codLinhaIntegra) return false;
        }
    }
    if(base->codEstIntegra != -1) {
        if(base->codEstIntegra == -2){
            if(temp->codEstIntegra != -1) return false;
        }else{
            if(temp->codEstIntegra != base->codLinhaIntegra) return false;
        }
    }
    if(base->tamNomeEstacao != -1 && base->tamNomeEstacao != temp->tamNomeEstacao) {
        return false;
    }
    if(base->nomeEstacao != NULL && strcmp(base->nomeEstacao, temp->nomeEstacao) != 0) {
        return false;
    }
    if(base->tamNomeLinha != -1 && base->tamNomeLinha != temp->tamNomeLinha) {
        return false;
    }
    if(base->nomeLinha != NULL && strcmp(base->nomeLinha, temp->nomeLinha) != 0) {
        return false;
    }
    return true;
}

// retorna quantas estacoes foram buscadas
int buscar_estacao(estacao* base, int** encontrados, FILE* arquivo, bool imprimir) {
    int limite = 100;
    *encontrados = malloc(limite*sizeof(int));
    fseek(arquivo, 5, SEEK_SET);
    int cont = 0;
    int tam;
    fread(&tam,sizeof(int),1,arquivo);
    for(int i = 0; i < tam; i++){
        fseek(arquivo,17 + i * 80,SEEK_SET);
        estacao temp;
        fread(&temp.removido,sizeof(char),1,arquivo);
        if(temp.removido == '1') continue;
        fseek(arquivo,22 + i * 80,SEEK_SET);
        
        fread(&temp.codEstacao,sizeof(int),1,arquivo);
        fread(&temp.codLinha,sizeof(int),1,arquivo);
        fread(&temp.codProxEstacao,sizeof(int),1,arquivo);
        fread(&temp.distProxEstacao,sizeof(int),1,arquivo);
        fread(&temp.codLinhaIntegra,sizeof(int),1,arquivo);
        fread(&temp.codEstIntegra,sizeof(int),1,arquivo);
        fread(&temp.tamNomeEstacao,sizeof(int),1,arquivo);
        temp.nomeEstacao = malloc(sizeof(char) * (temp.tamNomeEstacao));
        fread(temp.nomeEstacao,sizeof(char) * temp.tamNomeEstacao,1,arquivo);
        fread(&temp.tamNomeLinha,sizeof(int),1,arquivo);
        temp.nomeLinha = malloc(sizeof(char) * (temp.tamNomeLinha));
        fread(temp.nomeLinha,sizeof(char) * temp.tamNomeLinha,1,arquivo);
        
        if(satisfazBase(base, &temp)) {
            if(imprimir) {
                cont++;
                printar_estacao(&temp);
                continue;
            }
            (*encontrados)[cont++] = i;
            if(cont > limite-10) {
                limite *= 2;
                (*encontrados) = realloc((*encontrados), limite*sizeof(int));
            }
        }
    }
    if(imprimir == 1 && cont == 0) printf("Registro inexistente.\n");
    return cont;
}