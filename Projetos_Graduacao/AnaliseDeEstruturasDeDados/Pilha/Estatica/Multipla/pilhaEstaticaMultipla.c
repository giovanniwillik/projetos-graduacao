#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Tamanho máximo da pilha
#define N 3     // Número de pilhas múltiplas

// Estrutura para representar uma pilha múltipla estática
typedef struct
{
    int topo[N];        // Vetor para armazenar os topos de cada pilha
    int elementos[MAX]; // Array único para armazenar todas as pilhas
    int limite[N + 1];  // Delimitação dos espaços das pilhas
} PilhaMultipla;

// Função para inicializar a pilha múltipla
void inicializarPilha(PilhaMultipla *p)
{
    int intervalo = MAX / N;
    for (int i = 0; i < N; i++)
    {
        p->topo[i] = (i * intervalo) - 1;
        p->limite[i] = i * intervalo;
    }
    p->limite[N] = MAX;
}

// Função para reinicializar a pilha múltipla
void reinicializarPilha(PilhaMultipla *p)
{
    inicializarPilha(p);
}

// Função para verificar se uma pilha específica está cheia
int pilhaCheia(PilhaMultipla *p, int k)
{
    return p->topo[k] == p->limite[k + 1] - 1;
}

// Função para verificar se uma pilha específica está vazia
int pilhaVazia(PilhaMultipla *p, int k)
{
    return p->topo[k] < p->limite[k];
}

// Função para empilhar (Push) um elemento em uma pilha específica
void push(PilhaMultipla *p, int k, int valor)
{
    if (pilhaCheia(p, k))
    {
        printf("Erro: Pilha %d cheia!\n", k);
        return;
    }
    p->elementos[++p->topo[k]] = valor;
}

// Função para desempilhar (Pop) um elemento de uma pilha específica
int pop(PilhaMultipla *p, int k)
{
    if (pilhaVazia(p, k))
    {
        printf("Erro: Pilha %d vazia!\n", k);
        return -1;
    }
    return p->elementos[p->topo[k]--];
}

// Função para deslocar os elementos de uma pilha para a direita
void deslocarDireita(PilhaMultipla *p, int k)
{
    if (pilhaCheia(p, k))
    {
        printf("Erro: Não é possível deslocar à direita, pilha %d cheia!\n", k);
        return;
    }
    for (int i = p->topo[k]; i >= p->limite[k]; i--)
    {
        p->elementos[i + 1] = p->elementos[i];
    }
    p->topo[k]++;
}

// Função para deslocar os elementos de uma pilha para a esquerda
void deslocarEsquerda(PilhaMultipla *p, int k)
{
    if (pilhaVazia(p, k))
    {
        printf("Erro: Não é possível deslocar à esquerda, pilha %d vazia!\n", k);
        return;
    }
    for (int i = p->limite[k]; i < p->topo[k]; i++)
    {
        p->elementos[i] = p->elementos[i + 1];
    }
    p->topo[k]--;
}

// Função para obter o tamanho de uma pilha específica
int tamanhoPilha(PilhaMultipla *p, int k)
{
    return p->topo[k] - p->limite[k] + 1;
}

// Função para exibir os elementos de todas as pilhas
void exibirPilhas(PilhaMultipla *p)
{
    for (int k = 0; k < N; k++)
    {
        printf("Pilha %d: ", k);
        if (pilhaVazia(p, k))
        {
            printf("(vazia)");
        }
        else
        {
            for (int i = p->limite[k]; i <= p->topo[k]; i++)
            {
                printf("%d ", p->elementos[i]);
            }
        }
        printf("\n");
    }
}

// Programa principal para demonstrar a pilha estática múltipla
int main()
{
    PilhaMultipla p;
    inicializarPilha(&p);

    push(&p, 0, 10);
    push(&p, 0, 20);
    push(&p, 1, 30);
    push(&p, 2, 40);
    push(&p, 2, 50);

    printf("Pilhas após inserções:\n");
    exibirPilhas(&p);

    printf("Elemento removido da pilha 0: %d\n", pop(&p, 0));

    deslocarDireita(&p, 2);
    printf("Pilhas após deslocamento à direita na pilha 2:\n");
    exibirPilhas(&p);

    deslocarEsquerda(&p, 2);
    printf("Pilhas após deslocamento à esquerda na pilha 2:\n");
    exibirPilhas(&p);

    reinicializarPilha(&p);
    printf("Pilhas após reinicialização:\n");
    exibirPilhas(&p);

    return 0;
}
