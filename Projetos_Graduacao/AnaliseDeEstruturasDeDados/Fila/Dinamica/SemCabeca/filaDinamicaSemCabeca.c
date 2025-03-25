#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da fila dinâmica
typedef struct No
{
    int dado;
    struct No *proximo;
} No;

// Estrutura da fila dinâmica sem cabeça
typedef struct
{
    No *frente;
    No *tras;
    int tamanho;
} Fila;

// Função para inicializar a fila
void inicializar(Fila *f)
{
    f->frente = NULL;
    f->tras = NULL;
    f->tamanho = 0;
}

// Função para verificar se a fila está vazia
int estaVazia(Fila *f)
{
    return f->frente == NULL;
}

// Função para inserir um elemento na fila (Enqueue)
void enqueue(Fila *f, int valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    if (!novoNo)
    {
        printf("Erro de alocação de memória!\n");
        return;
    }
    novoNo->dado = valor;
    novoNo->proximo = NULL;

    if (estaVazia(f))
    {
        f->frente = novoNo;
    }
    else
    {
        f->tras->proximo = novoNo;
    }
    f->tras = novoNo;
    f->tamanho++;
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
    No *temp = f->frente;
    int valorRemovido = temp->dado;
    f->frente = f->frente->proximo;
    free(temp);

    if (f->frente == NULL)
    {
        f->tras = NULL;
    }
    f->tamanho--;
    return valorRemovido;
}

// Função para obter o tamanho da fila
int tamanho(Fila *f)
{
    return f->tamanho;
}

// Função para exibir os elementos da fila
void exibir(Fila *f)
{
    if (estaVazia(f))
    {
        printf("Fila vazia!\n");
        return;
    }
    No *atual = f->frente;
    printf("Fila: ");
    while (atual)
    {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}

// Função para reinicializar a fila
void reinicializar(Fila *f)
{
    while (!estaVazia(f))
    {
        dequeue(f);
    }
    printf("Fila reinicializada!\n");
}

// Função principal para testar a fila dinâmica sem cabeça
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
