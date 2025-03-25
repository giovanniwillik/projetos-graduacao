#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAX 100

// Estrutura da fila estática
typedef struct
{
    int itens[TAMANHO_MAX];
    int frente, tras;
} Fila;

// Função para inicializar a fila
void inicializar(Fila *f)
{
    f->frente = -1;
    f->tras = -1;
}

// Função para verificar se a fila está cheia
int estaCheia(Fila *f)
{
    return f->tras == TAMANHO_MAX - 1;
}

// Função para verificar se a fila está vazia
int estaVazia(Fila *f)
{
    return f->frente == -1 || f->frente > f->tras;
}

// Função para adicionar um elemento à fila (Enqueue)
void enqueue(Fila *f, int valor)
{
    if (estaCheia(f))
    {
        printf("Fila cheia!\n");
        return;
    }
    if (f->frente == -1)
    {
        f->frente = 0;
    }
    f->itens[++f->tras] = valor;
    printf("Elemento %d inserido na fila.\n", valor);
}

// Função para remover um elemento da fila (Dequeue)
int dequeue(Fila *f)
{
    if (estaVazia(f))
    {
        printf("Fila vazia!\n");
        return -1;
    }
    int valorRemovido = f->itens[f->frente];
    f->frente++;
    return valorRemovido;
}

// Função para obter o tamanho atual da fila
int tamanho(Fila *f)
{
    if (estaVazia(f))
        return 0;
    return f->tras - f->frente + 1;
}

// Função para exibir a fila
void exibir(Fila *f)
{
    if (estaVazia(f))
    {
        printf("Fila vazia!\n");
        return;
    }
    printf("Fila: ");
    for (int i = f->frente; i <= f->tras; i++)
    {
        printf("%d ", f->itens[i]);
    }
    printf("\n");
}

// Função para reinicializar a fila
void reinicializar(Fila *f)
{
    inicializar(f);
    printf("Fila reinicializada!\n");
}

// Função principal para testar a fila estática
int main()
{
    Fila fila;
    inicializar(&fila);

    enqueue(&fila, 10);
    enqueue(&fila, 20);
    enqueue(&fila, 30);

    exibir(&fila);

    printf("Elemento removido: %d\n", dequeue(&fila));

    exibir(&fila);

    printf("Tamanho da fila: %d\n", tamanho(&fila));

    reinicializar(&fila);
    exibir(&fila);

    return 0;
}
