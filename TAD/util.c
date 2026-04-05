#include "util.h"
#include "fornecidas.h"

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

void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
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

int conta_estacao(FILE* arquivo){
    fseek(arquivo,5,SEEK_SET);
    int registros;
    fread(&registros,sizeof(int),1,arquivo);
    char* lista[registros];
    int diferentes = 0;
    for(int i = 0; i < registros; i++){
        fseek(arquivo,17 + (80 * i),SEEK_SET);
        char removido;
        fread(&removido,sizeof(char),1,arquivo);
        if(removido == '1') continue;
        int tamstring;
        fseek(arquivo,17 + 29 + (80 * i),SEEK_SET);
        fread(&tamstring,sizeof(int),1,arquivo);
        char frase[tamstring + 1];                  //temos que sempre declarar um caractere a mais pois a função strcmp não funciona sem o \0 no final
        fread(frase,tamstring,1,arquivo);
        frase[tamstring] = '\0';
        bool novo = true;
        for(int j = 0; j < diferentes; j++){
            if(strcmp(frase,lista[j]) == 0){
                novo = false;
                break;
            }
        }
        if(novo){
            lista[diferentes] = malloc((tamstring + 1) * sizeof(char));
            for(int j = 0; j <= tamstring; j++){
                lista[diferentes][j] = frase[j];
            }
            diferentes++;
        }
    }
    for(int i = 0; i < diferentes; i++){
        free(lista[i]);
    }
    return diferentes;
}
int conta_par_estacao(FILE* arquivo){
    fseek(arquivo,5,SEEK_SET);
    int registros;
    fread(&registros,sizeof(int),1,arquivo);
    int lista[registros][2];
    int diferentes = 0;
    for(int i = 0; i < registros; i++){
        fseek(arquivo,17 + (80 * i),SEEK_SET);
        char removido;
        fread(&removido,sizeof(char),1,arquivo);
        if(removido == '1') continue;
        int id1,id2;
        fseek(arquivo,17 + 5 + (80 * i),SEEK_SET);
        fread(&id1,sizeof(int),1,arquivo);
        fseek(arquivo,17 + 13 + (80 * i),SEEK_SET);
        fread(&id2,sizeof(int),1,arquivo);
        if(id2 == -1) continue;
        bool novo = true;
        for(int j = 0; j < diferentes; j++){
            if(lista[j][0] == id1 && lista[j][1] == id2){
                novo = false;
                break;
            }
        }
        if(novo){
            lista[diferentes][0] = id1;
            lista[diferentes][1] = id2;
            diferentes++;
        }
    }
    return diferentes;
}

void pegar_info_estacao(estacao *nova,int rep){
    for(int i = 0; i < rep; i++){
        char s[20];
        scanf(" %s",s);
        if(strcmp(s, "codEstacao") == 0) {
            scanf(" %d",&nova->codEstacao);
        } else if(strcmp(s,"codLinha") == 0) {
            scanf(" %d",&nova->codLinha);
        } else if(strcmp(s,"codProxEstacao") == 0) {
            scanf(" %d",&nova->codProxEstacao);
        } else if(strcmp(s,"distProxEstacao") == 0) {
            scanf(" %d",&nova->distProxEstacao);
        } else if(strcmp(s,"codLinhaIntegra") == 0) {
            char* temp = malloc(sizeof(char) * 20);
            scanf("%s",temp);
            if(strcmp(temp,"NULO") == 0){
                nova->codLinhaIntegra = -2;
                continue;
            }
            nova->codLinhaIntegra = atoi(temp);
        } else if(strcmp(s,"codEstIntegra") == 0) {
            char* temp = malloc(sizeof(char) * 20);
            scanf("%s",temp);
            if(strcmp(temp,"NULO") == 0){
                nova->codEstIntegra = -2;
                continue;
            }
            nova->codEstIntegra = atoi(temp);
        } else if(strcmp(s,"tamNomeEstacao") == 0) {
            scanf(" %d",&nova->tamNomeEstacao);
        } else if(strcmp(s,"nomeEstacao") == 0) {
            nova->nomeEstacao = malloc(sizeof(char) * 50);
            ScanQuoteString(nova->nomeEstacao);
        } else if(strcmp(s,"tamNomeLinha") == 0) {
            scanf(" %d",&nova->tamNomeLinha);
        } else if(strcmp(s,"nomeLinha") == 0) {
            nova->nomeLinha = malloc(sizeof(char) * 50);
            ScanQuoteString(nova->nomeLinha);
        } else {
            printf("Campo invalido\n");
        }
    }
}