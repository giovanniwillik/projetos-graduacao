#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição da estrutura do nó da árvore binária
typedef struct No
{
    int valor;
    struct No *esquerdo;
    struct No *direito;
} No;

// Função para criar um novo nó da árvore binária
No *criarNo(int valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->esquerdo = NULL;
    novoNo->direito = NULL;
    return novoNo;
}

// Função para inserir um novo nó na árvore binária de forma sequencial
void inserir(No **raiz, int valor)
{
    if (*raiz == NULL)
    {
        *raiz = criarNo(valor);
        return;
    }

    No *fila[100]; // Implementação simples de fila para inserção sequencial
    int frente = 0, tras = 0;
    fila[tras++] = *raiz;

    while (frente < tras)
    {
        No *atual = fila[frente++];

        if (atual->esquerdo == NULL)
        {
            atual->esquerdo = criarNo(valor);
            return;
        }
        else
        {
            fila[tras++] = atual->esquerdo;
        }

        if (atual->direito == NULL)
        {
            atual->direito = criarNo(valor);
            return;
        }
        else
        {
            fila[tras++] = atual->direito;
        }
    }
}

// Função para buscar um valor na árvore binária
No *buscar(No *raiz, int valor)
{
    if (raiz == NULL)
        return NULL;
    if (raiz->valor == valor)
        return raiz;

    No *encontrado = buscar(raiz->esquerdo, valor);
    if (encontrado)
        return encontrado;

    return buscar(raiz->direito, valor);
}

// Função para exibir a árvore binária (Pré-Ordem)
void exibir(No *raiz, int nivel)
{
    if (raiz == NULL)
        return;

    for (int i = 0; i < nivel; i++)
        printf("  "); // Indentação
    printf("%d\n", raiz->valor);

    exibir(raiz->esquerdo, nivel + 1);
    exibir(raiz->direito, nivel + 1);
}

// Função para excluir a árvore binária
void excluir(No *raiz)
{
    if (raiz == NULL)
        return;

    excluir(raiz->esquerdo);
    excluir(raiz->direito);
    free(raiz);
}

// Função principal para testar a árvore binária
int main()
{
    No *raiz = NULL;

    inserir(&raiz, 1);
    inserir(&raiz, 2);
    inserir(&raiz, 3);
    inserir(&raiz, 4);
    inserir(&raiz, 5);
    inserir(&raiz, 6);
    inserir(&raiz, 7);

    printf("\nExibição da Árvore Binária:\n");
    exibir(raiz, 0);

    int buscaValor = 5;
    No *encontrado = buscar(raiz, buscaValor);
    if (encontrado)
    {
        printf("\nValor %d encontrado na árvore!\n", buscaValor);
    }
    else
    {
        printf("\nValor %d não encontrado na árvore.\n", buscaValor);
    }

    excluir(raiz);
    printf("\nÁrvore excluída com sucesso!\n");

    return 0;
}
