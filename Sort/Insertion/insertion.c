#include <stdio.h>

void insertionSort(int vet[], int tam){
    
    int pivot,i,j;

    for(j = 1; j < tam; j++){

        pivot = vet[j];
        i = j-1;

        while((i >= 0) && (vet[i] > pivot)){

            vet[i+1] = vet[i];
            i--;
        }
        vet[i+1] = pivot;
    }
}

void main(){

    //Exemplo
    int i, tam = 9;
    int vet[] = {5,3,2,6,7,1,4,8,9};

    insertionSort(vet,tam);

    //Imprimindo vetor
    for(i = 0; i < tam; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
}