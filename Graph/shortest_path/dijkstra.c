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

typedef struct heap_t{
    int capacity;
    int occupation;
    int *queue;
    int *priority;
}heap_t;

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

heap_t* createHeap(int capacity){

    int i;
    heap_t *heap = (heap_t*)malloc(sizeof(heap_t));
    heap->queue = (int*)malloc(sizeof(int)*capacity);
    heap->priority = (int*)malloc(sizeof(int)*capacity);
    heap->capacity = capacity;
    heap->occupation = 0;
    
    for(i = 0; i < capacity; i++){
        heap->queue[i] = -1;
        heap->priority[i] = INFINITE;
    }

    return heap;
}

void killHeap(heap_t *heap){
    free(heap->queue);
    free(heap->priority);
    free(heap);
}

void heapifyUp (heap_t *heap, int child){

    int parent = (child-1)/2;
    int vertexKey;

    while((child > 0) && (heap->priority[heap->queue[parent]] >= heap->priority[heap->queue[child]])){

        vertexKey = heap->queue[child];
        heap->queue[child] = heap->queue[parent];
        heap->queue[parent] = vertexKey;

        child = parent;
        parent = (parent-1)/2;      
    }
}

void heapifyDown (heap_t *heap, int parent){

    int child = 2*parent + 1;
    int vertexKey;

    while(child < heap->occupation){

        if(child < heap->occupation-1 && heap->priority[heap->queue[child]] > heap->priority[heap->queue[child+1]])
            child++;

        if(heap->priority[heap->queue[parent]] <= heap->priority[heap->queue[child]])
            break;

        vertexKey = heap->queue[parent];
        heap->queue[parent] = heap->queue[child];
        heap->queue[child] = vertexKey;

        parent = child;
        child = 2*parent + 1;
    }
}

int addVertex(heap_t *heap, int vertexKey){

    if (heap->occupation == heap->capacity)
        return 0;
    
    heap->priority[vertexKey] = INFINITE;
    heap->queue[heap->occupation] = vertexKey;
    heapifyUp(heap, heap->occupation);
    heap->occupation++;

    return 1;
}

int pullVertex(heap_t *heap){

    if (heap->occupation == 0)
        return -1;

    int vertexKey = heap->queue[0];
    heap->occupation--;
    heap->queue[0] = heap->queue[heap->occupation];
    heapifyDown(heap, 0);

    return vertexKey;
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

int getWeight(graph_t *graph, int vertex1, int vertex2){
    
    vertex_t *vertex = graph->adjacencyList[vertex1];
    
    while(vertex){
        if(vertex->vertexKey == vertex2)
            return vertex->weight;
        vertex = vertex->next;
    }

    return INFINITE;
}

int getHeapId(heap_t *heap, int key){
    
    int i;
    
    for(i = 0; i < heap->occupation; i++){
        if(heap->queue[i] == key)
            return i;
    }
    return -1;
}

void changeHeap(heap_t *heap, int vertexKey, int priority){
    heap->priority[vertexKey] = priority;
    heapifyUp(heap, getHeapId(heap, vertexKey));

}

int* dijkstra(graph_t *graph, int startVertex){
    
    heap_t *heap = createHeap(graph->vertexAmount);
    vertex_t *neighbors;
    int i, weight, vertex, visited[graph->vertexAmount];
    int *pi = (int*)malloc(sizeof(int)*graph->vertexAmount);

    for(i = 0; i < graph->vertexAmount; i++){
        visited[i] = 0;
        pi[i] = -1;
        addVertex(heap, i);
    }

    changeHeap(heap, startVertex, 0);

    while(heap->occupation > 0 && heap->priority[heap->queue[0]] != INFINITE){
        vertex = pullVertex(heap);
        visited[vertex] = 1;
        neighbors = graph->adjacencyList[vertex];

        while(neighbors){
            weight = getWeight(graph, vertex, neighbors->vertexKey);
            if((!visited[neighbors->vertexKey]) && (heap->priority[vertex] + weight < heap->priority[neighbors->vertexKey])){
                changeHeap(heap, neighbors->vertexKey, heap->priority[vertex] + weight);
                pi[neighbors->vertexKey] = vertex;
            }
            neighbors = neighbors->next;
        }
    }

    return pi;
}

int main(int argc, char const *argv[]){
    
    graph_t *graph = createGraph(9, 14); 
    int i, *pi;

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

    pi = dijkstra(graph, 0);


    for(i = 0; i < graph->vertexAmount; i++){
        
        if(pi[i] < 0){
            printf("%d <- NULL\n", i);
        }else{
            printf("%d <- %d\n", i, pi[i]);
        }
    }
}
