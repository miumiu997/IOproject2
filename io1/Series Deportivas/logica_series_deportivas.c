#include <stdio.h>
#include <stdlib.h> 
#include "logica_series_deportivas.h" 

float serie_deportiva(int num_partidos, float probaH, float probaV, int** serie, float**resultado){ 
	 
	int i, j, k;  
	float proba2H = 1 - probaH; 
	float proba2V = 1 - probaV; 
	printf("ProbaH %e \n", probaH);

	for(i = 0; i<= num_partidos; i++){ 
		for(j = 0; j <= num_partidos; j++){
			if(i == 0){ 
				resultado[i][j] = 1; 
				printf("Los 1: %e \n", resultado[i][j]);
			} 
			else if(j == 0){
				resultado[i][j] = 0; 
				printf("Los 0: %e \n", resultado[i][j]);
			}
		}
	} 


	for(i = 0; i<= num_partidos; i++){ 
		for(j = 0; j <= num_partidos; j++){
			if(i == 0){ 
				resultado[i][j] = 1;
			} 
			else if(j == 0){
				resultado[i][j] = 0;
			}  

			else{ 
				resultado[i][j] = resultado[i-1][j] * probaH + resultado[i][j-1] * probaV; 
				printf("resultado[i-1][j] %e \b", resultado[i-1][j]);
				printf("probaH %e \b", probaH);
				printf("resultado[i][j-1] %e \b", resultado[i][j-1]); 
				printf("probaV %e \n", probaV);
			}

		}
	} 


	printf("resultado final %e \b", resultado[num_partidos][num_partidos]); 
	return resultado[num_partidos][num_partidos]; 


}

void main(){   
	int i;
	int num_partidos = 4;  
	float probaH = 0.5; 
	float probaV = 0.5; 
	int **serie= (int *)calloc(num_partidos+1,sizeof(int));
	int **resultado = (int **)calloc(num_partidos+1,sizeof(int *));
    for (i=0; i<num_partidos+1; i++)
         resultado[i] = (int *)calloc(num_partidos+1,sizeof(int)); 
	serie_deportiva(num_partidos, probaH, probaV, serie, resultado);

	printf("holas");
}