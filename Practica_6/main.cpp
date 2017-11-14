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
#include "AVL.h"

#include "Diccionario.h"
#include "TextoPredictivo.h"

using namespace std;

/**
 * Funcion recursiva que muestra los 10 sucesores mas prioritarios, en caso de 
 que existan de un string dado.
 * @param palabra string del que se buscan sucesores.
 * @param diccionario objeto de tipo diccionario en el buscamos estas palabras.
 */
void mostrarSucesores ( const std::string &palabra, TextoPredictivo &predictivo ){
    unsigned int pos;
    int eleccion;
    std::list<int> ocurrencias;
    std::list<std::string> sucesores = predictivo.sugerencia( palabra, ocurrencias );
    auto iter = sucesores.begin();
    auto iter2 = ocurrencias.begin();
    auto aux = iter;
    if ( iter == sucesores.end() ){
        cout << "No hay sucesores" << endl;
        return;
    }
    cout << "Elija: " << endl;
    int i = 1;
    while ( iter != sucesores.end() ){
        cout << '\t' <<  i << ". " << (*iter) << " (" << (*iter2) << ")" << endl;
        iter++; i++; iter2++;
    }
    cout << " " << endl;
    cin >> eleccion;
    for (int i = 2; i <= eleccion; i++)
        aux++;
    mostrarSucesores( (*aux), predictivo );
};


/*
 * 
 */
int main(int argc, char** argv) {

    try {
        auto start = std::chrono::system_clock::now();
        Diccionario diccionario("listado-sin-acentos_v2.txt");
        diccionario.usaCorpus("corpus_spanish.txt"); 
        auto end = std::chrono::system_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end -
                start).count();
        cout << "Tiempo de carga y entrenamiento del diccionario (segundos): " << elapsed_ms/(float)1000 << endl;      
        TextoPredictivo predictivo( diccionario ); 
        unsigned int eleccion;
        std::string palabra;
        
        do {
            try {              
                cout << "0 buscar, 1 insertar, 2 sucesores, 3 salir: ";
                cin >> eleccion;
                switch ( eleccion ){
                    case 0: {
                        cout << "Palabra a buscar: ";
                        cin >> palabra;
                        Palabra buscado;
                        cout << diccionario.busca( palabra ).getTermino() << " encontrado" << endl;
                        
                        break;
                    }
                    
                    case 1: {
                        cout << "Palabra a insertar: ";
                        cin >> palabra;
                        bool insertado;
                        diccionario.inserta( palabra, insertado );
                        if ( insertado )
                            cout << "Insertado" << endl;
                        else
                            cout << "Ya existe" << endl;
                        break;
                    }
                    
                    case 2: {
                        cout << "Introduzca una palabra: ";
                        cin >> palabra;    
                        mostrarSucesores( palabra, predictivo );
                        break;
                    }
                    default:
                        break;
                }
            }catch (std::ifstream::failure& exception) {
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
        } while ( eleccion != 3 );
        
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



