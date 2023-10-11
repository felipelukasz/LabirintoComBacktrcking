#include <stdio.h>
#include "funcoes.h"

int main()
{
    Posicao inicio, fim;
    int n;
    int **labirinto = criarMatrizLabirinto("labirinto.txt", &n, &inicio, &fim);

    imprimeLabOrg(labirinto, n);
    encontraCaminho(labirinto,n,inicio,fim);
    libera(labirinto,n);
    return 0;
}

/*

    Trabalho de Estruturas de Dados I, 1º bimestre
    Prof. Gilberto Fernandes Junior
    Aluno: Felipe Guilhen Lukaszczuk
    5 de Outubro de 2023

*/