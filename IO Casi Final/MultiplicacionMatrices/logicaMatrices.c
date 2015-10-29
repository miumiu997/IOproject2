#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "logicaMatrices.h"
#include <math.h>
int **tablaP;

void putParenthesisAux(int**P,int i,int j, char parenthesis[][10],int modo){
    printf("entre!!\n");
    char change[10];
    if (modo ==0){
        if (P[i+1][j]!=0){
            strcat(parenthesis[i],"(");
            strcat(parenthesis[P[i+1][j]],")(");
            
            strcpy (change,")");
            strcat(change,parenthesis[j]);
            strcpy(parenthesis[j],change);
            putParenthesisAux(P,i,P[i+1][j],parenthesis,0);
            putParenthesisAux(P,P[i+1][j]+1,j,parenthesis,1);
        
        }
    }else{
        if (P[i][j]!=0){
            strcat(parenthesis[P[i+1][j]],")(");
            strcat(parenthesis[i],"(");
            strcat(parenthesis[j],")");
            putParenthesisAux(P,i,P[i+1][j],parenthesis,0);
            putParenthesisAux(P,P[i+1][j]+1,j,parenthesis,1);
        
        }
    }
    
}

void putParenthesis(int **P,int numMatrices){
    printf("entre!!principal\n");
    printf("%d\n",P[1][numMatrices] );
    char parenthesis[numMatrices+1][10];
    int* matrices;
    int i;
    char **resultado;
    resultado = calloc(1024,sizeof(char*));
    //parenthesis = calloc(numMatrices+1,10*sizeof(char*));
    matrices = calloc(numMatrices,sizeof(int));

    for (i = 0; i < numMatrices;i++){
        matrices[i] = i+1;
    }

    for (i = 0; i < numMatrices+1;i++){
        strcpy (parenthesis[i],"");
    }

    strcat(parenthesis[P[1][numMatrices]],")(");
    strcat(parenthesis[0],"(");
    strcat(parenthesis[numMatrices],")");


    putParenthesisAux(P,0,P[1][numMatrices],parenthesis,0);
    putParenthesisAux(P,P[1][numMatrices]+1,numMatrices,parenthesis,1);

    
    
    for (i = 0; i < numMatrices;i++){
        printf("%s %d",parenthesis[i],matrices[i]);
    }
    printf("%s\n",parenthesis[numMatrices] );


}


int calcularEntradaD(int nMatrices,int* dimensiones,int fila,int k,int columna){
	/** Permite calcular las entradas de la tabla M,
	donde j=i+1
	*/
	int valor=1;
	valor= dimensiones[fila]*dimensiones[k]*dimensiones[columna];
	
	tablaP[k][columna]=k;
	printf("tablaP[%d][%d]=[%d]",k,columna,k);
	//printf("Sali del ciclo, VALOR ES %d\n",valor);
	return valor;

}//end calcularDImensiones

int calcularMinEntrada(int** numeros,int* dimensiones,int fila, int k,int columna){
	int valor=1;
	int contValor=1;
	int **valores = (int **)calloc(columna+2,sizeof(int *));
	int a=0;
    for (a=0; a<columna+2; a++){
      valores[a] = (int *)calloc(columna+2,sizeof(int));
    }
	int i=k;
	for(i=k;i<columna;i++){
		printf("Para [%d][%d]= Valores [%d, %d]%d, %d [%d,%d]\n", k,columna,k,i,numeros[k][i],numeros[i+1][columna],i+1,columna );
		valores[contValor][0]=i;
		valores[contValor][1]=numeros[k][i]+numeros[i+1][columna]+(dimensiones[k-1]*dimensiones[i]*dimensiones[columna]);
		printf("K vale %d, EL primer valor es de %d\n",i,valores[contValor][1] );
		contValor=contValor+1;
	}

	valor=minValor(valores,contValor,k,columna);
	printf("El valor total es de %d se toman d_%d con %d, d_%d con %d,d_%d con %d\n",valor, fila,dimensiones[fila],k,dimensiones[k],columna,dimensiones[columna]);
	return valor;
}

int minValor(int **numeros, int nNumeros,int fila,int columna){

	int b=0;
	printf("Arreglo para buscar el menor\n");
	for(b=1;b<nNumeros;b++){
		printf(" Valor= %d, k=%d \n",numeros[b][1],numeros[b][0] );
	}
	
	int menor=0;
	int i;
	menor=numeros[1][1];
	int p=numeros[1][0];
	for(i=1;i<nNumeros;i++){
		if(numeros[i][1]<menor){
			menor=numeros[i][1];
			p=numeros[i][0];
		}
	}
	printf("TablaP[%d][%d]=%d\n",fila,columna,p);
	tablaP[fila][columna]=p;
	return menor;


}

void crearTablaM(char* nameMat,int nMatrices,int** matrices ,int* dimensiones){
	printf("Entre a crear tabla M\n");
	int **tablaM = (int **)calloc(nMatrices+2,sizeof(int *));
	int a=0;
    for (a=0; a<nMatrices+2; a++){
      tablaM[a] = (int *)calloc(nMatrices+2,sizeof(int));
    }
      
    int b=1;
    a=1;
    for (a=1; a<nMatrices+1; a++){
    	for(b=1; b<nMatrices+1; b++){
      		tablaM[a][b] = 0;
      	}
    }


    printf("Imprimir tabla M\n");
     b=1;
    a=1;
    for (a=1; a<nMatrices+1; a++){
    	for(b=1; b<nMatrices+1; b++){
      		printf("%d",tablaM[a][b]);
      	}
    }
   printf("Voy a empezar a generar la tabla\n");
   int i=1;
    int j=1;
    int valor=0;
    for (i=1; i<nMatrices+1; i++){
    	printf("i va por %d\n",i );
    	for(j=1; j<nMatrices+1; j++){
    		printf("j va por %d\n",j );
    		if(i==j){
    			printf("entre a i==j\n");
    			tablaM[i][j]=0;
    			printf("pase asignacion\n");
    			//tablaP[i][j]=0;
    			printf("TablaM[%d][%d]: %d TablaP[%d][%d]:%d",i,j,tablaM[i][j],i,j,tablaP[i][j]);
    			//printf("llene las diagonales hasta i=%d y j=%d\n",i,j );
    		}else if(j==i+1){
    			printf("entre a j=i+1\n");
    			valor=calcularEntradaD(nMatrices,dimensiones,i-1,i,j);
    			//printf("entre a calcularEntradaD valor es %d en i=%d y j=%d \n",valor,i,j);
    			tablaM[i][j]=valor;
    			printf("%d",tablaM[i][j]);
    			//printf("TablaM[i][j] tiene %d\n", tablaM[i][j] );
    		}else if(j!=i+1){
    			printf("j!=i+1\n");
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
 		fila=nMatrices;
    	while(0<fila){
    		if(fila<columna && columna!=fila && columna!=fila+1){    			
    			tablaM[fila][columna]=calcularMinEntrada(tablaM,dimensiones,fila-1,fila,columna);
    		}
    		fila=fila-1;
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

      printf("TablaP\n");

    for (i=1; i<nMatrices+1; i++){
    	for(j=1; j<nMatrices+1; j++){
    		printf(" %d ",tablaP[i][j]);
    		
    	}//end for columnas
      printf("\n");
    }//ennd for filas*/
    //putParenthesis(tablaP,nMatrices);
	printf("Voy al beamer\n");
    MatricesBeamer(nameMat,nMatrices,matrices,dimensiones,tablaM,tablaP);
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
    int *dimensiones = (int **)calloc(nMatrices+2,sizeof(int *));
    //matrices[6][2] = {{5,2},{2,3},{3,4},{4,6},{6,7},{7,8}};
   /*for(i=0; i<nMatrices;i++){
        printf("Filas de M[%d]\n",i );
        scanf("%d",&matrices[i][0]);
        printf("Columnas de M[%d]\n",i );
        scanf("%d",&matrices[i][1]);
    }*/

    printf("matrices\n");
    for(i=0; i<nMatrices;i++){
        printf("Filas de %d,0 es = %d\n",i,matrices[i][0] );
        printf("Filas de %d,1 es = %d\n",i,matrices[i][1] );
    }
    dimensiones= crearVDimensiones(dimensiones,nMatrices,matrices);

    printf("\nDimensiones\n");
    for(i=0; i<nMatrices+1;i++){
        printf("d_%d: %d\n",i, dimensiones[i]);
    }
    printf("NameMat %s\n",nameMat );
    tablaP=(int **)calloc(nMatrices+1,sizeof(int *));
     for (i=0; i<nMatrices+1; i++){      
      tablaP[i]= (int *)calloc(3,sizeof(int));
    }
    crearTablaM(nameMat,nMatrices,matrices ,dimensiones);
    
    
}// end LlenarDimensiones

void MatricesBeamer(char* nameMat, int nMatrices,int** matrices, int* dimensiones,int**matrizM,int**matrizP){
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
            fprintf(fp,"$%s_%d$",nameMat,i+1);
        }else{
            fprintf(fp," & $%s_%d$  ",nameMat,i+1);
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
   

    /////////////////////////////////////////////////
    /************************************************



			TABLA M



    ************************************************/
    fprintf(fp,"\\begin{frame}\\frametitle{TABLA M}\n ");
    fprintf(fp,"\\color{white}\n");

    fprintf(fp,"\\begin{table}\n ");
    fprintf(fp,"\\begin{tabular}{");
     
   /**Estructura de la tabla****/
    for(i=0; i<nMatrices+1;i++){
        if(i==0){
            fprintf(fp," c");
        }else{
            fprintf(fp," | c ");
        }//end else
    }//end for generador tabla
    fprintf(fp,"}\n \\\\  ");
    //termina la cantidad de columnas que va tener la tabla
    //Imprimir nombres de variables
    
    for(i=0; i<nMatrices+1;i++){
        if(i==0){
            fprintf(fp," ");
        }else{
            fprintf(fp," & %d  ", i);
        }//end if
    }//end for nombre de la matriz
    fprintf(fp,"\\\\ \n \\hline \\hline \n ");

    //Imprimir los valores de la tabla M
    int j=0;
    for(i=0; i<nMatrices+1;i++){
	    for(j=0; j<nMatrices+1;j++){
	        if(j==0){
	            fprintf(fp," %d ",i+1);
	        }else if(j<i+1){
	        	fprintf(fp," & ");
	        }else{
	            fprintf(fp,"& %d", matrizM[i+1][j]);
	        }	        
	    }//end for nombre de la matriz*/
	 fprintf(fp," \\\\ \n "); 
	}//end primer for
    
    
    fprintf(fp," \n ");     
    fprintf(fp,"\\end{tabular}\n ");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\caption{Tabla M}\n ");
    fprintf(fp,"\\end{table}\n ");

    fprintf(fp,"\\end{frame} \n");


    //////////////////////////////////////////////////////////////////
    /*****************TABLA P***********************/


    /* ************************************************/
    fprintf(fp,"\\begin{frame}\\frametitle{TABLA P}\n ");
    fprintf(fp,"\\color{white}\n");

    fprintf(fp,"\\begin{table}\n ");
    fprintf(fp,"\\begin{tabular}{");
     
   /**Estructura de la tabla****/
    for(i=0; i<nMatrices+1;i++){
        if(i==0){
            fprintf(fp," c");
        }else{
            fprintf(fp," | c ");
        }//end else
    }//end for generador tabla
    fprintf(fp,"}\n \\\\  ");
    //termina la cantidad de columnas que va tener la tabla
    //Imprimir nombres de variables
    
    for(i=0; i<nMatrices+1;i++){
        if(i==0){
            fprintf(fp," ");
        }else{
            fprintf(fp," & %d  ", i);
        }//end if
    }//end for nombre de la matriz
    fprintf(fp,"\\\\ \n \\hline \\hline \n ");

    //Imprimir los valores de la tabla M
    j=0;
    for(i=0; i<nMatrices+1;i++){
	    for(j=0; j<nMatrices+1;j++){
	        if(j==0){
	            fprintf(fp," %d ",i+1);
	        }else if(j<i+2){
	        	fprintf(fp," & ");
	        }else{
	            fprintf(fp,"& %d", matrizP[i+1][j]);
	        }	        
	    }//end for nombre de la matriz*/
	 fprintf(fp," \\\\ \n "); 
	}//end primer for
    
    
    fprintf(fp," \n ");     
    fprintf(fp,"\\end{tabular}\n ");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\caption{Tabla P}\n ");
    fprintf(fp,"\\end{table}\n ");

    fprintf(fp,"\\end{frame} \n");


    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{SOLUCI\\'ON FINAL}\n");
    fprintf(fp,"El n\\'umero m\\'inimo de multiplicacines es de %d.\n",matrizM[1][nMatrices]);
    fprintf(fp,"\\end{frame} \n");


    fprintf(fp,"\\end{document}");
    fclose(fp);
    system("pdflatex matrices.tex");
    system("evince --presentation matrices.pdf ");

}

/*void main(){

    //Variables
    int nMatrices;
    int i; 
    char c[50];
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

    
    //matrices[6][2] = {{5,2},{2,3},{3,4},{4,6},{6,7},{7,8}};

    
    llenarDimensiones(c,nMatrices,matrices);
	
}*/