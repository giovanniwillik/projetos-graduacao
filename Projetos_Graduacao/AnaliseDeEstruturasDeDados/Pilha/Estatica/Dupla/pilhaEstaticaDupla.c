#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Tamanho máximo do array que armazena as pilhas

// Estrutura para representar uma pilha dupla
typedef struct
{
    int topo1;          // Topo da primeira pilha
    int topo2;          // Topo da segunda pilha
    int elementos[MAX]; // Array que armazena ambas as pilhas
} PilhaDupla;

// Inicializa a pilha dupla
void inicializarPilha(PilhaDupla *p)
{
    p->topo1 = -1;  // Pilha 1 começa do início
    p->topo2 = MAX; // Pilha 2 começa do final
}

// Reinicializa a pilha dupla (resetar)
void reinicializarPilha(PilhaDupla *p)
{
    inicializarPilha(p);
}

// Verifica se a pilha está cheia
int pilhaCheia(PilhaDupla *p)
{
    return p->topo1 + 1 == p->topo2;
}

// Verifica se uma pilha específica está vazia
int pilhaVazia(PilhaDupla *p, int id)
{
    if (id == 1)
        return p->topo1 == -1;
    if (id == 2)
        return p->topo2 == MAX;
    return 1; // ID inválido
}

// Insere um elemento na pilha escolhida (1 ou 2)
void push(PilhaDupla *p, int id, int valor)
{
    if (pilhaCheia(p))
    {
        printf("Erro: Pilhas estão cheias!\n");
        return;
    }
    if (id == 1)
    {
        p->elementos[++p->topo1] = valor;
    }
    else if (id == 2)
    {
        p->elementos[--p->topo2] = valor;
    }
    else
    {
        printf("Erro: ID de pilha inválido!\n");
    }
}

// Remove um elemento da pilha escolhida (1 ou 2)
int pop(PilhaDupla *p, int id)
{
    if (pilhaVazia(p, id))
    {
        printf("Erro: Pilha %d vazia!\n", id);
        return -1;
    }
    if (id == 1)
    {
        return p->elementos[p->topo1--];
    }
    else if (id == 2)
    {
        return p->elementos[p->topo2++];
    }
    return -1;
}

// Retorna o tamanho da pilha escolhida (1 ou 2)
int tamanhoPilha(PilhaDupla *p, int id)
{
    if (id == 1)
        return p->topo1 + 1;
    if (id == 2)
        return MAX - p->topo2;
    return -1; // ID inválido
}

// Exibe os elementos de ambas as pilhas
void exibirPilhas(PilhaDupla *p)
{
    printf("Pilha 1: ");
    if (pilhaVazia(p, 1))
        printf("(vazia)");
    for (int i = 0; i <= p->topo1; i++)
    {
        printf("%d ", p->elementos[i]);
    }
    printf("\n");

    printf("Pilha 2: ");
    if (pilhaVazia(p, 2))
        printf("(vazia)");
    for (int i = MAX - 1; i >= p->topo2; i--)
    {
        printf("%d ", p->elementos[i]);
    }
    printf("\n");
}

// Programa principal para demonstrar a pilha dupla
int main()
{
    PilhaDupla p;
    inicializarPilha(&p);

    push(&p, 1, 10);
    push(&p, 1, 20);
    push(&p, 2, 30);
    push(&p, 2, 40);

    printf("Pilhas após inserções:\n");
    exibirPilhas(&p);

    printf("Elemento removido da pilha 1: %d\n", pop(&p, 1));
    printf("Elemento removido da pilha 2: %d\n", pop(&p, 2));

    printf("Tamanho da pilha 1: %d\n", tamanhoPilha(&p, 1));
    printf("Tamanho da pilha 2: %d\n", tamanhoPilha(&p, 2));

    reinicializarPilha(&p);
    printf("Pilhas após reinicialização:\n");
    exibirPilhas(&p);

    return 0;
}
