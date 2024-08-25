#include "exhash2019.h"
#include <string.h>
#include <stdio.h>

int main() {
  tipoHash a;
  tipoDado d;
  char chave[20]="";
  criaHash(&a,10);

  strcpy(d.nome,"jose");
  d.id = 50;
  insereNoHash(&a,d);

  strcpy(d.nome,"maria");
  d.id = 60;
  insereNoHash(&a,d);

 strcpy(d.nome,"ana");
  d.id = 70;
  insereNoHash(&a,d);

  while(strcmp(chave, "fim")) {
    printf("Digite um nome para busca (<fim> para terminar):"); 
    scanf("%[^\n]%*c",chave);
    if(buscaNoHash(&a,chave,&d)) {
      printf("Encontrado\n %s \n %u\n",d.nome,d.id);
    }
    else {
      printf("NÃO CONSTA NO HASH\n");
    }


  }

}
