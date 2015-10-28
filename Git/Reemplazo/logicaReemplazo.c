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
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{ALGORITMO PARA REEMPLAZO \\\\ DE EQUIPOS  }} \\\\ \\vspace{0.02cm} \n");
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
    fprintf(fp,"\\frametitle{FUNCIONAMIENTO}\n");
    fprintf(fp,"El empleo del an\\'alisis de reemplazo de equipo nos muestra \n");
    fprintf(fp,"\\\\una categor\\'ia de decisiones de inversi\\'on que implica \n"); 
    fprintf(fp,"\\\\considerar el gasto necesario para reemplazar equipo \n");
    fprintf(fp,"\\\\ desgastado u obsoleto por tecnolog\\'ia de punta que permita\n");
    fprintf(fp,"\\\\ mejorar la eficiencia de la producci\\'on y elevar el \\'indice de \n");
    fprintf(fp,"\\\\ productividad.\n");
    fprintf(fp,"\\end{frame} \n"); 

    fprintf(fp,"\\frame{\\frametitle{Reemplazo de Equipos}\n ");
    fprintf(fp,"\\color{white}\n");
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
        	if(j == 0){ 
        		fprintf(fp,"%d",proximo[i][j]);
        	} 
        	else{  
        		fprintf(fp,", %d",proximo[i][j]);

        	}
            j++;
        }

        fprintf(fp,"\\\\ \\hline\n");
    }

    fprintf(fp,"\\end{tabular}\n");
    fprintf(fp,"\\end{center}\n ");
    fprintf(fp,"}\n");

    fprintf(fp,"\\frame{\\frametitle{Rutas Optimas}\n "); 
 	fprintf(fp,"\\color{white}\n");

    int* resultado=(int*)calloc(plazo+1, sizeof(int));

    rutasAux(0,proximo,0,plazo,resultado,fp);

    fprintf(fp,"}\n");

    fprintf(fp,"\\end{document}");
    fclose(fp);
    system("pdflatex equipment.tex");
    system("evince --presentation equipment.pdf");	
	
}

int rutasAux(int anterior, int** array,int sub,int max,int*aux,FILE* fp){
    int i=0; 
    int k=0;
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
                	if(k == 0){ 
                		fprintf(fp," %d ",aux[j]); 
                	} 
                	else{  
                		fprintf(fp,"-%d ",aux[j]); 

                	}
                    k = k+1; 
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
