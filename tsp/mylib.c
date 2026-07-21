#include "mylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct cidade{
    int id;
    double x;
    double y;
};
struct solucao{
    int *passos;
};

int tam(FILE* arq){
    if(!arq)
        return -1;
    int i = 0, tam = -1;
    char linha[200];
    while (i < 4){
        fgets(linha, sizeof(char)*200, arq);
    }
    sscanf(linha, "%d", &tam);
    return tam;
}
bool alocaCidades(Cidade** v, int tam){
    if(!v)
        return false;
    *v = malloc(sizeof(Cidade)*tam);
    if(!(*v))
        return false;
    return true;
}
bool leCidades(Cidade *v, FILE *arq){
    if(!v || !arq)
        return false;
    char linha[200];
    fgets(linha, sizeof(char)*200, arq);
    while(strcmp(linha, "NODE_COORD_SECTION"))
        fgets(linha, sizeof(char)*200, arq);
    double x, y;
    int id;
    while(fgets(linha, sizeof(char)*200, arq) != NULL){
        sscanf(linha, "%d %lf %lf", &id, &x, &y);
        v[id-1].id = id;
        v[id-1].x = x;
        v[id-1].y = y;
    }
    return true;
}
double calculaDist(Cidade a,Cidade b){
    if(a.id == b.id)
        return 0;
    double idx1 = a.x - b.x;
    double idx2 = a.y - b.y;
    return sqrt((pow(idx1, 2) + pow(idx2, 2)));
} 
double** criaMatrizDistancia(Cidade *v, int n){
    int i = 0, j =0;
    double **matriz = malloc(sizeof(double*)*n);
    if(!matriz)
        return NULL;
    for(i = 0; i < n; i++){
        matriz[i] = malloc(sizeof(double)*n);
        if(!matriz[i]){
            for(j = 0; j < i; j++)
                free(matriz[j]);
            free(matriz);
        return NULL;
        }
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            matriz[i][j] = calculaDist(v[i], v[j]);
        }
    }
    return matriz;
}
