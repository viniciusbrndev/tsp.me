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
    
    
}