#include "util.h"

const int um = 1;
const int zero = 0;
const char c_zero = '0';
const char c_um = '1';
const char cifrao = '$';

pair make_pair(int ff, int ss) {
    pair temp;
    temp.ff = ff; temp.ss = ss;
    return temp;
}

void printar_estacao(estacao* e) {

    printf("%d ", e->codEstacao);
    if(e->nomeEstacao != NULL) {
        printf("%s ", e->nomeEstacao);
    } else printf("NULO ");
    printf("%d ", e->codLinha);
    if(e->nomeLinha != NULL) {
        printf("%s ", e->nomeLinha);
    } else printf("NULO ");
    
    if(e->codProxEstacao != -1) {
        printf("%d ", e->codProxEstacao);
    } else printf("NULO ");
    if(e->distProxEstacao != -1) {
        printf("%d ", e->distProxEstacao);
    } else printf("NULO ");
    if(e->codLinhaIntegra != -1) {
        printf("%d ", e->codLinhaIntegra);
    } else printf("NULO ");
    if(e->codEstIntegra != -1) {
        printf("%d\n", e->codEstIntegra);
    } else printf("NULO\n");

    return;
}

void nulifica_estacao(estacao* temp){
    temp->codEstacao = -1;
    temp->codLinha = -1;
    temp->codProxEstacao = -1;
    temp->distProxEstacao = -1;
    temp->codLinhaIntegra = -1;
    temp->codEstIntegra = -1;
    temp->tamNomeEstacao = -1;
    temp->nomeEstacao = NULL;
    temp->tamNomeLinha = -1;
    temp->nomeLinha = NULL;
}