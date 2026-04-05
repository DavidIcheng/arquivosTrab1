#include "CREATE.h"
#include "util.h"

void CREATE_TABLE (char *arquivoCSV, char *arquivoBIN) {
    int um = 1;
    int zero = 0;
    char czero = '0';
    char c_um = '1';
    char cifrao = '$';

    FILE *ler;
    FILE *escrever;
    ler = fopen(arquivoCSV, "r");
    escrever = fopen(arquivoBIN,"rb+");

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

        // 1. codEstacao
        token = strsep(&resto, ",");
        temp.codEstacao = (token && *token != '\0') ? atoi(token) : -1;

        // 2. nomeEstacao
        token = strsep(&resto, ",");
        if (token && *token != '\0') {
            temp.nomeEstacao = strdup(token);
            temp.tamNomeEstacao = strlen(token);
        } else {
            temp.nomeEstacao = NULL;
            temp.tamNomeEstacao = 0;
        }

        // 3. codLinha
        token = strsep(&resto, ",");
        temp.codLinha = (token && *token != '\0') ? atoi(token) : -1;

        // 4. nomeLinha
        token = strsep(&resto, ",");
        if (token && *token != '\0') {
            temp.nomeLinha = strdup(token);
            temp.tamNomeLinha = strlen(token);
        } else {
            temp.nomeLinha = NULL;
            temp.tamNomeLinha = 0;
        }

        // 5. codProxEstacao
        token = strsep(&resto, ",");
        temp.codProxEstacao = (token && *token != '\0') ? atoi(token) : -1;

        // 6. distProxEstacao
        token = strsep(&resto, ",");
        temp.distProxEstacao = (token && *token != '\0') ? atoi(token) : -1;

        // 7. codLinhaIntegra (Lida com o caso de ser vazio antes da vírgula)
        token = strsep(&resto, ",");
        temp.codLinhaIntegra = (token && *token != '\0') ? atoi(token) : -1;

        // 8. codEstIntegra (Lida com o final da linha e o \n)
        token = strsep(&resto, "\r\n"); 
        temp.codEstIntegra = (token && *token != '\0') ? atoi(token) : -1;

        int menosum = -1;
        int bytesusados = 37;
        fwrite(&c_zero,sizeof(char),1,escrever);
        fwrite(&menosum,sizeof(int),1,escrever);
        fwrite(&temp.codEstacao,sizeof(int),1,escrever);
        fwrite(&temp.codLinha,sizeof(int),1,escrever);
        fwrite(&temp.codProxEstacao,sizeof(int),1,escrever);
        fwrite(&temp.distProxEstacao,sizeof(int),1,escrever);
        fwrite(&temp.codLinhaIntegra,sizeof(int),1,escrever);
        fwrite(&temp.codEstIntegra,sizeof(int),1,escrever);
        int tam = 0;
        while(temp.nomeEstacao[tam] != 0) tam++;
        fwrite(&tam,sizeof(int),1,escrever);
        bytesusados += tam;
        fwrite(temp.nomeEstacao,sizeof(char) * tam,1,escrever);
        tam = 0;
        while(temp.nomeLinha[tam] != 0)tam++;
        fwrite(&tam,sizeof(int),1,escrever);
        bytesusados += tam;
        fwrite(temp.nomeLinha,sizeof(char) * tam,1,escrever);
        for(int i = bytesusados; i < 80; i++){
            fwrite(&cifrao,sizeof(char),1,escrever);
        }
    
    }
    

    fseek(escrever, 0, SEEK_SET); // volta p comeco
    // SEEK_SET: movimentação do cmc do arquivo 
    // SEEK_CUR: a partir da posição do ponteiro
    // SEEK_END: do final

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