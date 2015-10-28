#include <stdio.h>
#include "logicaArboles.h"
int main( int argc, const char* argv[] ){


	char *llaves[] = {"carpenter", "cash","cobain", "harrison", "hendrix", "joplin", "lennon", "morrison", "presley"};
	//double probabilidades[] = {0.05, 0.07, 0.01, 0.35, 0.09, 0.23, 0.15, 0.04, 0.01};

    //char *llaves[] = {"carpenter", "cash","cobain", "harrison", "hendrix", "joplin", "lennon", "morrison", "presley"};
    double probabilidades[] = {0.18, 0.32, 0.39, 0.11};

	int i;
	int cantidad = 4;
	double **A = (double **)calloc(cantidad+1,sizeof(double *));
    for (i=0; i<cantidad+1; i++){
    	A[i] = (double *)calloc(cantidad+1,sizeof(double));
    }
         
    int **R = (int **)calloc(cantidad+1,sizeof(int *));
    for (i=0; i<cantidad+1; i++){
    	R[i] = (int *)calloc(cantidad+1,sizeof(int));
    }

    arbolBinarioBusqueda(cantidad, llaves, probabilidades);

    return 0;
}
