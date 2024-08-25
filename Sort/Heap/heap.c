#include <stdio.h>

void criaHeap(int vet[], int inicio, int final){

    int aux = vet[inicio];
    int j = inicio*2+1;
    while(j <= final){
        if(j < final){
            if(vet[j] < vet[j+1]){
                j++;
            }
        }
        if(aux < vet[j]){
            vet[inicio] = vet[j];
            inicio = j;
            j = 2*inicio+1;
        }else{
            j = final+1;
        }
    }
    vet[inicio] = aux;
}

void heapSort(int vet[], int tam){

    int i, aux;
    //cria heap a partir dos dados
    for(i = (tam-1)/2; i >= 0 ; i--){  
        criaHeap(vet, i, tam-1);
    }
    //pegar o maior elemento da heap e colocar na sua posição correspondente no array
    for(i = tam-1; i >= 1; i--){
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;
        criaHeap(vet, 0, i-1);
    }
}


void main(){

    //Exemplo
    int i, tam = 9;
    int vet[] = {5,7,9,2,8,4,3,6,1};

    heapSort(vet,tam);

    //Imprimindo o vetor
    for(i = 0; i < tam; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
}