#ifndef MYLIB_H
#define MYLIB_H
#include "mylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct cidade Cidade;
typedef struct solucao Solucao;

int tam(FILE* arq);
bool alocaCidades(Cidade** v, int tam);
Solucao* alocaSolucao();
bool leCidades(Cidade *v, FILE *arq);

double calculaDist(Cidade a,Cidade b);
double calculaCusto(Solucao *v, double** dist);
double** criaMatrizDistancia(Cidade *v, int n);

int vizinhoMaisProximo(int atual, bool *visitado,double **dist, int n);
bool geraSolucao(Solucao *solucao,double **dist,int ini, int n);

Cidade* destroiCidades(Cidade *c);
Solucao* destroiSolucao(Solucao *v, int n);
#endif