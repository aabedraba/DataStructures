#include <iostream>
#include <fstream>
#include "THashCerrada.h"
#include "Palabra.h"


using namespace std;

int main() {
    unsigned long tam = 125182;
    int iteraciones = 0;
//    while (iteraciones < 20){
        THashCerrada<Palabra> palabras(tam);
        ifstream archivo;
        archivo.open("/home/aabedraba/Github/EstructurasDeDatos/Practica_7/listado-sin-acentos_v2.txt");
        if (!archivo.good()) {
            cout << "No se ha abierto el archivo" << endl;
            return 0;
        }
        string linea;
        while (!archivo.eof()) {
            archivo >> linea;
            unsigned long clave = palabras.toDjb2(linea.c_str());
            Palabra palabra(linea);
            palabras.inserta(clave, palabra);
        }

        cout << "Tamaño de la tabla: " << palabras.tamaTabla() << endl;
        cout << "Numero de elementos; " << palabras.numElementos() << endl;
        cout << "Numero máximo de colisiones: " << palabras.maxColisiones() << endl;
        cout << "Promedio de colisiones: " << palabras.promedioColisiones() << endl;
        cout << "Factor de caraga: " << palabras.factorCarga() << endl;
//        tam = palabras.tamaTabla();
//        iteraciones++;
//    }

    return 0;
}