#include "buscar.h"

// Checa se a estação temp satisfaz as condições para a busca.

// base: Representa as condições que devem ser satisfeitas.
//       Caso um campo seja NULO, ele é representado por -2
//       Caso um campo não seja especificado (não é uma condição para buscar), ele é representado por -1
// temp: Representa a estação em que estamos checando se satisfaz a base.
//       Caso um campo seja NULO, ele é representado por -1
bool satisfazBase(estacao* base, estacao* temp) {
    // Passamos por cada campo do registro checando se é igual
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
        if(base->codLinhaIntegra == -2) { // NULO
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
    if(base->nomeEstacao != NULL && strcmp(base->nomeEstacao, temp->nomeEstacao) != 0) {
        return false;
    }
    if(base->nomeLinha != NULL && strcmp(base->nomeLinha, temp->nomeLinha) != 0) {
        return false;
    }

    return true; // A estação temp satisfaz as condições para busca
}

// Retorna quantas estações foram buscadas

// base: Representa as condições que devem ser satisfeitas.
//       Caso um campo seja NULO, ele é representado por -2
//       Caso um campo não seja especificado (não é uma condição para buscar), ele é representado por -1
// encontrados: Ponteiro para lista de inteiro representando os RRN das estações encontradas.
//       Inicialmente deve ser NULL.
//       IMPORTANTE: Lembrar de desalocar após o uso da função
// arquivo: Arquivo binário dos registros onde será feito a busca
// imprimir: Um booleano que representa se as estações buscadas devem ser impressas ou não.
int buscar_estacao(estacao* base, int** encontrados, FILE* arquivo, bool imprimir) {
    int limite = 100; // Representa o tamanho da lista de encontrados, ela é alocada dinamicamente. Caso o limite passe, nós vamos duplicando o tamanho até ser o suficiente.
    *encontrados = malloc(limite*sizeof(int));

    fseek(arquivo, 5, SEEK_SET);
    int cont = 0;
    int tam; // Quantidade de registros no arquivo
    fread(&tam,sizeof(int),1,arquivo);

    for(int i = 0; i < tam; i++) { // Iterando sobre cada registro
        fseek(arquivo,17 + i * 80,SEEK_SET); // O cabeçalho tem 17 bytes e cada registro tem 80 bytes.

        // Colocando o registro atual em 'temp'
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
        
        if(satisfazBase(base, &temp)) { // Caso a estação deva ser buscada, podemos imprimi-la, e colocamos o seu RRN na lista de encontrados.
            if(imprimir) {
                cont++;
                printar_estacao(&temp);
                continue;
            }
            (*encontrados)[cont++] = i;
            if(cont > limite-10) { // Checa se o tamanho da lista encontrados está perto do limite. Se tiver perto, duplicamos o limite.
                limite *= 2;
                (*encontrados) = realloc((*encontrados), limite*sizeof(int));
            }
        }
    }
    if(imprimir == 1 && cont == 0) printf("Registro inexistente.\n");
    return cont; // Retorna a quantidade de estações buscadas
}