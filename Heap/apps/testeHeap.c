#include <stdio.h>
#include <string.h>
#include "myHeap.h"

int main(){
    tipoDado v[10];
    int i;

    printf("Entre com os dados no vetor:\n");
    for ( i = 0; i < 10; i++){
        printf("Dados %d:\n", i);
        scanf("%[^\n]%*c", v[i].nome);
        scanf("%d%*c", &v[i].id);
    }

    printf("Mostrando os 5 maiores:\n ");
    topK(v, 10, 5);

    
}


