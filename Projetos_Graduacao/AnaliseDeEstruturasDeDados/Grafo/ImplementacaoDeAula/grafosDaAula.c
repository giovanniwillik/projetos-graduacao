#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define V 11 // Número máximo de vértices

// -----------------------------
// ESTRUTURAS DE FILA (DINÂMICA)
// -----------------------------

// Nó da fila
typedef struct No
{
    int dado;
    struct No *prox;
} NO_FILA;

// Estrutura da fila com ponteiros para início e fim
typedef struct
{
    NO_FILA *inicio;
    NO_FILA *fim;
} FILA;

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

    printf("Elemento %d enfileirado.\n", valor);
}

// Remove elemento do início da fila e retorna seu valor
int sairFila(FILA *f)
{
    if (filaVazia(f))
    {
        printf("Fila vazia! Não é possível desenfileirar.\n");
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
    printf("Elemento %d desenfileirado.\n", valor);
    return valor;
}

// -----------------------------
// ESTRUTURAS DE GRAFO (LISTA)
// -----------------------------

// Nó da lista de adjacência
typedef struct s
{
    struct s *prox;
    int adj;
    int peso; // peso da aresta (opcional)
} NO;

// Estrutura de vértice: lista de adjacência + flags
typedef struct
{
    NO *inicio; // início da lista de adjacência
    int flag;   // usado para marcações de busca
    int via;    // usado para reconstruir o menor caminho
} VERTICE;

// Inicializa o grafo com todas as listas vazias
void inicializar(VERTICE *g)
{
    for (int i = 1; i <= V; i++)
    {
        g[i].inicio = NULL;
    }
}

// Verifica se uma aresta i -> j existe e retorna ponteiro para o nó
NO *arestaExiste(VERTICE *g, int i, int j, NO **ant)
{
    *ant = NULL;
    NO *p = g[i].inicio;

    while (p)
    {
        if (p->adj == j)
            return p;
        *ant = p;
        p = p->prox;
    }

    return NULL;
}

// Insere aresta direcionada i -> j (se ainda não existir)
bool inserirAresta(VERTICE *g, int i, int j)
{
    NO *ant;
    NO *atual = arestaExiste(g, i, j, &ant);
    if (atual)
        return false; // já existe

    NO *novo = (NO *)malloc(sizeof(NO));
    novo->adj = j;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;

    return true;
}

bool inserirArestaComPeso(VERTICE *h, int i, int j, int peso)
{
    NO *ant;
    NO *atual = arestaExiste(h, i, j, &ant);
    if (atual)
        return false; // já existe

    NO *novo = (NO *)malloc(sizeof(NO));
    novo->adj = j;
    novo->prox = h[i].inicio;
    novo->peso = peso;
    h[i].inicio = novo;

    return true;
}

// Remove aresta i -> j (se existir)
bool excluirAresta(VERTICE *g, int i, int j)
{
    NO *ant;
    NO *atual = arestaExiste(g, i, j, &ant);
    if (!atual)
        return false; // não existe

    if (ant)
        ant->prox = atual->prox;
    else
        g[i].inicio = atual->prox;

    free(atual);
    return true;
}

// Retorna o grau de saída (quantidade de arestas que saem do vértice i)
int grauSaida(VERTICE *g, int i)
{
    int resp = 0;
    NO *p = g[i].inicio;
    while (p)
    {
        resp++;
        p = p->prox;
    }
    return resp;
}

// Retorna o grau de entrada (quantas arestas chegam ao vértice i)
int grauEntrada(VERTICE *g, int i)
{
    int resp = 0;
    for (int j = 1; j <= V; j++)
    {
        NO *p = g[j].inicio;
        while (p)
        {
            if (p->adj == i)
                resp++;
            p = p->prox;
        }
    }
    return resp;
}

// Cria uma cópia profunda do grafo original
VERTICE *copiarGrafo(VERTICE *g)
{
    VERTICE *h = (VERTICE *)malloc(sizeof(VERTICE) * (V + 1));
    for (int i = 1; i <= V; i++)
    {
        NO *p = g[i].inicio;
        h[i].inicio = NULL;
        while (p)
        {
            NO *novo = (NO *)malloc(sizeof(NO));
            novo->adj = p->adj;
            novo->prox = h[i].inicio;
            h[i].inicio = novo;
            p = p->prox;
        }
    }
    return h;
}

// Reseta os flags dos vértices para 0
void zerarFlags(VERTICE *g)
{
    for (int i = 1; i <= V; i++)
    {
        g[i].flag = 0;
    }
}

// Busca em profundidade (DFS) recursiva
void profundidade(VERTICE *g, int i)
{
    g[i].flag = 1;
    NO *p = g[i].inicio;

    while (p)
    {
        if (g[p->adj].flag == 0)
        {
            profundidade(g, p->adj);
        }
        p = p->prox;
    }
    g[i].flag = 2;
}

// Busca em largura (BFS) a partir de vértice i
void largura(VERTICE *g, int i)
{
    zerarFlags(g);
    FILA *f = (FILA *)malloc(sizeof(FILA));
    inicializaFila(f);

    entrarFila(f, i);
    g[i].flag = 1;

    while (!filaVazia(f))
    {
        i = sairFila(f);
        g[i].flag = 2;

        NO *p = g[i].inicio;
        while (p)
        {
            if (g[p->adj].flag == 0)
            {
                entrarFila(f, p->adj);
                g[p->adj].flag = 1;
            }
            p = p->prox;
        }
    }

    free(f);
}

// Busca o menor caminho (em arestas) de origem até destino via BFS
void buscaMenorCaminho(VERTICE *g, int origem, int destino)
{
    zerarFlags(g);
    for (int j = 1; j <= V; j++)
    {
        g[j].via = -1;
    }

    g[origem].via = 0;
    g[origem].flag = 1;

    FILA *f = (FILA *)malloc(sizeof(FILA));
    inicializaFila(f);
    entrarFila(f, origem);

    while (!filaVazia(f))
    {
        int atual = sairFila(f);
        g[atual].flag = 2;

        NO *p = g[atual].inicio;
        while (p)
        {
            if (g[p->adj].flag == 0)
            {
                g[p->adj].flag = 1;
                entrarFila(f, p->adj);
                g[p->adj].via = atual;
            }
            p = p->prox;
        }
    }

    // Impressão do caminho reconstruído
    printf("\nMenor caminho de %d até %d:\n", origem, destino);

    if (g[destino].via == -1 && origem != destino)
    {
        printf("Não existe caminho de %d até %d.\n", origem, destino);
    }
    else
    {
        int caminho[V + 1];
        int tam = 0;
        int atual = destino;

        while (atual != 0)
        {
            caminho[tam++] = atual;
            if (atual == origem)
                break;
            atual = g[atual].via;
        }

        if (caminho[tam - 1] != origem)
        {
            printf("Não existe caminho de %d até %d.\n", origem, destino);
        }
        else
        {
            for (int i = tam - 1; i >= 0; i--)
            {
                printf("%d", caminho[i]);
                if (i > 0)
                    printf(" -> ");
            }
            printf("\n");
        }
    }

    free(f);
}

// Exibe o grafo em formato de listas de adjacência
void exibirGrafo(VERTICE *g)
{
    for (int i = 1; i <= V; i++)
    {
        printf("%d: ", i);
        NO *p = g[i].inicio;
        while (p)
        {
            printf("%d -> ", p->adj);
            p = p->prox;
        }
        printf("NULL\n");
    }
}

// ----------------------------
// Exercícios básicos em grafos: Lista 1
// ----------------------------

// 1. Escreva um algoritmo para contar a quantidade de laços em um grafo.

int quantidadeDeLaços(VERTICE *g)
{
    int lacos = 0;
    for (int i = 1; i <= V; i++)
    {
        NO *p = g[i].inicio;
        while (p)
        {
            if (p->adj == i)
            {
                lacos++;
            }
            p = p->prox;
        }
    }
    return lacos;
}

// 2. Variação: remover todos os laços encontrados.

int removeLacosEncontrados(VERTICE *g)
{
    int lacosRemovidos = 0;
    for (int i = 1; i <= V; i++)
    {
        NO *p = g[i].inicio;
        NO *ant = NULL;

        while (p)
        {
            if (p->adj == i)
            {
                if (ant)
                {
                    ant->prox = p->prox;
                }
                else
                {
                    g[i].inicio = p->prox;
                }
                free(p);
                p = ant ? ant->prox : g[i].inicio;
                lacosRemovidos++;
            }
            else
            {
                ant = p;
                p = p->prox;
            }
            p = p->prox;
        }
    }
    return lacosRemovidos;
}

// 3. Escreva um algoritmo para destruir as arestas de um grafo, tornando-o vazio.

int destroiArestas(VERTICE *g)
{
    int arestasDestruidas = 0;
    for (int i = 0; i <= V; i++)
    {
        NO *p = g[i].inicio;
        while (p)
        {
            NO *temp = p;
            p = p->prox;
            free(temp);
            arestasDestruidas++;
        }
    }
}

// 4. Seja um grafo g dirigido. Escreva um algoritmo para
// retornar o grafo transposto de g.

void grafoTransposto(VERTICE *g, VERTICE *h)
{
    for (int i = 0; i <= V; i++)
    {
        NO *p = g[i].inicio;
        while (p)
        {
            inserirAresta(h, p->adj, i);
            p = p->prox;
        }
    }
}

// 5. Escreva um algoritmo que dado um grafo m representado em matriz,
// retorne o mesmo grafo em listas de adjacências.

void matrizParaLista(VERTICE *g, int matriz[V][V])
{
    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            if (matriz[i][j] != 0)
            {
                inserirArestaComPeso(g, i, j, matriz[i][j]);
            }
        }
    }
}

// 6. Uma árvore enraizada é um grafo acíclico, conexo e dirigido, com um único vértice fonte de onde
// todas as arestas partem. Escreva um algoritmo que, dado um grafo g, verifique se é uma árvore
// enraizada ou não, retornando true/false conforme o caso.

bool ehArvoreEnraizada(VERTICE *g)
{
    int raiz = 0;
    int numVertices = 0;
    for (int i = 1; i <= V; i++)
    {
        if (grauEntrada(g, i) == 0)
        {
            raiz = i;
            numVertices++;
        }
    }
    if (numVertices != 1)
    {
        return false;
    }
    zerarFlags(g);
    profundidade(g, raiz);
    for (int i = 1; i <= V; i++)
    {
        if (g[i].flag != 2)
        {
            return false;
        }
    }
    return true;
}

// 7. Seja um grafo g não-dirigido ponderado (com um peso inteiro associado a cada aresta). Escreva um
// algoritmo que, dado g e um custo mínimo int c, retorne uma cópia de g contendo apenas as arestas
// de custo maior do que c.

void grafoComCustoMaior(VERTICE *g, VERTICE *h, int c)
{
    for (int i = 1; i <= V; i++)
    {
        NO *p = g[i].inicio;
        while (p)
        {
            if (p->peso > c)
            {
                inserirArestaComPeso(h, i, p->adj, p->peso);
            }
        }
    }
}

// 8. Sejam dois grafos g1 e g2 contendo exatamente os mesmos vértices. Verifique se g2 é um subgrafo
// de g1, retornando true/false conforme o caso. Para tornar o problema mais interessante, considere
// que um grafo é representado em listas e outro em matriz.

bool ehSubgrafo(VERTICE *g1, int matriz[V][V], VERTICE *g2)
{
    matrizParaLista(g2, matriz);
    for (int i = 1; i <= V; i++)
    {
        NO *p = g2[i].inicio;
        NO *ant = NULL;
        while (p)
        {
            if (!arestaExiste(g1, i, p->adj, &ant))
            {
                return false; // aresta não existe em g1
            }
        }
    }
}

// 9. Dados dois grafos g1 e g2, escreva um algoritmo que retorne um grafo g3 cujas arestas estejam
// presentes em g1 mas não em g2.

void grafoExclusivoDeg1(VERTICE *g1, VERTICE *g2, VERTICE *g3)
{
    for (int i = 1; i <= V; i++)
    {
        NO *p = g1[i].inicio;
        NO *ant = NULL;
        while (p)
        {
            if (!arestaExiste(g2, i, p->adj, &ant))
            {
                inserirArestaComPeso(g3, i, p->adj, p->peso);
            }
        }
    }
}

// 10. Considere um grafo dirigido em lista de adjacências representando uma rede de troca de emails,
// onde cada vértice representa um usuário, e cada aresta representa um email enviado. Cada aresta
// possui um campo int id que representa o conteúdo da mensagem (ou seja, o campo id faz parte da
// definição do nó das listas de adjacências). Problema: circula pela rede uma mensagem x do tipo
// spam. Escreva um algoritmo para exibir os usuários suspeitos de iniciar a propagação de x. Um
// usuário é considerado suspeito se ele próprio não recebeu a mensagem x nenhuma vez.

typedef struct s2
{
    struct s2 *prox;
    int adj;
    int id;
} EMAIL;

// Estrutura de vértice: lista de adjacência + flags
typedef struct
{
    EMAIL *inicio; // início da lista de adjacência
    int flag;      // usado para marcações de busca
} USUARIO;

int usuariosSuspeitos(USUARIO *g, int x, int **suspeitos)
{
    int cont = 0;
    bool *recebeuSpam = (bool *)malloc(sizeof(bool) * (V + 1));
    for (int i = 1; i <= V; i++)
    {
        recebeuSpam[i] = false;
    }
    for (int i = 1; i <= V; i++)
    {
        EMAIL *p = g[i].inicio;
        while (p)
        {
            if (p->id == x)
            {
                recebeuSpam[p->adj] = true;
            }
            p = p->prox;
        }
    }
    printf("Usuários suspeitos de iniciar a propagação de %d:\n", x);
    for (int i = 1; i <= V; i++)
    {
        if (!recebeuSpam[i])
        {
            suspeitos[cont] = (int *)malloc(sizeof(int));
            *suspeitos[cont] = i;
            cont++;
            printf("%d ", i);
        }
    }
    return cont;
}

// 11. Considere um grafo dirigido em lista de adjacências representando uma rede de chamadas
// telefônicas entre diversas unidades de uma empresa, onde cada vértice representa uma unidade, e
// cada aresta representa uma chamada efetuada. As unidades podem estar em diferentes países,
// identificados por um campo int país definido no respectivo vértice. Problema: a conta de telefone
// global da empresa está muito alta. Escreva um algoritmo que identifique a unidade que efetua
// chamadas para o maior número de países. Havendo empate, retorne qualquer resposta possível.

typedef struct s3
{
    struct s3 *prox;
    int adj;
} CHAMADA;

// Estrutura de vértice: lista de adjacência + flags
typedef struct
{
    CHAMADA *inicio; // início da lista de adjacência
    int pais;        // país da unidade
    int flag;        // usado para marcações de busca
} UNIDADE;

int unidadeMaiorNumeroDePaises(UNIDADE *g)
{
    int unidadeMaxima = -1;
    int maior = 0;
    for (int i = 1; i <= V; i++)
    {
        bool paisVisitado[V + 1] = {false};
        int temp = 0;
        CHAMADA *p = g[i].inicio;

        while (p)
        {
            int paisAdj = g[p->adj].pais;
            if (paisAdj != g[i].pais && !paisVisitado[paisAdj])
            {
                paisVisitado[paisAdj] = true;
                temp++;
            }
            p = p->prox;
        }
        if (temp > maior)
        {
            maior = temp;
            unidadeMaxima = i;
        }
    }
    return unidadeMaxima;
}

// 12. Seja um grafo g não-dirigido. Escreva uma função para detectar ciclos em g, retornando true/false.

bool detectarCicloProfundidade(VERTICE *g, int i)
{
    g[i].flag = 1;
    NO *p = g[i].inicio;

    while (p)
    {
        if (g[p->adj].flag == 0)
        {
            if (detectarCicloProfundidade(g, p->adj))
            {
                return true; // ciclo encontrado
            }
            else if (g[p->adj].flag == 1)
            {
                return true; // ciclo encontrado
            }
        }
        p = p->prox;
    }
    g[i].flag = 2; // marca como visitado
    return false;  // nenhum ciclo encontrado
}

bool detectarCicloLargura(VERTICE *g, int i)
{
    FILA *f = (FILA *)malloc(sizeof(FILA));
    inicializaFila(f);
    entrarFila(f, i);
    g[i].flag = 1;

    while (f)
    {
        i = sairFila(f);
        g[i].flag = 2;
        NO *p = g[i].inicio;
        while (p)
        {
            if (g[p->adj].flag == 0)
            {
                entrarFila(f, p->adj);
                g[p->adj].flag = 1;
            }
            else if (g[p->adj].flag == 1)
            {
                free(f);
                return true; // ciclo encontrado
            }
            p = p->prox;
        }
    }
    free(f);
    return false; // nenhum ciclo encontrado
}

// 13. Variação 1: remover as arestas que provocam ciclo.

bool detectarCicloProfundidadeV1(VERTICE *g, int i)
{
    g[i].flag = 1;
    NO *p = g[i].inicio;

    while (p)
    {
        if (g[p->adj].flag == 0)
        {
            if (detectarCicloProfundidade(g, p->adj))
            {
                return true; // ciclo encontrado
            }
            else if (g[p->adj].flag == 1)
            {
                excluirAresta(g, i, p->adj); // remove a aresta que provoca ciclo
                g[p->adj].flag = 2;          // marca como visitado
                return true;                 // ciclo encontrado
            }
        }
        p = p->prox;
    }
    g[i].flag = 2; // marca como visitado
    return false;  // nenhum ciclo encontrado
}

bool detectarCicloLarguraV1(VERTICE *g, int i)
{
    FILA *f = (FILA *)malloc(sizeof(FILA));
    inicializaFila(f);
    entrarFila(f, i);
    g[i].flag = 1;

    while (f)
    {
        i = sairFila(f);
        g[i].flag = 2;
        NO *p = g[i].inicio;
        while (p)
        {
            if (g[p->adj].flag == 0)
            {
                entrarFila(f, p->adj);
                g[p->adj].flag = 1;
            }
            else if (g[p->adj].flag == 1)
            {
                excluirAresta(g, i, p->adj); // remove a aresta que provoca ciclo
                g[p->adj].flag = 2;          // marca como visitado
                free(f);
                return true; // ciclo encontrado
            }
            p = p->prox;
        }
    }
    free(f);
    return false; // nenhum ciclo encontrado
}

// 14. Variação 2: retornar o comprimento (i.e., a quantidade de arestas) do maior ciclo encontrado.

void detectarCicloProfundidadeV2(VERTICE *g, int i, int *profundidade, int nivel, int *maiorCiclo)
{
    profundidade[i] = nivel; // Marca a profundidade do vértice na DFS
    g[i].flag = 1;
    NO *p = g[i].inicio;

    while (p)
    {
        if (g[p->adj].flag == 0)
        { // Vértice ainda não visitado
            detectarCicloProfundidadeV2(g, p->adj, profundidade, nivel + 1, maiorCiclo);
        }
        else if (g[p->adj].flag == 1)
        { // Encontrou um ciclo
            int tamanhoCiclo = nivel - profundidade[p->adj] + 1;
            if (tamanhoCiclo > *maiorCiclo)
            {
                *maiorCiclo = tamanhoCiclo;
            }
        }
        p = p->prox;
    }

    g[i].flag = 2; // Marca como processado
}

int encontrarMaiorCiclo(VERTICE *g, int numVertices)
{
    int maiorCiclo = 0;
    int *profundidade = (int *)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++)
    {
        memset(profundidade, -1, numVertices * sizeof(int)); // Inicializa profundidade como -1
        for (int j = 0; j < numVertices; j++)
        {
            g[j].flag = 0; // Reseta flags para cada nova DFS
        }
        detectarCicloProfundidadeV2(g, i, profundidade, 0, &maiorCiclo);
    }

    free(profundidade);
    return maiorCiclo;
}

// 15. Seja um grafo g não-conexo e não-dirigido. Escreva uma função para contar a quantidade de
// grupos disjuntos de vértices mutuamente alcançáveis em g.

int contarGrupos(VERTICE *g)
{
    int grupos = 0;
    for (int i = 1; i <= V; i++)
    {
        if (g[i].flag == 0)
        {
            grupos++;
            profundidade(g, i); // Marca todos os vértices do grupo
        }
    }
}

// 16. Variação: ao invés de contar os grupos, retornar uma lista ligada contendo os vértices do maior
// grupo identificado. Se dois ou mais grupos possuem a mesma quantidade de vértices, retornar a
// lista de vértices de qualquer um.

typedef struct No
{
    int valor;
    struct No *prox;
} No;

// Estrutura da lista ligada circular
typedef struct
{
    No *cabeca;
    int tamanho;
} Lista;

void profundidadeContaTamanho(VERTICE *g, int i, int *tamanho)
{
    g[i].flag = 1;
    *tamanho += 1; // Incrementa o tamanho do grupo
    NO *p = g[i].inicio;

    while (p)
    {
        if (g[p->adj].flag == 0)
        {
            profundidadeContaTamanho(g, p->adj, tamanho); // Marca todos os vértices do grupo
        }
        p = p->prox;
    }
    g[i].flag = 2;
}

void criaListaMaiorGrupo (VERTICE *g, int i, Lista *listaMaiorGrupo) {
    zerarFlags(g);
    profundidade(g, i); // Marca todos os vértices do grupo

    for (int j = 1; j <= V; j++)
    {
        if (g[j].flag != 0)
        { // Vértice pertence ao grupo
            No *novo = (No *)malloc(sizeof(No));
            novo->valor = j;
            novo->prox = listaMaiorGrupo->cabeca;
            listaMaiorGrupo->cabeca = novo;
            listaMaiorGrupo->tamanho++;
        }
    }
}

void listaMaiorGrupo(VERTICE *g, Lista *listaMaiorGrupo, int *maiorGrupo) {

    int grupos = 0;
    int *tamanhoGrupos = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++)
    {
        tamanhoGrupos[i] = 0;
    }
    for (int i = 1; i <= V; i++)
    {
        if (g[i].flag == 0)
        {
            grupos++;
            profundidadeContaTamanho(g, i, &tamanhoGrupos[i]); // Marca todos os vértices do grupo
        }
    }
    int maiorTamanho = 0;
    int fonteMaiorTamanho = 0;
    for (int i = 1; i <= V; i++) {
        if (tamanhoGrupos[i] > maiorTamanho) {
            maiorTamanho = tamanhoGrupos[i];
            fonteMaiorTamanho = i;
        }
    }
    printf("Tamanho do maior grupo: %d\n", maiorTamanho);
    printf("Vértices do maior grupo: ");
    criaListaMaiorGrupo(g, fonteMaiorTamanho, listaMaiorGrupo);
    No *p = listaMaiorGrupo->cabeca;
    while (p != NULL) {
        printf("%d ", p->valor);
        p = p->prox;
    }
    printf("\n");
    free(tamanhoGrupos);
    listaMaiorGrupo->cabeca = NULL; // Limpa a lista ligada
    listaMaiorGrupo->tamanho = 0; // Reseta o tamanho da lista
    free(listaMaiorGrupo); // Libera a memória da lista ligada
}

// 17. Seja um grafo g e dois vértices a e b. Verifique se há um caminho qualquer entre a e b retornando
// true/false conforme o caso.

// 18. Variação 1: contar quantos vértices há no caminho de a até b.

// 19. Variação 2: retornar a lista dos vértices que compõe o caminho de a até b.

// 20. Um grafo não dirigido é completo se todos seus vértices são adjacentes, ou seja, existe uma aresta
// conectando cada par de vértices de um grafo. Escreva um algoritmo que, dado um grafo simples g,
// verifique se g é completo, retornando true/false conforme o caso.

// 21. Seja G = (V;A) um grafo simples e Ḡ = (V; V2-A) seu complemento, onde V2 é o conjunto de todos
// os pares de vértices em V . Escreva um método que, dado um grafo simples G, retorne seu
// complemento Ḡ.

// 22. Seja um grafo g representando salas de aula (vértices) e suas ligações (arestas). Cada sala possui
// uma ocupação representada por um inteiro. Escreva um algoritmo que, a partir da sala atual i,
// encontre a sala vazia mais próxima, retornando o número do vértice correspondente. Havendo
// mais de uma sala que atenda estas condições, retorne a primeira que encontrar.

// 23. Variação: havendo empate, retorne uma lista ligada contendo todas as salas vazias mais próximas.

// 24. Para todos os vértices de um grafo, calcular o tamanho do caminho mais curto a partir de um
// vértice inicial i.

// 25. Seja um grafo não-dirigido representando uma rede social. Os vértices são os usuários e as arestas
// indicam relações (e.g., de amizade) entre pares de usuários. Dado um usuário i, escreva um
// algoritmo para exibir todos os usuários relacionados a i com até d graus de distância (medida em
// quantidade de arestas). Os amigos imediatos estão no grau 1, os amigos dos amigos no grau 2, e
// assim por diante.

// 26. Seja um grafo dirigido representando trocas de email entre usuários. Os vértices são usuários e as
// arestas orientadas indicam que houve envio de mensagens na respectiva direção, incluindo um
// contador do número de mensagens enviadas. Escreva um algoritmo que, dado um usuário atual i,
// retorne uma lista ligada contendo todos os usuários que estão diretamente relacionados com i, e
// que enviaram ou receberam pelo menos k mensagens de/para i. A constante k é fornecida como
// parâmetro de entrada para a função.

// 27. Seja um grafo representando uma malha aérea. Vértices são cidades e arestas são voos. Escreva um
// algoritmo que, dada uma cidade origem a, um destino b e uma companhia aérea c, encontre o
// trajeto com menor número de conexões de a até b voando apenas pela companhia c. A resposta
// deve ser fornecida na forma de uma lista ligada de vértices de a até b.

// 28. Seja um grafo representando as ruas de uma cidade ligando pontos de interesse identificados por
// um código numérico inteiro (1=hotéis, 2=restaurante etc.) Escreva um algoritmo que, dado um
// código de ponto de interesse x e uma posição atual i, retorne o vértice contendo o x mais próximo.
// Havendo empate, retorne o primeiro que encontrar.

// 29. Variação: considere ainda que existe um local n que não deve ser visitado (por exemplo, n pode ser
// uma área da cidade que foi interditada por alguma razão). Modifique o algoritmo de acordo.

// -----------------------------
// Função principal de testes
// -----------------------------
int main()
{
    VERTICE g[V + 1];
    inicializar(g);

    // ----------------------------
    // Teste 1: Grau, remoção, DFS
    // ----------------------------
    /*
    // Criação de um grafo com ciclo: 1 → 2, 1 → 3, 2 → 4, 3 → 4, 4 → 5, 5 → 1
    inserirAresta(g, 1, 2);
    inserirAresta(g, 1, 3);
    inserirAresta(g, 2, 4);
    inserirAresta(g, 3, 4);
    inserirAresta(g, 4, 5);
    inserirAresta(g, 5, 1);

    printf("Representacao do Grafo:\n");
    exibirGrafo(g);

    printf("\nTestando grau de saída e entrada:\n");
    for (int i = 1; i <= V; i++) {
        printf("Vértice %d - Grau de saída: %d, Grau de entrada: %d\n", i, grauSaida(g, i), grauEntrada(g, i));
    }

    printf("\nTestando remoção de aresta 1 -> 2:\n");
    excluirAresta(g, 1, 2);
    exibirGrafo(g);

    printf("\nTestando busca em profundidade a partir do vértice 1:\n");
    zerarFlags(g);
    profundidade(g, 1);
    for (int i = 1; i <= V; i++) {
        printf("Vértice %d - Flag: %d\n", i, g[i].flag);
    }
    */

    // ----------------------------
    // Teste 2: BFS e menor caminho
    // ----------------------------

    inserirAresta(g, 1, 2);
    inserirAresta(g, 1, 3);
    inserirAresta(g, 2, 4);
    inserirAresta(g, 3, 4);
    inserirAresta(g, 4, 5);

    printf("Grafo:\n");
    exibirGrafo(g);

    printf("\nBusca em Largura a partir do vértice 1:\n");
    largura(g, 1);
    for (int i = 1; i <= V; i++)
    {
        printf("Vértice %d: flag = %d\n", i, g[i].flag);
    }

    printf("\nBusca do Menor Caminho (via BFS) de 1 até 5:\n");
    buscaMenorCaminho(g, 1, 5);
    for (int i = 1; i <= V; i++)
    {
        printf("Vértice %d veio de %d\n", i, g[i].via);
    }

    printf("\nTESTE EXERCÍCIO 14: \n");
    VERTICE g1[V + 1];
    inicializar(g1);

    inserirAresta(g1, 1, 2);
    inserirAresta(g1, 1, 7);
    inserirAresta(g1, 1, 10);
    inserirAresta(g1, 2, 3);
    inserirAresta(g1, 3, 4);
    inserirAresta(g1, 4, 5);
    inserirAresta(g1, 5, 6);
    inserirAresta(g1, 6, 2);
    inserirAresta(g1, 7, 9);
    inserirAresta(g1, 9, 8);
    inserirAresta(g1, 8, 7);
    inserirAresta(g1, 10, 11);

    printf("Comprimento do maior ciclo encontrado: %d\n", encontrarMaiorCiclo(g1, 11));

    return 0;
}