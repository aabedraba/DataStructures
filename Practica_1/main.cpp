/* 
 * File:   main.cpp
 * Author: aabedraba
 *
 * Created on September 19, 2017, 9:55 AM
 */

#include <cstdlib>
#include "Diccionario.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    Diccionario diccionario( "listado-general.txt" );
   
    do {
        
        std::string palabra, eleccion;
        std::cout << "1 para insertar palabra, 0 para buscar, -1 para terminar: ";
        std::cin >> eleccion;
        if ( eleccion == "1" ){
            int pos;
            std::cout << "Palabra a insertar: ";
            std::cin >> palabra;
            std::cout << "Posicion: ";
            std::cin >> pos;
            try{
                diccionario.inserta( palabra, pos );
            } catch ( std::string &e ) {
                std::cout << e << std::endl;
            }
        }
        else if ( eleccion == "0" ){
            std::cout << "Palabra a buscar: ";
            std::cin >> palabra;
            int pos = diccionario.busca( palabra );
            if ( pos != -1 ) 
                std::cout << "La palabra se encuentra en la posicion " 
                    << pos << " del vector." << endl;
            else 
                std::cerr << "No se ha encontrado la palabra." << endl;
        }
        else{
            std::cout << "Fin de ejecucion." << std::endl;
            break; //Fin del programa
        }
        
    } while ( true );
    
    return 0;
}

