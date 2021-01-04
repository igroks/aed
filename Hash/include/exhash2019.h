#ifndef _exhash2019
#define _exhash2019

// AQUI AS DEFINICOES DE TIPOS

typedef struct tipoDado {
  char nome[30];
  int id;
}  tipoDado;

typedef struct tipoNoHash {
  tipoDado  d;
  struct tipoNoHash * prox;
}  tipoNoHash;


typedef struct tipoHash {
  tipoNoHash **tabela;
  unsigned tamHash;
} tipoHash;

// AQUI AS FUNCOES DO MODULO QUE VAO SER USADAS POR OUTROS PROGRAMAS

// CRIAR UM HASH PASSANDO O TAMANHO E o ENDERECO DE UMA VARIAVEL HASH DECLARADA

void criaHash(tipoHash *h, unsigned tam);

unsigned _hash(char *chave);

// INSERIR NO HASH

void insereNoHash(tipoHash *h, tipoDado d);

// BUSCAR

int buscaNoHash(tipoHash *h, char *chave, tipoDado *d);

// FALTA FAZER A REMOVER DO HASH, QUE REMOVE DA LISTA ENCADEADA UMA CHAVE FORNECIDA


// FALTA FAZER A DESTROI HASH, QUE DESTROI TODAS AS LISTAS ENCADEADAS  E DEPOIS LIBERA MEMORIA DO VETOR DE PONTEIROS


#endif
