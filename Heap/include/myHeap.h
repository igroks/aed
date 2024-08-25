#ifndef _myHeap
#define _myHeap

// AS FUNÇÕES FORAM IMPLEMENTADAS PARA UMA MIN-HEAP
// Definições de tipos e constantes para a Heap:

typedef struct tipoDado{
    char nome[30];
    int id;
}tipoDado;

typedef struct tipoHeap{
    int qtd;
    int tamanho;
    tipoDado *dados;
}tipoHeap;

// Funções para manipular a Heap:

// Auxiliares:

void heapifyUp (tipoHeap *tp, int filho); // função que "promove" os nós da Heap caso for necessário

void heapifyDown (tipoHeap *tp, int pai); // função que "rebaixa" os nós da Heap caso for necessário

// Básicas:

void criaHeap (tipoHeap *tp, int tam); // Cria a estrutura com o tamanho passado por paremetro.

int insereNaHeap (tipoHeap *tp, tipoDado d); // Insere os dados na Heap e retorna 1 se conseguir e 0 caso contrário

int removeDaHeap (tipoHeap *tp); // Remove o dado com maior chave(neste caso o ID) da Heap e retorna 1 se conseguir e 0 caso contrário

void destroiHeap (tipoHeap *tp); // Libera a memória onde está a estrutura da Heap

void substituiTopo (tipoHeap *tp, tipoDado d); // troca o valor da raiz da Heap e chama a função heapifyDown para manter as propiedades

void topK (tipoDado vet[], int tam , int k); // Função que imprime os K maiores elementos do vetor (Obs: usando o ID como chave)

#endif