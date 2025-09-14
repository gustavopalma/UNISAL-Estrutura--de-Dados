#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do elemento da fila
typedef struct Elemento
{
    int prioridade;        // menor número = maior prioridade
    char nome[50];         // nome do paciente/tarefa
    struct Elemento *prox; // ponteiro para o próximo elemento
} Elemento;

// Estrutura da fila de prioridade
typedef struct
{
    Elemento *inicio;
} FilaPrioridade;

// Função para criar um novo elemento
Elemento *criarElemento(const char *nome, int prioridade)
{
    Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
    strcpy(novo->nome, nome);
    novo->prioridade = prioridade;
    novo->prox = NULL;
    return novo;
}

// Inserir elemento na fila de prioridade (ordenado por prioridade)
void inserir(FilaPrioridade *fila, const char *nome, int prioridade)
{
    Elemento *novo = criarElemento(nome, prioridade);

    // Se a fila está vazia ou o novo elemento tem maior prioridade que o primeiro
    if (fila->inicio == NULL || prioridade < fila->inicio->prioridade)
    {
        novo->prox = fila->inicio;
        fila->inicio = novo;
    }
    else
    {
        // Percorrer para encontrar a posição correta
        Elemento *atual = fila->inicio;
        while (atual->prox != NULL && atual->prox->prioridade <= prioridade)
        {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }

    printf("Inserido: %s (Prioridade %d)\n", nome, prioridade);
}

// Remover elemento da fila (atender paciente de maior prioridade)
void remover(FilaPrioridade *fila)
{
    if (fila->inicio == NULL)
    {
        printf("Fila vazia! Nada para remover.\n");
        return;
    }

    Elemento *temp = fila->inicio;
    printf("Removendo: %s (Prioridade %d)\n", temp->nome, temp->prioridade);
    fila->inicio = fila->inicio->prox;
    free(temp);
}

// Exibir estado da fila
void exibir(FilaPrioridade *fila)
{
    printf("Fila atual: ");
    if (fila->inicio == NULL)
    {
        printf("[vazia]\n");
        return;
    }

    printf("\n");
    Elemento *atual = fila->inicio;
    while (atual != NULL)
    {
        printf("(%d) -> %s", atual->prioridade, atual->nome);
        atual = atual->prox;
    }
    
}

void pressione_continuar() {
    printf("Pressione Qualquer tecla para continuar\n");
    getchar();
}

int main()
{
    FilaPrioridade fila = {NULL};
    int opcao = 0;
    char nome[50] = {0};
    int prioridade = 0;
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
                printf("insira a prioridade:\n");
                scanf("%d",&prioridade);
                inserir(&fila, nome, prioridade);
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
