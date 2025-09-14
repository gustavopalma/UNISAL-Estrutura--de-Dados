#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó da fila
typedef struct _Elemento {
    char dado[50];        // valor armazenado (pode ser int, string, etc.)
    struct _Elemento* prox;      // ponteiro para o próximo nó
} Elemento;

// Estrutura da fila (mantém ponteiros para início e fim)
typedef struct {
    Elemento* inicio;
    Elemento* fim;
} Fila;

// Inicializar fila
void inicializar(Fila* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// Verifica se a fila está vazia
int vazia(Fila* f) {
    return (f->inicio == NULL);
}

// Inserir elemento no final da fila (enqueue)
void inserir(Fila* f, const char* valor) {
    Elemento* novo = (Elemento*) malloc(sizeof(Elemento));
    strcpy(novo->dado, valor);
    novo->prox = NULL;

    if (vazia(f)) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }

    printf("Inserido: %s\n", valor);
}

// Remover elemento do início da fila (dequeue)
void remover(Fila* f) {
    if (vazia(f)) {
        printf("Fila vazia! Nada a remover.\n");
        return;
    }

    Elemento* temp = f->inicio;
    printf("Removido: %s\n", temp->dado);

    f->inicio = f->inicio->prox;
    if (f->inicio == NULL) {
        f->fim = NULL; // fila ficou vazia
    }

    free(temp);
}

// Exibir fila
void exibir(Fila* f) {
    if (vazia(f)) {
        printf("Fila: [vazia]\n");
        return;
    }

    Elemento* atual = f->inicio;
    printf("Fila: ");
    printf("\n");
    while (atual != NULL) {
        printf("-> %s \n", atual->dado);
        atual = atual->prox;
    }
}

void pressione_continuar() {
    printf("Pressione Qualquer tecla para continuar\n");
    getchar();
}

int main()
{
    Fila fila = {NULL};
    int opcao = 0;
    char nome[50] = {0};
    while (1){
        printf("************************************************\n");
        printf("*                                              *\n");
        printf("* 1 - Exibir fila                              *\n");
        printf("* 2 - Inserir elementos fila                   *\n");
        printf("* 3 - Remover Elementos da fila                *\n");
        printf("* 4 - Sair                                     *\n");
        printf("*                                              *\n");
        printf("************************************************\n");
        scanf("%d", &opcao);
        getchar();
        switch (opcao)
        {
            case 1:
            {
                exibir(&fila);
                pressione_continuar();
                break;
            }
            case 2:
            {
                printf("Insira o nome para a fila:\n");
                fgets(nome, sizeof(nome), stdin);
                inserir(&fila, nome);
                break;
            }

            case 3:
            {
                remover(&fila);
                pressione_continuar();
                break;
            }

            case 4:
            {
                return 0;
            }
        }
    } 
}
