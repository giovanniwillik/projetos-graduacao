#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore binária de pesquisa
typedef struct No
{
    int valor;
    struct No *esquerdo;
    struct No *direito;
} No;

// Função para criar um novo nó da árvore binária de pesquisa
No *criarNo(int valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->esquerdo = NULL;
    novoNo->direito = NULL;
    return novoNo;
}

// Função para inserir um valor na árvore binária de pesquisa
No *inserir(No *raiz, int valor)
{
    if (raiz == NULL)
        return criarNo(valor);

    if (valor < raiz->valor)
    {
        raiz->esquerdo = inserir(raiz->esquerdo, valor);
    }
    else if (valor > raiz->valor)
    {
        raiz->direito = inserir(raiz->direito, valor);
    }

    return raiz;
}

// Função para buscar um valor na árvore binária de pesquisa
No *buscar(No *raiz, int valor)
{
    if (raiz == NULL || raiz->valor == valor)
        return raiz;

    if (valor < raiz->valor)
        return buscar(raiz->esquerdo, valor);
    return buscar(raiz->direito, valor);
}

// Função para contar o número de elementos na árvore
int contarElementos(No *raiz)
{
    if (raiz == NULL)
        return 0;
    return 1 + contarElementos(raiz->esquerdo) + contarElementos(raiz->direito);
}

// Função para exibir a árvore em ordem (leitura ordenada)
void exibirEmOrdem(No *raiz)
{
    if (raiz == NULL)
        return;
    exibirEmOrdem(raiz->esquerdo);
    printf("%d ", raiz->valor);
    exibirEmOrdem(raiz->direito);
}

// Função para encontrar o menor valor de uma subárvore
No *encontrarMinimo(No *raiz)
{
    while (raiz->esquerdo != NULL)
        raiz = raiz->esquerdo;
    return raiz;
}

// Função para remover um elemento da árvore binária de pesquisa
No *remover(No *raiz, int valor)
{
    if (raiz == NULL)
        return NULL;

    if (valor < raiz->valor)
    {
        raiz->esquerdo = remover(raiz->esquerdo, valor);
    }
    else if (valor > raiz->valor)
    {
        raiz->direito = remover(raiz->direito, valor);
    }
    else
    {
        if (raiz->esquerdo == NULL)
        {
            No *temp = raiz->direito;
            free(raiz);
            return temp;
        }
        else if (raiz->direito == NULL)
        {
            No *temp = raiz->esquerdo;
            free(raiz);
            return temp;
        }

        No *temp = encontrarMinimo(raiz->direito);
        raiz->valor = temp->valor;
        raiz->direito = remover(raiz->direito, temp->valor);
    }
    return raiz;
}

// Função para liberar a memória da árvore
void excluirArvore(No *raiz)
{
    if (raiz == NULL)
        return;
    excluirArvore(raiz->esquerdo);
    excluirArvore(raiz->direito);
    free(raiz);
}

// Função principal para testar a árvore binária de pesquisa
int main()
{
    No *raiz = NULL;

    raiz = inserir(raiz, 50);
    inserir(raiz, 30);
    inserir(raiz, 70);
    inserir(raiz, 20);
    inserir(raiz, 40);
    inserir(raiz, 60);
    inserir(raiz, 80);

    printf("\nÁrvore em ordem: ");
    exibirEmOrdem(raiz);

    printf("\nNúmero de elementos: %d", contarElementos(raiz));

    int buscaValor = 40;
    if (buscar(raiz, buscaValor))
    {
        printf("\nValor %d encontrado na árvore!", buscaValor);
    }
    else
    {
        printf("\nValor %d não encontrado na árvore.", buscaValor);
    }

    raiz = remover(raiz, 50);
    printf("\n\nÁrvore após remover 50: ");
    exibirEmOrdem(raiz);

    excluirArvore(raiz);
    printf("\n\nÁrvore excluída com sucesso!\n");

    return 0;
}
