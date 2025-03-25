#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAX 100

// Estrutura do nó da fila de prioridade
typedef struct
{
    int dado;
    int prioridade;
} Elemento;

// Estrutura da fila de prioridade
typedef struct
{
    Elemento itens[TAMANHO_MAX];
    int tamanho;
} FilaPrioridade;

// Função para inicializar a fila de prioridade
void inicializar(FilaPrioridade *f)
{
    f->tamanho = 0;
}

// Função para verificar se a fila está vazia
int estaVazia(FilaPrioridade *f)
{
    return f->tamanho == 0;
}

// Função para verificar se a fila está cheia
int estaCheia(FilaPrioridade *f)
{
    return f->tamanho == TAMANHO_MAX;
}

// Função para inserir um elemento na fila de prioridade (Enqueue)
void enqueue(FilaPrioridade *f, int valor, int prioridade)
{
    if (estaCheia(f))
    {
        printf("Fila de prioridade cheia!\n");
        return;
    }

    // Encontrar posição correta para inserção
    int i = f->tamanho - 1;
    while (i >= 0 && f->itens[i].prioridade > prioridade)
    {
        f->itens[i + 1] = f->itens[i];
        i--;
    }

    // Inserir elemento
    f->itens[i + 1].dado = valor;
    f->itens[i + 1].prioridade = prioridade;
    f->tamanho++;
    printf("Elemento %d (prioridade %d) inserido.\n", valor, prioridade);
}

// Função para remover um elemento da fila de prioridade (Dequeue)
int dequeue(FilaPrioridade *f)
{
    if (estaVazia(f))
    {
        printf("Fila de prioridade vazia!\n");
        return -1;
    }
    int valorRemovido = f->itens[0].dado;
    for (int i = 0; i < f->tamanho - 1; i++)
    {
        f->itens[i] = f->itens[i + 1];
    }
    f->tamanho--;
    return valorRemovido;
}

// Função para obter o tamanho da fila de prioridade
int tamanho(FilaPrioridade *f)
{
    return f->tamanho;
}

// Função para exibir os elementos da fila de prioridade
void exibir(FilaPrioridade *f)
{
    if (estaVazia(f))
    {
        printf("Fila de prioridade vazia!\n");
        return;
    }
    printf("Fila de Prioridade: ");
    for (int i = 0; i < f->tamanho; i++)
    {
        printf("(%d, P%d) ", f->itens[i].dado, f->itens[i].prioridade);
    }
    printf("\n");
}

// Função para reinicializar a fila de prioridade
void reinicializar(FilaPrioridade *f)
{
    inicializar(f);
    printf("Fila de prioridade reinicializada!\n");
}

// Função principal para testar a fila de prioridade
int main()
{
    FilaPrioridade fila;
    inicializar(&fila);

    enqueue(&fila, 10, 2);
    enqueue(&fila, 20, 1);
    enqueue(&fila, 30, 3);

    exibir(&fila);

    printf("Elemento removido: %d\n", dequeue(&fila));

    exibir(&fila);

    printf("Tamanho da fila: %d\n", tamanho(&fila));

    reinicializar(&fila);
    exibir(&fila);

    return 0;
}
