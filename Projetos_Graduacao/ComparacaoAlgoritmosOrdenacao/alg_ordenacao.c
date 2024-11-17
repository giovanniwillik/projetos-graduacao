#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    int chave;
    int *campoDaEstrutura[1]; // Ponteiro para array de tamanho variável
} Registro1;

typedef struct {
    int chave;
    int campoDaEstrutura[1000]; // Ponteiro para array de tamanho variável
} Registro1000;

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
double medirTempo1(void (*func)(Registro1*, int), Registro1 *vetor, int n) {
	struct timespec inicio;
	clock_gettime(CLOCK_MONOTONIC, &inicio);
	func(vetor, n);
	struct timespec fim;
	clock_gettime(CLOCK_MONOTONIC, &fim);
    return difTempo(fim, inicio);
}

// Função para medir o tempo de execução (funções com 3 parâmetros)
double medirTempo3Param1(void (*func)(Registro1*, int, int), Registro1 *vetor, int i, int f) {
	struct timespec inicio;
	clock_gettime(CLOCK_MONOTONIC, &inicio);
	func(vetor, i, f);
	struct timespec fim;
	clock_gettime(CLOCK_MONOTONIC, &fim);
    return difTempo(fim, inicio);
}

double medirTempo4Param1(void (*func)(Registro1*, int, int, int), Registro1 *vetor, int p, int r, int n) {
	struct timespec inicio;
	clock_gettime(CLOCK_MONOTONIC, &inicio);
	func(vetor, p, r, n);
	struct timespec fim;
	clock_gettime(CLOCK_MONOTONIC, &fim);
    return difTempo(fim, inicio);
}


// Função para medir o tempo de execução (funções com 2 parâmetros)
double medirTempo1000(void (*func)(Registro1000*, int), Registro1000 *vetor, int n) {
	struct timespec inicio;
	clock_gettime(CLOCK_MONOTONIC, &inicio);
	func(vetor, n);
	struct timespec fim;
	clock_gettime(CLOCK_MONOTONIC, &fim);
    return difTempo(fim, inicio);
}

// Função para medir o tempo de execução (funções com 3 parâmetros)
double medirTempo3Param1000(void (*func)(Registro1000*, int, int), Registro1000 *vetor, int i, int f) {
	struct timespec inicio;
	clock_gettime(CLOCK_MONOTONIC, &inicio);
	func(vetor, i, f);
	struct timespec fim;
	clock_gettime(CLOCK_MONOTONIC, &fim);
    return difTempo(fim, inicio);
}

double medirTempo4Param1000(void (*func)(Registro1000*, int, int, int), Registro1000 *vetor, int p, int r, int n) {
	struct timespec inicio;
	clock_gettime(CLOCK_MONOTONIC, &inicio);
	func(vetor, p, r, n);
	struct timespec fim;
	clock_gettime(CLOCK_MONOTONIC, &fim);
    return difTempo(fim, inicio);
}


// Implementação dos algoritmos de ordenação com contagem de operações
void insertionSort1(Registro1 *vetor, int n) {
    for (int i = 1; i < n; i++) {
        num_movimentacoes++;
        Registro1 key = vetor[i];
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

void selectionSort1(Registro1 *vetor, int n) {
     for (int i = 0; i < n-1; i++) {
         int min_idx = i;
         for (int j = i+1; j < n; j++) {
            num_comparacoes++;
            if (vetor[j].chave < vetor[min_idx].chave) {
                min_idx = j;
            }
         }
         if (min_idx != i) {
             Registro1 temp = vetor[min_idx];
             vetor[min_idx] = vetor[i];
             vetor[i] = temp;
             num_movimentacoes += 3; // Contagem correta de movimentações
         }
     }
}

void bubbleSort1(Registro1 *vetor, int n) {
     for (int end = n-1; end > 0; end--) {
         bool movimentou = false;
         for (int i = 0; i < end; i++) {
             num_comparacoes++;
             if (vetor[i].chave > vetor[i+1].chave) {
                 Registro1 temp = vetor[i];
                 vetor[i] = vetor[i+1];
                 vetor[i+1] = temp;
                 movimentou = true;
                 num_movimentacoes += 3; // Contagem correta de movimentações
             }
         }
         if (!movimentou) return;
     }
}

void shellSort1(Registro1 *vetor, int n) {
     int h;
     for (h = 1; h < n; h = 3*h+1);
     while (h > 0) {
         h = (h-1)/3;
         for (int j = h; j < n; j++) {
             num_movimentacoes++;
             Registro1 key = vetor[j];
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

void mergeSort1(Registro1 *vetor, int i, int f) {
    if (i < f) {
        int m = (i + f)/2;
        mergeSort1(vetor, i, m);
        mergeSort1(vetor, m+1, f);
        
        int v1 = i, v2 = m+1;
        int tamanho = f - i + 1;
        Registro1 *temp = malloc(tamanho * sizeof(Registro1));
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

void refazHeapMaximo1 (Registro1 *vetor, int i, int n) {
    int l = 2*i + 1;
    int r = 2*i + 2;
    int maior = i;
    num_comparacoes++;
    if (l < n && vetor[l].chave > vetor[maior].chave) maior = l;
    num_comparacoes++;
    if (r < n && vetor[r].chave > vetor[maior].chave) maior = r;
    if (maior != i) {
        Registro1 temp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = temp;
        num_movimentacoes += 3;
        refazHeapMaximo1(vetor, maior, n);
    }
}

void heapSort1(Registro1 *vetor, int n) {
    for (int i = n/2 - 1; i >= 0; i--) refazHeapMaximo1(vetor, i, n);
    for (int i = n - 1; i > 0; i--) {
        Registro1 temp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temp;
        num_movimentacoes += 3;
        refazHeapMaximo1(vetor, 0, i);
    }
}

int qparticao1(Registro1 *vetor, int p, int r){
    int x = vetor[r].chave;
    int i = p - 1;
    Registro1 temp;
    for (int j = p; j < r; j++){
        num_comparacoes++;
        if(vetor[j].chave <= x){
            i = i+1;
            temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            num_movimentacoes += 3;
        }
    }
    temp = vetor[i+1];
    vetor[i+1] = vetor[r];
    vetor[r] = temp;
    num_movimentacoes += 3;

    return (i+1);

}

int partAleatoria1(Registro1 *vetor, int p, int r){
    int deslocamento, i;
    Registro1 temp;
    time_t t;

    srand((unsigned) time(&t));

    deslocamento = rand() % (r-p+1);
    i = p + deslocamento;

    temp = vetor[r];
    vetor[r] = vetor[i];
    vetor[i] = temp;
    num_movimentacoes += 3;

    return qparticao1(vetor, p, r);
}

void quickSortAleatorio1(Registro1* vetor, int p, int r, int n){
    int q;
    if(p < r){
        q = partAleatoria1(vetor, p, r);
        quickSortAleatorio1(vetor, p, q-1, n);
        quickSortAleatorio1(vetor, q+1, r, n);
    }
}

int particao1(Registro1 *vetor, int p, int r) {
    int x = vetor[r].chave;
    int i = p - 1;
    for (int j = p; j < r; j++) {
        num_comparacoes++;
        if (vetor[j].chave <= x) {
            i++;
            Registro1 temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            num_movimentacoes += 3;
        }
    }
    Registro1 temp = vetor[i + 1];
    vetor[i + 1] = vetor[r];
    vetor[r] = temp;
    num_movimentacoes += 3;
    return i + 1;
}

void quickSort1(Registro1 *vetor, int p, int r) {
    if (p < r) {
        int q = particao1(vetor, p, r);
        quickSort1(vetor, p, q - 1);
        quickSort1(vetor, q + 1, r);
    }
}

void insertionSort1000(Registro1000 *vetor, int n) {
    for (int i = 1; i < n; i++) {
        num_movimentacoes++;
        Registro1000 key = vetor[i];
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

void selectionSort1000(Registro1000 *vetor, int n) {
     for (int i = 0; i < n-1; i++) {
         int min_idx = i;
         for (int j = i+1; j < n; j++) {
             num_comparacoes++;
             if (vetor[j].chave < vetor[min_idx].chave) {
                 min_idx = j;
             }
         }
         if (min_idx != i) {
             Registro1000 temp = vetor[min_idx];
             vetor[min_idx] = vetor[i];
             vetor[i] = temp;
             num_movimentacoes += 3; // Contagem correta de movimentações
         }
     }
}

void bubbleSort1000(Registro1000 *vetor, int n) {
     for (int end = n-1; end > 0; end--) {
         bool movimentou = false;
         for (int i = 0; i < end; i++) {
             num_comparacoes++;
             if (vetor[i].chave > vetor[i+1].chave) {
                 Registro1000 temp = vetor[i];
                 vetor[i] = vetor[i+1];
                 vetor[i+1] = temp;
                 movimentou = true;
                 num_movimentacoes += 3; // Contagem correta de movimentações
             }
         }
         if (!movimentou) return;
     }
}

void shellSort1000(Registro1000 *vetor, int n) {
     int h;
     for (h = 1; h < n; h = 3*h+1);
     while (h > 0) {
         h = (h-1)/3;
         for (int j = h; j < n; j++) {
             num_movimentacoes++;
             Registro1000 key = vetor[j];
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

void mergeSort1000(Registro1000 *vetor, int i, int f) {
    if (i < f) {
        int m = (i + f)/2;
        mergeSort1000(vetor, i, m);
        mergeSort1000(vetor, m+1, f);
        
        int v1 = i, v2 = m+1;
        int tamanho = f - i + 1;
        Registro1000 *temp = malloc(tamanho * sizeof(Registro1000));
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

void refazHeapMaximo1000 (Registro1000 *vetor, int i, int n) {
    int l = 2*i + 1;
    int r = 2*i + 2;
    int maior = i;
    num_comparacoes++;
    if (l < n && vetor[l].chave > vetor[maior].chave) maior = l;
    num_comparacoes++;
    if (r < n && vetor[r].chave > vetor[maior].chave) maior = r;
    if (maior != i) {
        Registro1000 temp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = temp;
        num_movimentacoes += 3;
        refazHeapMaximo1000(vetor, maior, n);
    }
}

void heapSort1000(Registro1000 *vetor, int n) {
    for (int i = n/2 - 1; i >= 0; i--) refazHeapMaximo1000(vetor, i, n);
    for (int i = n - 1; i > 0; i--) {
        Registro1000 temp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temp;
        num_movimentacoes += 3;
        refazHeapMaximo1000(vetor, 0, i);
    }
}


int qparticao1000(Registro1000 *vetor, int p, int r){
    int x = vetor[r].chave;
    int i = p - 1;
    Registro1000 temp;
    for (int j = p; j < r; j++){
        num_comparacoes++;
        if(vetor[j].chave <= x){
            i = i+1;
            temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            num_movimentacoes += 3;
        }
    }
    temp = vetor[i+1];
    vetor[i+1] = vetor[r];
    vetor[r] = temp;
    num_movimentacoes += 3;

    return (i+1);

}

int partAleatoria1000(Registro1000 *vetor, int p, int r){
    int deslocamento, i;
    Registro1000 temp;
    time_t t;

    srand((unsigned) time(&t));

    deslocamento = rand() % (r-p+1);
    i = p + deslocamento;

    temp = vetor[r];
    vetor[r] = vetor[i];
    vetor[i] = temp;
    num_movimentacoes += 3;

    return qparticao1000(vetor, p, r);
}

void quickSortAleatorio1000(Registro1000* vetor, int p, int r, int n){
    int q;
    if(p < r){
        q = partAleatoria1000(vetor, p, r);
        quickSortAleatorio1000(vetor, p, q-1, n);
        quickSortAleatorio1000(vetor, q+1, r, n);
    }
}


int particao1000(Registro1000 *vetor, int p, int r) {
    int x = vetor[r].chave;
    int i = p - 1;
    for (int j = p; j < r; j++) {
        num_comparacoes++;
        if (vetor[j].chave <= x) {
            i++;
            Registro1000 temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            num_movimentacoes += 3;
        }
    }
    Registro1000 temp = vetor[i + 1];
    vetor[i + 1] = vetor[r];
    vetor[r] = temp;
    num_movimentacoes += 3;
    return i + 1;
}

void quickSort1000(Registro1000 *vetor, int p, int r) {
    if (p < r) {
        int q = particao1000(vetor, p, r);
        quickSort1000(vetor, p, q - 1);
        quickSort1000(vetor, q + 1, r);
    }
}

// Função para carregar os dados do arquivo
Registro1* carregarDados1(const char *nome_arquivo, int *n) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }
    fscanf(arquivo, "%d", n);
    Registro1 *vetor = (Registro1*)malloc((*n) * sizeof(Registro1));
    for (int i = 0; i < *n; i++) {
        fscanf(arquivo, "%d", &vetor[i].chave);
    }
    fclose(arquivo);
    return vetor;
}

Registro1000* carregarDados1000(const char *nome_arquivo, int *n) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }
    fscanf(arquivo, "%d", n);
    Registro1000 *vetor = (Registro1000*)malloc((*n) * sizeof(Registro1000));
    for (int i = 0; i < *n; i++) {
        fscanf(arquivo, "%d", &vetor[i].chave);
    }
    fclose(arquivo);
    return vetor;
}

// Função para liberar memória alocada dinamicamente
void liberarDados1(Registro1 *vetor, int n) {
    for (int i = 0; i < n; i++) free(vetor[i].campoDaEstrutura);
    free(vetor);
}

void liberarDados1000(Registro1000 *vetor, int n) {
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
    int n;
    Registro1 *vetor1Insertion, *vetor1Selection, *vetor1Bubble, *vetor1Shell, *vetor1Merge, *vetor1Heap, *vetor1Quick;
    Registro1000 *vetor1000Insertion, *vetor1000Selection, *vetor1000Bubble, *vetor1000Shell, *vetor1000Merge, *vetor1000Heap, *vetor1000Quick;

    for (int i = 0; i < 9; i++) {
        printf("\nArquivo: %s, Tamanho do campo: 1\n", arquivos[i]);

        vetor1Insertion = carregarDados1(arquivos[i], &n);
        resetarContadores();
        double tempo1 = medirTempo1(insertionSort1, vetor1Insertion, n);
        printf("Insertion Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo1, num_comparacoes, num_movimentacoes);

        vetor1Selection = carregarDados1(arquivos[i], &n);
        resetarContadores();
        tempo1 = medirTempo1(selectionSort1, vetor1Selection, n);
        printf("Selection Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo1, num_comparacoes, num_movimentacoes);

        vetor1Bubble = carregarDados1(arquivos[i], &n);
        resetarContadores();
        tempo1 = medirTempo1(bubbleSort1, vetor1Bubble, n);
        printf("Bubble Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo1, num_comparacoes, num_movimentacoes);

        vetor1Shell = carregarDados1(arquivos[i], &n);
        resetarContadores();
        tempo1 = medirTempo1(shellSort1, vetor1Shell, n);
        printf("Shell Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo1, num_comparacoes, num_movimentacoes);

        vetor1Merge = carregarDados1(arquivos[i], &n);
        resetarContadores();
        tempo1 = medirTempo3Param1(mergeSort1, vetor1Merge, 0, n-1);
        printf("Merge Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo1, num_comparacoes, num_movimentacoes);

        vetor1Heap = carregarDados1(arquivos[i], &n);
        resetarContadores();
        tempo1 = medirTempo1(heapSort1, vetor1Heap, n);
        printf("Heap Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo1, num_comparacoes, num_movimentacoes);

        vetor1Quick = carregarDados1(arquivos[i], &n);
        resetarContadores();
        tempo1 = medirTempo4Param1(quickSortAleatorio1, vetor1Quick, 0, n-1, n);
        printf("Quick Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo1, num_comparacoes, num_movimentacoes);


        printf("\nArquivo: %s, Tamanho do campo: 1000\n", arquivos[i]);

        vetor1000Insertion = carregarDados1000(arquivos[i], &n);
        resetarContadores();
        double tempo1000 = medirTempo1000(insertionSort1000, vetor1000Insertion, n);
        printf("Insertion Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo1000, num_comparacoes, num_movimentacoes);

        vetor1000Selection = carregarDados1000(arquivos[i], &n);
        resetarContadores();
        tempo1000 = medirTempo1000(selectionSort1000, vetor1000Selection, n);
        printf("Selection Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo1000, num_comparacoes, num_movimentacoes);

        vetor1000Bubble = carregarDados1000(arquivos[i], &n);
        resetarContadores();
        tempo1000 = medirTempo1000(bubbleSort1000, vetor1000Bubble, n);
        printf("Bubble Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo1000, num_comparacoes, num_movimentacoes);

        vetor1000Shell = carregarDados1000(arquivos[i], &n);
        resetarContadores();
        tempo1000 = medirTempo1000(shellSort1000, vetor1000Shell, n);
        printf("Shell Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo1000, num_comparacoes, num_movimentacoes);

        vetor1000Merge = carregarDados1000(arquivos[i], &n);
        resetarContadores();
        tempo1000 = medirTempo3Param1000(mergeSort1000, vetor1000Merge, 0, n-1);
        printf("Merge Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo1000, num_comparacoes, num_movimentacoes);

        vetor1000Heap = carregarDados1000(arquivos[i], &n);
        resetarContadores();
        tempo1000 = medirTempo1000(heapSort1000, vetor1000Heap, n);
        printf("Heap Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo1000, num_comparacoes, num_movimentacoes);

        vetor1000Quick = carregarDados1000(arquivos[i], &n);
        resetarContadores();
        tempo1000 = medirTempo4Param1000(quickSortAleatorio1000, vetor1000Quick, 0, n-1, n);
        printf("Quick Sort -> Tempo: %.2f ns, Comparacoes: %lld, Movimentacoes: %lld\n", tempo1000, num_comparacoes, num_movimentacoes);
    }
    return 0;

}