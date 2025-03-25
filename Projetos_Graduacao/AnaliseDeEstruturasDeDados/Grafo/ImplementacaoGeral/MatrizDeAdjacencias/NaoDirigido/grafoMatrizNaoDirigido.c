#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX // Representa ausência de caminho

// Estrutura do Grafo
typedef struct
{
    int matriz[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Grafo;

// Função para inicializar o grafo
void inicializarGrafo(Grafo *g, int numVertices)
{
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
            g->matriz[i][j] = 0;
}

// Função para verificar a existência de uma aresta
int existeAresta(Grafo *g, int v1, int v2)
{
    return g->matriz[v1][v2];
}

// Função para inserir uma aresta (grafo não dirigido)
void inserirAresta(Grafo *g, int v1, int v2)
{
    g->matriz[v1][v2] = 1;
    g->matriz[v2][v1] = 1; // Bidirecional
}

// Função para excluir uma aresta
void excluirAresta(Grafo *g, int v1, int v2)
{
    g->matriz[v1][v2] = 0;
    g->matriz[v2][v1] = 0; // Bidirecional
}

// Função para obter o grau de um vértice
int grauVertice(Grafo *g, int v)
{
    int grau = 0;
    for (int i = 0; i < g->numVertices; i++)
        if (g->matriz[v][i])
            grau++;
    return grau;
}

// Função para copiar o grafo
void copiarGrafo(Grafo *src, Grafo *dest)
{
    dest->numVertices = src->numVertices;
    for (int i = 0; i < src->numVertices; i++)
        for (int j = 0; j < src->numVertices; j++)
            dest->matriz[i][j] = src->matriz[i][j];
}

// ---------------- BUSCA EM PROFUNDIDADE (DFS) ----------------
void buscaProfundidade(Grafo *g, int v, int visitado[], int *contador, int respostas[], int N)
{
    visitado[v] = 1;
    if (*contador < N)
    {
        respostas[(*contador)++] = v;
    }
    for (int i = 0; i < g->numVertices; i++)
    {
        if (g->matriz[v][i] && !visitado[i])
        {
            buscaProfundidade(g, i, visitado, contador, respostas, N);
        }
    }
}

// ---------------- BUSCA EM LARGURA (BFS) ----------------
void buscaLargura(Grafo *g, int inicio, int N, int respostas[])
{
    int visitado[MAX_VERTICES] = {0};
    int fila[MAX_VERTICES], frente = 0, fim = 0;

    fila[fim++] = inicio;
    visitado[inicio] = 1;

    int contador = 0;
    while (frente < fim && contador < N)
    {
        int v = fila[frente++];
        respostas[contador++] = v;

        for (int i = 0; i < g->numVertices; i++)
        {
            if (g->matriz[v][i] && !visitado[i])
            {
                fila[fim++] = i;
                visitado[i] = 1;
            }
        }
    }
}

// ---------------- DETECÇÃO DE CICLOS ----------------
int detectaCicloDFS(Grafo *g, int v, int visitado[], int pai)
{
    visitado[v] = 1;

    for (int i = 0; i < g->numVertices; i++)
    {
        if (g->matriz[v][i])
        {
            if (!visitado[i])
            {
                if (detectaCicloDFS(g, i, visitado, v))
                    return 1;
            }
            else if (i != pai)
            {
                return 1;
            }
        }
    }
    return 0;
}

int detectarCiclo(Grafo *g)
{
    int visitado[MAX_VERTICES] = {0};

    for (int i = 0; i < g->numVertices; i++)
        if (!visitado[i] && detectaCicloDFS(g, i, visitado, -1))
            return 1;
    return 0;
}

// ---------------- IDENTIFICAÇÃO DE COMUNIDADES ----------------
void encontrarComunidades(Grafo *g)
{
    int visitado[MAX_VERTICES] = {0};

    for (int i = 0; i < g->numVertices; i++)
    {
        if (!visitado[i])
        {
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
void exibirRaio(Grafo *g)
{
    for (int i = 0; i < g->numVertices; i++)
    {
        printf("Raio de %d: ", i);
        int visitado[MAX_VERTICES] = {0};
        int fila[MAX_VERTICES], frente = 0, fim = 0;

        fila[fim++] = i;
        visitado[i] = 1;

        int nivel = 0;
        while (frente < fim)
        {
            int tam = fim;
            for (int i = 0; i < tam; i++)
            {
                int v = fila[frente++];
                printf("%d ", v);

                for (int j = 0; j < g->numVertices; j++)
                {
                    if (g->matriz[v][j] && !visitado[j])
                    {
                        fila[fim++] = j;
                        visitado[j] = 1;
                    }
                }
            }
            printf("\n");
            nivel++;
        }
    }
}

// ---------------- MELHOR CAMINHO ----------------
void mehorCaminho(Grafo *g, int origem, int destino)
{
    int visitado[MAX_VERTICES] = {0};
    int fila[MAX_VERTICES], frente = 0, fim = 0;

    fila[fim++] = origem;
    visitado[origem] = 1;

    int via[MAX_VERTICES];
    for (int i = 0; i < g->numVertices; i++)
        via[i] = -1;
    via[origem] = 0;

    while (frente < fim)
    {
        int v = fila[frente++];

        for (int i = 0; i < g->numVertices; i++)
        {
            if (g->matriz[v][i] && !visitado[i])
            {
                fila[fim++] = i;
                visitado[i] = 1;
                via[i] = v;
            }
        }
    }

    printf("Melhor caminho de %d até %d:\n", origem, destino);
    if (via[destino] == -1 && origem != destino)
    {
        printf("Não existe caminho de %d até %d.\n", origem, destino);
    }
    else
    {
        int caminho[MAX_VERTICES], tam = 0;
        int atual = destino;

        while (atual != 0)
        {
            caminho[tam++] = atual;
            if (atual == origem)
                break;
            atual = via[atual];
        }

        if (caminho[tam - 1] != origem)
        {
            printf("Não existe caminho de %d até %d.\n", origem, destino);
        }
        else
        {
            for (int i = tam - 1; i >= 0; i++)
                printf("%d", caminho[i]);
        }
    }
}

// ---------------- TESTE ----------------
int main()
{
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
