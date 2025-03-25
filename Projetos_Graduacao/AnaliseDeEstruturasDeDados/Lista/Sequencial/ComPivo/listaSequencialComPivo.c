#include <stdio.h>
#include <stdlib.h>

// Estrutura da lista sequencial com pivô
typedef struct {
    int* elementos;
    int tamanho;
    int capacidade;
} Lista;

// Função para inicializar a lista
void inicializar(Lista* l, int capacidade) {
    l->elementos = (int*)malloc(capacidade * sizeof(int));
    if (!l->elementos) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    l->tamanho = 0;
    l->capacidade = capacidade;
}

// Função para verificar se a lista está cheia
int estaCheia(Lista* l) {
    return l->tamanho == l->capacidade;
}

// Função para inserir um elemento na lista
void inserir(Lista* l, int valor) {
    if (estaCheia(l)) {
        printf("Lista cheia! Não é possível inserir o elemento.\n");
        return;
    }
    l->elementos[l->tamanho++] = valor;
    printf("Elemento %d inserido na lista.\n", valor);
}

// Função para ordenar a lista usando o pivô (algoritmo de partição)
void ordenar(Lista* l) {
    if (l->tamanho <= 1) return;

    int pivo = l->elementos[0];
    int i = 1;
    int j = l->tamanho - 1;

    while (i <= j) {
        while (i <= j && l->elementos[i] <= pivo) i++;
        while (i <= j && l->elementos[j] > pivo) j--;

        if (i < j) {
            int temp = l->elementos[i];
            l->elementos[i] = l->elementos[j];
            l->elementos[j] = temp;
        }
    }
    l->elementos[0] = l->elementos[j];
    l->elementos[j] = pivo;
    printf("Lista ordenada usando pivô.\n");
}

// Função para excluir um elemento da lista
void excluir(Lista* l, int valor) {
    int i, encontrado = 0;
    for (i = 0; i < l->tamanho; i++) {
        if (l->elementos[i] == valor) {
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Elemento não encontrado na lista.\n");
        return;
    }
    for (int j = i; j < l->tamanho - 1; j++) {
        l->elementos[j] = l->elementos[j + 1];
    }
    l->tamanho--;
    printf("Elemento %d excluído da lista.\n", valor);
}

// Função para buscar um elemento na lista
int buscar(Lista* l, int valor) {
    for (int i = 0; i < l->tamanho; i++) {
        if (l->elementos[i] == valor) {
            return i;
        }
    }
    return -1;
}

// Função para obter o tamanho da lista
int obterTamanho(Lista* l) {
    return l->tamanho;
}

// Função para exibir os elementos da lista
void exibir(Lista* l) {
    if (l->tamanho == 0) {
        printf("Lista vazia.\n");
        return;
    }
    printf("Lista: ");
    for (int i = 0; i < l->tamanho; i++) {
        printf("%d ", l->elementos[i]);
    }
    printf("\n");
}

// Função para limpar a lista
void limpar(Lista* l) {
    l->tamanho = 0;
    printf("Lista limpa.\n");
}

// Função principal para testar a lista sequencial com pivô
int main() {
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
