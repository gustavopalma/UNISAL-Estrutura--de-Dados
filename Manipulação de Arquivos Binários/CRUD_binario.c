#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _pessoa {
    long id; // para dos dados indexação
    char nome[100];
    int idade;
    char endereco[100];
} pessoa;

#define ARQUIVO "pessoas.dat"
#define TEMPORARIO "temp.dat"

//Protótipos de Função
void gravarPessoa(const pessoa p);
void listarPessoas();
void atualizarPessoa(long id, pessoa nova);
void removerPessoa(long id);
void limpaTela();
pessoa pessoaEntradaUsuario(bool somenteId);
void limparBufferDoTeclado();

// Programa Principal
int main() {
    int opcao = 0;
    while(opcao != 5){
        limpaTela();
        printf("*************** CRUD com arquivos em C ***************\n");
        printf("* Insira a Opção Desejada:                           *\n");
        printf("*   1 - Cadastrar Pessoa;                            *\n");
        printf("*   2 - Listar Pessoas Cadastradas;                  *\n");
        printf("*   3 - Editar Pessoas Cadastradas;                  *\n");
        printf("*   4 - Excluir Pessoa Cadastrada;                   *\n");
        printf("*   5 - Sair;                                        *\n");
        printf("******************************************************\n");
        printf("Opção Escolhida: ");
        // Lê a opção escolhida
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:{
                    limparBufferDoTeclado();
                    pessoa p = pessoaEntradaUsuario(false);
                    gravarPessoa(p);
                }
            break;

            case 2: {
                    limparBufferDoTeclado();
                    listarPessoas();
                }
            break;
            
            case 3: {
                limparBufferDoTeclado();
                listarPessoas();
                limparBufferDoTeclado();
                printf("Insira o ID da pessoa para alterar:\n");
                pessoa p = pessoaEntradaUsuario(true);
                limparBufferDoTeclado();
                pessoa pessoaNova = pessoaEntradaUsuario(false);
                limparBufferDoTeclado();
                atualizarPessoa(p.id, pessoaNova);
            }   
            break;
            
            case 4: {
                limparBufferDoTeclado();
                listarPessoas();
                printf("Insira o ID da pessoa para remover:\n");
                pessoa p = pessoaEntradaUsuario(true);
                removerPessoa(p.id);
            }
            break;

            case 5:
                break;
            break;
        
            default:
                limparBufferDoTeclado();
            continue;
        }
    }
    return 0;
}

void limpaTela() {
// Macro para saber se o programa está sendo executado no windows ou no linux, e limpar a tela da forma correta
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

pessoa pessoaEntradaUsuario(bool somenteId) {
    pessoa p;
    do {
       printf("Insira o id:\n");    
    } while(scanf("%ld", &p.id) <= 0);
    getchar(); //necessário para limpar o caractere /n, ignorado pelo scanf  
    if(somenteId) {
      return p;   
    }
    do {
        printf("Insira o nome:\n");
    } while (fgets(p.nome, sizeof(p.nome), stdin) == NULL);
    
    do {
       printf("Insira a Idade:\n");    
    } while(scanf("%d", &p.idade) <= 0);
    getchar(); //necessário para limpar o caractere /n, ignorado pelo scanf
    do {
        printf("Insira o endereço:\n");
        fflush(stdin);
    } while (fgets(p.endereco, sizeof(p.endereco), stdin) == NULL);
    return p;
}

// Função para inserir pessoa (CREATE)
void gravarPessoa(const pessoa p) {
    FILE *f = fopen(ARQUIVO, "ab"); // append binário
    if (!f) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    fwrite(&p, sizeof(pessoa), 1, f);
    fclose(f);
    printf("Pessoa Cadastrada Com sucesso!\n");
    printf("Pressione Qualquer Tecla para continuar!\n");
    getchar(); // espera qualquer tecla ser pressionada;
}

// Função para listar todas as pessoas (READ)
void listarPessoas() {
    FILE *f = fopen(ARQUIVO, "rb");
    if (!f) {
        printf("Nenhum registro encontrado.\n");
        return;
    }

    pessoa p;
    printf("\n--- Lista de Pessoas ---\n");
    while (fread(&p, sizeof(pessoa), 1, f)) {
        printf("ID: %ld | Nome: %s | Idade: %d | Endereço: %s\n",
               p.id, p.nome, p.idade, p.endereco);
    }
    fclose(f);
    printf("Pressione qualquer tecla para continuar\n");
    getchar();
}

// Função para atualizar uma pessoa pelo ID (UPDATE)
void atualizarPessoa(long id, pessoa nova) {
    FILE *f = fopen(ARQUIVO, "r+b"); // leitura+escrita binária
    if (!f) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    pessoa p;
    while (fread(&p, sizeof(pessoa), 1, f)) {
        if (p.id == id) {
            fseek(f, -sizeof(pessoa), SEEK_CUR); // volta 1 registro
            fwrite(&nova, sizeof(pessoa), 1, f);
            printf("Registro atualizado!\n");
            getchar(); // espera qualquer tecla ser pressionada;
            fclose(f);
            return;
        }
    }
    printf("ID %ld não encontrado!\n", id);
    fclose(f);
    getchar(); // espera qualquer tecla ser pressionada;
}

// Função para remover uma pessoa pelo ID (DELETE)
void removerPessoa(long id) {
    FILE *f = fopen(ARQUIVO, "rb");
    FILE *temp = fopen(TEMPORARIO, "wb");
    if (!f || !temp) {
        printf("Erro ao abrir arquivos!\n");
        return;
    }

    pessoa p;
    int removido = 0;
    while (fread(&p, sizeof(pessoa), 1, f)) {
        if (p.id == id) {
            removido = 1; // não grava no novo arquivo
        } else {
            fwrite(&p, sizeof(pessoa), 1, temp);
        }
    }

    fclose(f);
    fclose(temp);

    remove(ARQUIVO);          // remove original
    rename("temp.dat", ARQUIVO); // renomeia temporário

    if (removido)
        printf("Registro removido!\n");
    else
        printf("ID %ld não encontrado!\n", id);
    getchar(); // espera qualquer tecla ser pressionada;
}

void limparBufferDoTeclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}