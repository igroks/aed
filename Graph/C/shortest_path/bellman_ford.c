#include <stdio.h>
#include <stdlib.h>

#define INFINITE 1000

typedef struct vertex_t{
    int vertexKey;
    int weight;
    struct vertex_t *next;
}vertex_t;

typedef struct graph_t{
    int vertexAmount;
    int edgesAmount;
    vertex_t **adjacencyList;
}graph_t;

typedef struct edge_t{
    int weight;
    int startNode;
    int endNode;
}edge_t;

graph_t* createGraph(int vertexAmount, int edgesAmount){

    int i;
    graph_t *graph = (graph_t*)malloc(sizeof(graph_t));
    graph->adjacencyList = (vertex_t**)malloc(sizeof(vertex_t*)*vertexAmount);
    graph->vertexAmount = vertexAmount;
    graph->edgesAmount = edgesAmount;
    
    for(i = 0; i < vertexAmount; i++){
        graph->adjacencyList[i] = NULL;
    }

    return graph;    
}

void addEdge(graph_t *graph, int vertex1, int vertex2, int weight){

    vertex_t *vertex;

    // Vertice 1 é vizinho do vertice 2: adicona vertice 1 na lista de adjacencia do vertice 2
    vertex = (vertex_t*)malloc(sizeof(vertex_t));
    vertex->vertexKey = vertex1;
    vertex->weight = weight;
    vertex->next = graph->adjacencyList[vertex2];
    graph->adjacencyList[vertex2] = vertex;

    // Vertice 2 é vizinho do vertice 1: adicona vertice 2 na lista de adjacencia do vertice 1
    vertex = (vertex_t*)malloc(sizeof(vertex_t));
    vertex->vertexKey = vertex2;
    vertex->weight = weight;
    vertex->next = graph->adjacencyList[vertex1];
    graph->adjacencyList[vertex1] = vertex;
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
    vertex_t *vertex;
    edge_t *edge;
    int i, j = 0;

    for(i = 0; i < graph->edgesAmount; i++){
        edges[i] = NULL;
    }

    for(i = 0; i < graph->vertexAmount; i++){
        vertex = graph->adjacencyList[i];
        while(vertex){
            edge = (edge_t*)malloc(sizeof(edge_t));
            edge->startNode = i;
            edge->endNode = vertex->vertexKey;
            edge->weight = vertex->weight;
            if(!hasEdge(edges, graph->edgesAmount, edge)){
                edges[j++] = edge;
            }
            vertex = vertex->next;
        }
    }

    return edges;
}

int* bellmanFord(graph_t *graph, int startVertex){

    int *pi = (int*)malloc(sizeof(int)*graph->vertexAmount);
    int key[graph->vertexAmount], i, j;
    edge_t **edges = getEdges(graph);

    for(i = 0; i < graph->vertexAmount; i++){
        key[i] = INFINITE;
        pi[i] = -1;
    }
    key[startVertex] = 0;

    for(i = 1; i < graph->vertexAmount; i++){
        for(j = 0; j < graph->edgesAmount; j++){
            if(key[edges[j]->startNode] != INFINITE && key[edges[j]->startNode] + edges[j]->weight < key[edges[j]->endNode]){

                key[edges[j]->endNode] = key[edges[j]->startNode] + edges[j]->weight;
                pi[edges[j]->endNode] = edges[j]->startNode;
            }
        }
    }

    for(i = 0; i < graph->edgesAmount; i++){
        if(key[edges[i]->startNode] != INFINITE && key[edges[i]->startNode] + edges[i]->weight < key[edges[i]->endNode]){
            printf("Graph contains negative weight cycle");
            return NULL;
        }
    }

    return pi;
}

int main(int argc, char const *argv[]){
    
    graph_t *graph = createGraph(5, 7); 
    int i, *pi;

    addEdge(graph, 0, 1, -1);
    addEdge(graph, 0, 2, 4);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 1);
    addEdge(graph, 1, 4, 2);
    addEdge(graph, 3, 2, 5);
    addEdge(graph, 4, 3, -3);

    pi = bellmanFord(graph, 0);

    if(pi){
        for(i = 0; i < graph->vertexAmount; i++){
        
            if(pi[i] < 0){
                printf("%d <- NULL\n", i);
            }else{
                printf("%d <- %d\n", i, pi[i]);
            }
        }
    }
}
