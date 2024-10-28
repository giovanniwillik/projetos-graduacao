#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// Função para medir o tempo de execução
double medirTempo(void (*func)(Registro*, int), Registro *vetor, int n) {
    clock_t inicio, fim;
    inicio = clock();
    func(vetor, n);
    fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

void insertionSort(Registro *vetor, int n) {
	for (int i = 1; i < n; i++) {
        num_movimentacoes++;
    	int key = vetor[i].chave;
    	int j = i - 1;
    	// Move elementos do vetor[0..i-1].chave que são maiores que key
       	// para uma posição à frente da sua posição atual
        while (j >= 0 && vetor[j].chave > key) {
            num_comparacoes++;
        	vetor[j + 1].chave = vetor[j].chave;
            num_movimentacoes++;
        	j = j - 1;
        }	
        if (j >= 0) num_comparacoes++; // Contabiliza a comparação que faz o while parar
        
        vetor[j + 1].chave = key;
        num_movimentacoes++;  // Contabiliza a movimentação ao inserir a key
    }  
}

void selectionSort(Registro *vetor, int n) {
    int i, j, min_idx; // Um por um, mover o limite do subarray não ordenado 
	for (i = 0; i < n-1; i++) { // Encontrar o menor elemento no subarray não ordenado 
        min_idx = i; 
        for (j = i+1; j < n; j++){
            num_comparacoes++;
            if (vetor[j].chave < vetor[min_idx].chave){
                min_idx = j; // Trocar o menor elemento encontrado com o primeiro elemento 
            }
        }
        // Troca o menor elemento encontrado com o primeiro elemento
        if (min_idx != i) { // Só troca se min_idx for diferente de i
            int temp = vetor[min_idx].chave;
            vetor[min_idx].chave = vetor[i].chave;
            vetor[i].chave = temp;
            num_movimentacoes += 3;  // Incrementa as movimentações (3 atribuições para a troca)
        }
	}
}

void bubbleSort(Registro *vetor, int n) {
    int end, i, temp;
    // end é o último elemento do vetor, o lugar no qual o maior elemento precisa se deslocar
    for (end = n-1; end > 0; end--) {
        // a cada ciclo será ajustado a ordenação do par i e i+1
        for (i = 0; i < end; i++) {
            // confere se a ordem está errada
            num_comparacoes++;
            if (vetor[i].chave > vetor[i+1].chave) {
                num_movimentacoes += 3;
                temp = vetor[i].chave;
                vetor[i].chave = vetor[i+1].chave;
                vetor[i+1].chave = temp;
            }
        }
    }
}

void shellSort(Registro *vetor, int n) {
    int i, j, h, key;
    for (h = 1; h < n; h = 3*h+1); //valor máximo de h
    while (h > 0) {
        h = (h-1)/3;
        for (j = h; j < n; j++) {
            num_movimentacoes++;
            key = vetor[j].chave;
            i = j;
            while (i >= h) {
                num_comparacoes++;
                if (vetor[i - h].chave > key) {
                    num_movimentacoes++;
                    vetor[i].chave = vetor[i - h].chave;
                    i = i - h;
                }
                else {
                    break;
                }
            }
            num_movimentacoes++;
            vetor[i].chave = key;
        }
    }  
}

void mergeSort(Registro *vetor, int n);
void heapSort(Registro *vetor, int n);
void quickSort(Registro *vetor, int n);

// Função para carregar os dados do arquivo
Registro* carregarDados(const char *nome_arquivo, int *n, int tamanho_campo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    fscanf(arquivo, "%d", n);
    Registro *vetor = (Registro*) malloc((*n) * sizeof(Registro));

    for (int i = 0; i < *n; i++) {
        fscanf(arquivo, "%d", &vetor[i].chave);
        vetor[i].campoDaEstrutura = (int*) malloc(tamanho_campo * sizeof(int));
        // campoDaEstrutura não precisa ser inicializado, conforme especificado
    }

    fclose(arquivo);
    return vetor;
}

// Função para liberar memória alocada dinamicamente no vetor de Registros
void liberarDados(Registro *vetor, int n) {
    for (int i = 0; i < n; i++) {
        free(vetor[i].campoDaEstrutura); // Libera cada campoDaEstrutura
    }
    free(vetor); // Libera o vetor principal
}

// Função principal para testar os algoritmos
int main() {
    const char *arquivos[] = {
        "100_aleatorio.txt",
        "100_crescente.txt",
        "100_decrescente.txt",
        "1000_aleatorio.txt",
        "1000_crescente.txt",
        "1000_decrescente.txt",
        "10000_aleatorio.txt",
        "10000_crescente.txt",
        "10000_decrescente.txt"
    };
    int tamanhos[] = {1, 1000};

    // Loop pelos arquivos de entrada
    for (int i = 0; i < 9; i++) {
        printf("ENTRADA: %s", arquivos[i]);
        for (int j = 0; j < 2; j++) { // Tamanhos de campoDaEstrutura
            int n;
            // Testa cada algoritmo
            printf("Arquivo: %s, Tamanho do campo: %d\n", arquivos[i], tamanhos[j]);
            double tempo_execucao;

            // Insertion Sort
            Registro *vetor = carregarDados(arquivos[i], &n, tamanhos[j]);
            resetarContadores();
            tempo_execucao = medirTempo(insertionSort, vetor, n);
            printf("Insertion Sort - Tempo: %.4fs, Comparacoes: %lld, Movimentacoes: %lld\n",
                   tempo_execucao, num_comparacoes, num_movimentacoes);
            liberarDados(vetor, n);

            // Selection Sort
            vetor = carregarDados(arquivos[i], &n, tamanhos[j]);
            resetarContadores();
            tempo_execucao = medirTempo(selectionSort, vetor, n);
            printf("Selection Sort - Tempo: %.4fs, Comparacoes: %lld, Movimentacoes: %lld\n",
                   tempo_execucao, num_comparacoes, num_movimentacoes);
            liberarDados(vetor, n);

            // Bubble Sort
            vetor = carregarDados(arquivos[i], &n, tamanhos[j]);
            resetarContadores();
            tempo_execucao = medirTempo(bubbleSort, vetor, n);
            printf("Bubble Sort - Tempo: %.4fs, Comparacoes: %lld, Movimentacoes: %lld\n",
                   tempo_execucao, num_comparacoes, num_movimentacoes);
            liberarDados(vetor, n);

            // Shell Sort
            vetor = carregarDados(arquivos[i], &n, tamanhos[j]);
            resetarContadores();
            tempo_execucao = medirTempo(shellSort, vetor, n);
            printf("Shell Sort - Tempo: %.4fs, Comparacoes: %lld, Movimentacoes: %lld\n",
                   tempo_execucao, num_comparacoes, num_movimentacoes);
            liberarDados(vetor, n);

            // Merge Sort
            vetor = carregarDados(arquivos[i], &n, tamanhos[j]);
            resetarContadores();
            tempo_execucao = medirTempo(mergeSort, vetor, n);
            printf("Merge Sort - Tempo: %.4fs, Comparacoes: %lld, Movimentacoes: %lld\n",
                   tempo_execucao, num_comparacoes, num_movimentacoes);
            liberarDados(vetor, n);

            // Heap Sort
            vetor = carregarDados(arquivos[i], &n, tamanhos[j]);
            resetarContadores();
            tempo_execucao = medirTempo(heapSort, vetor, n);
            printf("Heap Sort - Tempo: %.4fs, Comparacoes: %lld, Movimentacoes: %lld\n",
                   tempo_execucao, num_comparacoes, num_movimentacoes);
            liberarDados(vetor, n);

            // Quick Sort
            vetor = carregarDados(arquivos[i], &n, tamanhos[j]);
            resetarContadores();
            tempo_execucao = medirTempo(quickSort, vetor, n);
            printf("Quick Sort - Tempo: %.4fs, Comparacoes: %lld, Movimentacoes: %lld\n",
                   tempo_execucao, num_comparacoes, num_movimentacoes);
            liberarDados(vetor, n);
        }
    }

    return 0;
}
