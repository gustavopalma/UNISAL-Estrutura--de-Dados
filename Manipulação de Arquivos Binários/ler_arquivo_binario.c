#include <stdio.h>
#include <stdlib.h>

typedef struct _pessoa {
    long id; // para dos dados indexação
    char nome[100];
    int idade;
    char endereco[100];
} pessoa;


int main() {
    pessoa p;
    FILE *arquivo;

    // abre o arquivo em modo leitura ("r" = read)
    arquivo = fopen("dados.dat", "ab");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    
    printf(" ----- Dados Gravados  ----- \n");
    while (fread(&p, sizeof(pessoa), 1, f)) {
        printf("ID: %ld | Nome: %s | Idade: %d | Endereço: %s\n",
               p.id, p.nome, p.idade, p.endereco);
    }
    printf(" --------------------------- \n");
    fclose(arquivo);
    return 0;
}