#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "logicaFloyd.h"
#include <math.h>

void leerFloyd(int cantidad,int** matriz){
    FILE *fp;
    fp = fopen("floyd", "r");
    char ch;

    char* palabra;
    int largo = 0;
    palabra = (char*)calloc(1, sizeof(char));   
    int i,j;

    //int matriz[cantidad][cantidad];
    for(i=0;i<cantidad;i++)
    {
        for(j=0;j<cantidad;j++)
            matriz[i][j] = 99;
    }

    int nodo1;
    int nodo2;

    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch == '\n' ){

            printf("%d",atoi(palabra));

            printf("\n");

            matriz[nodo1-1][nodo2-1] =atoi(palabra);

            largo=0;
            palabra = (char*) realloc(palabra,0);
        }
        else if (ch == '-'){
            fseek( fp, ftell(fp)-2, SEEK_SET );
            nodo1 = fgetc(fp)- '0';
            printf("nodo1:%d - ",nodo1);
            fgetc(fp);
            largo=0;
            palabra = (char*) realloc(palabra,0);
        }
        else if (ch == '='){
            fseek( fp, ftell(fp)-2, SEEK_SET );
            nodo2 = fgetc(fp)- '0';
            printf("nodo2:%d - ",nodo2);
            fgetc(fp);
            largo=0;
            palabra = (char*) realloc(palabra,0);
        }
        else{
            largo++;
            palabra = (char*) realloc(palabra,largo * sizeof(char));
            palabra[largo-1] = ch;

        }
    }


    for(i=0;i<cantidad;i++)
    {
        for(j=0;j<cantidad;j++)
            printf("%d \t",matriz[i][j]);
        printf("\n");
    }


    fclose(fp);
    printf("\n");

}


int rutasPAux(int x,int y,int **p,int* resultado,int largo,int sub,FILE*fp){
    int l,c;
    if (p[x][y] != 0)
    {
        int o = largo+1;
        resultado = (int*) realloc(resultado,o+1 * sizeof(int));

        for (c = largo ; c >= sub+1; c--)
            resultado[c+1] = resultado[c];

        resultado[sub+1] = p[x][y];

        int j;
        for (j = 0; j < o; ++j)
        {
            fprintf(fp,"%d-",resultado[j]);
        }
        fprintf(fp,"\n");
        fprintf(fp,"\\newline\n");


        l = rutasPAux(x,p[x][y]-1,p,resultado,o,sub,fp);
        rutasPAux(p[x][y]-1,y,p,resultado,l,sub+1,fp);
    }
    else{
        return largo;
    }
/*
    for (c = n - 1; c >= position - 1; c--)
      array[c+1] = array[c];

    array[position-1] = value;
*/

}


void floydK (int **routes, int order, int**p,FILE* fp){
    int k,i,j;

    for(i=0;i<order;i++)
    {
        for(j=0;j<order;j++)
            p[i][j]=0;
    }

    for (k = 0; k < order; ++k) {
        for (i = 0; i < order; ++i) {
            for (j = 0; j < order; ++j) {
                if (i==j){
                    routes[i][j]=0;
                    p[i][j] = 0;
                }
                else{
                    if (routes[i][k] + routes[k][j] < routes[i][j]){
                        routes[i][j] = routes[i][k] + routes[k][j];
                        p[i][j] = k+1;
                    }
                }
            }
        }
        fprintf(fp,"\\frame{\\frametitle{D%d}\n ",k+1); 
        fprintf(fp,"\\color{white}\n");
        fprintf(fp,"\\begin{center}\n ");
        fprintf(fp,"\\begin{tabular}{|");
        for ( i = 0; i < order; ++i)
        {
            fprintf(fp,"l |");
        }

        fprintf(fp,"} \\hline\n");

        for (i = 0; i < order; i++) {
            for (j = 0; j < order; j++) {
                fprintf(fp,"%d",routes[i][j]);
                if (j==order-1)
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
    }
}

void floyd (int **routes, int order, int**p){
    int k,i,j;

    for(i=0;i<order;i++)
    {
        for(j=0;j<order;j++)
            p[i][j]=0;
    }

    for (k = 0; k < order; ++k) {
        for (i = 0; i < order; ++i) {
            for (j = 0; j < order; ++j) {
                if (i==j){
                    routes[i][j]=0;
                    p[i][j] = 0;
                }
                else{
                    if (routes[i][k] + routes[k][j] < routes[i][j]){
                        routes[i][j] = routes[i][k] + routes[k][j];
                        p[i][j] = k+1;
                    }
                }
            }
        }
    }

    for(i=0;i<order;i++)
    {
        for(j=0;j<order;j++)
            printf("%d \t",routes[i][j]);
        printf("\n");
    }
    printf("\n");
    for(i=0;i<order;i++)
    {
        for(j=0;j<order;j++)
            printf("%d \t",p[i][j]);
        printf("\n");
    }  
}

void floydBeamer(int**zero, int**d,int**p,int order){


    FILE* fp;
    int i,j;

    fp = fopen("floyd.tex", "w");

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
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{ALGORITMO DE FLOYD }} \\\\ \\vspace{0.02cm} \n");
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
    fprintf(fp,"\\frametitle{ALGORITMO DE RUTAS M\\'AS CORTAS'}\n");
    fprintf(fp,"El algoritmo de Floyd-Warshall, descrito en 1959 por Bernard Roy.\n");
    fprintf(fp,"\\\\Es un algoritmo de an\\'alisis sobre grafos para encontrar el camino m\\'inimo en grafos dirigidos ponderados.\n"); 
    fprintf(fp,"\\\\El algoritmo encuentra el camino entre todos los pares de v\\'ertices en una \\'unica ejecuci\\'on.\n");
    fprintf(fp,"\\\\ El algoritmo de Floyd-Warshall es un ejemplo de programaci\\'on din\\'amica.\n");
    fprintf(fp,"\\end{frame} \n");


    fprintf(fp,"\\frame{\\frametitle{D0}\n "); 
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\begin{center}\n ");
    fprintf(fp,"\\begin{tabular}{|");
    for ( i = 0; i < order; ++i)
    {
        fprintf(fp,"l |");
    }

    fprintf(fp,"} \\hline\n");

    printf("d0\n");

    for (i = 0; i < order; i++) {
        for (j = 0; j < order; j++) {
            fprintf(fp,"%d",zero[i][j]);
            if (j==order-1)
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
    fprintf(fp,"\\frame{\\frametitle{DN}\n "); 
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\begin{center}\n ");
    fprintf(fp,"\\begin{tabular}{|");
    for ( i = 0; i < order; ++i)
    {
        fprintf(fp,"l |");
    }

    fprintf(fp,"} \\hline\n");
    printf("dn\n");


    for (i = 0; i < order; i++) {
        for (j = 0; j < order; j++) {
            fprintf(fp,"%d ",d[i][j]);
            if (j==order-1)
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
    fprintf(fp,"\\frame{\\frametitle{P}\n ");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\begin{center}\n ");
    fprintf(fp,"\\begin{tabular}{|");
    for ( i = 0; i < order; ++i)
    {
        fprintf(fp,"l |");
    }

    fprintf(fp,"} \\hline\n");
    printf("p\n");

    for (i = 0; i < order; i++) {
        for (j = 0; j < order; j++) {
            fprintf(fp,"%d",p[i][j]);
            if (j==order-1)
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

    fprintf(fp,"\\frame{\\frametitle{rutas}\n "); 
    fprintf(fp,"\\color{white}\n");
/*
    for (i = 0; i < order; ++i)
    {
        for (j = 0; j < order; ++j)
        {
            fprintf(fp,"nodo:%d - nodo:%d\n",i+1,j+1);
            fprintf(fp,"\\newline\n");

            int* resultado=(int*)calloc(2, sizeof(int));

            resultado[0]=i+1;
            resultado[1]=j+1;
            rutasPAux(resultado[0]-1,resultado[1]-1,p,resultado,2,0,fp);

        }
    }
*/
    fprintf(fp,"}\n");
    floydK (zero,order,p,fp);

    

    fprintf(fp,"\\end{document}");
    fclose(fp);
    system("pdflatex floyd.tex");
    system("evince --presentation floyd.pdf");
    return 0;
}
 