#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arquivo;

    // abre o arquivo em modo leitura ("r" = read)
    arquivo = fopen("dados.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    
    printf(" ----- Dados Gravados  ----- \n");
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);  // imprime cada linha lida
    }
    printf(" --------------------------- \n");
    fclose(arquivo);
    return 0;
}