#include <stdio.h>
#include <stdlib.h>

typedef struct node_t{
    int key;
    int weight;
    struct node_t *next;
}node_t;

typedef struct graph_t{
    int vertexAmount;
    int edgesAmount;
    node_t **listAdj;
}graph_t;

typedef struct edge_t{
    int weight;
    int startNode;
    int endNode;
}edge_t;

typedef struct set_t{
    int representative;
    int length;
    node_t *first;
    node_t *last;
}set_t;

graph_t* createGraph(int vertexAmount, int edgesAmount){

    int i;
    graph_t *graph = (graph_t*)malloc(sizeof(graph_t));
    graph->listAdj = (node_t**)malloc(sizeof(node_t*)*vertexAmount);
    graph->vertexAmount = vertexAmount;
    graph->edgesAmount = edgesAmount;
    
    for(i = 0; i < vertexAmount; i++){
        graph->listAdj[i] = NULL;
    }

    return graph;    
}

void addEdge(graph_t *graph, int vertex1, int vertex2, int weight){

    node_t *node;

    // Vertice 1 é vizinho do vertice 2: adicona vertice 1 na lista de adjacencia do vertice 2
    node = (node_t*)malloc(sizeof(node_t));
    node->key = vertex1;
    node->weight = weight;
    node->next = graph->listAdj[vertex2];
    graph->listAdj[vertex2] = node;

    // Vertice 2 é vizinho do vertice 1: adicona vertice 2 na lista de adjacencia do vertice 1
    node = (node_t*)malloc(sizeof(node_t));
    node->key = vertex2;
    node->weight = weight;
    node->next = graph->listAdj[vertex1];
    graph->listAdj[vertex1] = node;
}

int hasEdge(edge_t **edges, int length, edge_t *edge){

    int i;
    for(i = 0; i < length; i++){
        if(edges[i] && edges[i]->endNode == edge->startNode && edges[i]->startNode == edge->endNode){
            return 1;
        }
    }

    return 0;
}

edge_t** getEdges(graph_t *graph){

    edge_t **edges = (edge_t**)malloc(sizeof(edge_t*)*graph->edgesAmount);
    node_t *node;
    edge_t *edge;
    int i, j = 0;

    for(i = 0; i < graph->edgesAmount; i++){
        edges[i] = NULL;
    }

    for(i = 0; i < graph->vertexAmount; i++){
        node = graph->listAdj[i];
        while(node){
            edge = (edge_t*)malloc(sizeof(edge_t));
            edge->startNode = i;
            edge->endNode = node->key;
            edge->weight = node->weight;
            if(!hasEdge(edges, graph->edgesAmount, edge)){
                edges[j++] = edge;
            }
            node = node->next;
        }
    }

    return edges;
}

set_t* makeSet(int key){

    node_t *node = (node_t*)malloc(sizeof(node_t));
    set_t *set = (set_t*)malloc(sizeof(set_t));

    node->key = key;
    node->weight = 0;
    node->next = NULL;
    set->representative = node->key;
    set->length = 1;
    set->first = node;
    set->last = node;

    return set;
}

int findSet(int vertex, set_t **sets){
    return sets[vertex]->representative;
}

void setUnion(int vertex1, int vertex2, set_t **sets){

    set_t *setX = sets[findSet(vertex1, sets)];
    set_t *setY = sets[findSet(vertex2, sets)];
    node_t *node;

    if(setX->length < setY->length){
        node = setX->first;
        while(node){
            sets[node->key]->representative = setY->representative;
            node = node->next;
        }
        setY->length += setX->length;
        setX->length = 0;
        setY->last->next = setX->first;
        setY->last = setX->last;
        setX->first = NULL; 
        setX->last = NULL;
        
    }else{
        node = setY->first;
        while(node){
            sets[node->key]->representative = setX->representative;
            node = node->next;
        }
        setX->length += setY->length;
        setY->length = 0;
        setX->last->next = setY->first;
        setX->last = setY->last;
        setY->first = NULL; 
        setY->last = NULL;
    }
}

void insertionSort(edge_t **edges, int length){
    
    int i,j;
    edge_t *pivot;

    for(j = 1; j < length; j++){

        pivot = edges[j];
        i = j-1;

        while((i >= 0) && (edges[i]->weight > pivot->weight)){

            edges[i+1] = edges[i];
            i--;
        }
        edges[i+1] = pivot;
    }
}

int* kruskal(graph_t *graph){
    
    int i, j, *pi = (int*)malloc(sizeof(int)*graph->vertexAmount);
    edge_t **edges = getEdges(graph);
    set_t **sets = (set_t**)malloc(sizeof(set_t*)*graph->vertexAmount);

    insertionSort(edges, graph->edgesAmount);

    for(i = 0; i < graph->vertexAmount; i++){
        sets[i] = makeSet(i);
        pi[i] = -1;
    }

    for(i = 0; i < graph->edgesAmount; i++){
        if(sets[edges[i]->startNode]->representative != sets[edges[i]->endNode]->representative){
            setUnion(edges[i]->startNode, edges[i]->endNode, sets);
            if(pi[edges[i]->endNode] != -1){
                pi[edges[i]->startNode] = edges[i]->endNode;
            }else{
                pi[edges[i]->endNode] = edges[i]->startNode;
            }
        }
    }

    free(sets);
    free(edges);

    return pi;
}

int main(int argc, char const *argv[]) {
    
    graph_t *graph = createGraph(9, 14);
    int *pi, i;

    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);

    pi = kruskal(graph);

   for(i = 0; i < graph->vertexAmount; i++){
        if(pi[i] < 0){
            printf("%d <- NULL\n", i);
        }else{
            printf("%d <- %d\n", i, pi[i]);
        }
    }
}
