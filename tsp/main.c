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
    Solucao **solucoes = malloc(sizeof(Solucao*)*t);
    for(int a = 0; a < t; a++)
        solucoes[a] = alocaSolucao();

    if(!test)
        return -1;
    test = leCidades(cidades, arq);
    if(!test)
        return -1;
    double **dist = criaMatrizDistancia(cidades, t);
    for(int k = 0; k < t; k++){
        test = geraSolucao(solucoes[k], dist, k, t);

        printf("%lf\n", calculaCusto(solucoes[k], dist));
    }
    //liberando memoria
    cidades = destroiCidades(cidades);
    for(int a = 0; a < t; a++)
        solucoes[a] = destroiSolucao(solucoes[a], t);
    free(solucoes);
    destroiMatriz(dist, t);
    fclose(arq);
}