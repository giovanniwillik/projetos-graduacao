#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

int intcmp(const void *a, const void *b){
	return (*(int*)a - *(int*)b);
}

int* geraArray(int qn){	
	return (int*) malloc (qn*sizeof(int));
}

void arrayAleatorio(int *array, int qn, int semente, int nmax) {
	srand(semente);
	for (int i = 0; i < qn; i++){
		array[i] = rand() % nmax;
	}
}

void imprimeArray(int* array, int qn){
	for (int i = 0; i < qn; i++){
		printf("%d\n", array[i]);
	}
}

long double difTempo(struct timespec fim, struct timespec inicio){
	long double Ttest = ((fim.tv_nsec) - (inicio.tv_nsec)) / pow(10,9);
	long double execSec = (fim.tv_sec) - (inicio.tv_sec) + Ttest;
	long double execNsec = execSec * pow(10,9);
	return execNsec;
}

int *qSort(int* array, int qn){
	qsort (array, qn, sizeof(int), intcmp);
	return array;
}

int *iSort(int* array, int qn){
	for (int i = 1; i < qn; i++) {
    	int key = array[i];
    	int j = i - 1;
    	// Move elementos do arr[0..i-1] que são maiores que key
       	// para uma posição à frente da sua posição atual
        while (j >= 0 && array[j] > key) {
        	array[j + 1] = array[j];
        	j = j - 1;
        }	
        array[j + 1] = key;
    	}
    	return array;
}

int *sSort(int* array, int qn){
	int i, j, min_idx; // Um por um, mover o limite do subarray não ordenado 
	for (i = 0; i < qn-1; i++) { // Encontrar o menor elemento no subarray não ordenado 
	min_idx = i; 
	for (j = i+1; j < qn; j++){
		if (array[j] < array[min_idx]){
			min_idx = j; // Trocar o menor elemento encontrado com o primeiro elemento 
		}
	}
	int temp = array[min_idx]; 
	array[min_idx] = array[i]; 
	array[i] = temp;
	}
	return array;
}

int main(){
	printf("Insira a quantidade de itens: ");
	int qn;
	scanf("%d", &qn);
	printf("Insira valor máximo do número aleatório: ");
	int nmax;
	scanf("%d", &nmax);
	nmax++;
	printf("Deseja rodar qsort? (Digite 0 para NAO e 1 para SIM) ");
	int booleanQsort;
	scanf("%d", &booleanQsort);
	while ((booleanQsort != 0) && (booleanQsort != 1)){
		printf("Insira um valor válido\n");
		scanf("%d", &booleanQsort);
	} 
	if (booleanQsort == 1){
		int *A = geraArray(qn);
		arrayAleatorio(A, qn, 32717, nmax);
		printf("Array ordenado por qsort: \n");
		struct timespec tiq;
		clock_gettime(CLOCK_MONOTONIC, &tiq);
		qSort(A, qn);
		struct timespec tfq;
		clock_gettime(CLOCK_MONOTONIC, &tfq);
		imprimeArray(A, qn);
		printf("Tempo de execução em nanosegundos: %Lf\n", difTempo(tfq, tiq));
		printf("Tempo de execução em segundos: %Lf\n", difTempo(tfq, tiq) * 1E-9);
	}
	printf("Deseja rodar Insertion sort? (Digite 0 para NAO e 1 para SIM) ");
	int booleanIsort;
	scanf("%d", &booleanIsort);
	while ((booleanIsort != 0) && (booleanIsort != 1)){
		printf("Insira um valor válido\n");
		scanf("%d", &booleanIsort);
	} 
	if (booleanIsort == 1){
		int *B = geraArray(qn);
		arrayAleatorio(B, qn, 32717, nmax);
		printf("Array ordenado por Insertion sort: \n");
		struct timespec tii;
		clock_gettime(CLOCK_MONOTONIC, &tii);
		iSort(B, qn);
		struct timespec tfi;
		clock_gettime(CLOCK_MONOTONIC, &tfi);
		imprimeArray(B, qn);
		printf("Tempo de execução em nanosegundos: %Lf\n", difTempo(tfi, tii));
		printf("Tempo de execução em segundos: %Lf\n", difTempo(tfi, tii) * 1E-9);
	}
	printf("Deseja rodar Selection sort? (Digite 0 para NAO e 1 para SIM) ");
	int booleanSsort;
	scanf("%d", &booleanSsort);
	while ((booleanSsort != 0) && (booleanSsort != 1)){
		printf("Insira um valor válido\n");
		scanf("%d", &booleanSsort);
	} 
	if (booleanSsort == 1){
		int *C = geraArray(qn);
		arrayAleatorio(C, qn, 32717, nmax);
		printf("Array ordenado por Insertion sort: \n");
		struct timespec tis;
		clock_gettime(CLOCK_MONOTONIC, &tis);
		sSort(C, qn);
		struct timespec tfs;
		clock_gettime(CLOCK_MONOTONIC, &tfs);
		imprimeArray(C, qn);
		printf("Tempo de execução em nanosegundos: %Lf\n", difTempo(tfs, tis));
		printf("Tempo de execução em segundos: %Lf\n", difTempo(tfs, tis) * 1E-9);
	}
	return 0;
}
