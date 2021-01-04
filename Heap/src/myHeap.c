#include <stdio.h>
#include <stdlib.h>
#include "myHeap.h"

void heapifyUp (tipoHeap *tp, int filho){
    int pai = (filho-1)/2;
    tipoDado tmp;

    while((filho > 0) && (tp->dados[pai].id >= tp->dados[filho].id)){

        tmp = tp->dados[filho];
        tp->dados[filho] = tp->dados[pai];
        tp->dados[pai] = tmp;

        filho = pai;
        pai = (pai-1)/2;
                
    }
}

void heapifyDown (tipoHeap *tp, int pai){
    int filho = 2*pai + 1;
    tipoDado tmp;

    while(filho < tp->qtd){
        if(filho < tp->qtd-1){
            if(tp->dados[filho].id > tp->dados[filho+1].id){
                filho++;
            }
        }

        if(tp->dados[pai].id <= tp->dados[filho].id){
            break;
        }

        tmp  = tp->dados[pai];
        tp->dados[pai] = tp->dados[filho];
        tp->dados[filho] = tmp;

        pai = filho;
        filho = 2*pai + 1;
    }
}

void criaHeap (tipoHeap *tp, int tam){

    tp->dados = (tipoDado*) malloc(sizeof(tipoDado)*tam);
    tp->qtd = 0;
    tp->tamanho = tam;
}

int insereNaHeap (tipoHeap* tp, tipoDado d){

    if(tp->qtd == tp->tamanho)return 0; //A heap está cheia!
    tp->dados[tp->qtd] = d;
    heapifyUp(tp, tp->qtd);
    tp->qtd++;
    return 1;

}

int removeDaHeap (tipoHeap *tp){

    if(tp->qtd == tp->tamanho)return 0; //A heap está cheia!
    
    tp->qtd--;
    tp->dados[0] = tp->dados[tp->qtd];
    heapifyDown(tp, 0);
    return 1;
    
}

void detroiHeap (tipoHeap *tp){
    tp->qtd = 0;
    tp->tamanho = 0;
    free(tp->dados);
}

void substituiTopo (tipoHeap *tp, tipoDado d){
    tp->dados[0] = d;
    heapifyDown(tp, 0);
}

void topK (tipoDado vet[], int tam, int k){
    tipoHeap result;
    int i;
    criaHeap(&result, k);
        
    for( i = 0; i < k; i++){
        insereNaHeap(&result, vet[i]);    
    }

    for( i = k; i < tam; i++){
        if(vet[i].id > result.dados[0].id){
            substituiTopo(&result, vet[i]);
        }
    }
    printf("\nOs %d maiores são: ", k);
    for(i = 0; i < k; i++){
        printf("\n");
        printf("%s\n", result.dados[i].nome);
        printf("%d\n", result.dados[i].id);
        printf("\n");

    }
}