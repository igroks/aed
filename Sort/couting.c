#include <stdio.h>

#define MAX 100

void coutingSort(int vet[], int tam){

    int i, j, k, aux[MAX];

    for(i = 0; i < MAX; i++){
        aux[i] = 0;
    }
    for(i = 0; i < tam; i++){
        aux[vet[i]]++;
    }
    for(i = 0, j = 0; j < MAX; j++){
        for(k = aux[j]; k > 0; k--){
            vet[i++] = j;
        }
    }
}