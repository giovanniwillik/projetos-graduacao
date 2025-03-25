#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura da Matriz
typedef struct {
    int **dados; // Ponteiro para armazenar os valores da matriz
    int linhas;
    int colunas;
} Matriz;

// Função para inicializar uma matriz de tamanho linhas x colunas
Matriz* inicializarMatriz(int linhas, int colunas) {
    Matriz *mat = (Matriz*)malloc(sizeof(Matriz));
    mat->linhas = linhas;
    mat->colunas = colunas;
    
    // Alocação de memória para as linhas
    mat->dados = (int**)malloc(linhas * sizeof(int*));
    for (int i = 0; i < linhas; i++) {
        // Alocação de memória para as colunas
        mat->dados[i] = (int*)malloc(colunas * sizeof(int));
        
        // Inicializando a matriz com zero
        for (int j = 0; j < colunas; j++) {
            mat->dados[i][j] = 0;
        }
    }
    return mat;
}

// Função para atribuir um valor a uma posição específica na matriz
void atribuirValor(Matriz *mat, int linha, int coluna, int valor) {
    if (linha >= 0 && linha < mat->linhas && coluna >= 0 && coluna < mat->colunas) {
        mat->dados[linha][coluna] = valor;
    } else {
        printf("Índices fora dos limites da matriz!\n");
    }
}

// Função para acessar um valor da matriz
int acessarValor(Matriz *mat, int linha, int coluna) {
    if (linha >= 0 && linha < mat->linhas && coluna >= 0 && coluna < mat->colunas) {
        return mat->dados[linha][coluna];
    } else {
        printf("Índices fora dos limites da matriz!\n");
        return -1; // Retorna -1 em caso de erro
    }
}

// Função para excluir um valor da matriz (resetando para zero)
void excluirValor(Matriz *mat, int linha, int coluna) {
    if (linha >= 0 && linha < mat->linhas && coluna >= 0 && coluna < mat->colunas) {
        mat->dados[linha][coluna] = 0;
    } else {
        printf("Índices fora dos limites da matriz!\n");
    }
}

// Função para liberar a memória alocada para a matriz
void destruirMatriz(Matriz *mat) {
    for (int i = 0; i < mat->linhas; i++) {
        free(mat->dados[i]); // Libera cada linha
    }
    free(mat->dados); // Libera o array de ponteiros
    free(mat); // Libera a estrutura principal
}

// Função para imprimir a matriz
void imprimirMatriz(Matriz *mat) {
    for (int i = 0; i < mat->linhas; i++) {
        for (int j = 0; j < mat->colunas; j++) {
            printf("%d ", mat->dados[i][j]);
        }
        printf("\n");
    }
}

// Programa principal para demonstrar o uso da matriz
int main() {
    // Inicializando uma matriz 3x3
    Matriz *minhaMatriz = inicializarMatriz(3, 3);
    
    // Atribuindo valores
    atribuirValor(minhaMatriz, 0, 0, 10);
    atribuirValor(minhaMatriz, 1, 1, 20);
    atribuirValor(minhaMatriz, 2, 2, 30);
    
    printf("Matriz após atribuições:\n");
    imprimirMatriz(minhaMatriz);
    
    // Acessando valores
    printf("Valor na posição (1,1): %d\n", acessarValor(minhaMatriz, 1, 1));
    
    // Excluindo um valor
    excluirValor(minhaMatriz, 1, 1);
    printf("Matriz após excluir valor da posição (1,1):\n");
    imprimirMatriz(minhaMatriz);
    
    // Liberando memória
    destruirMatriz(minhaMatriz);
    
    return 0;
}
