#include <stdio.h>
#include <stdlib.h>

typedef struct _pessoa {
    char nome[100];
    int idade;
    char endereco[100];
} pessoa;

int main() {
    pessoa p;
    FILE *arquivo;
    arquivo = fopen("dados.txt", "w");

    printf(" ----- Cadastro de Pessoas -----\n");
    do {
        printf("| Insira o nome:\n");
    } while (fgets(p.nome, sizeof(p.nome), stdin) == NULL);
    
    do {
       printf("| Insira a Idade:\n");    
    } while(scanf("%d", &p.idade) <= 0);
    getchar();//necessário para limpar o caractere /n, ignorado pelo scanf
    do {
        printf("| Insira o endereço:\n");
        fflush(stdin);
    } while (fgets(p.endereco, sizeof(p.endereco), stdin) == NULL);
    printf(" ------------------------------\n");

    
    // abre o arquivo em modo escrita ("w" = write)
    arquivo = fopen("dados.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // escreve algumas informações no arquivo
    fprintf(arquivo, "Nome: %s\n",p.nome);
    fprintf(arquivo, "Idade: %d\n", p.idade);
    fprintf(arquivo, "Endereço: %s\n", p.endereco);

    // fecha o arquivo (muito importante!)
    fflush(arquivo);
    fclose(arquivo);
    
    printf(" ----- Dados Gravados  ----- \n");
    printf("| Nome: %s\n", p.nome);
    printf("| Idade %d\n", p.idade);
    printf("| Endereço: %s\n", p.endereco);

    return 0;
}