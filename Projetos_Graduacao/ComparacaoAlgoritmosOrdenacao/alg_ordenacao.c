#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

// Estrutura Registro com alocação dinâmica para campoDaEstrutura
typedef struct {
    int chave;
    int *campoDaEstrutura; // Ponteiro para array de tamanho variável
} Registro;

// Variáveis globais para contagem de comparações e movimentações
long long int num_comparacoes = 0;
long long int num_movimentacoes = 0;

// Funções para manipulação do contador
void resetarContadores() {
    num_comparacoes = 0;
    num_movimentacoes = 0;
}

long double difTempo(struct timespec fim, struct timespec inicio){
	long double Ttest = ((fim.tv_nsec) - (inicio.tv_nsec)) / pow(10,9);
	long double execSec = (fim.tv_sec) - (inicio.tv_sec) + Ttest;
	long double execNsec = execSec * pow(10,9);
	return execNsec;
}

// Função para medir o tempo de execução (funções com 2 parâmetros)
double medirTempo(void (*func)(Registro*, int), Registro *vetor, int n) {
	struct timespec inicio;
	clock_gettime(CLOCK_MONOTONIC, &inicio);
	func(vetor, n);
	struct timespec fim;
	clock_gettime(CLOCK_MONOTONIC, &fim);
    return difTempo(fim, inicio);
}

// Função para medir o tempo de execução (funções com 3 parâmetros)
double medirTempo3Param(void (*func)(Registro*, int, int), Registro *vetor, int i, int f) {
	struct timespec inicio;
	clock_gettime(CLOCK_MONOTONIC, &inicio);
	func(vetor, i, f);
	struct timespec fim;
	clock_gettime(CLOCK_MONOTONIC, &fim);
    return difTempo(fim, inicio);
}

// Implementação dos algoritmos de ordenação com contagem de operações
void insertionSort(Registro *vetor, int n) {
    for (int i = 1; i < n; i++) {
        num_movimentacoes++;
        Registro key = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j].chave > key.chave) {
            num_comparacoes++;
            vetor[j + 1] = vetor[j];
            num_movimentacoes++;
            j = j - 1;
        }
        if (j >= 0) num_comparacoes++;
        vetor[j + 1] = key;
        num_movimentacoes++;
    }
}

void selectionSort(Registro *vetor, int n) {
     for (int i = 0; i < n-1; i++) {
         int min_idx = i;
         for (int j = i+1; j < n; j++) {
             num_comparacoes++;
             if (vetor[j].chave < vetor[min_idx].chave) {
                 min_idx = j;
             }
         }
         if (min_idx != i) {
             Registro temp = vetor[min_idx];
             vetor[min_idx] = vetor[i];
             vetor[i] = temp;
             num_movimentacoes += 3; // Contagem correta de movimentações
         }
     }
}

void bubbleSort(Registro *vetor, int n) {
     for (int end = n-1; end > 0; end--) {
         bool movimentou = false;
         for (int i = 0; i < end; i++) {
             num_comparacoes++;
             if (vetor[i].chave > vetor[i+1].chave) {
                 Registro temp = vetor[i];
                 vetor[i] = vetor[i+1];
                 vetor[i+1] = temp;
                 movimentou = true;
                 num_movimentacoes += 3; // Contagem correta de movimentações
             }
         }
         if (!movimentou) return;
     }
}

void shellSort(Registro *vetor, int n) {
     int h;
     for (h = 1; h < n; h = 3*h+1);
     while (h > 0) {
         h = (h-1)/3;
         for (int j = h; j < n; j++) {
             num_movimentacoes++;
             Registro key = vetor[j];
             int i = j;
             while (i >= h && vetor[i - h].chave > key.chave) {
                 num_comparacoes++; // Contagem correta de comparações
                 vetor[i] = vetor[i - h];
                 num_movimentacoes++;
                 i = i - h;
             }
             if (i >= h) num_comparacoes++; // Contagem adicional para a última comparação
             vetor[i] = key;
             num_movimentacoes++;
         }
     }
}

void mergeSort(Registro *vetor, int i, int f) {
    if (i < f) {
        int m = (i + f)/2;
        mergeSort(vetor, i, m);
        mergeSort(vetor, m+1, f);
        
        int v1 = i, v2 = m+1;
        int tamanho = f - i + 1;
        Registro *temp = malloc(tamanho * sizeof(Registro));
        int k = 0;

        while (v1 <= m && v2 <= f) {
            num_comparacoes++;
            if (vetor[v1].chave <= vetor[v2].chave) {
                temp[k++] = vetor[v1++];
                num_movimentacoes++;
            } else {
                temp[k++] = vetor[v2++];
                num_movimentacoes++;
            }
        }
        while (v1 <= m) {
            temp[k++] = vetor[v1++];
            num_movimentacoes++;
        }
        while (v2 <= f) {
            temp[k++] = vetor[v2++];
            num_movimentacoes++;
        }
        for (k = 0; k < tamanho; k++) {
            vetor[i + k] = temp[k];
            num_movimentacoes++;
        }
        free(temp);
    }
}

void refazHeapMaximo (Registro *vetor, int i, int n) {
    int l = 2*i + 1;
    int r = 2*i + 2;
    int maior = i;
    num_comparacoes++;
    if (l < n && vetor[l].chave > vetor[maior].chave) maior = l;
    num_comparacoes++;
    if (r < n && vetor[r].chave > vetor[maior].chave) maior = r;
    if (maior != i) {
        Registro temp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = temp;
        num_movimentacoes += 3;
        refazHeapMaximo(vetor, maior, n);
    }
}

void heapSort(Registro *vetor, int n) {
    for (int i = n/2 - 1; i >= 0; i--) refazHeapMaximo(vetor, i, n);
    for (int i = n - 1; i > 0; i--) {
        Registro temp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temp;
        num_movimentacoes += 3;
        refazHeapMaximo(vetor, 0, i);
    }
}

int particao(Registro *vetor, int p, int r) {
    int x = vetor[r].chave;
    int i = p - 1;
    for (int j = p; j < r; j++) {
        num_comparacoes++;
        if (vetor[j].chave <= x) {
            i++;
            Registro temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            num_movimentacoes += 3;
        }
    }
    Registro temp = vetor[i + 1];
    vetor[i + 1] = vetor[r];
    vetor[r] = temp;
    num_movimentacoes += 3;
    return i + 1;
}

void quickSort(Registro *vetor, int p, int r) {
    if (p < r) {
        int q = particao(vetor, p, r);
        quickSort(vetor, p, q - 1);
        quickSort(vetor, q + 1, r);
    }
}

// Função para carregar os dados do arquivo
Registro* carregarDados(const char *nome_arquivo, int *n, int tamanho_campo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }
    fscanf(arquivo, "%d", n);
    Registro *vetor = malloc((*n) * sizeof(Registro));
    for (int i = 0; i < *n; i++) {
        fscanf(arquivo, "%d", &vetor[i].chave);
        vetor[i].campoDaEstrutura = malloc(tamanho_campo * sizeof(int));
    }
    fclose(arquivo);
    return vetor;
}

// Função para liberar memória alocada dinamicamente
void liberarDados(Registro *vetor, int n) {
    for (int i = 0; i < n; i++) free(vetor[i].campoDaEstrutura);
    free(vetor);
}

// Função principal para testar os algoritmos
int main() {
    const char *arquivos[] = {
        "C:/Users/giova/OneDrive/Documentos/Computacao/projetos-graduacao/Projetos_Graduacao/ComparacaoAlgoritmosOrdenacao/100_aleatorio.txt", 
        "C:/Users/giova/OneDrive/Documentos/Computacao/projetos-graduacao/Projetos_Graduacao/ComparacaoAlgoritmosOrdenacao/100_crescente.txt", 
        "C:/Users/giova/OneDrive/Documentos/Computacao/projetos-graduacao/Projetos_Graduacao/ComparacaoAlgoritmosOrdenacao/100_decrescente.txt",
        "C:/Users/giova/OneDrive/Documentos/Computacao/projetos-graduacao/Projetos_Graduacao/ComparacaoAlgoritmosOrdenacao/1000_aleatorio.txt", 
        "C:/Users/giova/OneDrive/Documentos/Computacao/projetos-graduacao/Projetos_Graduacao/ComparacaoAlgoritmosOrdenacao/1000_crescente.txt", 
        "C:/Users/giova/OneDrive/Documentos/Computacao/projetos-graduacao/Projetos_Graduacao/ComparacaoAlgoritmosOrdenacao/1000_decrescente.txt",
        "C:/Users/giova/OneDrive/Documentos/Computacao/projetos-graduacao/Projetos_Graduacao/ComparacaoAlgoritmosOrdenacao/10000_aleatorio.txt", 
        "C:/Users/giova/OneDrive/Documentos/Computacao/projetos-graduacao/Projetos_Graduacao/ComparacaoAlgoritmosOrdenacao/10000_crescente.txt", 
        "C:/Users/giova/OneDrive/Documentos/Computacao/projetos-graduacao/Projetos_Graduacao/ComparacaoAlgoritmosOrdenacao/10000_decrescente.txt"
    };
    int tamanhos[] = {1, 1000};
    int n;
    Registro *vetor;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 2; j++) { // Para tamanhos 1 e 1000 de campoDaEstrutura
            vetor = carregarDados(arquivos[i], &n, tamanhos[j]);
            printf("\nArquivo: %s, Tamanho do campo: %d\n", arquivos[i], tamanhos[j]);

            resetarContadores();
            double tempo = medirTempo(insertionSort, vetor, n);
            printf("Insertion Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo, num_comparacoes, num_movimentacoes);

            resetarContadores();
            tempo = medirTempo(selectionSort, vetor, n);
            printf("Selection Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo, num_comparacoes, num_movimentacoes);

            resetarContadores();
            tempo = medirTempo(bubbleSort, vetor, n);
            printf("Bubble Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo, num_comparacoes, num_movimentacoes);

            resetarContadores();
            tempo = medirTempo(shellSort, vetor, n);
            printf("Shell Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo, num_comparacoes, num_movimentacoes);

            resetarContadores();
            tempo = medirTempo3Param(mergeSort, vetor, 0, n-1);
            printf("Merge Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo, num_comparacoes, num_movimentacoes);

            resetarContadores();
            tempo = medirTempo(heapSort, vetor, n);
            printf("Heap Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo, num_comparacoes, num_movimentacoes);

            resetarContadores();
            tempo = medirTempo3Param(quickSort, vetor, 0, n-1);
            printf("Quick Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo, num_comparacoes, num_movimentacoes);

            liberarDados(vetor, n);
        }
    }
    return 0;

}