#include <iostream>
#include <fstream>
#include <chrono>
#include "THashCerrada.h"
#include "Palabra.h"


using namespace std;

int main() {
    auto start = std::chrono::system_clock::now();
    unsigned long tam = 126150;
    THashCerrada<Palabra> palabras(tam);
    auto end = std::chrono::system_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                            start).count();
    cout << "Tiempo de carga y entrenamiento del diccionario (segundos): " << elapsed_ms/(float)1000 << endl;
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
    return 0;
}