#include <stdio.h>
#include <stdlib.h>

#define TAM 5 //Tamanho do balde

typedef struct tipoBalde{
    int qtd;
    int valores[TAM];
}tipoBalde;

void insertionSort(int vet[], int tam){
    
    int pivot,i,j;

    for(i = 0; j < tam; j++){

        pivot = vet[j];
        i = j-1;

        while((i >= 0) && (vet[i] > pivot)){

            vet[i+1] = vet[i];
            i--;
        }
        vet[i+1] = pivot;
    }
}

void bucketSort(int vet[], int tam){
    
    int i, j, maior, menor, numBaldes, pos;
    tipoBalde *bd;

    //Acha maior e menor valor
    maior = menor = vet[0];
    for(i = 1; i < tam; i++){
        
        if(vet[i] > maior)maior = vet[i];
        if(vet[i] < menor)menor = vet[i];

    }

    //Iniciliza baldes
    numBaldes = (maior-menor)/TAM+1;
    bd = (tipoBalde*)malloc(numBaldes*sizeof(tipoBalde));

    for(i = 0; i < numBaldes; i++){
        bd[i].qtd = 0;
    }

    //Distribui os valores nos baldes
    for(i = 0; i < tam; i++){
        pos = (vet[i]-menor)/TAM;
        bd[pos].valores[bd[pos].qtd] = vet[i];
        bd[pos].qtd++;
    }

    //Ordena baldes e coloca no array original
    pos = 0;
    for(i = 0; i < numBaldes; i++){
        insertionSort(bd[i].valores, bd[i].qtd);
        for(j = 0; j < bd[i].qtd; j++){
            vet[pos] = bd[i].valores[j];
            pos++;
        }
    }
    free(bd);
}