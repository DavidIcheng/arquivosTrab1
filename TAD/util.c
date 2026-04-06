#include "util.h"
#include "fornecidas.h"

// Constantes frequentemente usados para dar fwrite nos arquivos.
const int um = 1;
const int zero = 0;
const char c_zero = '0';
const char c_um = '1';
const char cifrao = '$';

// Preenche uma struct pair.
pair make_pair(int ff, int ss) {
    pair temp;
    temp.ff = ff; temp.ss = ss;
    return temp;
}

// Pega dois ponteiros e troca seus valores.
void swap(int* a, int* b) {
    int c = *a;
    *a = *b;
    *b = c;
}

// Imprime uma estação na formatação correta, considerando os campos NULOs.

// e: Ponteiro para a estação a ser impressa
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

// Preenche a struct com valores nulos (-1 para inteiros e NULL para strings)

// temp: estação a ser realizado o preenchimento
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

// Conta a quantidade de estações DIFERENTES que tem

// arquivo: Arquivo binário contendo os registros.
int conta_estacao(FILE* arquivo) {

    fseek(arquivo,5,SEEK_SET);
    int registros; // Quantidade de registros existentes no arquivo
    fread(&registros,sizeof(int),1,arquivo);
    
    // Salva todos os nomes encontrados nos registros
    char* lista[registros];
    int diferentes = 0; // Contador de quantos nomes diferentes tem nos registros

    // Iterando por cada registro
    for(int i = 0; i < registros; i++) {
        fseek(arquivo,17 + (80 * i),SEEK_SET); // O cabeçalho tem 17 bytes e cada registro tem 80 bytes

        char removido;
        fread(&removido,sizeof(char),1,arquivo);
        if(removido == '1') continue; // Ignora estações marcadas como removidas

        // Le o nome da estação e armazena na frase.
        int tamstring;
        fseek(arquivo,17 + 29 + (80 * i),SEEK_SET);
        fread(&tamstring,sizeof(int),1,arquivo);
        char frase[tamstring + 1];                  //temos que sempre declarar um caractere a mais pois a função strcmp não funciona sem o \0 no final
        fread(frase,tamstring,1,arquivo);
        frase[tamstring] = '\0'; // Adicionando o terminador da string

        bool novo = true; // flag representando se o nome ainda não apareceu no registro.
        for(int j = 0; j < diferentes; j++) {
            if(strcmp(frase,lista[j]) == 0) { // Passa por cada nome já visto e marca o flag como falso se já existir
                novo = false;
                break;
            }
        }
        if(novo) {
            // Caso o nome não tenha aparecido ainda, precisamos salva-lo na lista.
            lista[diferentes] = malloc((tamstring + 1) * sizeof(char));
            for(int j = 0; j <= tamstring; j++){
                lista[diferentes][j] = frase[j];
            }
            diferentes++; // Incrementando o contador
        }
    }
    // Desalocando a memória
    for(int i = 0; i < diferentes; i++){
        free(lista[i]);
    }
    return diferentes;
}

// Conta a quantidade de pares estações DIFERENTES que tem. Essa função é quase idêntica a conta_estacao.

// arquivo: Arquivo binário contendo os registros.
int conta_par_estacao(FILE* arquivo) {
    
    fseek(arquivo,5,SEEK_SET);
    int registros; // Quantidade de registros existentes no arquivo
    fread(&registros,sizeof(int),1,arquivo);
    
    // Salva todos os pares de estação encontrados nos registros
    int lista[registros][2];
    int diferentes = 0; // Contador de quantos nomes diferentes tem nos registros
    
    // Iterando por cada registro
    for(int i = 0; i < registros; i++){
        fseek(arquivo,17 + (80 * i),SEEK_SET); // O cabeçalho tem 17 bytes e cada registro tem 80 bytes

        char removido;
        fread(&removido,sizeof(char),1,arquivo);
        if(removido == '1') continue; // Ignora estações removidas.

        // Lê os pares de estação e armazena.
        // id1: codEstacao
        // id2: codProxEstacao
        int id1, id2;
        fseek(arquivo,17 + 5 + (80 * i),SEEK_SET);
        fread(&id1,sizeof(int),1,arquivo);
        fseek(arquivo,17 + 13 + (80 * i),SEEK_SET);
        fread(&id2,sizeof(int),1,arquivo);
        if(id2 == -1) continue; // Nao existe codProxEstacao, entao ignora pois nao forma par.

        bool novo = true; // flag representando se o nome ainda não apareceu no registro.
        for(int j = 0; j < diferentes; j++){
            if(lista[j][0] == id1 && lista[j][1] == id2) { // Passa por par já visto e marca o flag como falso se já existir
                novo = false;
                break;
            }
        }
        if(novo) {
            // Caso o par não tenha aparecido ainda, precisamos salva-lo na lista.
            lista[diferentes][0] = id1;
            lista[diferentes][1] = id2;
            diferentes++;
        }
    }
    return diferentes; // Retorna a quantidade de pares de estações diferentes.
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
            free(temp);
        } else if(strcmp(s,"codEstIntegra") == 0) {
            char* temp = malloc(sizeof(char) * 20);
            scanf("%s",temp);
            if(strcmp(temp,"NULO") == 0){
                nova->codEstIntegra = -2;
                continue;
            }
            nova->codEstIntegra = atoi(temp);
            free(temp);
        } else if(strcmp(s,"nomeEstacao") == 0) {
            nova->nomeEstacao = malloc(sizeof(char) * 50);
            ScanQuoteString(nova->nomeEstacao);
            int tam = 0;
            while(nova->nomeEstacao[tam] != '\0') tam++;
            nova->tamNomeEstacao = tam;
        }else if(strcmp(s,"nomeLinha") == 0) {
            nova->nomeLinha = malloc(sizeof(char) * 50);
            ScanQuoteString(nova->nomeLinha);
            int tam = 0;
            while(nova->nomeLinha[tam] != '\0') tam++;
            nova->tamNomeLinha = tam;
        } else {
            printf("Campo invalido\n");
        }
    }
}

void estacao_para_binario(estacao *est, int index ,FILE* arquivo){
    fseek(arquivo,17 + (80 * index),SEEK_SET);
    int bytesusados = 37;
    fwrite(&est->removido,sizeof(char),1,arquivo);
    fwrite(&est->proximo,sizeof(int),1,arquivo);
    fwrite(&est->codEstacao,sizeof(int),1,arquivo);
    fwrite(&est->codLinha,sizeof(int),1,arquivo);
    fwrite(&est->codProxEstacao,sizeof(int),1,arquivo);
    fwrite(&est->distProxEstacao,sizeof(int),1,arquivo);
    fwrite(&est->codLinhaIntegra,sizeof(int),1,arquivo);
    fwrite(&est->codEstIntegra,sizeof(int),1,arquivo);
    int tam = 0;
    while(est->nomeEstacao[tam] != 0) tam++;
    fwrite(&tam,sizeof(int),1,arquivo);
    bytesusados += tam;
    fwrite(est->nomeEstacao,sizeof(char) * tam,1,arquivo);
    tam = 0;
    while(est->nomeLinha[tam] != 0)tam++;
    fwrite(&tam,sizeof(int),1,arquivo);
    bytesusados += tam;
    fwrite(est->nomeLinha,sizeof(char) * tam,1,arquivo);
    for(int i = bytesusados; i < 80; i++){
        fwrite(&cifrao,sizeof(char),1,arquivo);
    }
}

void binario_para_estacao(estacao *est, int index,FILE* arquivo){
    fseek(arquivo,17 + (80 * index),SEEK_SET);

    fread(&est->removido,sizeof(char),1,arquivo);
    fread(&est->proximo,sizeof(int),1,arquivo);
    fread(&est->codEstacao,sizeof(int),1,arquivo);
    fread(&est->codLinha,sizeof(int),1,arquivo);
    fread(&est->codProxEstacao,sizeof(int),1,arquivo);
    fread(&est->distProxEstacao,sizeof(int),1,arquivo);
    fread(&est->codLinhaIntegra,sizeof(int),1,arquivo);
    fread(&est->codEstIntegra,sizeof(int),1,arquivo);
    
    fread(&est->tamNomeEstacao,sizeof(int),1,arquivo);
    est->nomeEstacao = malloc((est->tamNomeEstacao + 1) * sizeof(char));
    fread(est->nomeEstacao,sizeof(char),est->tamNomeEstacao,arquivo);
    est->nomeEstacao[est->tamNomeEstacao] = '\0';
    
    fread(&est->tamNomeLinha,sizeof(int),1,arquivo);
    est->nomeLinha = malloc((est->tamNomeLinha + 1) * sizeof(char));
    fread(est->nomeLinha,sizeof(char),est->tamNomeLinha,arquivo);
    est->nomeLinha[est->tamNomeLinha] = '\0';
}