// IV-Serialização de EDs

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

typedef struct {
    REGISTRO *registros; // ponteiro para os registros
    int tamanho; // número de registros
    int capacidade; // capacidade do vetor de registros
} Tabela;

typedef struct NO {
    int nroUSP; // chave primária
    struct NO *proximo; // ponteiro para o próximo nó
} NO;

// Passo 1: Escolha uma estrutura de dados dentre lista sequencial (i.e., vetor), lista ligada dinâmica (simples ou dupla), árvore de busca binária, grafo em listas de adjacências ou grafo em matriz de adjacências. 
// Passo 2: Escolha a operação de leitura (do arquivo para a memória) ou escrita (da ED em arquivo). Tipicamente a leitura é mais trabalhosa, pois envolve recriar a ED usando malloc() etc. 
// Passo 3: Escolha o tipo de arquivo: texto com delimitadores (use fprintf/fscanf) ou binário (use fwrite/fread). Passo 4: Implemente o algoritmo correspondente à configuração escolhida (ED, operação, tipo de arquivo)  e, em caso de dúvidas, teste no próprio compilador. 

void serializarED(const char *nomeArquivo, Tabela *tabela) {
    FILE *arq = fopen(nomeArquivo, "wb");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }
    
    fwrite(&tabela->tamanho, sizeof(int), 1, arq);
    fwrite(tabela->registros, sizeof(REGISTRO), tabela->tamanho, arq);
    
    fclose(arq);
}

void desserializarED(const char *nomeArquivo, Tabela *tabela) {
    FILE *arq = fopen(nomeArquivo, "rb");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }
    
    fread(&tabela->tamanho, sizeof(int), 1, arq);
    tabela->capacidade = tabela->tamanho; // Inicializa a capacidade igual ao tamanho
    tabela->registros = malloc(tabela->capacidade * sizeof(REGISTRO));
    
    if (tabela->registros == NULL) {
        perror("Erro ao alocar memória para os registros");
        fclose(arq);
        return;
    }
    
    fread(tabela->registros, sizeof(REGISTRO), tabela->tamanho, arq);
    
    fclose(arq);
}
void inicializarTabela(Tabela *tabela, int capacidadeInicial) {
    tabela->tamanho = 0;
    tabela->capacidade = capacidadeInicial;
    tabela->registros = malloc(capacidadeInicial * sizeof(REGISTRO));
    if (tabela->registros == NULL) {
        perror("Erro ao alocar memória para a tabela");
        exit(EXIT_FAILURE);
    }
}
int main() {
    Tabela tabela;
    inicializarTabela(&tabela, 10); // Inicializa a tabela com capacidade para 10 registros
    
    // Exemplo de uso
    REGISTRO r1 = {12345, 1, 1, 20, true};
    tabela.registros[tabela.tamanho++] = r1; // Adiciona um registro
    serializarED("dados.bin", &tabela); // Serializa a tabela para o arquivo
    
    Tabela novaTabela;
    inicializarTabela(&novaTabela, 10);
    desserializarED("dados.bin", &novaTabela); // Desserializa do arquivo para uma nova tabela
    
    // Exibe os registros desserializados
    for (int i = 0; i < novaTabela.tamanho; i++) {
        printf("NroUSP: %d, Curso: %d, Estado: %d, Idade: %d, Valido: %d\n",
               novaTabela.registros[i].NroUSP,
               novaTabela.registros[i].curso,
               novaTabela.registros[i].estado,
               novaTabela.registros[i].idade,
               novaTabela.registros[i].valido);
    }
    
    free(tabela.registros);
    free(novaTabela.registros);
    
    return 0;
}  