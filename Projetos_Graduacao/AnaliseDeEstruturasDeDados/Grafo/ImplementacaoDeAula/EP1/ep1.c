//--------------------------------------------------------------
// COLOQUE OS NOMES DOS RESPONSÁVEIS AQUI: Giovanni Willik Del Piccolo
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

// INFORME O NRO DO GRUPO CONFORME PLANILHA DIVULGADA
int grupo() {
  return 39;
}

// ######### ESCREVA O NROUSP AQUI
int nroUSP1() {
    return 15455979;
}

// E O SEGUNDO NROUSP AQUI, SE HOUVER
int nroUSP2() {
    return 0;
}

// -----------------------------
// ESTRUTURAS DE FILA (DINÂMICA)
// -----------------------------

// Nó da fila
typedef struct NoFila
{
    int dado;
    struct NoFila *prox;
} NO_FILA;

// Estrutura da fila com ponteiros para início e fim
typedef struct
{
    NO_FILA *inicio;
    NO_FILA *fim;
} FILA;

// -----------------------------
// ESTRUTURAS DE GRAFO (LISTA DE ADJACÊNCIA)
// -----------------------------

// elemento da lista de resposta - NAO ALTERE ESTA DEFINICAO
typedef struct estr {
    int adj; // um nro. de vertice
    struct estr *prox;
} NO;

typedef struct {
  NO *inicio;   // ponteiro para a lista ligada de adjacência
  int flag;
} VERTICE;

// funcao principal
NO *equidistantes(int V, int A, int ij[], int v1, int v2);

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------

// -----------------------------
// FUNÇÕES AUXILIARES DE FILA (DINÂMICA)
// -----------------------------

// Inicializa a fila vazia
void inicializaFila(FILA *f)
{
    f->inicio = NULL;
    f->fim = NULL;
}

// Verifica se a fila está vazia
int filaVazia(FILA *f)
{
    return f->inicio == NULL;
}

// Insere elemento no final da fila
void entrarFila(FILA *f, int valor)
{
    NO_FILA *novo = (NO_FILA *)malloc(sizeof(NO_FILA));
    if (novo == NULL)
    {
        printf("Erro de alocação de memória!\n");
        return;
    }
    novo->dado = valor;
    novo->prox = NULL;

    if (filaVazia(f))
    {
        f->inicio = novo;
    }
    else
    {
        f->fim->prox = novo;
    }
    f->fim = novo;
}

// Remove elemento do início da fila e retorna seu valor
int sairFila(FILA *f)
{
    if (filaVazia(f))
    {
        return -1;
    }

    NO_FILA *remover = f->inicio;
    int valor = remover->dado;
    f->inicio = remover->prox;

    if (f->inicio == NULL)
    {
        f->fim = NULL;
    }

    free(remover);
    return valor;
}

// -----------------------------
// FUNÇÕES AUXILIARES DE GRAFO (LISTA DE ADJACÊNCIA)
// -----------------------------

void inicializaGrafo(VERTICE *g, int V) {
    int i;
    for (i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
    }
}

void zerarFlags(VERTICE *g, int V)
{
    for (int i = 1; i <= V; i++)
    {
        g[i].flag = 0;
    }
}

NO *existeAresta(VERTICE *g, int i, int j, NO **ant) {
    *ant = NULL;
    NO *p = g[i].inicio;
    while (p) {
        if (p->adj == j) return p;
        *ant = p;
        p = p->prox;
    }
    return NULL;
}

bool inserirAresta(VERTICE *g, int i, int j) {
    NO *ant;
    NO *atual = existeAresta(g, i, j, &ant);
    if (atual) return false; // já existe
    NO *novo = (NO *)malloc(sizeof(NO));
    novo->adj = j;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;
    return true;
}

void larguraComDistancia (int i, int V, VERTICE *g, int *dist) {
    zerarFlags(g, V);
    FILA *f = (FILA *)malloc(sizeof(FILA));
    inicializaFila(f);
    entrarFila(f, i);
    g[i].flag = 1;

    for (int j = 1; j <= V; j++) {
        dist[j] = -1; // Inicializa todas as distâncias como -1
    }
    dist[i] = 0; // Distância inicial é 0

    while (!filaVazia(f))
    {
        i = sairFila(f);
        g[i].flag = 2;

        NO *p = g[i].inicio;
        while (p)
        {
            if (g[p->adj].flag == 0)
            {
                dist[p->adj] = dist[i] + 1; // Atualiza a distância
                entrarFila(f, p->adj);
                g[p->adj].flag = 1;
            }
            p = p->prox;
        }
    }

    free(f);
}

// -----------------------------
// IMPLEMENTAÇÃO FUNÇÃO PRINCIPAL
// -----------------------------

NO *equidistantes(int V, int A, int ij[], int v1, int v2) {
    VERTICE *g = (VERTICE *)malloc((V + 1) * sizeof(VERTICE));
    if (g == NULL) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }

    inicializaGrafo(g, V);
    int i;
    for (i = 0; i < A; i++) {
        int u = ij[2 * i];
        int v = ij[2 * i + 1];
        inserirAresta(g, u, v);
        inserirAresta(g, v, u); // grafo não dirigido
    }

    int *dist1 = (int *)malloc((V + 1) * sizeof(int));
    int *dist2 = (int *)malloc((V + 1) * sizeof(int));
    if (dist1 == NULL || dist2 == NULL) {
        printf("Erro de alocação de memória!\n");
        free(g);
        return NULL;
    }

    larguraComDistancia(v1, V, g, dist1);
    larguraComDistancia(v2, V, g, dist2);

    NO *resposta = NULL;
    NO *ultimo = NULL;
    for (i = 1; i <= V; i++) {
        if (i != v1 && i != v2 && dist1[i] == dist2[i]) {
            NO *novo = (NO *)malloc(sizeof(NO));
            novo->adj = i;
            novo->prox = NULL;
            if (resposta == NULL) {
                resposta = novo;
                ultimo = novo;
            } else {
                ultimo->prox = novo;
                ultimo = novo;
            }
        }
    }
    return resposta; // Retorna a lista de vértices equidistantes
}

//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {


	// aqui vc pode incluir codigo de teste - mas não precisa entregar isso

    int V = 4; // número de vértices
    int A = 4; // número de arestas
    int ij[] = {1, 2, 1, 3, 2, 4, 3, 4}; // arestas (i,j) do grafo
    int v1 = 1; // primeiro vértice
    int v2 = 3; // segundo vértice


	// o EP sera testado com uma serie de chamadas como esta
	NO* teste = NULL;
	teste = equidistantes(V, A, ij, v1, v2);
    printf("Vértices equidistantes a %d e %d:\n", v1, v2);
    NO *p = teste;
    while (p != NULL) {
        printf("%d ", p->adj);
        p = p->prox;
    }
    printf("\n");

    int V2 = 6; // número de vértices
    int A2 = 8; // número de arestas
    int ij2[] = {1, 2, 1, 4, 1, 6, 2, 3, 3, 4, 3, 5, 4, 5, 4, 6}; // arestas (i,j) do grafo
    int v12 = 1; // primeiro vértice
    int v22 = 2; // segundo vértice


	// o EP sera testado com uma serie de chamadas como esta
	NO* teste2 = NULL;
	teste2 = equidistantes(V2, A2, ij2, v12, v22);
    printf("Vértices equidistantes a %d e %d:\n", v12, v22);
    NO *p2 = teste2;
    while (p2 != NULL) {
        printf("%d ", p2->adj);
        p2 = p2->prox;
    }
    printf("\n");

}

// por favor nao inclua nenhum código abaixo da função main()
