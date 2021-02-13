#include <stdio.h>

void selectionSort(int vet[], int tam){

    int i,j,posMenor,temp,tamMenos1 = tam-1;

    for(i = 0; i < tamMenos1; i++){
        posMenor = i;
        for(j = i+1; j < tam; j++){
            if(vet[j] < vet[posMenor]){
                posMenor = j;
            }
        }
        temp = vet[i];
        vet[i] = vet[posMenor];
        vet[posMenor] = temp;
    }
}

void main(){

    //Exemplo
    int i,tam = 9;
    int vet[] = {4,6,5,3,8,7,9,2,1};
    
    selectionSort(vet, tam);

    //Imprimindo o vetor
    for(i = 0; i < tam; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
}