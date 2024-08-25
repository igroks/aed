#include <stdio.h>
#include <stdlib.h>

#define INFINITE 1000

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

typedef struct heap_t{
    int capacity;
    int occupation;
    int *priorityQueue;
}heap_t;

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

heap_t* createHeap(int capacity){

    int i;
    heap_t *hp = (heap_t*)malloc(sizeof(heap_t));
    hp->capacity = capacity;
    hp->occupation = 0;
    hp->priorityQueue = (int*)malloc(sizeof(int)*capacity);

    for(i = 0; i < capacity; i++){
        hp->priorityQueue[i] = -1;
    }

    return hp;
}

void killHeap(heap_t *hp){
    free(hp->priorityQueue);
    free(hp);
}

void heapifyUp (heap_t *hp, int child){

    int parent = (child-1)/2;
    int node;

    while((child > 0) && (hp->priorityQueue[parent] >= hp->priorityQueue[child])){

        node = hp->priorityQueue[child];
        hp->priorityQueue[child] = hp->priorityQueue[parent];
        hp->priorityQueue[parent] = node;

        child = parent;
        parent = (parent-1)/2;      
    }
}

void heapifyDown (heap_t *hp, int parent){

    int child = 2*parent + 1;
    int node;

    while(child < hp->occupation){

        if(child < hp->occupation-1 && hp->priorityQueue[child] > hp->priorityQueue[child+1])
            child++;

        if(hp->priorityQueue[parent] <= hp->priorityQueue[child])
            break;

        node = hp->priorityQueue[parent];
        hp->priorityQueue[parent] = hp->priorityQueue[child];
        hp->priorityQueue[child] = node;

        parent = child;
        child = 2*parent + 1;
    }
}

int addNode(heap_t *hp, int key){

    if (hp->occupation == hp->capacity)
        return 0;
    
    hp->priorityQueue[hp->occupation] = key;
    heapifyUp(hp, hp->occupation);
    hp->occupation++;

    return 1;
}

int pullNode(heap_t *hp){

    if (hp->occupation == 0)
        return -1;

    int node = hp->priorityQueue[0];
    hp->occupation--;
    hp->priorityQueue[0] = hp->priorityQueue[hp->occupation];
    heapifyDown(hp, 0);

    return node;
}

int hasNode(heap_t *hp, int key){
    
    int node;
    int i;

    for(i = 0; i < hp->occupation; i++){
        node = hp->priorityQueue[i];
        if(node > 0 && node == key)
            return 1;
    }

    return 0;
}

int getWeight(graph_t *gp, int vertex1, int vertex2){
    
    node_t *node = gp->listAdj[vertex1];
    
    while(node){
        if(node->key == vertex2)
            return node->weight;
        node = node->next;
    }

    return INFINITE;
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

int* prim(graph_t *graph, int first){

    heap_t *heap = createHeap(graph->vertexAmount);
    node_t *neighbors;
    int *key = (int*)malloc(sizeof(int)*graph->vertexAmount); 
    int *pi = (int*)malloc(sizeof(int)*graph->vertexAmount);
    int i, weight, node;

    for(i = 0; i < graph->vertexAmount; i++){
        if(graph->listAdj[i]){
            addNode(heap, i);
        }
    }

    for(i = 0; i < graph->vertexAmount; i++){
        key[i] = INFINITE;
    }

    pi[first] = -1;
    key[first] = 0;

    while(heap->occupation > 0){

        node = pullNode(heap);
        neighbors = graph->listAdj[node];
       
        while(neighbors){

            weight = getWeight(graph, node, neighbors->key);

            if(hasNode(heap, neighbors->key) && weight < key[neighbors->key]){
                pi[neighbors->key] = node;
                key[neighbors->key] = weight;
            }
            neighbors = neighbors->next;   
        }
    }
    killHeap(heap);
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

    pi = prim(graph, 0);

    for(i = 0; i < graph->vertexAmount; i++){
        
        if(pi[i] < 0){
            printf("%d <- NULL\n", i);
        }else{
            printf("%d <- %d\n", i, pi[i]);
        }
    }

    /*
    Expected output:
    0 <- NULL
    1 <- 0
    2 <- 1
    3 <- 2
    4 <- 3
    5 <- 2
    6 <- 5
    7 <- 6
    8 <- 2 

    obs: the root node will be the node passed as a parameter in the prim() function!
    */

}


