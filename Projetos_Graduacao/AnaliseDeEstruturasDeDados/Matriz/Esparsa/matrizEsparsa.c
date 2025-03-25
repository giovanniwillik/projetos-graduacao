#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um elemento da matriz esparsa
typedef struct Elemento
{
    int linha, coluna, valor;
    struct Elemento *prox;
} Elemento;

// Estrutura para representar a matriz esparsa
typedef struct
{
    int linhas, colunas;
    Elemento *cabeca;
} MatrizEsparsa;

// Inicializa uma matriz esparsa
MatrizEsparsa *inicializarMatriz(int linhas, int colunas)
{
    MatrizEsparsa *mat = (MatrizEsparsa *)malloc(sizeof(MatrizEsparsa));
    mat->linhas = linhas;
    mat->colunas = colunas;
    mat->cabeca = NULL; // Lista vazia no início
    return mat;
}

// Atribui um valor na matriz esparsa
void atribuirValor(MatrizEsparsa *mat, int linha, int coluna, int valor)
{
    if (linha < 0 || linha >= mat->linhas || coluna < 0 || coluna >= mat->colunas)
    {
        printf("Índices fora dos limites!\n");
        return;
    }

    Elemento **atual = &(mat->cabeca);
    while (*atual != NULL)
    {
        if ((*atual)->linha == linha && (*atual)->coluna == coluna)
        {
            if (valor == 0)
            {
                // Remove o elemento da lista
                Elemento *temp = *atual;
                *atual = (*atual)->prox;
                free(temp);
            }
            else
            {
                // Atualiza o valor existente
                (*atual)->valor = valor;
            }
            return;
        }
        atual = &((*atual)->prox);
    }

    if (valor != 0)
    {
        // Insere um novo elemento na lista
        Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
        novo->linha = linha;
        novo->coluna = coluna;
        novo->valor = valor;
        novo->prox = mat->cabeca;
        mat->cabeca = novo;
    }
}

// Acessa um valor da matriz esparsa
int acessarValor(MatrizEsparsa *mat, int linha, int coluna)
{
    Elemento *atual = mat->cabeca;
    while (atual != NULL)
    {
        if (atual->linha == linha && atual->coluna == coluna)
        {
            return atual->valor;
        }
        atual = atual->prox;
    }
    return 0; // Elemento não encontrado, então assume-se que é zero
}

// Exclui um valor da matriz esparsa (equivalente a atribuir zero)
void excluirValor(MatrizEsparsa *mat, int linha, int coluna)
{
    atribuirValor(mat, linha, coluna, 0);
}

// Libera toda a memória da matriz esparsa
void destruirMatriz(MatrizEsparsa *mat)
{
    Elemento *atual = mat->cabeca;
    while (atual != NULL)
    {
        Elemento *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(mat);
}

// Exibe a matriz esparsa mostrando apenas os elementos não nulos
void imprimirMatriz(MatrizEsparsa *mat)
{
    Elemento *atual = mat->cabeca;
    printf("Elementos não nulos da matriz:\n");
    while (atual != NULL)
    {
        printf("(Linha: %d, Coluna: %d) = %d\n", atual->linha, atual->coluna, atual->valor);
        atual = atual->prox;
    }
}

// Programa principal para demonstrar a matriz esparsa
int main()
{
    MatrizEsparsa *mat = inicializarMatriz(5, 5);

    atribuirValor(mat, 1, 2, 10);
    atribuirValor(mat, 3, 4, 20);
    atribuirValor(mat, 0, 0, 30);

    printf("Matriz após inserções:\n");
    imprimirMatriz(mat);

    printf("Valor na posição (1,2): %d\n", acessarValor(mat, 1, 2));

    excluirValor(mat, 1, 2);
    printf("Matriz após excluir valor da posição (1,2):\n");
    imprimirMatriz(mat);

    destruirMatriz(mat);
    return 0;
}
