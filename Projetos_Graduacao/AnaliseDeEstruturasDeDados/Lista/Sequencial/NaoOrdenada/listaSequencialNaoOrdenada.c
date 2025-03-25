#include <stdio.h>
#include <stdlib.h>

// Estrutura da lista sequencial
typedef struct
{
    int *elementos;
    int tamanho;
    int capacidade;
} Lista;

// Função para inicializar a lista
void inicializar(Lista *l, int capacidade)
{
    l->elementos = (int *)malloc(capacidade * sizeof(int));
    if (!l->elementos)
    {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    l->tamanho = 0;
    l->capacidade = capacidade;
}

// Função para verificar se a lista está cheia
int estaCheia(Lista *l)
{
    return l->tamanho == l->capacidade;
}

// Função para inserir um elemento na lista
void inserir(Lista *l, int valor)
{
    if (estaCheia(l))
    {
        printf("Lista cheia! Não é possível inserir o elemento.\n");
        return;
    }
    l->elementos[l->tamanho++] = valor;
    printf("Elemento %d inserido na lista.\n", valor);
}

// Função para ordenar a lista
void ordenar(Lista *l)
{
    for (int i = 0; i < l->tamanho - 1; i++)
    {
        for (int j = i + 1; j < l->tamanho; j++)
        {
            if (l->elementos[i] > l->elementos[j])
            {
                int temp = l->elementos[i];
                l->elementos[i] = l->elementos[j];
                l->elementos[j] = temp;
            }
        }
    }
    printf("Lista ordenada.\n");
}

// Função para excluir um elemento da lista
void excluir(Lista *l, int valor)
{
    int i, encontrado = 0;
    for (i = 0; i < l->tamanho; i++)
    {
        if (l->elementos[i] == valor)
        {
            encontrado = 1;
            break;
        }
    }
    if (!encontrado)
    {
        printf("Elemento não encontrado na lista.\n");
        return;
    }
    for (int j = i; j < l->tamanho - 1; j++)
    {
        l->elementos[j] = l->elementos[j + 1];
    }
    l->tamanho--;
    printf("Elemento %d excluído da lista.\n", valor);
}

// Função para buscar um elemento na lista
int buscar(Lista *l, int valor)
{
    for (int i = 0; i < l->tamanho; i++)
    {
        if (l->elementos[i] == valor)
        {
            return i;
        }
    }
    return -1;
}

// Função para obter o tamanho da lista
int obterTamanho(Lista *l)
{
    return l->tamanho;
}

// Função para exibir os elementos da lista
void exibir(Lista *l)
{
    if (l->tamanho == 0)
    {
        printf("Lista vazia.\n");
        return;
    }
    printf("Lista: ");
    for (int i = 0; i < l->tamanho; i++)
    {
        printf("%d ", l->elementos[i]);
    }
    printf("\n");
}

// Função para limpar a lista
void limpar(Lista *l)
{
    l->tamanho = 0;
    printf("Lista limpa.\n");
}

// Função principal para testar a lista sequencial não ordenada
int main()
{
    Lista lista;
    inicializar(&lista, 10);

    inserir(&lista, 5);
    inserir(&lista, 3);
    inserir(&lista, 8);
    inserir(&lista, 1);

    exibir(&lista);

    excluir(&lista, 3);

    exibir(&lista);

    printf("Elemento 8 encontrado na posição: %d\n", buscar(&lista, 8));

    ordenar(&lista);

    exibir(&lista);

    printf("Tamanho da lista: %d\n", obterTamanho(&lista));

    limpar(&lista);
    exibir(&lista);

    return 0;
}