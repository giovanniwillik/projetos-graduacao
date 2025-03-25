#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição da estrutura do nó da árvore N-ária
typedef struct No {
    int valor;
    int numFilhos;
    struct No** filhos;
} No;

// Função para criar um novo nó da árvore N-ária
No* criarNo(int valor, int capacidade) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->numFilhos = 0;
    novoNo->filhos = (No**)malloc(capacidade * sizeof(No*));
    return novoNo;
}

// Função para inserir um novo nó na árvore N-ária
void inserir(No* pai, int valor, int capacidade) {
    if (pai->numFilhos < capacidade) {
        pai->filhos[pai->numFilhos] = criarNo(valor, capacidade);
        pai->numFilhos++;
    } else {
        printf("O nó %d atingiu a capacidade máxima de %d filhos.\n", pai->valor, capacidade);
    }
}

// Função para buscar um valor na árvore N-ária
No* buscar(No* raiz, int valor) {
    if (raiz == NULL) return NULL;
    if (raiz->valor == valor) return raiz;
    
    for (int i = 0; i < raiz->numFilhos; i++) {
        No* encontrado = buscar(raiz->filhos[i], valor);
        if (encontrado) return encontrado;
    }
    return NULL;
}

// Função para exibir a árvore N-ária (Pré-Ordem)
void exibir(No* raiz, int nivel) {
    if (raiz == NULL) return;
    
    for (int i = 0; i < nivel; i++) printf("  "); // Indentação
    printf("%d\n", raiz->valor);
    
    for (int i = 0; i < raiz->numFilhos; i++) {
        exibir(raiz->filhos[i], nivel + 1);
    }
}

// Função para excluir um nó e seus filhos
void excluir(No* raiz) {
    if (raiz == NULL) return;
    
    for (int i = 0; i < raiz->numFilhos; i++) {
        excluir(raiz->filhos[i]);
    }
    free(raiz->filhos);
    free(raiz);
}

// Função principal para testar a árvore N-ária
int main() {
    int capacidade = 3; // Cada nó pode ter até 3 filhos
    No* raiz = criarNo(1, capacidade);
    
    inserir(raiz, 2, capacidade);
    inserir(raiz, 3, capacidade);
    inserir(raiz, 4, capacidade);
    inserir(raiz->filhos[0], 5, capacidade);
    inserir(raiz->filhos[0], 6, capacidade);
    inserir(raiz->filhos[1], 7, capacidade);
    inserir(raiz->filhos[1], 8, capacidade);
    inserir(raiz->filhos[2], 9, capacidade);
    
    printf("\nExibição da Árvore N-ária:\n");
    exibir(raiz, 0);
    
    int buscaValor = 7;
    No* encontrado = buscar(raiz, buscaValor);
    if (encontrado) {
        printf("\nValor %d encontrado na árvore!\n", buscaValor);
    } else {
        printf("\nValor %d não encontrado na árvore.\n", buscaValor);
    }
    
    excluir(raiz);
    printf("\nÁrvore excluída com sucesso!\n");
    
    return 0;
}
