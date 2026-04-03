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

    printf("%d %s %d %s", e->codEstacao, e-> nomeEstacao, e->codLinha, e->nomeLinha);
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