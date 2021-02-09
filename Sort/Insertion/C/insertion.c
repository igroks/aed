#include <stdio.h>

void insertionSort(int vet[], int tam){
    
    int pivot,i,j;

    for(j = 0; j < tam; j++){

        pivot = vet[j];
        i = j-1;

        while((i >= 0) && (vet[i] > pivot)){

            vet[i+1] = vet[i];
            i--;
        }
        vet[i+1] = pivot;
    }
}
