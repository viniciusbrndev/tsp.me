#include "mylib.h"
#include <stdlib.h>
#include <stdio.h>



int main(int argc,char *argv[]){
    if(argc !=2){
        printf("Arquivo não localizado!!");
        return 0;
    }
    FILE *arq = fopen(argv[1], "r");
    if(!arq){
        printf("Arquivo não pode ser aberto!");
        return 1;
    }
    int t = tam(arq);
    Cidade *cidades;
    bool test = alocaCidades(&cidades, t);
    Solucao *solucoes = alocaSolucao();

    if(!test)
        return -1;
    test = leCidades(cidades, arq);
    if(!test)
        return -1;
    double **dist = criaMatrizDistancia(cidades, t);
    test = geraSolucao(solucoes, dist, 0, t);

    printf("%lf", calculaCusto(solucoes, dist));

    cidades = destroiCidades(cidades);
    solucoes = destroiSolucao(solucoes, 1);
}