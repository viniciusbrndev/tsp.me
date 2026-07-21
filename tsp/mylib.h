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
bool leCidades(Cidade *v, FILE *arq);

#endif