#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "logicaArbolesB.h"
#include <math.h>


int ArbolesBBeamer(void){
    FILE* fp;
    fp = fopen("arbolesB.tex", "w");


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
   
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\end{document}");
    fclose(fp);
    system("pdflatex arbolesB.tex");
    system("evince --presentation arbolesB.pdf ");

}

void main(){
	ArbolesBBeamer();
}