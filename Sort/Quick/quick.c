#include <stdio.h>

void quickInterno(int vet[], int inicio, int fim){

    int pivot, temp, i, j;

    if(fim-inicio > 0){
        i = inicio;
        j = fim;
        pivot = vet[(i+j)/2];

        do{
            while(vet[i] < pivot)i++;
            while(vet[j] > pivot)j--;

            if(i <= j){
                temp = vet[i];
                vet[i] = vet[j];
                vet[j] = temp;
                i++;
                j--;
            }
        }while(i <= j);

        quickInterno(vet,inicio, j);
        quickInterno(vet, i, fim);
    }
}

void quickSort(int vet[], int tam){
    quickInterno(vet, 0, tam-1);
}

void main(){
    
    //Exemplo
    int i, tam = 9;
    int vet[] = {3,5,1,6,7,2,8,9,4};

    quickSort(vet,tam);

    //Imprimindo vetor
    for(i = 0; i < tam; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
    
}