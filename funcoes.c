#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

#ifdef _WIN32
#include <windows.h>
#define CLEARSCREEN "cls"
#define SLEEP_MS(ms) Sleep(ms)
#else
#define SLEEP_MS(ms) usleep(ms * 1000)
#define CLEARSCREEN "clear"
#include <unistd.h>
#endif

void inicializarPilha(Pilha *pilha){
    pilha -> cabeca = NULL;
}

int pilhaVazia(Pilha *pilha){
    return pilha -> cabeca == NULL;
}

void empilhar(Pilha *pilha, Personagem personagem){
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo -> per = personagem;
    novoNo -> prox = pilha -> cabeca;
    pilha -> cabeca = novoNo;
}

void desempilhar(Pilha *pilha){
    if(pilha -> cabeca != NULL){
        No *temp = pilha -> cabeca;
        pilha -> cabeca = pilha -> cabeca -> prox;
        free(temp);
    }
}

int posicaoValida(int **labirinto, int n, int x, int y){
    return n >= 0 && x < n && y >= 0 && y < n && (labirinto[x][y] == 0 || labirinto[x][y] == 3);
}

void imprimeLabOrg(int **labirinto, int n){
    printf("Labirinto original:\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(labirinto[i][j] == 1){
                printf("+ ");
            }else if(labirinto[i][j] == 0){
                printf("  ");
            }else if(labirinto[i][j] == 3){
                printf("x ");
            }else{
                printf("o ");
            }
        }
        printf("\n");
    }
    printf("\n");
    SLEEP_MS(1000);
}

int encontraCaminho(int **labirinto, int n, Posicao inicio, Posicao fim){ //função principal que realiza o backtracking
    Pilha pilha;
    inicializarPilha(&pilha);

    int rastro[n][n]; //matriz auxiliar que marca o rastro
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            rastro[i][j] = 0;
        }
    }

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    Personagem personagem;
    personagem.x = inicio.x;
    personagem.y = inicio.y;
    empilhar(&pilha,personagem);

    while(!pilhaVazia(&pilha)){
        personagem = pilha.cabeca->per;
        Posicao pos;
        pos.x = personagem.x;
        pos.y = personagem.y;

        if(pos.x == fim.x && pos.y == fim.y){
            printf("\nFoi possivel chegar ao fim! Rastro na tela e a sequencia de coordenadas eh:\n");
            No *noAtual = pilha.cabeca;
            while(noAtual != NULL){
                Personagem per = noAtual->per;
                printf("(%d,%d) ",per.x,per.y);
                noAtual = noAtual->prox;
            }
            return 1;
        }
        int direcao = 0;
        int movimentoValido = 0;

        while(direcao < 4){
            int proxX = pos.x + dx[direcao];
            int proxY = pos.y + dy[direcao];

            if(posicaoValida(labirinto, n, proxX, proxY)){
                personagem.x = proxX;
                personagem.y = proxY;
                empilhar(&pilha, personagem);
                labirinto[proxX][proxY] = -1; //ja passou
                rastro[proxX][proxY] = 1; //rastro
                movimentoValido = 1;

                SLEEP_MS(200);
                system(CLEARSCREEN);
                for(int i=0; i<n; i++){
                    for(int j=0; j<n; j++){
                        if(i == inicio.x && j == inicio.y){
                            printf("  ");
                        }else{
                            if(i == personagem.x && j == personagem.y){
                                printf("o ");
                            }else if(rastro[i][j] == 1){
                                printf(". ");
                            }else if(labirinto[i][j] == 1){
                                printf("+ ");
                            }else if(labirinto[i][j] == 0){
                                printf("  ");
                            }else if(labirinto[i][j] == 3){
                                printf("x ");
                            }else{
                                printf("  ");
                            }
                        }
                    }
                    printf("\n");
                }
                printf("\n");
                break;
            }
            direcao++;
        }

        if(!movimentoValido){
            labirinto[pos.x][pos.y] = -1;
            desempilhar(&pilha);

            SLEEP_MS(200);
            system(CLEARSCREEN);
            for(int i=0; i<n; i++){
                for(int j=0; j<n; j++){
                    if(i == inicio.x && j == inicio.y){
                        printf("  ");
                    }else if(i == personagem.x && j == personagem.y){
                            printf("o ");;
                    }else if(rastro[i][j] == 1){
                            printf(". ");
                    }else if(labirinto[i][j] == 1){
                            printf("+ ");
                    }else if(labirinto[i][j] == 0){
                            printf("  ");
                    }else if(labirinto[i][j] == 3){
                            printf("x ");
                    }else{
                        printf("  ");
                    }
                }
                printf("\n");
            }
            printf("\n");
            rastro[pos.x][pos.y] = 0;
        }
    }
    printf("Nao ha caminho possivel.\n");
    return 0;
}

int **criarMatrizLabirinto(const char *nomeArquivo, int *n, Posicao *inicio, Posicao *fim){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    fscanf(arquivo, "%d", n);

    int **labirinto = (int **)malloc(*n * sizeof(int *));
    for(int i=0; i<*n; i++){
        labirinto[i] = (int *)malloc(*n * sizeof(int));
    }

    for (int i = 0; i<*n; i++){
        for(int j=0; j < *n; j++) {
            fscanf(arquivo, "%d", &labirinto[i][j]);
            if(labirinto[i][j] == 2){
                inicio->x = i;
                inicio->y = j;
            } else if(labirinto[i][j] == 3){
                fim->x = i;
                fim->y = j;
            }
        }
    }
    fclose(arquivo);
    return labirinto;
}

void libera(int **labirinto, int n){
    for(int i=0; i<n; i++){
        free(labirinto[i]);
    }
    free(labirinto);
}