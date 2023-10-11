#ifndef FUNCOES_H
#define FUNCOES_H
#include <stdio.h>

//posicao do labirinto
typedef struct{
    int x, y;
}Posicao;

//personagem
typedef struct{
    int x, y;
}Personagem;

//nó da pilha
typedef struct no{
    Personagem per;
    struct no *prox;
}No;

//armazena os nós
typedef struct{
    No *cabeca;
    int comprimento;
}Pilha;

//funcoes triviais da pilha
void inicializarPilha(Pilha *pilha);
int pilhaVazia(Pilha *pilha);
void empilhar(Pilha *pilha, Personagem personagem);
void desempilhar(Pilha *pilha);

//verifica se uma posicao é valida no labirinto
int posicaoValida(int **labirinto, int n, int x, int y);

//cria uma matriz com o formato do labirinto
int **criarMatrizLabirinto(const char *nomeArquivo, int *n, Posicao *inicio, Posicao *fim);

// printa o labirinto original
void imprimeLabOrg(int **labirinto, int n);

//funçao principal que realiza o backtracking
int encontraCaminho(int **labirinto, int n, Posicao inicio, Posicao fim);

//libera a memoria alocada
void libera(int **labirinto, int n);

#endif