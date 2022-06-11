#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Variables Globales//

int pos1, pos2, pos3;
const int tam = 9;

/*//*//*//*//*//*//*//*//*//*//*//*/

//Declaración de Funciones//

/// Inicializa el Sudoku 's' llenando todas las celdas con el valor 0.
void inicializar_sudoku (int s[][tam]);

/// Imprime el Sudoku en pantalla con un formato matricial mostrando la separación entre regiones.
void imprimir_sudoku (int s[][tam]);

///Genera aleatoriamente un nuevo Sudoku con la cantidad de elementos cant_elem
void generar_sudoku_valido (int s [9][9], int cant_elem);

///Recibe un numero y la linea y verifica si esta el numero en la linea
bool numEstaEnLaLinea(int numRandom, int lineaRandom, int s[][tam]);

///Recibe un numero y la linea y verifica si esta ese numero en la linea
bool numEstaEnLaColumn(int numRandom, int columnRandom, int s[][tam]);

///Ingreso un numero y en donde comienza la linea y la columna de una region, y devuelve si el numero esta en la region
bool numEstaEnLaRegion(int numRandom, int inicioLineReg, int inicioColumnReg, int s[][tam]);

///Ingreso una coordenada de region y devuelve la posicion inicial de esa region
int posicion_region(int num);

///Ingreso fila y columna y encuentra los candidatos para esa celda vacia
void crear_candidatos (int s[][9], int fila, int columna, bool candidatos[][tam][tam]);

///Devuelve true si ‘num’ es candidato para la celda del Sudoku ‘s’ dada por ‘fila’ y ‘columna’
bool es_candidato (int s [][9], int num, int fila, int columna, bool candidatos[][tam][tam]);

/*//*//*//*//*//*//*//*//*//*//*//*/


int main()
{
    srand(time(NULL));
    int sudoku[tam][tam], cantElemInicial;
    bool candidatos[tam][tam][tam];

    inicializar_sudoku(sudoku);
    printf("Cuantos elementos queres agregar?: ");
    scanf("%d", &cantElemInicial);
    generar_sudoku_valido(sudoku, cantElemInicial);
    imprimir_sudoku(sudoku);

    //Descomentar esto para probar la funcion crear_candidatos()
    /*int filaCandidatos, columnaCandidatos;
    printf("\nDe que lugar deseas saber los candidatos? 1 significa que es candidato, 0 significa que no lo es");
    printf("\nIngresa la fila: ");
    scanf("%d", &filaCandidatos);
    printf("Ingresa la columna: ");
    scanf("%d", &columnaCandidatos);
    crear_candidatos(sudoku, filaCandidatos, columnaCandidatos, candidatos);
    for(int i=1;i<=tam;i++)
        printf("%d: %d \n", i, candidatos[filaCandidatos][columnaCandidatos][i]);*/

    //Decomentar esto para probar la funcion es_candidato()
    /*int numCandidato, filaCandidato, columnaCandidato;
    bool esCandidato;
    printf("Que numero deseas saber si es candidato? 1 significa que lo es, 0 significa que no lo es");
    scanf("%d", &numCandidato);
    printf("De que fila?");
    scanf("%d", &filaCandidato);
    printf("De que columna?");
    scanf("%d", &columnaCandidato);
    esCandidato = es_candidato(sudoku, numCandidato, filaCandidato, columnaCandidato, candidatos);
    printf("%d es candidato?: %d", numCandidato, esCandidato);*/



    return 0;
}


/*//*//*//*//*//*//*//*//*//*//*//*/

// Definición de Funciones //

///Inicializa el Sudoku 's' llenando todas las celdas con el valor 0.
void inicializar_sudoku (int s[][tam]){


    for(pos1=0 ; pos1<tam ; pos1++)
        for(pos2=0 ; pos2<tam ; pos2++)
            s[pos1][pos2] = 0;
}

///Imprime el Sudoku en pantalla con un formato matricial mostrando la separación entre regiones.
void imprimir_sudoku (int s[][tam]){

    for(pos1=0 ; pos1<tam ; pos1++){
        for(pos2=0 ; pos2<tam ; pos2++){
            if(pos2 == 2 || pos2 == 5)
                printf(" %d |  |", s[pos1][pos2]);
            else
                printf(" %d |", s[pos1][pos2]);
        }
        if(pos1 == 2 || pos1 == 5)
                printf("\n\n");
            else
                printf("\n");
    }
}

///Genera aleatoriamente un nuevo Sudoku ‘s’ con la cantidad de elementos ‘cant_elem’.
void generar_sudoku_valido (int s[][tam], int cant_elem){

    int numRandom, lineRandom, columnRandom;
    bool numEnLinea, numEnColumna, numEnRegion;

    while(cant_elem > 0){

        //Lo repite hasta encontrar una combinacion valida
        do{
            numRandom = rand()%9+1;
            //Genera un nuevo numero y ubicacion random para cada pasada sin sobreescribir a menos que sea cero
            do{
                lineRandom = rand()%9;
                columnRandom = rand()%9;
            }while(s[lineRandom][columnRandom]!=0);

            numEnRegion = numEstaEnLaRegion(numRandom, lineRandom, columnRandom, s);

            if(numEnRegion){
                numEnLinea = true;
                numEnColumna = true;
            } else {
                numEnLinea = numEstaEnLaLinea(numRandom, lineRandom, s);
                numEnColumna = numEstaEnLaColumn(numRandom, columnRandom, s);
            }

        }while(numEnLinea != false || numEnColumna != false);

        s[lineRandom][columnRandom] = numRandom;
        cant_elem--;
    }
}

///Recibe un numero y la linea y verifica si esta el numero en la linea
bool numEstaEnLaLinea(int numRandom, int lineRandom, int s[][tam]){
    bool numEnLinea = false;

    for(int i=0 ; i<tam ; i++){
        if(s[lineRandom][i] == numRandom)
            numEnLinea = true;
    }
    return numEnLinea;
}

///Recibe un numero y la columna y verifica si esta ese numero en la columna
bool numEstaEnLaColumn(int numRandom, int columnRandom, int s[][tam]){
    bool numEnColumna = false;

    for(int i=0 ; i<tam ; i++){
        if(s[i][columnRandom] == numRandom)
            numEnColumna = true;
    }
    return numEnColumna;
}

///Ingreso una coordenada de region y devuelve la posicion inicial de esa region
int posicion_region(int num){

    int posInicial;

    switch(num){
        case  0: case 1: case 2:
            posInicial = 0;
        break;
        case 3: case 4: case 5:
            posInicial = 3;
        break;
        case 6: case 7: case 8:
            posInicial = 6;
        break;
    }

    return posInicial;
}

///Ingreso un numero y en donde comienza la linea y la columna de una region, y devuelve si el numero esta en la region
bool numEstaEnLaRegion(int numRandom, int line, int column, int s[][tam]){
    bool numEnRegion = false;

    //Primero obtengo el valor inicial de la region tanto de su fila como de su columna
    int inicioLineReg = posicion_region(line);
    int inicioColumnReg = posicion_region(column);

    for(int pos1=inicioLineReg ; pos1<=inicioLineReg+2 ; pos1++){
        for(int pos2=inicioColumnReg ; pos2<=inicioColumnReg+2 ; pos2++){
            if(s[pos1][pos2] == numRandom){
                numEnRegion = true;
            }
        }
    }

    return numEnRegion;
}

///Ingreso fila y columna y encuentra los candidatos para esa celda vacia
void crear_candidatos (int s[][9], int fila, int columna, bool candidatos[][tam][tam]){

    for(int i=1 ; i<=tam ; i++){

        candidatos[fila][columna][i] = true;

        if(numEstaEnLaLinea(i, fila, s) == true){
            candidatos[fila][columna][i] = false;
        } else {
            if(numEstaEnLaColumn(i, columna, s)){
                candidatos[fila][columna][i] = false;
            } else {
                if(numEstaEnLaRegion(i, fila, columna, s)){
                    candidatos[fila][columna][i] = false;
                }
            }
        }
    }

}

///Devuelve true si ‘num’ es candidato para la celda del Sudoku ‘s’ dada por ‘fila’ y ‘columna’
bool es_candidato (int s [][9], int num, int fila, int columna, bool candidatos[][tam][tam]){

    bool esCandidato = false;

    crear_candidatos(s, fila, columna, candidatos);

    if(s[fila][columna]==0 && candidatos[fila][columna][num]==true)
        esCandidato = true;

    return esCandidato;

}

