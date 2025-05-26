// III-Exercícios em tabelas de índices secundários 

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

typedef struct NO {
    int nroUSP; // chave primária
    struct NO *proximo; // ponteiro para o próximo nó
} NO;

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

// Nos exercícios a seguir considere ainda a existência de tabelas de índices secundários (e suas respectivas operações de inserção e exclusão) para os campos int curso e int estado, e duas funções adicionais que, dada uma chave secundária de interesse, retornam a lista ligada das chaves primárias a ela relacionadas:

// NO* chavesCurso(int curso) 
// NO *chavesEstado(int estado) 

NO* chavesCurso(Tabela *tabela, int curso) {
    NO *lista = NULL;
    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->registros[i].curso == curso) {
            NO *novo = malloc(sizeof(NO));
            novo->nroUSP = tabela->registros[i].NroUSP;
            novo->proximo = lista;
            lista = novo;
        }
    }
    return lista;
}
NO* chavesEstado(Tabela *tabela, int estado) {
    NO *lista = NULL;
    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->registros[i].estado == estado) {
            NO *novo = malloc(sizeof(NO));
            novo->nroUSP = tabela->registros[i].NroUSP;
            novo->proximo = lista;
            lista = novo;
        }
    }
    return lista;
}

// No caso dos exercícios de exclusão, certifique-se de que você entende porque a atualização de índices secundários (mas não do índice primário, que sempre precisa ser excluído) é opcional. 

// 1. Escreva uma função para inserir um novo registro r no arquivo, tomando cuidado para evitar chaves duplicadas (verifique quais índices precisam ser atualizados). 

void exercicio1(Tabela *indicePrimario, Tabela *indiceCurso, Tabela *indiceEstado, REGISTRO r, FILE *arq) {
    // Verifica se o registro já existe no índice primário
    if (buscarEndereco(indicePrimario, r.NroUSP) != -1) {
        printf("Registro com NroUSP %d já existe.\n", r.NroUSP);
        return; // Registro duplicado
    }
    
    // Insere o registro no arquivo
    fseek(arq, 0, SEEK_END); // Move para o final do arquivo
    int end = ftell(arq);
    fwrite(&r, sizeof(REGISTRO), 1, arq);
    
    // Insere no índice primário
    inserirIndice(indicePrimario, r.NroUSP, end);
    
    // Insere no índice secundário de curso
    inserirIndice(indiceCurso, r.curso, end);
    
    // Insere no índice secundário de estado
    inserirIndice(indiceEstado, r.estado, end);
}

// 2. Escreva uma função para exibir todos os registros do curso X. 

void exercicio2(Tabela *indiceCurso, int curso, FILE *arq) {
    NO *lista = chavesCurso(indiceCurso, curso);
    if (lista == NULL) {
        printf("Nenhum registro encontrado para o curso %d.\n", curso);
        return;
    }
    
    printf("Registros do curso %d:\n", curso);
    NO *temp = lista;
    while (temp != NULL) {
        REGISTRO r;
        fseek(arq, buscarEndereco(indiceCurso, temp->nroUSP), SEEK_SET);
        fread(&r, sizeof(REGISTRO), 1, arq);
        printf("NroUSP: %d, Curso: %d, Estado: %d, Idade: %d\n", r.NroUSP, r.curso, r.estado, r.idade);
        temp = temp->proximo;
    }
    
    // Libera a lista ligada
    while (lista != NULL) {
        NO *aux = lista;
        lista = lista->proximo;
        free(aux);
    }
}

// 3. Escreva uma função para excluir o registro de nroUSP X (verifique quais índices precisam ser atualizados). 

void exercicio3(Tabela *indicePrimario, Tabela *indiceCurso, Tabela *indiceEstado, int nroUSP, FILE *arq) {
    // Busca o endereço do registro no índice primário
    int end = buscarEndereco(indicePrimario, nroUSP);
    if (end == -1) {
        printf("Registro com NroUSP %d não encontrado.\n", nroUSP);
        return; // Registro não encontrado
    }
    
    // Exclui do índice primário
    excluirIndice(indicePrimario, nroUSP);
    
    // Exclui do índice secundário de curso
    REGISTRO r;
    fseek(arq, end, SEEK_SET);
    fread(&r, sizeof(REGISTRO), 1, arq);
    excluirIndice(indiceCurso, r.NroUSP);
    
    // Exclui do índice secundário de estado
    excluirIndice(indiceEstado, r.NroUSP);
    
    // Marca o registro como inválido (exclusão lógica)
    r.valido = false;
    fseek(arq, end, SEEK_SET);
    fwrite(&r, sizeof(REGISTRO), 1, arq);
    
    printf("Registro com NroUSP %d excluído.\n", nroUSP);
}

// 4. Escreva uma função para excluir todos os registros do curso X (verifique quais índices precisam ser atualizados). 

void exercicio4(Tabela *indicePrimario, Tabela *indiceCurso, Tabela *indiceEstado, int curso, FILE *arq) {
    NO *lista = chavesCurso(indiceCurso, curso);
    if (lista == NULL) {
        printf("Nenhum registro encontrado para o curso %d.\n", curso);
        return;
    }
    
    printf("Excluindo registros do curso %d:\n", curso);
    NO *temp = lista;
    while (temp != NULL) {
        REGISTRO r;
        int end = buscarEndereco(indicePrimario, temp->nroUSP);
        if (end != -1) {
            fseek(arq, end, SEEK_SET);
            fread(&r, sizeof(REGISTRO), 1, arq);
            
            // Exclui do índice primário
            excluirIndice(indicePrimario, r.NroUSP);
            
            // Exclui do índice secundário de estado
            excluirIndice(indiceEstado, r.NroUSP);
            
            // Marca o registro como inválido
            r.valido = false;
            fseek(arq, end, SEEK_SET);
            fwrite(&r, sizeof(REGISTRO), 1, arq);
            
            printf("Registro com NroUSP %d excluído.\n", r.NroUSP);
        }
        temp = temp->proximo;
    }
    
    // Libera a lista ligada
    while (lista != NULL) {
        NO *aux = lista;
        lista = lista->proximo;
        free(aux);
    }
}

// 5. Escreva uma função para alterar a idade atual de um registro de nroUSP X para a idade Y (verifique quais índices precisam ser atualizados). 

void exercicio5(Tabela *indicePrimario, int nroUSP, int novaIdade, FILE *arq) {
    // Busca o endereço do registro no índice primário
    int end = buscarEndereco(indicePrimario, nroUSP);
    if (end == -1) {
        printf("Registro com NroUSP %d não encontrado.\n", nroUSP);
        return; // Registro não encontrado
    }
    
    // Lê o registro
    REGISTRO r;
    fseek(arq, end, SEEK_SET);
    fread(&r, sizeof(REGISTRO), 1, arq);
    
    // Atualiza a idade
    r.idade = novaIdade;
    
    // Escreve o registro atualizado de volta no arquivo
    fseek(arq, end, SEEK_SET);
    fwrite(&r, sizeof(REGISTRO), 1, arq);
    
    printf("Idade do registro com NroUSP %d atualizada para %d.\n", nroUSP, novaIdade);
}

// 6. Escreva uma função para alterar o curso de um registro de nroUSP X para o curso Y (verifique quais índices precisam ser atualizados). 

void exercicio6(Tabela *indicePrimario, Tabela *indiceCurso, int nroUSP, int novoCurso, FILE *arq) {
    // Busca o endereço do registro no índice primário
    int end = buscarEndereco(indicePrimario, nroUSP);
    if (end == -1) {
        printf("Registro com NroUSP %d não encontrado.\n", nroUSP);
        return; // Registro não encontrado
    }
    
    // Lê o registro
    REGISTRO r;
    fseek(arq, end, SEEK_SET);
    fread(&r, sizeof(REGISTRO), 1, arq);
    
    // Atualiza o curso
    r.curso = novoCurso;
    
    // Escreve o registro atualizado de volta no arquivo
    fseek(arq, end, SEEK_SET);
    fwrite(&r, sizeof(REGISTRO), 1, arq);
    
    // Atualiza o índice secundário de curso
    excluirIndice(indiceCurso, r.NroUSP); // Remove do índice antigo
    inserirIndice(indiceCurso, novoCurso, end); // Insere no novo índice
    
    printf("Curso do registro com NroUSP %d atualizado para %d.\n", nroUSP, novoCurso);
}

// 7. Escreva uma função para alterar o registro de nroUSP X para o nroUSP Y se possível (verifique quais índices precisam ser atualizados). 

void exercicio7(Tabela *indicePrimario, Tabela *indiceCurso, Tabela *indiceEstado, int nroUSPX, int nroUSPY, FILE *arq) {
    // Verifica se o novo NroUSP já existe no índice primário
    if (buscarEndereco(indicePrimario, nroUSPY) != -1) {
        printf("Chave duplicada: %d\n", nroUSPY);
        return; // Chave já existe
    }
    
    // Busca o endereço do registro antigo
    int end = buscarEndereco(indicePrimario, nroUSPX);
    if (end == -1) {
        printf("Registro com NroUSP %d não encontrado.\n", nroUSPX);
        return; // Registro não encontrado
    }
    
    // Lê o registro antigo
    REGISTRO r;
    fseek(arq, end, SEEK_SET);
    fread(&r, sizeof(REGISTRO), 1, arq);
    
    // Atualiza o NroUSP
    r.NroUSP = nroUSPY;
    
    // Escreve o registro atualizado de volta no arquivo
    fseek(arq, end, SEEK_SET);
    fwrite(&r, sizeof(REGISTRO), 1, arq);
    
    // Atualiza o índice primário
    excluirIndice(indicePrimario, nroUSPX); // Remove do índice antigo
    inserirIndice(indicePrimario, nroUSPY, end); // Insere no novo índice
    
    // Atualiza os índices secundários de curso e estado
    excluirIndice(indiceCurso, r.curso); // Remove do índice antigo de curso
    inserirIndice(indiceCurso, r.curso, end); // Insere no novo índice de curso
    
    excluirIndice(indiceEstado, r.estado); // Remove do índice antigo de estado
    inserirIndice(indiceEstado, r.estado, end); // Insere no novo índice de estado
    
    printf("Registro alterado de NroUSP %d para %d.\n", nroUSPX, nroUSPY);
}