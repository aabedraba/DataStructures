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
        std::string palabra;
        int pos, eleccion;
        do {
            cout << "Introduzca una palabra: ";
            cin >> palabra;    
            if (palabra == "-1")
                break;
            ListaEnlazada<Sucesor>::Iterador iter = diccionario.busca( palabra, pos ).sucesores().iterador();
            ListaEnlazada<Sucesor>::Iterador aux = iter;
            if ( iter.fin() ){
                cout << "No hay sucesores" << endl;
                continue;
            }
            int eleccion, i = 1;
            cout << "Elija: ";
            while ( !iter.fin() ){
                cout << i << ". " << iter.dato().getTermino() << "(" << iter.dato().getNumOcurrencias() << ")  ";
                iter.siguiente();
                i++;
            }
            cout << "\n: ";
            cin >> eleccion;
            for (int i = 2; i <= eleccion; i++)
                aux.siguiente();
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



