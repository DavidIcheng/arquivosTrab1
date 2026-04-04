#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct Pair {
    int ff;
    int ss;
} pair;

extern const int um;
extern const int zero;
extern const char c_zero;
extern const char c_um;
extern const char cifrao;

pair make_pair(int ff, int ss);

void printar_estacao(estacao* estacaoPrintar);

void nulifica_estacao(estacao* temp);

#endif