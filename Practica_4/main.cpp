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

#include "Diccionario.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    try {
        Diccionario diccionario("listado-sin-acentos_v2.txt");
        diccionario.usaCorpus("corpus_spanish-2.txt"); 
        do {
//            int eleccion;
//            cout << "0 buscar, 1 insertar, 2 eliminar: ";
//            cin >> eleccion;
//            std::string palabra;
//            unsigned int pos;
//
//            if ( eleccion == 0 ){
//                cout << "Palabra a buscar: ";
//                cin >> palabra;
//                diccionario.busca( palabra, pos );
//                if ( pos == -1 )
//                    cout << "No se encuentra" << endl;
//                else 
//                    cout << "Encontrado en la posicion: " << pos << endl;
//            }
//            if ( eleccion == 1 ){
//                cout << "Palabra a insertar: ";
//                cin >> palabra;
//                diccionario.insertar( palabra, pos );
//                if ( pos == -1 )
//                    cout << "Ya existe" << endl;
//                else
//                    cout << "Insertado en la posicion: " << pos << endl;
//            }
//            if ( eleccion == 2 ){
//                cout << "Palabra a eliminar: ";
//                cin >> palabra;
//                diccionario.eliminar( palabra, pos );
//                cout << "Eliminado correctamente de la posicion " << pos << endl;
//            }    
            std::string palabra;
            unsigned int pos;
            cout << "Introduzca una palabra (0 para salir): ";
            cin >> palabra;    
            if (palabra == "0")
                break;
            std::list<Sucesor> sucesores = diccionario.busca( palabra, pos ).sucesores();
            std::list<Sucesor>::iterator iter = sucesores.begin();
            std::list<Sucesor>::iterator aux = iter;
            if ( iter == sucesores.end() ){
                cout << "No hay sucesores" << endl;
                continue;
            }
            int eleccion, i = 1;
            cout << "Elija: ";
            while ( iter != sucesores.end() ){
                cout << i << ". " << (*iter).getTermino() << "(" << (*iter).getNumOcurrencias() << ")  ";
                iter++;
                i++;
            }
            cout << " " << endl;
            cin >> eleccion;
            for (int i = 2; i <= eleccion; i++)
                aux++;
            cout << (*aux).getTermino() << endl;

       } while (true);
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



