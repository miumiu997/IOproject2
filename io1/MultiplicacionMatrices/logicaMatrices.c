#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "logicaMatrices.h"
#include <math.h>

int calcularEntradaD(int nMatrices,int* dimensiones,int fila,int k,int columna){
	/** Permite calcular las entradas de la tabla M,
	donde j=i+1
	*/
	int valor=1;
	valor= dimensiones[fila]*dimensiones[k]*dimensiones[columna];
	//printf("Sali del ciclo, VALOR ES %d\n",valor);
	return valor;

}//end calcularDImensiones

int calcularMinEntrada(){
	
}

void crearTablaM(char* nameMat,int nMatrices,int** matrices ,int* dimensiones){
	
	int **tablaM = (int **)calloc(nMatrices+2,sizeof(int *));
	int a=0;
    for (a=0; a<nMatrices+2; a++){
      tablaM[a] = (int *)calloc(nMatrices+2,sizeof(int));
    }
    int **tablaP = (int **)calloc(nMatrices+1,sizeof(int *));
     for (a=0; a<nMatrices; a++){
      tablaP[a] = (int *)calloc(2,sizeof(int));
    }

    printf("Antes de llenar la matriz\n");
    int b=1;
    a=1;
    for (a=1; a<nMatrices+1; a++){
    	for(b=1; b<nMatrices+1; b++){
      		tablaM[a][b] = 0;
      	}
    }
    printf("llene la matriz\n");

   int i=1;
    int j=1;
    int valor=0;
    for (i=1; i<nMatrices+1; i++){
    	for(j=1; j<nMatrices+1; j++){
    		if(i==j){
    			tablaM[i][j]=0;
    			printf("%d",tablaM[i][j]);
    			//printf("llene las diagonales hasta i=%d y j=%d\n",i,j );
    		}else if(j==i+1){
    			valor=calcularEntradaD(nMatrices,dimensiones,i-1,i,j);
    			//printf("entre a calcularEntradaD valor es %d en i=%d y j=%d \n",valor,i,j);
    			tablaM[i][j]=valor;
    			printf("%d",tablaM[i][j]);
    			//printf("TablaM[i][j] tiene %d\n", tablaM[i][j] );
    		}else if(j!=i+1){
    			//printf("estoy entrando al uno con i=%d y j=%d\n",i,j);
    			tablaM[i][j]=1;
    			printf("%d",tablaM[i][j]);
    		}
    	}//end for columnas
      printf("\n");
    }//ennd for filas*/
    

    //Empiezo a llenar los valores de la tabla que dependen de 
    // los valores i=j o j=i+1
    printf("entre a otros valores\n");
 	//int columnaGeneral=1;
 	int fila=1;
 	int columna=1;
 	//X funcionan como las filas
 	while(columna<nMatrices+1){
 		fila=1;
    	while(fila<=nMatrices+1){
    		if(fila<columna && columna!=fila && columna!=fila+1){
    			printf("entre a i=%d j=%d\n",fila,columna );
    			tablaM[fila][columna]=99;
    		}else{
    			printf("me salte la entrada [%d][%d]\n",fila,columna);
    		}
    		fila=fila+1;
    	}
    	columna=columna+1;
    }//ennd for filas*/
    printf("sali de otros valores\n");

    for (i=1; i<nMatrices+1; i++){
    	for(j=1; j<nMatrices+1; j++){
    		printf("%d",tablaM[i][j]);
    		
    	}//end for columnas
      printf("\n");
    }//ennd for filas*/
    
	printf("Voy al beamer\n");
    //MatricesBeamer(nameMat,nMatrices,matrices,dimensiones,tablaM);
}
int* crearVDimensiones(int *dimensiones,int nMatrices ,int** matrices){
	/*FUncion que permite llenar el vector con las dimensiones de cada
	matriz
	*/
	int i=0;
	int nDimensiones=0;
	for (i = 0; i < nMatrices; i++)
	{
		/* code */
		if(i==0){
			dimensiones[nDimensiones]=matrices[i][0];
		}
		nDimensiones++;
		dimensiones[nDimensiones]=matrices[i][1];
		
	}
	return(dimensiones);
}//end CrearVDimensiones

void llenarDimensiones(char* nameMat,int nMatrices ,int** matrices){
    /*
    Se llenan las dimensiones de cada matriz.
    [0] corresponde a las filas
    [1] corresponde a columnas

    Matrices contiene las dimensiones de cada matriz.
    **/
    int i;
    int j;
    int *dimensiones = (int **)calloc(nMatrices+2,sizeof(int *));
    //matrices[6][2] = {{5,2},{2,3},{3,4},{4,6},{6,7},{7,8}};
    for(i=0; i<nMatrices;i++){
        printf("Filas de M[%d]\n",i );
        scanf("%d",&matrices[i][0]);
        printf("Columnas de M[%d]\n",i );
        scanf("%d",&matrices[i][1]);
    }
    dimensiones= crearVDimensiones(dimensiones,nMatrices,matrices);

    printf("\nDimensiones\n");
    for(i=0; i<nMatrices+1;i++){
        printf("d_%d: %d\n",i, dimensiones[i]);
    }

    crearTablaM(nameMat,nMatrices,matrices ,dimensiones);
    //crearTablaM(nameMat,nMatrices,dimensiones);
    
}// end LlenarDimensiones

void MatricesBeamer(char* nameMat, int nMatrices,int** matrices, int* dimensiones,int**matrizM){
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
            fprintf(fp,"$%c_%d$",nameMat,i+1);
        }else{
            fprintf(fp," & $%c_%d$  ",nameMat,i+1);
        }//end if
    }//end for nombre de la matriz
    fprintf(fp,"\\\\ \n \\hline \\hline \n ");

    //Imprimir las dimensiones de cada matriz
    for(i=0; i<nMatrices;i++){
        if(i==0){
            fprintf(fp,"$%dx%d$",dimensiones[i],dimensiones[i+1]);
        }else{
            fprintf(fp,"& $%dx%d$", dimensiones[i],dimensiones[i+1]);
        }
        
    }//end for nombre de la matriz*/
    fprintf(fp," \\\\ \n "); 

    //imprimir las letras con su repectivo indice dimensiones
    i=0;
    while(i<nMatrices){
    	if(i==0){
    		fprintf(fp," $d_%dxd_%d$",i,i+1);
    	}else{
        	fprintf(fp,"& $d_%dxd_%d$",i,i+1);
        }
        i=i+1;
    }//end for nombre de la matriz
    fprintf(fp," \n ");     
    fprintf(fp,"\\end{tabular}\n ");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\caption{Valores iniciales}\n ");
    fprintf(fp,"\\end{table}\n ");

    fprintf(fp,"\\end{frame} \n");
   
   
    fprintf(fp,"\\begin{frame}\\frametitle{Tabla M}\n ");
    fprintf(fp,"\\color{white}\n");

    fprintf(fp,"\\begin{table}\n ");
    fprintf(fp,"\\begin{tabular}{");

    i=0;
    for(i=0; i<nMatrices+1;i++){
        if(i==0){
            fprintf(fp," c");
        }else{
            fprintf(fp," | c ");
        }//end else
    }//end for generador tabla
    fprintf(fp,"}\n \\\\  ");

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
    scanf("%c",&c);
    printf("NOmbres de la matriz %c\n",c );
    printf("\n nMatrices\n");
    scanf("%d",&nMatrices);
    printf("Matrices: %d\n",nMatrices );  
    int **matrices = (int **)calloc(nMatrices+1,sizeof(int *));
     for (i=0; i<nMatrices+1; i++){
      matrices[i] = (int *)calloc(3,sizeof(int));
    }
    //matrices[6][2] = {{5,2},{2,3},{3,4},{4,6},{6,7},{7,8}};

    llenarDimensiones(c,nMatrices,matrices);
	
}