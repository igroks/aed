#include <stdio.h>

#define MAX 100 //Tamanho máximo do vetor auxliar que irá armazenar a contagem

void countingSort(int vet[], int tam){

    int i, j, k, aux[MAX];

    //incializando vetor auxiliar
    for(i = 0; i < MAX; i++){
        aux[i] = 0;
    }

    //Contando
    for(i = 0; i < tam; i++){
        aux[vet[i]]++;
    }

    //Reatribuindo intens ao vetor original de forma ordenada
    for(i = 0, j = 0; j < MAX; j++){
        for(k = aux[j]; k > 0; k--){
            vet[i++] = j;
        }
    }
}

void main(){

    //Exemplo
    int i, tam = 9;
    int vet[] = {5,7,3,6,9,1,8,2,4};

    countingSort(vet,tam);

    //Imprimindo o vetor
    for(i = 0; i < tam; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");

}