#include <stdio.h>
#include <stdlib.h> 
#include "logica_series_deportivas.h" 

float serie_deportiva(int num_partidos, float probaH, float probaV, int* serie, float**resultado, int tamanio_serie){ 
	 
	int i, j, k;   
	float usarproba1; 
	float usarproba2;
	int partido_actual;
	float proba2H = 1 - probaV; 
	float proba2V = 1 - probaH;  
	printf("ProbaH %e \n", probaH);
	printf("Serie %d \n", serie[0]); 
	printf("Serie %d \n", serie[1]); 

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
				partido_actual = (num_partidos - j) + (num_partidos - i) + 1; 
				printf("Partido actual %d = \b", partido_actual);   
				printf(" (%d \b", num_partidos);
				printf("- %d) \b", j); 
				printf("+ (%d \b", num_partidos); 
				printf("- %d) \b", i);  
				printf("+ 1 \b");
 
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
				printf(" | resultado %4f = \b", resultado[i][j]); 
				printf(" %.4f \b", resultado[i-1][j]);
				printf("* %.4f \b", usarproba1);
				printf("+ %.4f \b", resultado[i][j-1]); 
				printf(" * %4f \n", usarproba2);  

			} 
		} 
		printf("\n"); 
		printf(" ------------------------------------------- \n"); 

	} 

	printf("resultado final %.4f \b", resultado[num_partidos][num_partidos]); 
	deportesBeamer(num_partidos, probaH, probaV, serie, resultado, tamanio_serie);

	return resultado[num_partidos][num_partidos]; 

} 

void deportesBeamer(int num_partidos, float probaH, float probaV, int* serie, float**resultado, int tamanio_serie){
	printf("HOLIZ BEAMER"); 
	FILE* fp;
    fp = fopen("deportes.tex", "w");


    fprintf(fp,"\\documentclass[10]{beamer} \n");
    fprintf(fp,"\\usepackage[T1]{fontenc} \n");
    fprintf(fp,"\\usepackage{lmodern}\n");
    fprintf(fp,"\\usepackage[spanish]{babel}\n");
    fprintf(fp,"\\usepackage{fancyhdr}\n");
    fprintf(fp,"\\usepackage{xcolor}\n");
    fprintf(fp,"\\usepackage{color}\n");
    fprintf(fp,"\\usepackage{dirtytalk}\n");

    fprintf(fp,"\\definecolor{dgreen}{rgb}{0.,0.6,0.}\n");
    fprintf(fp,"\\definecolor{WHITE}{RGB}{255,255,255}\n");
    fprintf(fp,"\\definecolor{amarillo}{RGB}{255,255,0}\n");
    fprintf(fp,"\\definecolor{gris}{RGB}{174,174,174}\n");
    fprintf(fp,"\\definecolor{ROJO}{RGB}{237,28,36}\n");
    fprintf(fp,"\\setbeamercolor{normal text}{bg=black!80}\n"); 
    fprintf(fp,"\\setbeamercolor{frametitle}{fg=black,bg=amarillo!20}\n");
    fprintf(fp,"\\setbeamercolor{subtitle}{fg=WHITE}\n");
    fprintf(fp,"\\setbeamercolor{section in head/foot}{bg=amarillo}\n");
    fprintf(fp,"\\setbeamercolor{author}{fg=WHITE}\n");
    fprintf(fp,"\\setbeamercolor{date in head/foot}{fg=amarillo}\n");

    fprintf(fp,"\\title{{\\color{WHITE} \\large \\textbf{INSTITUTO TECNOL\\'OGICO DE COSTA RICA}} \\\\ \\vspace{0.02cm} \n");
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{ESCUELA DE INGENIER\\'IA EN COMPUTACI'ON }} \\\\ \\vspace{0.02cm} \n");
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{INVESTIGACI\\'ON DE OPERACIONES  }} \\\\ \\vspace{0.02cm} \n");
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{ALGORITMO PARA LAS \\\\ SERIES DEPORTIVAS  }} \\\\ \\vspace{0.02cm} \n");
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{I SEMESTRE  }}\\\\ \\vspace{0.02cm}\n"); 
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{PROFESOR}} \\\\ \\vspace{0.02cm}\n"); 
    fprintf(fp,"{\\color{WHITE} \\large DR. FRANCISCO J. TORRES ROJAS  } \\\\ \\vspace{0.02cm}\n"); 
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{GRUPO 40}} \\\\ \\vspace{0.01cm}\n");
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{ESTUDIANTES} }} \n");  
    fprintf(fp,"\\color{WHITE} \\author{KATHY ANDRE\\'INA BRENES GUERRERO. \\\\ ADRIAN CUBERO MORA. \\\\MIUYIN YONG WONG}\n");
    fprintf(fp,"\\date{\\em \\color{WHITE} \\today}\n");
    fprintf(fp,"\\begin{document}\n");
    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\titlepage portada\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{ALGORITMO PARA SERIE DEPORTIVAS}\n");
    fprintf(fp,"Entre dos equipos A y B se dice que A tiene una posibilidad p de ganar y B tiene una posibilidad q = 1-p de ganar.\n");
    fprintf(fp,"\\\\ Cu\\'al es la probabilidad de que el grupo A sea campe\\'on ?\n"); 
    fprintf(fp,"\\\\Este algoritmo permite contestar esa pregunta.\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{PROPIEDADES DE LAS SERIES DEPORTIVAS}\n");
    fprintf(fp,"La cantidad de filas y columnas deben ser igual a la canitdad de partidos comenzando desde 0.\n");
    fprintf(fp,"\\\\ Un par ordenado ser\\'ia (i,j) donde i representa la cantidad de partidos que le faltan a A para ganar y j representa la cantiad de partidos que le faltan a B para ganar.\n"); 
    fprintf(fp,"\\\\El estado inicial ser\\'ia (cantidad de partidos, cantidad de partidos).\n");
    fprintf(fp,"\\\\ En cada una de esas casillas se calulara la probabilidad que tiene el equipo A en ganar (cada probabilidad es independiente).\n");
    fprintf(fp,"\\end{frame} \n");


    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{FUNCIONES}\n");
    fprintf(fp,"La funci\\'on que regresa la probabilidad de que A sea campi\\'on se define como:\n");
    fprintf(fp,"\\\\F(i,j)=p*F(i-1,j) + q*F(i, j-1) \n"); 
    fprintf(fp,"\\\\ Casos triviales: F(0,j) = 1    F(i,0) = 0\n"); 
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{VENTAJA LOCAL}\n");
    fprintf(fp,"Los equipos tienden a jugar mejor en casa en ciertos deportes.\n");
    fprintf(fp,"\\\\Por esa raz\\'on se establecen dos probabilidades Ph y Pr. \n"); 
    fprintf(fp,"\\\\ Ph siendo en casa y Pr de visita, las probabilidades del equipo contrario son los complementos.\n"); 
    fprintf(fp,"\\\\ Dada una serie de cuantos equipos ocurriran en casa, se calculan cu\\'al de las dos probabildiades se tiene que usar.\n"); 
    fprintf(fp,"\\end{frame} \n");  

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{VALORES INICIALES}\n"); 
    fprintf(fp,"Cantidad de partidos: $%d $ \\\\", num_partidos); 
    fprintf(fp,"Probabilidad Home: $%.4f $ \\\\", probaH); 
    fprintf(fp,"Probabilidad Road: $%.4f $ \\\\", probaV); 

    int i, j, k; 
    for(i = 0; i < tamanio_serie; i++){  
    	if(i == 0){ 
    		fprintf(fp,"Serie: %d , ", serie[i]); 
    	}  
    	else if(i == tamanio_serie-1){ 
    		fprintf(fp,"%d ", serie[i]); 
    	} 
    	else{
    		fprintf(fp,"%d , ", serie[i]); 
    	}
    }
    fprintf(fp,"\\end{frame} \n");  

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{RESULTADO}\n"); 

	float usarproba1; 
	float usarproba2;
	int partido_actual;
	float proba2H = 1 - probaV; 
	float proba2V = 1 - probaH;  
	//printf("ProbaH %e \n", probaH);
	//printf("Serie %d \n", serie[0]); 
	//printf("Serie %d \n", serie[1]); 

	fprintf(fp,"\\begin{table}\n ");
    fprintf(fp,"\\begin{tabular}{"); 
    for(i=0; i<=num_partidos;i++){
        if(i==0){
            fprintf(fp," c");
        }else{
            fprintf(fp," | c ");
        }//end else
    }//end for generador tabla
    fprintf(fp,"}\n \\\\  ");  

    for(i=0; i<=num_partidos;i++){
        if(i==0){
            fprintf(fp,"$%d$",i);
        }else{
            fprintf(fp," & $%d$  ",i);
        }//end if
    }//end for nombre de la matriz
    fprintf(fp,"\\\\ \n \\hline \\hline \n ");

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
				//printf("%4f | \b", resultado[i][j]); 
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


	for(i = 0; i <= num_partidos; i++){
		for(j = 0; j <= num_partidos; j++){ 
			if(i==0 && j==0){ 
				fprintf(fp, " ");
			}
			else if(j==0){
            	fprintf(fp,"$%.4f$",resultado[i][j]);
        	}else{
            	fprintf(fp," & $%.4f$  ",resultado[i][j]);
        	}//end if
		} 
		fprintf(fp," \\\\ \n "); 
	} 

	//fprintf(fp,"$%.4f$", resultado[num_partidos][num_partidos]);  
	fprintf(fp,"\\end{tabular}\n ");
    fprintf(fp,"\\end{table}\n ");
    fprintf(fp,"\\end{frame} \n");  


    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{RESULTADO FINAL}\n"); 
    fprintf(fp,"La probabilidad de que el equipo A gane es de $%.4f$. \\\\", resultado[num_partidos][num_partidos]); 

    fprintf(fp,"\\end{frame} \n"); 


    fprintf(fp,"\\end{document}");
    fclose(fp);
    system("pdflatex deportes.tex");
    system("evince --presentation deportes.pdf ");
}

/*
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
	deportesBeamer(num_partidos, probaH, probaV, serie, resultado, tamanio_serie);

}*/  
