#include <stdio.h>
#include <stdlib.h> 
#include "logica_series_deportivas.h" 

float serie_deportiva(int num_partidos, float probaH, float probaV, int** serie, float**resultado, int tamanio_serie){ 
	 
	int i, j, k;   
	float usarproba1; 
	float usarproba2;
	int partido_actual;
	float proba2H = 1 - probaV; 
	float proba2V = 1 - probaH;  
	//printf("ProbaH %e \n", probaH);
	//printf("Serie %d \n", serie[0]); 
	//printf("Serie %d \n", serie[1]); 

	for(i = 0; i<= num_partidos; i++){ 
		for(j = 0; j <= num_partidos; j++){
			if(i == 0){ 
				resultado[i][j] = 1; 
				//printf("Los 1: %e \n", resultado[i][j]);
			} 
			else if(j == 0){
				resultado[i][j] = 0; 
				//printf("Los 0: %e \n", resultado[i][j]);
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
				partido_actual = (num_partidos - j) + (num_partidos - i) + 1; 
				//printf("Partido actual %d = \b", partido_actual);   
				//printf(" (%d \b", num_partidos);
				//printf("- %d) \b", j); 
				//printf("+ (%d \b", num_partidos); 
				//printf("- %d) \b", i);  
				//printf("+ 1 \b");
 
				for(k = 0; k < tamanio_serie; k++){ 
					if(k == 0){
						if(partido_actual <= serie[k]){  
							usarproba1 = probaH; 
							usarproba2 = proba2V;
						}
					}
					else{ 
						if(partido_actual <= serie[k] && partido_actual > serie[k-1] && k%2 == 0){
							usarproba1 = probaH; 
							usarproba2 = proba2V;
						} 
						else if(partido_actual <= serie[k] && partido_actual > serie[k-1]){ 
							usarproba1 = probaV; 
							usarproba2 = proba2H;
						}
					} 
					
				}

				resultado[i][j] = resultado[i-1][j] * usarproba1 + resultado[i][j-1] * usarproba2;  
				printf("%4f | \b", resultado[i][j]); 
				//printf(" | resultado %4f = \b", resultado[i][j]); 
				//printf(" %.4f \b", resultado[i-1][j]);
				//printf("* %.4f \b", usarproba1);
				//printf("+ %.4f \b", resultado[i][j-1]); 
				//printf(" * %4f \n", usarproba2);  

			} 
		} 
		printf("\n"); 
		//printf(" ------------------------------------------- \n"); 

	} 


	printf("resultado final %.4f \b", resultado[num_partidos][num_partidos]); 
	return resultado[num_partidos][num_partidos]; 


}

void main(){   
	int i;
	int num_partidos = 4;  
	float probaH = 0.52; 
	float probaV = 0.48;  
	int **serie= (int *)calloc(num_partidos+1,sizeof(int)); 
	serie[0] = 4; 
	serie[1] = 7;    
	int tamanio_serie = 2; 
	int **resultado = (int **)calloc(num_partidos+1,sizeof(int *));
    for (i=0; i<num_partidos+1; i++)
         resultado[i] = (int *)calloc(num_partidos+1,sizeof(int));  
	serie_deportiva(num_partidos, probaH, probaV, serie, resultado, tamanio_serie);

}
