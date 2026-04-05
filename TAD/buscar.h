#ifndef BUSCAR_H
#define BUSCAR_H

    #include "util.h"

    int buscar_estacao(estacao* base, int** encontrados, FILE* arquivo, bool imprimir, bool quebralinhafinal);
    int conta_estacao(FILE *ler);
    int conta_par_estacao(FILE *ler);
#endif