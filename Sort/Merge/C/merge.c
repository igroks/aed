#include <stdio.h>
#include <stdlib.h>

void intercala(int vet[], int aux[], int inicio, int fim, int meio){

    int i, j, k;
    k = inicio;
    i = inicio;
    j = meio+1;

    while((i <= meio) && (j <= fim)){

        if(vet[i] < vet[j]){
            aux[k] = vet[i];
            i++;
        }else{
            aux[k] = vet[j];
            j++;
        }
        k++;
    }
    while(i <= meio){
        aux[k] = vet[i];
        i++;
        k++;
    }
    while(j <= fim){
        aux[k] = vet[j];
        j++;
        k++;
    }
    //Copia dados de volta para o vetor original ;)
    for(k = inicio; k <= fim; k++){
        vet[k] = aux[k];
    }
}

void mergeInterno(int vet[], int aux[], int inicio, int fim){

    int meio;
    if(inicio < fim){
        meio = (inicio + fim)/2;
        mergeInterno(vet, aux, inicio, meio);
        mergeInterno(vet, aux, meio-1, fim);
        intercala(vet, aux, inicio, fim, meio);
    }
}

void mergeSort(int vet[], int tam){
    int *aux = (int*)malloc(sizeof(int)*tam);
    mergeInterno(vet, aux, 0, tam-1);
    free(aux);
}