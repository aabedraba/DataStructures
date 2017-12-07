#include <iostream>
#include <fstream>
#include "THashCerrada.h"
#include "Palabra.h"


using namespace std;

int main() {
    long tam = 120000;
    int *hola = new int(5);
    cout << *hola << endl;
    THashCerrada<Palabra> palabras( tam );
    ifstream archivo;
    archivo.open("/home/aabedraba/Github/EstructurasDeDatos/Practica_7/listado-sin-acentos_v2.txt");
    if ( !archivo.good() ){
        cout << "No se ha abierto el archivo" << endl;
        return 0;
    }
    string linea;
    while ( !archivo.eof() ){
        archivo >> linea;
        unsigned long clave = palabras.toDjb2( linea.c_str() );
        Palabra palabra( linea );
        palabras.insertar( clave, palabra );
    }

    cout << "Tamaño de la tabla: " << palabras.tamaTabla() << endl;
    cout << "Numero de elementos; " << palabras.numElementos() << endl;
    cout << "Numero máximo de colisiones: " << palabras.maxColisiones() << endl;
    cout << "Promedio de colisiones: " << palabras.promedioColisiones() << endl;
    cout << "Factor de caraga: " << palabras.factorCarga() << endl;

    delete hola;
    return 0;
}