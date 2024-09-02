#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Biblioteca que contém a função para calcular a raiz quadrada "sqrt()"
#include <limits.h> // Biblioteca que contém as constantes "INT_MIN" e "INT_MAX"

#define MAX_SIZE 255  // Define o tamanho máximo da matriz quadrada

// Função para alocar memória para a matriz (dinâmicamente)
int** inicializarMatriz (int dimensao) {
    int** matriz = (int**) malloc (dimensao * sizeof (int*)) // int** matriz == int matriz[][]
    if (matriz == NULL) {
        perror("Erro ao alocar memória para a matriz"); // Exibe mensagem de erro caso a alocação falhe
        return NULL; 
    }
    for (int i = 0; i < dimensao; i++) {
        matriz[i] = (int*) malloc (dimensao * sizeof(int)); // Alocando espaço para as linhas da matriz
        if (matriz[i] == NULL) {
            perror("Erro ao alocar memória para a linha da matriz");
            // Libera a memória que foi alocada antes, caso a alocação de memória para as linhas falhe
            for (int j = 0; j < i; j++) {
                free (matriz[j]); // Liberando o espaço alocado às linhas
            }
            free (matriz); // Liberando espaço alocado à matriz, como um todo
            return NULL;
        }
    }
    return matriz;
}

// Função para liberar memória da matriz
void liberarMatriz (int **matriz, int dimensao) {
    for (int i = 0; i < dimensao; i++) {
        free(matriz[i]); // Libera memória da linha da matriz
    }
    free(matriz); // Libera memória da matriz, como um todo
}

// Função que lê arquivo de entrada e transcreve a matriz numa estrutura de dados
int lerArquivo (const char* arquivoEntrada, int** matriz, int dimensao) {
    FILE* arquivo = fopen(arquivoEntrada, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo"); // Mensagem de erro caso a tentativa de abrir o arquivo falhe
        return -1;
    }
    int i = 0; // Índice para ler as linhas da matriz
    int j = 0; // Índice para ler as colunas da matriz
    int valor;
    // Enquanto a leitura dos elementos da matriz for válida
    while (fscanf(arquivo, "%d", &valor) == 1) {
        // Verificando se os valores da matriz estão dentro do escopo delimitado
        if (valor < 0 || valor > MAX_SIZE) {
            fprintf(stderr, "Erro: valor %d fora do intervalo válido (0-255) na posição (%d, %d)\n", valor, i, j);
            fclose(arquivo);
            return -1;
        }
        matriz[i][j] = valor;
        j++;
        // Quando j for o último elemento da linha, j retorna a 0 (primeiro elemento) e linha++
        if (j >= dimensao) {
            j = 0;
            i++;
        }
        // Quando i ultrapassar a última linha da matriz, encerra-se o "while"
        if (i >= dimensao) {
            break;
        }
    }
    if (ferror (arquivo)) {
        perror ("Erro ao ler o arquivo");
        fclose (arquivo);
        return -1;
    }
    fclose(arquivo);
    return 0;
}

// Função que descobre o min e o max da matriz e suas respectivas coordenadas
void acharMinMax (int** matriz, int XInicio, int XFim, int YInicio, int YFim, int* min, int* max, int* XMin, int* XMax, int* YMin, int* YMax) {
    if ((XInicio > XFim) || (YInicio > YFim)) {
        return;
    }
    // Se a matriz for 1x1 (um pixel)
    if ((XInicio == XFim) && (YInicio == YFim)) {
        // Caso base: uma única célula
        int valor = matriz[XInicio][YInicio];
        // Considerando caso de empate no valor mínimo
        if (((valor == *min) && (XInicio < XMin)) || ((valor == *min) && (XInicio == XMin) && (YInicio < YMin))) {
            *min = valor;
            *XMin = XInicio;
            *YMin = YInicio;
        }
        // Considerando caso de empate no valor máximo
        if (((valor == *max) && (XInicio < XMax)) || ((valor == *max) && (XInicio == XMax) && (YInicio < YMax))) {
            *max = valor;
            *XMax = XInicio;
            *YMax = YInicio;
        }
        // Atribuindo as informações do pixel às informações do min caso o valor seja menor que o min existente
        if (valor < *min) {
            *min = valor;
            *XMin = XInicio;
            *YMin = YInicio;
        }
        // Atribuindo as informações do pixel às informações do max caso o valor seja maior que o max existente
        if (valor > *max) {
            *max = valor;
            *XMax = XInicio;
            *YMax = YInicio;
        }
        return;
    }
    int XMeio = (XInicio + XFim) / 2; // Pegando valor do meio horizontal, que irá dividir a matriz em duas partes iguais (esquerda e direita)
    int YMeio = (YInicio + YFim) / 2; // Pegando valor do meio vertical, que irá dividir a matriz verticalmete em duas partes iguais (cima e baixo)
    // Dividindo a matriz em quatro quadrantes e aplicando a chamada recursiva
    acharMinMax(matriz, XInicio, XMeio, YInicio, YMeio, min, max, XMin, XMax, YMin, YMax);
    acharMinMax(matriz, XInicio, XMeio, YMeio + 1, YFim, min, max, XMin, XMax, YMin, YMax);
    acharMinMax(matriz, XMeio + 1, XFim, YInicio, YMeio, min, max, XMin, XMax, YMin, YMax);
    acharMinMax(matriz, XMeio + 1, XFim, YMeio + 1, YFim, min, max, XMin, XMax, YMin, YMax);
    // Obs: ao final da execução, todos os pixels terão sido consultados e os valores referentes ao min e max estarão corretamente atribuidos
}

// Função que ecreve resutado no arquivo de saída de nome desejado
void escreverResultado (const char* arquivoSaida, int min, int XMin, int YMin, int max, int XMax, int YMax) {
    FILE* arquivo = fopen(arquivoSaida, "w");
    // retornando caso falhe a abertura do arquivo de saída
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return;
    }
    fprintf(arquivo, "min =  %d; pos = (%d, %d)\n", min, minX, minY);
    fprintf(arquivo, "max = %d; pos = (%d, %d)\n", max, maxX, maxY);
    fclose (arquivo);
}

int main (int argc, char* argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Uso: %s <tamanho> <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        return 1;
    }
    
    int tamanho = atoi(argv[1]); // atoi: função que converte string para int
    const char* arquivoEntrada = argv[2]
    const char* arquivoSaida = argv[3]
    
    // Retornando erro caso o tamanho é um inteiro N potência de 2 e no máximo 64
    if ((tamanho != 1) && (tamanho != 2) && (tamanho != 4) && (tamanho != 8) && (tamanho != 16) && (tamanho != 32) && (tamanho != 64)) {
        fprintf(stderr, "O tamanho só é válido para inteiros que são potência de 2 e com valor máximo de 64 \n");
        return 1;
    }
    
    int dimensao = sqrt(tamanho); // Definição da dimensão da matriz quadrada. Ex: tamanho = 64 -> dimensao = 8
    
    // Retornando erro caso a matriz seja nula
    int** matriz = inicializarMatriz(dimensao);
    if (matriz == NULL) {
        return 1;
    }
    
    // Retornando erro caso haja falha na leitura do arquivo de entrada
    if (lerArquivo (arquivoEntrada, matriz, tamanho) != 0) {
        liberarMatriz (matriz, dimensao); // Liberando espaço que havia sido alocado
        return 1;
    }
    
    // Declarando variáveis que serão utilizadas em acharMinMax()
    int min, XMin, YMin = INT_MAX; // min inicializa como o maior inteiro possível para garantir que seu valor seja trocado na primeira interaçaõ de acharMinMax()
    int max, XMax, YMax = INT_MIN; // max inicializa como o menor inteiro possível para garantir que seu valor seja trocado na primeira interaçaõ de acharMinMax()
    
    // Descobrindo valores de min, max, XMin, XMax, YMin, YMax
    acharMinMax (matriz, 0, dimensao - 1, 0, dimensao - 1, &min, &max, &XMin, &XMax, &YMin, &YMax);
    // Escrevendo resultado no arquivo de saída
    escreverResultado (arquivoSaida, min, XMin, YMin, max, XMax, YMax);
    // Liberando memória alocada da matriz após gravar resultado
    liberarMatriz (matriz, dimensao);
    
    return 0;
}