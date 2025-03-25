#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da lista ligada
typedef struct No
{
    int valor;
    struct No *prox;
} No;

// Estrutura da lista ligada
typedef struct
{
    No *cabeca;
    int tamanho;
} Lista;

// Função para inicializar a lista
void inicializar(Lista *l)
{
    l->cabeca = NULL;
    l->tamanho = 0;
}

// Função para criar um novo nó
No *criarNo(int valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    if (!novoNo)
    {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    novoNo->valor = valor;
    novoNo->prox = NULL;
    return novoNo;
}

// Função para inserir um elemento na lista
void inserir(Lista *l, int valor)
{
    No *novoNo = criarNo(valor);
    if (l->cabeca == NULL)
    {
        l->cabeca = novoNo;
    }
    else
    {
        No *temp = l->cabeca;
        while (temp->prox != NULL)
        {
            temp = temp->prox;
        }
        temp->prox = novoNo;
    }
    l->tamanho++;
    printf("Elemento %d inserido na lista.\n", valor);
}

// Função para ordenar a lista (usando o algoritmo de ordenação por bolha)
void ordenar(Lista *l)
{
    if (l->tamanho <= 1)
        return;

    No *i = l->cabeca;
    No *j = NULL;
    int temp;

    for (i = l->cabeca; i != NULL; i = i->prox)
    {
        for (j = i->prox; j != NULL; j = j->prox)
        {
            if (i->valor > j->valor)
            {
                temp = i->valor;
                i->valor = j->valor;
                j->valor = temp;
            }
        }
    }
    printf("Lista ordenada.\n");
}

// Função para excluir um elemento da lista
void excluir(Lista *l, int valor)
{
    No *temp = l->cabeca;
    No *anterior = NULL;

    if (temp != NULL && temp->valor == valor)
    {
        l->cabeca = temp->prox;
        free(temp);
        l->tamanho--;
        printf("Elemento %d excluído da lista.\n", valor);
        return;
    }

    while (temp != NULL && temp->valor != valor)
    {
        anterior = temp;
        temp = temp->prox;
    }

    if (temp == NULL)
    {
        printf("Elemento %d não encontrado.\n", valor);
        return;
    }

    anterior->prox = temp->prox;
    free(temp);
    l->tamanho--;
    printf("Elemento %d excluído da lista.\n", valor);
}

// Função para buscar um elemento na lista
No *buscar(Lista *l, int valor)
{
    No *temp = l->cabeca;
    while (temp != NULL)
    {
        if (temp->valor == valor)
        {
            return temp;
        }
        temp = temp->prox;
    }
    return NULL;
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

    No *temp = l->cabeca;
    printf("Lista: ");
    while (temp != NULL)
    {
        printf("%d ", temp->valor);
        temp = temp->prox;
    }
    printf("\n");
}

// Função para limpar a lista
void limpar(Lista *l)
{
    No *temp = l->cabeca;
    No *prox;

    while (temp != NULL)
    {
        prox = temp->prox;
        free(temp);
        temp = prox;
    }

    l->cabeca = NULL;
    l->tamanho = 0;
    printf("Lista limpa.\n");
}

// Função principal para testar a lista ligada estática
int main()
{
    Lista lista;
    inicializar(&lista);

    inserir(&lista, 5);
    inserir(&lista, 3);
    inserir(&lista, 8);
    inserir(&lista, 1);

    exibir(&lista);

    excluir(&lista, 3);

    exibir(&lista);

    No *resultado = buscar(&lista, 8);
    if (resultado)
    {
        printf("Elemento 8 encontrado na lista.\n");
    }
    else
    {
        printf("Elemento 8 não encontrado.\n");
    }

    ordenar(&lista);

    exibir(&lista);

    printf("Tamanho da lista: %d\n", obterTamanho(&lista));

    limpar(&lista);
    exibir(&lista);

    return 0;
}
