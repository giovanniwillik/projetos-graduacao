#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Tamanho máximo da pilha

// Estrutura da pilha estática
typedef struct
{
    int topo;           // Índice do topo da pilha
    int elementos[MAX]; // Array que armazena os elementos da pilha
} Pilha;

// Função para inicializar a pilha
void inicializarPilha(Pilha *p)
{
    p->topo = -1; // Pilha vazia
}

// Função para reinicializar a pilha (resetar)
void reinicializarPilha(Pilha *p)
{
    p->topo = -1;
}

// Função para verificar se a pilha está cheia
int pilhaCheia(Pilha *p)
{
    return p->topo == MAX - 1;
}

// Função para verificar se a pilha está vazia
int pilhaVazia(Pilha *p)
{
    return p->topo == -1;
}

// Função para empilhar (Push) um elemento
void push(Pilha *p, int valor)
{
    if (pilhaCheia(p))
    {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->elementos[++p->topo] = valor;
}

// Função para desempilhar (Pop) um elemento
int pop(Pilha *p)
{
    if (pilhaVazia(p))
    {
        printf("Erro: Pilha vazia!\n");
        return -1; // Valor de erro
    }
    return p->elementos[p->topo--];
}

// Função para obter o tamanho da pilha
int tamanhoPilha(Pilha *p)
{
    return p->topo + 1;
}

// Função para exibir os elementos da pilha
void exibirPilha(Pilha *p)
{
    if (pilhaVazia(p))
    {
        printf("Pilha vazia!\n");
        return;
    }
    printf("Elementos da pilha: ");
    for (int i = 0; i <= p->topo; i++)
    {
        printf("%d ", p->elementos[i]);
    }
    printf("\n");
}

// Programa principal para testar a pilha estática
int main()
{
    Pilha p;
    inicializarPilha(&p);

    push(&p, 10);
    push(&p, 20);
    push(&p, 30);

    exibirPilha(&p);

    printf("Elemento removido: %d\n", pop(&p));
    printf("Tamanho da pilha: %d\n", tamanhoPilha(&p));

    reinicializarPilha(&p);
    printf("Pilha reinicializada.\n");
    exibirPilha(&p);

    return 0;
}
