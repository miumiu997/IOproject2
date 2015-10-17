#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "logicaMatrices.h"
#include <math.h>

int max(int a, int b) { return (a > b)? a : b; }
int min(int a, int b) { return (a < b)? a : b; }

int boundedknapSack(int top, int peso[], int valor[], int cantidad[], int numero,int**resultado,int**colores,int**sub)
{
    int i,j,Q;  
    
    int maximo;

    for (i = 0; i <= numero; i++)
    { 
        //printf("columna %d \n", i);
        for (j = 0; j <= top; j++)
        {
            //printf("fila %d \n", j); 

            if (i==0 || j==0) {                 
                resultado[i][j] = 0;
                colores[i][j] = 0;
                sub[i][j] = 0;
            }
            else if (peso[i-1] <= j) {  
                maximo = resultado[i-1][j];  
                Q = min(floor(j/peso[i-1]), cantidad[i-1]); 
                int k = 1; 
                int x = 0;
                while(k <= Q){ 
                    if (maximo < (k*valor[i-1] + resultado[i-1][j-(k*peso[i-1])]))
                    {
                        x = k;
                    }
                    maximo = max(maximo, k*valor[i-1] + resultado[i-1][j-(k*peso[i-1])]); 
                    k++; 
                } 
                sub[i][j] = x; 
                if (x!=0)
                {
                    colores[i][j] = 1;
                }
                else{
                    colores[i][j] = 0;
                }
                resultado[i][j] = maximo; 
            }
            else {
                resultado[i][j] = resultado[i - 1][j];
                colores[i][j] = 0;
                sub[i][j] = 0;
            }
        }
    }
} 

int unboundedknapSack(int top, int peso[], int valor[], int numero,int** resultado,int**colores,int**sub)
{
    int i,j,Q;  
    
    int maximo;

    for (i = 0; i <= numero; i++)
    { 
        //printf("columna %d \n", i);
        for (j = 0; j <= top; j++)
        {

            //printf("fila %d \n", j); 

            if (i==0 || j==0) {                 
                resultado[i][j] = 0;
                colores[i][j] = 0;
                sub[i][j] = 0;
            }
            else if (peso[i-1] <= j) {  
                maximo = resultado[i-1][j];  
                Q = floor(j/peso[i-1]); 
                int k = 1; 
                int x = 0;
                while(k <= Q){ 

                    if (maximo < (k*valor[i-1] + resultado[i-1][j-(k*peso[i-1])]))
                    {
                        x = k;
                    }
                    maximo = max(maximo, k*valor[i-1] + resultado[i-1][j-(k*peso[i-1])]); 
                    
                    k++; 
                } 
                //printf("%d\n", x);
                sub[i][j] = x; 
                if (x!=0)
                {
                    colores[i][j] = 1;
                }
                else{
                    colores[i][j] = 0;
                }

                resultado[i][j] = maximo; 
            }
            else {
                resultado[i][j] = resultado[i - 1][j];
                colores[i][j] = 0;
                sub[i][j] = 0;
            }
        }
    }
}

int knapSackBeamer(int** resultado,int max, int numero, int** colores){
    FILE* fp;
    int i,j;

    fp = fopen("knapSack.tex", "w");


    fprintf(fp,"\\documentclass[10]{beamer} \n");
    fprintf(fp,"\\usepackage[T1]{fontenc} \n");
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
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{ALGORITMO DE LA MOCHILA - KNAPSACK  }} \\\\ \\vspace{0.02cm} \n");
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
    fprintf(fp,"\\frametitle{ALGORITMO DE LA MOCHILA}\n");
    fprintf(fp,"El algoritmo de Floyd-Warshall, descrito en 1959 por Bernard Roy.\n");
    fprintf(fp,"\\\\Es un algoritmo de análisis sobre grafos para encontrar el camino mínimo en grafos dirigidos ponderados.\n"); 
    fprintf(fp,"\\\\El algoritmo encuentra el camino entre todos los pares de vértices en una única ejecución.\n");
    fprintf(fp,"\\\\ El algoritmo de Floyd-Warshall es un ejemplo de programación dinámica.\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{ROBERT W. FLOYD}\n");
    fprintf(fp,"\\\\Cient\\'ifico de la computaci\\'on USA (1936-2001)\\\\\n");
    fprintf(fp,"Bachiller en Artes Liberales y F\\'isica. \\\\ Operador de computadoras (1960). \\\\ Gan\\'o un premio Turing en 1978.\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\frame{\\frametitle{knapSack}\n ");
    fprintf(fp,"\\begin{center}\n ");
    fprintf(fp,"\\begin{tabular}{|");
    for ( i = 0; i <= numero; ++i)
    {
        fprintf(fp,"l |");
    }

    fprintf(fp,"} \\hline\n");

    
    for (i = 0; i <= max; i++) {
        for (j = 1; j <= numero; j++) {
            if (colores[j][i]==0)
            {
                fprintf(fp,"\\color{red}");
            }
            else{
                fprintf(fp,"\\color{green}");
            }
            fprintf(fp,"%d",resultado[j][i]);
            if (j==numero)
            {
                fprintf(fp,"\\\\ \\hline\n");
            }
            else{
                fprintf(fp,"&");
            }
        }
    }

    fprintf(fp,"\\end{tabular}\n");
    fprintf(fp,"\\end{center}\n ");
    fprintf(fp,"}\n");
    fprintf(fp,"\\end{document}");
    fclose(fp);
    system("pdflatex knapSack.tex");

}