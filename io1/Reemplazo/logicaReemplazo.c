#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "logicaReemplazo.h"
#include <math.h>

int equipmentReplacement(int compra,int vidaUtil,int plazo,int mantenimiento[],int venta[],int*g,int**proximo){

    int i,j;
    int costo;  
    int costos[vidaUtil];
    
    for(i=0; i<vidaUtil; i++){
        costo = compra;
        for(j=0; j<=i; j++){
            costo += mantenimiento[j];
        }
        costo -= venta[i];
        
        costos[i]= costo;
    }

    g[plazo]=0;

    int c;
    printf("%d\n",plazo );
    for (i = plazo-1; 0 <= i; --i)
    {   
        int min = -1;
        for (j = 1; j <= vidaUtil; ++j)
        {
            c = costos[j-1] + g[i+j];

            if (min>=c || min == -1)
            {
                min = c;
            }
            if ((i+j) == plazo)
            {
                break;
            }
        }
        int cantidad = 1;
        for (j = 1; j <= vidaUtil; ++j)
        { 
            c = costos[j-1] + g[i+j];
            if (min==c)
            {   
                proximo[i] = (int *) realloc(proximo[i], cantidad * sizeof(int));
                proximo[i][cantidad-1]=i+j;
                cantidad++;
            }
            if ((i+j) == plazo)
            {
                break;
            }
        }

       g[i]=min; 

       printf("%d\n",min);
    }

}

void equipmentBeamer(int* g,int** proximo,int plazo){
    FILE* fp;
    int i,j;

    fp = fopen("equipment.tex", "w");

    fprintf(fp,"\\documentclass{beamer}\n");
    fprintf(fp,"\\usepackage{color}\n");
    fprintf(fp,"\\begin{document}\n");
    fprintf(fp,"\\title{Reemplazo de Equipos}\n ");
    fprintf(fp,"\\author{Kathy Brenes, Miuyin, Adrian Cubero}\n");
    fprintf(fp,"\\date{\\today}\n ");
    fprintf(fp,"\\frame{\\titlepage}\n ");
     fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{black}\n");
    fprintf(fp,"\\frametitle{Funcionamiento}\n");
    fprintf(fp,"El empleo del análisis de reemplazo de equipo nos muestra \n");
    fprintf(fp,"\\\\una categoría de decisiones de inversión que implica \n"); 
    fprintf(fp,"\\\\considerar el gasto necesario para reemplazar equipo \n");
    fprintf(fp,"\\\\ desgastado u obsoleto por tecnología de punta que permita\n");
    fprintf(fp,"\\\\ mejorar la eficiencia de la producción y elevar el índice de \n");
    fprintf(fp,"\\\\ productividad.\n");
    fprintf(fp,"\\end{frame} \n");
    fprintf(fp,"\\frame{\\frametitle{Reemplazo de Equipos}\n ");
    fprintf(fp,"\\begin{center}\n ");
    fprintf(fp,"\\begin{tabular}{|");
    for ( i = 0; i <= 3; ++i)
    {
        fprintf(fp,"l |");
    }

    fprintf(fp,"}\n \\hline\n");
    fprintf(fp," &G(T)&Proximo\\\\ \\hline\n");
    
    //printf("%d\n",g[0] );

    for (i = 0; i < plazo; ++i) {
        fprintf(fp,"%d&%d&",i,g[i]);
         j=0;
        while (proximo[i][j] != 0){
            fprintf(fp,"%d,",proximo[i][j]);
            j++;
        }

        fprintf(fp,"\\\\ \\hline\n");
    }

    fprintf(fp,"\\end{tabular}\n");
    fprintf(fp,"\\end{center}\n ");
    fprintf(fp,"}\n");

    fprintf(fp,"\\frame{\\frametitle{Rutas Optimas}\n ");

    int* resultado=(int*)calloc(plazo+1, sizeof(int));

    rutasAux(0,proximo,0,plazo,resultado,fp);

    fprintf(fp,"}\n");

    fprintf(fp,"\\end{document}");
    fclose(fp);
    system("pdflatex equipment.tex");
    system("evince --fullscreen equipment.pdf");	
	
}

int rutasAux(int anterior, int** array,int sub,int max,int*aux,FILE* fp){
    int i=0;
    while(array[sub][i] != 0){
        if (anterior > array[sub][i])
        {

        }
        else if (max == array[sub][i])
        {
            aux[sub] = array[sub][i];
            int j;
            for (j = 0; j < max; ++j)
            {
                if (aux[j] != 0)
                {
                    fprintf(fp,"%d-",aux[j]);
                }
            }
            fprintf(fp,"\\newline");
        }
        else{
            aux[sub] = array[sub][i];
            rutasAux(array[sub][i], array, sub+1,max,aux,fp);
        }
        i++;
    }
}
