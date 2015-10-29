#include <stdio.h>
#include <stdlib.h>
#include "logicaArboles.h"

void arbolBinarioBusqueda(int cantidad, char** llaves, double* probablidades){
	int i,j;
	double **A = (double **)calloc(cantidad+1,sizeof(double *));
    for (i=0; i<cantidad+1; i++){
    	A[i] = (double *)calloc(cantidad+1,sizeof(double));
    }
         
    int **R = (int **)calloc(cantidad+1,sizeof(int *));
    for (i=0; i<cantidad+1; i++){
    	R[i] = (int *)calloc(cantidad+1,sizeof(int));
    }

	int imprimir = cantidad;
	int k = 2;
	
	for (i = 0; i < cantidad; ++i)
	{
		A[i][i+1] = probablidades[i];
		R[i][i+1] = i+1;

	}
    cantidad--;
    while (cantidad != 0){
    	for (i = 0; i < cantidad; ++i)
		{
			int pum = k-1;
			double* pumpumpum=(double*)calloc(k, sizeof(double));
			int* ks=(int*)calloc(k, sizeof(int));
			int cosa = i+k;
			int mover = i;
			double proba = 0.0;
			for (j = i; j < i+k; ++j)
			{
				proba = proba + probablidades[j];
			}
			for (j = i; j < i+k; ++j)
			{
				pumpumpum[pum] = A[mover][j]+A[cosa-(imprimir-cantidad)][i+k] + proba;
				ks[pum] = j+1;

				printf("k = %d, %f\n",ks[pum],pumpumpum[pum] );

				cosa++;
				pum--;
			}
			double final = pumpumpum[0];
			int sub = ks[0];
			for (j = 0; j < k; ++j)
			{
				if (final > pumpumpum[j])
				{
					final = pumpumpum[j];
					sub = ks[j];
				}
			}
			A[i][i+k] = final;
			R[i][i+k] = sub;

		}
		cantidad--;
		k++;
    }


	for (i = 0; i < imprimir+1; i++) {
        for (j = 0; j < imprimir+1; j++) {
            printf("%d ",R[i][j]);
        }
        printf("\n");
    }

    arbol(imprimir,llaves,R);

    //ArbolesBBeamer(imprimir,llaves,probablidades,A,R);

    return 0;
}

void arbol(int cantidad, char** llaves, int** R){
	printf("root:\n");
	arbolAUX(cantidad,1,cantidad,llaves,R);

}

int arbolAUX(int cantidad, int desde, int hasta, char** llaves, int** R){
	if (desde == hasta)
	{
		int entrada = R[desde-1][hasta];
		printf("%d -> {\n", entrada);
		return 0;
	}
	else{
		int entrada = R[desde-1][hasta];
		printf("%d -> {\n", entrada);

		arbolAUX(cantidad, entrada+1, cantidad, llaves, R);
		printf(",,,,\n");
		arbolAUX(cantidad, 1, entrada-1, llaves, R);
	}
}

void ordenarPalabras(int cantidad ,char** llaves,double* probablidades){

	char temp[99];

	double tempP;

    int i, j, n;
	for (i = 0; i < cantidad - 1 ; i++)
    {
        for (j = i + 1; j < cantidad; j++)
        {
            if (strcmp(llaves[i], llaves[j]) > 0)
            {
                strcpy(temp, llaves[i]);
                tempP = probablidades[i];

                strcpy(llaves[i], llaves[j]);
                probablidades[i] = probablidades[j];

                strcpy(llaves[j], temp);
                probablidades[j] = tempP;

            }
        }
    }
}

void ArbolesBBeamer(int cantidad,char** llaves,double* probablidades,double** A,int** R){
    FILE* fp;
    fp = fopen("arbolesB.tex", "w");
    int i,j;


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
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{ALGORITMO DE A\\'RBOLES BINARIOS DE \\\\ B\\'USQUEDAS \\'OPTIMAS  }} \\\\ \\vspace{0.02cm} \n");
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
    fprintf(fp,"\\frametitle{ALGORITMO DE A\\'RBOLES BINARIOS DE B\\'USQUEDAS \\'OPTIMAS}\n");
    fprintf(fp,"Tambi\\'en llamados BST (acr\\'onimo del ingl\\'es Binary Search Tree).\n");
    fprintf(fp,"\\\\ Tipo particular de \\'arbol binario que presenta una estructura de datos en forma de \\'arbol .\n"); 
    fprintf(fp,"\\\\Un \\'arbol binario no vac\\'io, de ra\\'iz R.\n");
    fprintf(fp,"\\\\ Existe una relaci\\'on de orden establecida entre los elementos de los nodos.\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{CONDICIONES DE UN \\'ARBOL BINARIO}\n");
    fprintf(fp,"En caso de tener sub\\'arbol izquierdo, la ra\\'iz R debe ser mayor que el valor m\\'aximo almacenado en el sub\\'arbol izquierdo, y que el sub\\'arbol izquierdo sea un \\'arbol binario de b\\'usqueda.\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{CONDICIONES DE UN \\'ARBOL BINARIO - CONT}\n");
    fprintf(fp,"En caso de tener sub\\'arbol derecho, la ra\\'iz R debe ser menor que el valor m\\'inimo almacenado en el sub\\'arbol derecho, y que el sub\\'arbol derecho sea un \\'arbol binario de b\\'usqueda.\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{PRINCIPIO DE OPTIMALIDAD}\n");
    fprintf(fp,"Todos los sub\\'arboles de un \\'arbol \\'optimo son \\'optimos con respecto a las claves que contienen.\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\\frametitle{VALORES INICIALES}\n ");
    fprintf(fp,"\\color{white}\n");

    fprintf(fp,"\\begin{table}[H]\n");
    fprintf(fp,"\\centering\n");
    fprintf(fp,"\\caption{VALORES INICIALES}\n");
    fprintf(fp,"\\label{my-label}\n");
    fprintf(fp,"\\begin{tabular}{|l|l|}\n");
    fprintf(fp,"\\hline\n");

    for (i = 0; i < cantidad; ++i)
    {
    	fprintf(fp," %s & %.02f \\\\ \\hline\n",llaves[i],probablidades[i]);
    	printf(" %s & %f \\\\ \\hline\n",llaves[i],probablidades[i]);
    }

    fprintf(fp,"\\end{tabular}\n");
    fprintf(fp,"\\end{table} \n");
    fprintf(fp,"\\end{frame} \n");


    fprintf(fp,"\\begin{frame}\\frametitle{Tabla A}\n ");
    fprintf(fp,"\\color{white}\n");

    fprintf(fp,"\\begin{table}[H]\n");
    fprintf(fp,"\\centering\n");
    fprintf(fp,"\\caption{A}\n");
    fprintf(fp,"\\label{A}\n");


    fprintf(fp,"\\begin{tabular}{|");
    for (i = 0; i < cantidad+1; ++i)
    {
    	fprintf(fp,"l|");
    }
    fprintf(fp,"}\n");


    fprintf(fp,"\\hline\n");

    for (i = 0; i < cantidad+1; ++i)
    {
    	for (j = 0; j < cantidad+1; ++j)
    	{
    		if (j == 0)
    		{
    			fprintf(fp,"%.02f",A[i][j]);
    		}
    		else
    		{
    			fprintf(fp,"& %.02f",A[i][j]);
    		}
    	}
    	fprintf(fp,"\\\\ \\hline\n");
    }

    fprintf(fp,"\\end{tabular}\n");
    fprintf(fp,"\\end{table} \n");
    fprintf(fp,"\\end{frame} \n");


        fprintf(fp,"\\begin{frame}\\frametitle{Tabla R}\n ");
    fprintf(fp,"\\color{white}\n");

    fprintf(fp,"\\begin{table}[H]\n");
    fprintf(fp,"\\centering\n");
    fprintf(fp,"\\caption{R}\n");
    fprintf(fp,"\\label{R}\n");


    fprintf(fp,"\\begin{tabular}{|");
    for (i = 0; i < cantidad+1; ++i)
    {
    	fprintf(fp,"l|");
    }
    fprintf(fp,"}\n");


    fprintf(fp,"\\hline\n");

    for (i = 0; i < cantidad+1; ++i)
    {
    	for (j = 0; j < cantidad+1; ++j)
    	{
    		if (j == 0)
    		{
    			fprintf(fp,"%d",R[i][j]);
    		}
    		else
    		{
    			fprintf(fp,"& %d",R[i][j]);
    		}
    	}
    	fprintf(fp,"\\\\ \\hline\n");
    }

    fprintf(fp,"\\end{tabular}\n");
    fprintf(fp,"\\end{table} \n");
    fprintf(fp,"\\end{frame} \n");


    fprintf(fp,"\\end{document}");
    fclose(fp);
    system("pdflatex arbolesB.tex");
    system("evince --presentation arbolesB.pdf ");
    return 0;
}