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
    int n;
    double custo;
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
Solucao* alocaSolucao(){
    Solucao* sol = malloc(sizeof(Solucao));
    if(!sol)
        sol = NULL;
    return sol;
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
    while(strcmp(linha, "NODE_COORD_SECTION\n"))
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
//implementando método do vizinho mais próximo com a cidade inicial fixa;
int vizinhoMaisProximo(int atual, bool *visitado,double **dist, int n){
    int melhorCidade = -1;
    double menorDist = INFINITY;

    for(int i = 0; i < n; i++){
        // ignora cidades já visitadas
        if(visitado[i])
            continue;
        // encontrou uma cidade mais próxima?
        if(dist[atual][i] < menorDist){
            menorDist = dist[atual][i];
            melhorCidade = i;
        }
    }

    return melhorCidade;
}

bool geraSolucao(Solucao *solucao,double **dist,int ini, int n){
    if(!solucao || !*dist|| n <= 0)
        return false;
    solucao->passos = malloc(sizeof(int)*n);
    bool *visitado = malloc(sizeof(bool)*n);

    for(int a = 0; a < n; a++)
        visitado[a] = false;
    
    solucao->passos[0] = 0;
    visitado[0] = true;
    
    int atual = ini;//ini = 0
    int prox;
    for(int i = 1; i < n; i++){
        prox = vizinhoMaisProximo(atual, visitado, dist, n);
        
        solucao->passos[i] = prox;
        visitado[prox] = true;
        
        atual = prox;
    }
    free(visitado);
    return true;
}
double calculaCusto(Solucao *v, double** dist){
    v->custo = 0;
    int i;
    for(i = 0; i < v->n; i++){
        v->custo += dist[v->passos[i]][v->passos[i+1]];
    }
    v->custo += dist[0][v->passos[i]];
    return v->custo;
}
Cidade* destroiCidades(Cidade *c){
    if(!c)
        return NULL;
    free(c);
    return NULL;
}
Solucao* destroiSolucao(Solucao *v, int n){
    if(!v)
        return NULL;
    for(int i = 0; i < n; i++){
        free(v[i].passos);
    }
    free(v);
    return NULL;
}