#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da pilha
typedef struct No
{
    int dado;
    struct No *proximo;
} No;

// Estrutura da pilha dinâmica
typedef struct
{
    No *topo;
    int tamanho;
} Pilha;

// Inicializa a pilha
void inicializarPilha(Pilha *p)
{
    p->topo = NULL;
    p->tamanho = 0;
}

// Reinicializa a pilha (limpa todos os elementos)
void reinicializarPilha(Pilha *p)
{
    while (p->topo != NULL)
    {
        No *temp = p->topo;
        p->topo = p->topo->proximo;
        free(temp);
    }
    p->tamanho = 0;
}

// Verifica se a pilha está vazia
int estaVazia(Pilha *p)
{
    return p->topo == NULL;
}

// Empilha (Push) um elemento
void push(Pilha *p, int valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    if (!novoNo)
    {
        printf("Erro: Falha na alocação de memória!\n");
        return;
    }
    novoNo->dado = valor;
    novoNo->proximo = p->topo;
    p->topo = novoNo;
    p->tamanho++;
}

// Desempilha (Pop) um elemento
int pop(Pilha *p)
{
    if (estaVazia(p))
    {
        printf("Erro: Pilha vazia!\n");
        return -1;
    }
    No *temp = p->topo;
    int valor = temp->dado;
    p->topo = p->topo->proximo;
    free(temp);
    p->tamanho--;
    return valor;
}

// Retorna o elemento do topo sem removê-lo (Peak)
int peak(Pilha *p)
{
    if (estaVazia(p))
    {
        printf("Erro: Pilha vazia!\n");
        return -1;
    }
    return p->topo->dado;
}

// Retorna o tamanho da pilha
int tamanhoPilha(Pilha *p)
{
    return p->tamanho;
}

// Exibe os elementos da pilha
void exibirPilha(Pilha *p)
{
    if (estaVazia(p))
    {
        printf("Pilha vazia!\n");
        return;
    }
    No *atual = p->topo;
    printf("Pilha: ");
    while (atual != NULL)
    {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}

// Programa principal para demonstrar a pilha dinâmica
int main()
{
    Pilha p;
    inicializarPilha(&p);

    push(&p, 10);
    push(&p, 20);
    push(&p, 30);

    printf("Pilha após inserções:\n");
    exibirPilha(&p);

    printf("Elemento no topo: %d\n", peak(&p));
    printf("Elemento removido: %d\n", pop(&p));

    printf("Pilha após remoção:\n");
    exibirPilha(&p);

    printf("Tamanho da pilha: %d\n", tamanhoPilha(&p));

    reinicializarPilha(&p);
    printf("Pilha após reinicialização:\n");
    exibirPilha(&p);

    return 0;
}
