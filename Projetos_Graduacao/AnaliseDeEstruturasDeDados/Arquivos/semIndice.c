// I-Exercícios em arquivos simples (sem índices) 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct { 
    int NroUSP; // chave primária int curso; int estado; 
    int curso;
    int estado;
    int idade; 
    bool valido; // para exclusão lógica 
    } REGISTRO; 

// Todos os arquivos são mantidos em ordem aleatória de chaves. Para os exercícios a seguir, não há nenhuma estrutura de índices disponível.

// 1. Reescreva um arquivo binário arq1 em um novo arquivo arq2 do tipo texto com separador barra (|), eliminado os registros inválidos. 

void exercicio1() {
    FILE *arq1, *arq2;
    REGISTRO r;
    arq1 = fopen("arq1.bin", "rb");
    arq2 = fopen("arq2.txt", "w");
    if (arq1 == NULL || arq2 == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }
    
    while (fread(&r, sizeof(REGISTRO), 1, arq1)) {
        if (r.valido) {
            fprintf(arq2, "%d|%d|%d|%d\n", r.NroUSP, r.curso, r.estado, r.idade);
        }
    }
    
    fclose(arq1);
    fclose(arq2);
}

// 2. O contrário, ou seja, copiando um arquivo texto para binário

void exercicio2() {
    FILE *arq1, *arq2;
    REGISTRO r;
    arq1 = fopen("arq1.txt", "r");
    arq2 = fopen("arq2.bin", "wb");
    if (arq1 == NULL || arq2 == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }
    
    while (fscanf(arq1, "%d|%d|%d|%d\n", &r.NroUSP, &r.curso, &r.estado, &r.idade) != EOF) {
        r.valido = true;
        fwrite(&r, sizeof(REGISTRO), 1, arq2);
    }
    
    fclose(arq1);
    fclose(arq2);
}

// 3. Escreva uma função que, dada um nroUSP X, retorne o registro correspondente. 

REGISTRO exercicio3(int nroUSP) {
    FILE *arq;
    REGISTRO r;
    arq = fopen("arq1.bin", "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    
    while (fread(&r, sizeof(REGISTRO), 1, arq)) {
        if (r.NroUSP == nroUSP && r.valido) {
            fclose(arq);
            return r;
        }
    }
    
    fclose(arq);
    r.NroUSP = -1; // Indica que não foi encontrado
    return r;
}

// 4. Escreva uma função para inserir um novo registro r no arquivo, tomando cuidado para evitar chaves duplicadas. 

void exercicio4(REGISTRO r) {
    FILE *arq;
    REGISTRO temp;
    bool encontrado = false;
    
    arq = fopen("arq1.bin", "rb+");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    while (fread(&temp, sizeof(REGISTRO), 1, arq)) {
        if (temp.NroUSP == r.NroUSP) {
            encontrado = true;
            break;
        }
    }
    
    if (!encontrado) {
        fseek(arq, 0, SEEK_END);
        fwrite(&r, sizeof(REGISTRO), 1, arq);
    } else {
        printf("Registro com NroUSP %d já existe.\n", r.NroUSP);
    }
    
    fclose(arq);
}

// 5. Escreva uma função para excluir todos os registros do curso X. 

void exercicio5(int curso) {
    FILE *arq;
    REGISTRO r;
    arq = fopen("arq1.bin", "rb+");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    while (fread(&r, sizeof(REGISTRO), 1, arq)) {
        if (r.curso == curso) {
            r.valido = false; // Marca como inválido
            fseek(arq, -sizeof(REGISTRO), SEEK_CUR);
            fwrite(&r, sizeof(REGISTRO), 1, arq);
        }
    }
    
    fclose(arq);
}

// 6. Escreva uma função para alterar o curso de um aluno de nroUSP do curso X para o curso Y. 

void exercicio6(int nroUSP, int novoCurso) {
    FILE *arq;
    REGISTRO r;
    arq = fopen("arq1.bin", "rb+");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    while (fread(&r, sizeof(REGISTRO), 1, arq)) {
        if (r.NroUSP == nroUSP && r.valido) {
            r.curso = novoCurso; // Altera o curso
            fseek(arq, -sizeof(REGISTRO), SEEK_CUR);
            fwrite(&r, sizeof(REGISTRO), 1, arq);
            fclose(arq);
            return;
        }
    }
    
    printf("Registro com NroUSP %d não encontrado.\n", nroUSP);
    fclose(arq);
}