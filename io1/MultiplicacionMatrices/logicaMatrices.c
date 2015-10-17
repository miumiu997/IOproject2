#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "logicaMatrices.h"
#include <math.h>


void llenarDimensiones(char* nameMat,int nMatrices ,int** matrices){
    /*
    Se llenan las dimensiones de cada matriz.
    [0] corresponde a las filas
    [1] corresponde a columnas
    **/
    int i;
    int j;
    for(i=0; i<nMatrices;i++){
        printf("Filas de M[%d]\n",i );
        scanf("%d",&matrices[i][0]);
        printf("Columnas de M[%d]\n",i );
        scanf("%d",&matrices[i][1]);
    }
    printf("Nombre de la matriz %s\n",nameMat );
    int num;
    scanf("%d",num);
    MatricesBeamer(nameMat,nMatrices,matrices);
}// end LlenarDimensiones

int MatricesBeamer(char* nameMat, int nMatrices, int** matrices){
    /*
    Genera el codigo beamer necesario para la estructuracion de la presentacion.
    Autores: Kathy Brenes, Miuyin Yong, Adrian Cubero.
    Creacion: 16/10/2015
    */
    FILE* fp;
    fp = fopen("matrices.tex", "w");


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
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{ALGORITMO PARA LA \\\\ MULTIPLICACI\\'ON DE MATRICES  }} \\\\ \\vspace{0.02cm} \n");
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
    fprintf(fp,"\\frametitle{ALGORITMO PARA LA MULTIPLICACI\\'ON DE DOS MATRICES}\n");
    fprintf(fp,"El n\\'umero de columnas de la primera deben ser iguales al n\\'umero de filas de la segunda.\n");
    fprintf(fp,"\\\\ Si las dimensiones de la primera son n * k la segunda debe ser k * m.\n");
    fprintf(fp,"\\\\ La matriz resultante es n * m.\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{PROPIEDADES DE LA MULTIPLICACI\\'ON DE MATRICES}\n");
    fprintf(fp,"Se realizan productos puntos entre vectores fila y vectores columna para encontrar cada entrada de la matriz resultante.\n");
    fprintf(fp,"\\\\ No es conmutativa.\n"); 
    fprintf(fp,"\\\\Un \\'arbol binario no vac\\'io, de ra\\'iz R.\n");
    fprintf(fp,"\\\\ Total de multiplicaciones requeridas? \\\\ n*k*m  \\\\ \\t con $M_1:n*k; M_2: k*m$.\n");
    fprintf(fp,"\\end{frame} \n");


    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{MULTIPLICACI\\'ON EN CADENA}\n");
    fprintf(fp,"Se pueden multiplicar varias matrices en sucesi\\'on.\n");
    fprintf(fp,"\\\\ No es conmutativa, pero si asociativa, es decir, se puede hacer las multiplicaciones en diversos \\'ordenes.\n"); 
    fprintf(fp,"\\\\ Distinto orden implica distinto costo.\n"); 
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\\frametitle{VALORES INICIALES}\n ");
    fprintf(fp,"\\color{white}\n");

    fprintf(fp,"\\begin{table}\n ");
    fprintf(fp,"\\begin{tabular}{");
     
    int i;
    for(i=0; i<nMatrices;i++){
        if(i==0){
            fprintf(fp," c");
        }else{
            fprintf(fp," | c ");
        }//end else
    }//end for generador tabla
    fprintf(fp,"}\n \\\\  ");
    //termina la cantidad de columnas que va tener la tabla
    //Imprimir nombres de variables
    
    for(i=0; i<nMatrices;i++){
        if(i==0){
            fprintf(fp,"$%s_%d$",nameMat,i);
        }else{
            fprintf(fp," & $%s_%d$  ",nameMat,i);
        }//end if
    }//end for nombre de la matriz
    fprintf(fp,"\\\\ \n \\hline \\hline \n ");

    //Imprimir las dimensiones de cada matriz
    for(i=0; i<nMatrices;i++){
        if(i==0){
            fprintf(fp,"$%dx%d$",matrices[i][0],matrices[i][1]);
        }else{
            fprintf(fp," & $%dx%d$  ",matrices[i][0],matrices[i][1]);
        }//end if
    }//end for nombre de la matriz
    fprintf(fp," \\\\ \n "); 

    //imprimir los d
    int dimensiones= nMatrices*2;
    i=0;
    while(i<dimensiones){
        if(i==0){
            fprintf(fp,"$d_%dxd_%d$",i,i+1);
        }else{
            fprintf(fp," & $d_%dxd_%d$  ",i,i+1);
        }//end if
        i=i+2;
    }//end for nombre de la matriz
    fprintf(fp," \n ");     
    fprintf(fp,"\\end{tabular}\n ");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\caption{Valores iniciales}\n ");
    fprintf(fp,"\\end{table}\n ");

    fprintf(fp,"\\end{frame} \n");
   
   
   

    fprintf(fp,"\\end{document}");
    fclose(fp);
    system("pdflatex matrices.tex");
    system("evince --presentation matrices.pdf ");

}

void main(){

    //Variables
    int nMatrices;
    int i; 
    char* c;
    printf("\n Nombre de las matrices\n");
    scanf("%s",&c);
    printf("NOmbres de la matriz %s\n",c );
    printf("\n nMatrices\n");
    scanf("%d",&nMatrices);
    printf("Matrices: %d\n",nMatrices );  
    int **matrices = (int **)calloc(nMatrices+1,sizeof(int *));
     for (i=0; i<nMatrices+1; i++){
      matrices[i] = (int *)calloc(3,sizeof(int));
    }
    llenarDimensiones(c,nMatrices,matrices);
	
}