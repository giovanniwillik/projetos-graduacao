// II-Exercícios em tabelas de índices primários 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Para os exercícios a seguir, considere os mesmos arquivos do tipo:

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

// E também a existência de uma tabela de índices primários mantida em memória e suas respectivas funções de manipulação.  

// bool inserirÍndice(Tabela, int nroUSP, int end); // inserção em tabela ordenada, retornando true/false 
// int buscarEndereço(Tabela, int nroUSP); // retorna -1 se end não existe 
// int excluirÍndice(Tabela, int nroUSP); // retorna o endereço exluído, ou -1 se não encontrar 

bool inserirIndice(Tabela *tabela, int nroUSP, int end) {
    if (tabela->tamanho >= tabela->capacidade) {
        tabela->capacidade *= 2;
        tabela->registros = realloc(tabela->registros, tabela->capacidade * sizeof(REGISTRO));
        if (tabela->registros == NULL) {
            return false; // falha na alocação
        }
    }
    
    // Inserção ordenada
    int i;
    for (i = tabela->tamanho - 1; (i >= 0 && tabela->registros[i].NroUSP > nroUSP); i--) {
        tabela->registros[i + 1] = tabela->registros[i];
    }
    
    tabela->registros[i + 1].NroUSP = nroUSP;
    tabela->registros[i + 1].estado = end; // armazenando o endereço
    tabela->tamanho++;
    
    return true;
}

int buscarEndereco(Tabela *tabela, int nroUSP) {
    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->registros[i].NroUSP == nroUSP) {
            return tabela->registros[i].estado; // retorna o endereço
        }
    }
    return -1; // não encontrado
}

int excluirIndice(Tabela *tabela, int nroUSP) {
    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->registros[i].NroUSP == nroUSP) {
            int end = tabela->registros[i].estado; // guarda o endereço
            // Move os registros para preencher o espaço
            for (int j = i; j < tabela->tamanho - 1; j++) {
                tabela->registros[j] = tabela->registros[j + 1];
            }
            tabela->tamanho--;
            return end; // retorna o endereço excluído
        }
    }
    return -1; // não encontrado
}

// 1. Implemente o procedimento de ordenação KeySort, que dado um arquivo arq1 cria uma tabela temporária de chaves em memória (idêntica a uma tabela de índices primários) e então reescreve o arquivo em um novo arquivo de saída arq2, na ordem correta de chaves. 

void exercicio1(FILE *arq1, FILE *arq2) {
    Tabela tabela;
    tabela.tamanho = 0;
    tabela.capacidade = 10;
    tabela.registros = malloc(tabela.capacidade * sizeof(REGISTRO));
    
    REGISTRO r;
    while (fread(&r, sizeof(REGISTRO), 1, arq1)) {
        if (r.valido) {
            inserirIndice(&tabela, r.NroUSP, ftell(arq2)); // Armazena o endereço do registro
        }
    }
    // Reescreve o arquivo na ordem correta
    for (int i = 0; i < tabela.tamanho; i++) {
        fseek(arq2, tabela.registros[i].estado, SEEK_SET); // Move para o endereço do registro
        fwrite(&tabela.registros[i], sizeof(REGISTRO), 1, arq2);
    }
    fclose(arq1);
    fclose(arq2);
    // Libera a memória alocada
    
    free(tabela.registros);
}

// 2. Escreva uma função para inserir um novo registro r no arquivo, tomando cuidado para evitar chaves duplicadas (use o índice). 

void exercicio2(FILE *arq, Tabela *tabela, REGISTRO r) {
    if (buscarEndereco(tabela, r.NroUSP) != -1) {
        printf("Chave duplicada: %d\n", r.NroUSP);
        return; // Chave já existe
    }
    
    // Insere o registro no arquivo
    fseek(arq, 0, SEEK_END); // Move para o final do arquivo
    fwrite(&r, sizeof(REGISTRO), 1, arq);
    
    // Insere o índice
    inserirIndice(tabela, r.NroUSP, ftell(arq) - sizeof(REGISTRO)); // Armazena o endereço do registro
}

// 3. Escreva uma função que, dada um nroUSP X, retorne o registro correspondente (use o índice). 

REGISTRO exercicio3(Tabela *tabela, int nroUSP) {
    int end = buscarEndereco(tabela, nroUSP);
    REGISTRO r;
    if (end != -1) {
        FILE *arq = fopen("arq.dat", "rb");
        fseek(arq, end, SEEK_SET);
        fread(&r, sizeof(REGISTRO), 1, arq);
        fclose(arq);
        return r; // Retorna o registro encontrado
    }
    r.valido = false; // Registro não encontrado
    return r;
}

// 4. Escreva uma função para excluir todos os registros do curso X (use o índice). 

void exercicio4(Tabela *tabela, FILE *arq, int curso) {
    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->registros[i].curso == curso) {
            excluirIndice(tabela, tabela->registros[i].NroUSP); // Exclui do índice
            // Marca o registro como inválido
            REGISTRO r;
            fseek(arq, tabela->registros[i].estado, SEEK_SET);
            fread(&r, sizeof(REGISTRO), 1, arq);
            r.valido = false;
            fseek(arq, tabela->registros[i].estado, SEEK_SET);
            fwrite(&r, sizeof(REGISTRO), 1, arq);
        }
    }
}

// 5. Escreva uma função para alterar o curso de um registro de nroUSP X para o curso Y (use o índice). 

void exercicio5(Tabela *tabela, FILE *arq, int nroUSP, int novoCurso) {
    int end = buscarEndereco(tabela, nroUSP);
    if (end != -1) {
        REGISTRO r;
        fseek(arq, end, SEEK_SET);
        fread(&r, sizeof(REGISTRO), 1, arq);
        r.curso = novoCurso; // Altera o curso
        fseek(arq, end, SEEK_SET);
        fwrite(&r, sizeof(REGISTRO), 1, arq);
    } else {
        printf("Registro com nroUSP %d não encontrado.\n", nroUSP);
    }
}

// 6. Escreva uma função para alterar o registro de nroUSP X para o nroUSP Y se possível (use o índice). 

void exercicio6(Tabela *tabela, FILE *arq, int nroUSPX, int nroUSPY) {
    if (buscarEndereco(tabela, nroUSPY) != -1) {
        printf("Chave duplicada: %d\n", nroUSPY);
        return; // Chave já existe
    }
    
    int end = buscarEndereco(tabela, nroUSPX);
    if (end != -1) {
        REGISTRO r;
        fseek(arq, end, SEEK_SET);
        fread(&r, sizeof(REGISTRO), 1, arq);
        r.NroUSP = nroUSPY; // Altera o nroUSP
        fseek(arq, end, SEEK_SET);
        fwrite(&r, sizeof(REGISTRO), 1, arq);
        
        // Atualiza o índice
        excluirIndice(tabela, nroUSPX); // Remove o antigo
        inserirIndice(tabela, nroUSPY, end); // Insere o novo
    } else {
        printf("Registro com nroUSP %d não encontrado.\n", nroUSPX);
    }
}