#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int a = 8457384;

    FILE* arquivo;
    arquivo = fopen("testear.bin", "wb");
    fwrite(&a,sizeof(int),1,arquivo);
    fclose(arquivo);
    arquivo = fopen("testear.bin", "rb");
    int x;
    fread(&x,sizeof(int),1,arquivo);
    printf("%d",x);
    fclose(arquivo);
}