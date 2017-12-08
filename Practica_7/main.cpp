/* 
 * File:   main.cpp
 * Author: aabedraba
 *
 * Created on September 19, 2017, 9:55 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

#include "Diccionario.h"
#include "TextoPredictivo.h"

using namespace std;

/**
 * Funcion recursiva que muestra los 10 sucesores mas prioritarios, en caso de 
 que existan de un string dado.
 * @param palabra string del que se buscan sucesores.
 * @param diccionario objeto de tipo diccionario en el buscamos estas palabras.
 */
void mostrarSucesores ( const std::string &palabra, Usuario* user ){
    std::list<std::string> sucesores;
    try {
        sucesores = user->sugerencia( palabra );
    } catch ( logic_error &e ) {
        cerr << "No hay más sugerencias" << endl;
        return;
    }
    auto iter = sucesores.begin();
    auto aux = iter;

    cout << "Elija: " << endl;
    int i = 1;
    while ( iter != sucesores.end() ){
        cout << '\t' <<  i << ". " << (*iter) << endl;
        iter++; i++;
    }


    int eleccion;
    cout << " " << endl;
    cin >> eleccion;
    if ( eleccion > sucesores.size() ){
        cerr << "Valor incorrecto" << std::endl;
        return;
    }
    for (int i = 2; i <= eleccion; i++)
        aux++;
    mostrarSucesores( (*aux), user );

};


/*
 * 
 */
int main(int argc, char** argv) {

    try {
        auto start = std::chrono::system_clock::now();
        Diccionario dicBase("/home/aabedraba/Github/EstructurasDeDatos/Practica_7/listado-sin-acentos_v2.txt");
        dicBase.usaCorpus("/home/aabedraba/Github/EstructurasDeDatos/Practica_7/corpus_spanish.txt");
        auto end = std::chrono::system_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        cout << "Tiempo de carga y entrenamiento del diccionario (segundos): " << elapsed_ms/(float)1000 << endl;

        TextoPredictivo predictivo( dicBase );
        predictivo.nuevoUsuario( "usr1", "Abdallah" );
        predictivo.nuevoUsuario( "usr2", "Jesus" );
        Usuario *us1 = predictivo.getUsuario( "usr1" );
        Usuario *us2 = predictivo.getUsuario( "usr2" );
        us1->escribeFrase( "hola colega como andas Yo regu porque yo estoy pillao con las prácticas de estructuras" );
        us2->escribeFrase( "colega el whatsapp el la tuit el pillao" );
        cout << "Mostrando sucesores  de: " << us1->getId() << endl;
        mostrarSucesores( "hola", us1 );
        cout << "Mostrando sucesores  de: " << us2->getId() << endl;
        mostrarSucesores( "whatsapp", us2 );
    } catch (std::ifstream::failure& exception) {
    std::cerr << exception.what() << std::endl;
    }
    catch (std::invalid_argument& exception) {
      std::cerr << exception.what() << std::endl;
    }
    catch (std::out_of_range& exception) {
      std::cerr << exception.what() << std::endl;
    }
    catch (std::exception& exception) {
      std::cerr << exception.what() << std::endl;
    }

    return 0;
}



