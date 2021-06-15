#include <stdio.h>
#include <stdlib.h>

typedef struct no_t{
    int rotulo;
    struct no_t *prox;
}no_t;

typedef struct grafo_t{
    int v;
    int e;
    no_t **lista_adj;
}grafo_t;

grafo_t* cria_grafo(int v, int e){
    int i;
    grafo_t *grafo = malloc(sizeof(grafo_t));
    grafo->v = v;
    grafo->e = e;
    grafo->lista_adj = malloc(sizeof(no_t*)*v);

    for(i = 0; i < v; i++){
        grafo->lista_adj[i] = NULL;
    }

    return grafo;    
}

void adiciona_aresta(grafo_t *grafo, int v1, int v2){
    no_t *aux;

    // Vertice v1 é vizinho do v2: adicona v1 na lista de adjacencia de v2
    aux = malloc(sizeof(no_t));
    aux->rotulo = v1;
    aux->prox = grafo->lista_adj[v2];
    grafo->lista_adj[v2] = aux;

    // Vertice v2 é vizinho do v1: adicona v2 na lista de adjacencia de v1
    aux = malloc(sizeof(no_t));
    aux->rotulo = v2;
    aux->prox = grafo->lista_adj[v1];
    grafo->lista_adj[v1] = aux;
}

// Função auxiliar: realiza de fato a busca em profundidade
void busca_profundidade(grafo_t *grafo, int inicio, int *visitado){
    no_t *vizinho = grafo->lista_adj[inicio];
    visitado[inicio] = 1;

    while(vizinho){
        if(!visitado[vizinho->rotulo]){
            busca_profundidade(grafo, vizinho->rotulo, visitado);
        }
        vizinho = vizinho->prox;
    }
}

// Função principal: faz a interface com o usuario (Opicional)
void busca_profundidade_grafo(grafo_t *grafo, int inicio, int *visitado){
    int i;

    for(i = 0; i < grafo->v; i++){
        visitado[i] = 0;
    }
    busca_profundidade(grafo, inicio, visitado);
} 
