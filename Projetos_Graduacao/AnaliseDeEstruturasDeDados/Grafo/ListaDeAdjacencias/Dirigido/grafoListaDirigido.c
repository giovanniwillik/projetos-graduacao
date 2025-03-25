#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX  // Representa ausência de caminho

// Estrutura de um nó na lista de adjacência
typedef struct No {
    int vertice;
    struct No *prox;
} No;

// Estrutura do Grafo
typedef struct {
    No *lista[MAX_VERTICES];
    int numVertices;
} Grafo;

// Função para criar um novo nó
No* criarNo(int vertice) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->vertice = vertice;
    novoNo->prox = NULL;
    return novoNo;
}

// Função para inicializar o grafo
void inicializarGrafo(Grafo *g, int numVertices) {
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++)
        g->lista[i] = NULL;
}

// Função para verificar a existência de uma aresta
int existeAresta(Grafo *g, int origem, int destino) {
    No *temp = g->lista[origem];
    while (temp) {
        if (temp->vertice == destino) return 1;
        temp = temp->prox;
    }
    return 0;
}

// Função para inserir uma aresta
void inserirAresta(Grafo *g, int origem, int destino) {
    No *novoNo = criarNo(destino);
    novoNo->prox = g->lista[origem];
    g->lista[origem] = novoNo;
}

// Função para excluir uma aresta
void excluirAresta(Grafo *g, int origem, int destino) {
    No *temp = g->lista[origem], *anterior = NULL;
    while (temp && temp->vertice != destino) {
        anterior = temp;
        temp = temp->prox;
    }
    if (temp) {
        if (anterior) anterior->prox = temp->prox;
        else g->lista[origem] = temp->prox;
        free(temp);
    }
}

// Função para obter o grau de saída de um vértice
int grauSaida(Grafo *g, int vertice) {
    int grau = 0;
    No *temp = g->lista[vertice];
    while (temp) {
        grau++;
        temp = temp->prox;
    }
    return grau;
}

// Função para obter o grau de entrada de um vértice
int grauEntrada(Grafo *g, int vertice) {
    int grau = 0;
    for (int i = 0; i < g->numVertices; i++) {
        No *temp = g->lista[i];
        while (temp) {
            if (temp->vertice == vertice) grau++;
            temp = temp->prox;
        }
    }
    return grau;
}

// ---------------- BUSCA EM PROFUNDIDADE (DFS) ----------------
void buscaProfundidade(Grafo *g, int vertice, int visitado[], int *contador, int respostas[], int N) {
    visitado[vertice] = 1;
    if (*contador < N) {
        respostas[(*contador)++] = vertice;
    }
    No *temp = g->lista[vertice];
    while (temp) {
        if (!visitado[temp->vertice]) {
            buscaProfundidade(g, temp->vertice, visitado, contador, respostas, N);
        }
        temp = temp->prox;
    }
}

// ---------------- BUSCA EM LARGURA (BFS) ----------------
void buscaLargura(Grafo *g, int inicio, int N, int respostas[]) {
    int visitado[MAX_VERTICES] = {0};
    int fila[MAX_VERTICES], frente = 0, fim = 0;
    
    fila[fim++] = inicio;
    visitado[inicio] = 1;
    
    int contador = 0;
    while (frente < fim && contador < N) {
        int v = fila[frente++];
        respostas[contador++] = v;
        
        No *temp = g->lista[v];
        while (temp) {
            if (!visitado[temp->vertice]) {
                fila[fim++] = temp->vertice;
                visitado[temp->vertice] = 1;
            }
            temp = temp->prox;
        }
    }
}

// ---------------- DETECÇÃO DE CICLOS ----------------
int detectaCicloDFS(Grafo *g, int v, int visitado[], int recStack[]) {
    visitado[v] = 1;
    recStack[v] = 1;
    
    No *temp = g->lista[v];
    while (temp) {
        if (!visitado[temp->vertice] && detectaCicloDFS(g, temp->vertice, visitado, recStack))
            return 1;
        else if (recStack[temp->vertice])
            return 1;
        temp = temp->prox;
    }
    
    recStack[v] = 0;
    return 0;
}

int detectarCiclo(Grafo *g) {
    int visitado[MAX_VERTICES] = {0};
    int recStack[MAX_VERTICES] = {0};
    
    for (int i = 0; i < g->numVertices; i++)
        if (!visitado[i] && detectaCicloDFS(g, i, visitado, recStack))
            return 1;
    return 0;
}

// ---------------- IDENTIFICAÇÃO DE COMUNIDADES ----------------
void encontrarComunidades(Grafo *g) {
    int visitado[MAX_VERTICES] = {0};
    
    for (int i = 0; i < g->numVertices; i++) {
        if (!visitado[i]) {
            printf("Comunidade: ");
            int respostas[MAX_VERTICES], contador = 0;
            buscaProfundidade(g, i, visitado, &contador, respostas, MAX_VERTICES);
            for (int j = 0; j < contador; j++)
                printf("%d ", respostas[j]);
            printf("\n");
        }
    }
}

// ---------------- EXIBIÇÃO EM RAIO (Melhores caminhos) ----------------
void exibirRaio(Grafo *g) {
    printf("Funcionalidade em desenvolvimento...\n");
}

// ---------------- MELHOR CAMINHO ----------------
void melhorCaminho(Grafo *g, int origem, int destino) {
    printf("Funcionalidade em desenvolvimento...\n");
}

// ---------------- TESTE ----------------
int main() {
    Grafo g;
    inicializarGrafo(&g, 5);
    
    inserirAresta(&g, 0, 1);
    inserirAresta(&g, 1, 2);
    inserirAresta(&g, 2, 3);
    inserirAresta(&g, 3, 4);
    inserirAresta(&g, 4, 0);

    printf("Ciclo detectado: %s\n", detectarCiclo(&g) ? "Sim" : "Não");
    
    encontrarComunidades(&g);
    
    return 0;
}
