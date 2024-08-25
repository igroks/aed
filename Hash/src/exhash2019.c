#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "exhash2019.h"
                      
void insereListaHash(tipoNoHash **prim, tipoDado d) {
  tipoNoHash *aux;

  aux = (tipoNoHash *) malloc(sizeof(tipoNoHash));
  aux ->d = d;
  aux -> prox = *prim;
  *prim = aux;
}

                   
int buscaListaHash(tipoNoHash *prim, char *chave, tipoDado *d) {

  while(prim) {
    if(!strcmp(prim->d.nome,chave)) {
      *d = prim->d;
      return 1;
    }
    prim = prim->prox;
  }
  return 0;
}


                   
int existeListaHash(tipoNoHash *prim, char *chave) {

  while(prim) {
    if(!strcmp(prim->d.nome,chave)) {
      return 1;
    }
    prim = prim->prox;
  }
  return 0;
}



void criaHash(tipoHash *h, unsigned tam) {
  unsigned x;
  h->tabela = (tipoNoHash **) malloc (sizeof(tipoNoHash*)*tam);
  h->tamHash = tam;  
  for(x = 0 ; x < tam; x++) {
    h->tabela[x] = NULL; 
  }

}

unsigned _hash(char *chave) {
  unsigned resultado=0,k=0;
  unsigned tamChave= strlen(chave);
  unsigned tam = tamChave/sizeof(unsigned);
  unsigned *p=(unsigned*) chave;
  unsigned x;
  for(x = 0; x< tam; x++) {
    resultado+=((x+1)*p[x]);
  }
  for(x = tam*4; x< tamChave; x++) {
    k= k | chave[x]; 
    k = k << 8;
  }
  return resultado+k;
}

void insereNoHash(tipoHash *h, tipoDado d) {
  unsigned pos = _hash(d.nome)%h->tamHash;
  printf("posicao inserida: %u\n",pos);
  if(!existeListaHash(h->tabela[pos], d.nome)) {
    insereListaHash(&(h->tabela[pos]),d);
  }
}



int buscaNoHash(tipoHash *h, char *chave, tipoDado *d) {
  unsigned pos = _hash(chave)%h->tamHash;
  printf("posicao buscada: %u\n",pos);
  return buscaListaHash(h->tabela[pos], chave,d);
}
