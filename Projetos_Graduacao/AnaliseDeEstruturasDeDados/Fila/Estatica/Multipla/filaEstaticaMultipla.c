#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAX 100
#define NUM_FILAS 3

// Estrutura da fila estática múltipla
typedef struct
{
    int itens[TAMANHO_MAX];
    int frente[NUM_FILAS], tras[NUM_FILAS];
    int limites[NUM_FILAS + 1];
} Filas;

// Função para inicializar as filas
void inicializar(Filas *f)
{
    int intervalo = TAMANHO_MAX / NUM_FILAS;
    for (int i = 0; i < NUM_FILAS; i++)
    {
        f->frente[i] = -1;
        f->tras[i] = -1;
        f->limites[i] = i * intervalo;
    }
    f->limites[NUM_FILAS] = TAMANHO_MAX;
}

// Função para verificar se uma fila está cheia
int estaCheia(Filas *f, int fila)
{
    return f->tras[fila] == f->limites[fila + 1] - 1;
}

// Função para verificar se uma fila está vazia
int estaVazia(Filas *f, int fila)
{
    return f->frente[fila] == -1 || f->frente[fila] > f->tras[fila];
}

// Função para adicionar um elemento a uma fila específica (Enqueue)
void enqueue(Filas *f, int fila, int valor)
{
    if (estaCheia(f, fila))
    {
        printf("Fila %d cheia!\n", fila);
        return;
    }
    if (f->frente[fila] == -1)
    {
        f->frente[fila] = f->limites[fila];
    }
    f->tras[fila] = (f->tras[fila] == -1) ? f->limites[fila] : f->tras[fila] + 1;
    f->itens[f->tras[fila]] = valor;
    printf("Elemento %d inserido na fila %d.\n", valor, fila);
}

// Função para remover um elemento de uma fila específica (Dequeue)
int dequeue(Filas *f, int fila)
{
    if (estaVazia(f, fila))
    {
        printf("Fila %d vazia!\n", fila);
        return -1;
    }
    int valorRemovido = f->itens[f->frente[fila]];
    f->frente[fila]++;
    return valorRemovido;
}

// Função para obter o tamanho atual de uma fila específica
int tamanho(Filas *f, int fila)
{
    if (estaVazia(f, fila))
        return 0;
    return f->tras[fila] - f->frente[fila] + 1;
}

// Função para exibir uma fila específica
void exibir(Filas *f, int fila)
{
    if (estaVazia(f, fila))
    {
        printf("Fila %d vazia!\n", fila);
        return;
    }
    printf("Fila %d: ", fila);
    for (int i = f->frente[fila]; i <= f->tras[fila]; i++)
    {
        printf("%d ", f->itens[i]);
    }
    printf("\n");
}

// Função para reinicializar as filas
void reinicializar(Filas *f)
{
    inicializar(f);
    printf("Filas reinicializadas!\n");
}

// Função principal para testar as filas estáticas múltiplas
int main()
{
    Filas filas;
    inicializar(&filas);

    enqueue(&filas, 0, 10);
    enqueue(&filas, 0, 20);
    enqueue(&filas, 1, 30);
    enqueue(&filas, 2, 40);

    exibir(&filas, 0);
    exibir(&filas, 1);
    exibir(&filas, 2);

    printf("Elemento removido da fila 0: %d\n", dequeue(&filas, 0));
    exibir(&filas, 0);

    printf("Tamanho da fila 1: %d\n", tamanho(&filas, 1));

    reinicializar(&filas);
    exibir(&filas, 0);
    exibir(&filas, 1);
    exibir(&filas, 2);

    return 0;
}
