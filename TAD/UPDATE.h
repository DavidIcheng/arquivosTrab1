#ifndef UPDATE_H
#define UPDATE_H
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #include "fornecidas.h"
    #include "util.h"
    #include "buscar.h"

    void UPDATE_ONE(FILE *arquivo,estacao* mudar, estacao* mudanca);
    void UPDATE(char *arquivoBIN,int vezes);

#endif