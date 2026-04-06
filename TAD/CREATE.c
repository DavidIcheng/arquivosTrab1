#include "CREATE.h"
#include "util.h"

void CREATE_TABLE (char *arquivoCSV, char *arquivoBIN) {
    FILE *ler;
    FILE *escrever;
    ler = fopen(arquivoCSV, "r");
    escrever = fopen(arquivoBIN,"rb+");
    if(ler == NULL || escrever == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    // 17bytes de 0, dps 
    
    for(int i = 0; i < 17; i++) {
        // Write 1 byte from the address of 'zero'
        fwrite(&zero, 1, 1, escrever); 
    }

    
    char c;
    int qtdVirgula = 0;
    char str[105];

    fgets(str,105,ler); //pular a primeira linha
    
    int proxRRN = 0;
    int nroEstacoes = 0;
    int nroParesDeEstacoes = 0;
    
    int limite = 100;
    int* arrEstacoes = malloc(limite*sizeof(int));
    pair* arrParesEstacoes = malloc(limite*sizeof(pair));
    
    while(fgets(str,105,ler)) {
        proxRRN++;
        
        estacao temp;
        // strsep modifica o ponteiro, por isso usamos uma variável auxiliar 'ptr'
        char *resto = str;
        char *token;

        token = strsep(&resto, ",");
        temp.codEstacao = (token && *token != '\0') ? atoi(token) : -1;

        token = strsep(&resto, ",");
        if (token && *token != '\0') {
            temp.nomeEstacao = strdup(token);
            temp.tamNomeEstacao = strlen(token);
        } else {
            temp.nomeEstacao = NULL;
            temp.tamNomeEstacao = 0;
        }

        token = strsep(&resto, ",");
        // Se o token existir e nn for nulo a gente transforma p inteiro, se nn ele recebe -1
        temp.codLinha = (token && *token != '\0') ? atoi(token) : -1;

        token = strsep(&resto, ",");
        if (token && *token != '\0') {
            temp.nomeLinha = strdup(token);
            temp.tamNomeLinha = strlen(token);
        } else {
            temp.nomeLinha = NULL;
            temp.tamNomeLinha = 0;
        }

        token = strsep(&resto, ",");
        temp.codProxEstacao = (token && *token != '\0') ? atoi(token) : -1;

        token = strsep(&resto, ",");
        temp.distProxEstacao = (token && *token != '\0') ? atoi(token) : -1;

        token = strsep(&resto, ",");
        temp.codLinhaIntegra = (token && *token != '\0') ? atoi(token) : -1;

        token = strsep(&resto, "\r\n"); 
        temp.codEstIntegra = (token && *token != '\0') ? atoi(token) : -1;

        temp.removido = '0';
        temp.proximo = -1;

        estacao_para_binario(&temp,proxRRN-1,escrever);
    }

    fseek(escrever, 0, SEEK_SET); // volta p comeco

    int topo = -1;
    fwrite(&c_um,sizeof(char),1,escrever);
    fwrite(&topo, sizeof(int), 1, escrever);
    fwrite(&proxRRN, sizeof(int), 1, escrever);
    nroEstacoes = conta_estacao(escrever);
    nroParesDeEstacoes = conta_par_estacao(escrever);
    fseek(escrever,9,SEEK_SET);
    fwrite(&nroEstacoes, sizeof(int), 1, escrever);
    fwrite(&nroParesDeEstacoes, sizeof(int), 1, escrever);

    fclose(escrever);
    fclose(ler);

    BinarioNaTela(arquivoBIN);
    return;
}