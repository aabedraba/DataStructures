/* 
 * File:   main.cpp
 * Author: aabedraba
 *
<<<<<<< HEAD
 * Created on September 19, 2017, 9:55 AM
 */

#include <cstdlib>
#include "Diccionario.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    try {
        Diccionario diccionario("listado-sin-acentos.txt");
        std::string palabra;
        int pos;

        cout << "Introducir frases y pulsar enter (Cntrl+D para finalizar): ";
        unsigned int total = 0;
        while ( !std::cin.eof() ){
            std::cin >> palabra;
            if ( palabra != "" ){
                pos = diccionario.busca( palabra );
                if ( pos != -1 ){
                    cout << palabra << " ya existe en diccionario en la posicion " << pos << endl;
                    continue;
                }
                diccionario.insertar( palabra );
                total++;
                palabra = "";
            }
        }
        cout << "TOTAL PALABRAS INTRODUCIDAS: " << total << endl; 

        cin.clear(); //Para quitar el estado de Cntr+D de cin

        do {
            int eleccion;
            cout << "0 buscar, 1 insertar, 2 eliminar, 3 salir: ";
            cin >> eleccion;
            if ( eleccion == 0 ){
                cout << "Palabra a buscar: ";
                cin >> palabra;
                pos = diccionario.busca( palabra );
                if ( pos == -1 )
                    cout << "Palabra no encontrada" << endl;
                else
                    cout << "La palabra " << palabra << " se encuentra en la posicion " 
                            << pos << endl;
            } else if ( eleccion == 1 ) {
                cout << "Palabra a insertar: ";
                cin >> palabra;
                diccionario.insertar( palabra );
                pos = diccionario.busca( palabra );
                cout << "Insertado correctamente en la posicion " << pos << endl;
            } else if ( eleccion == 2 ){
                cout << "Palabra a eliminar: ";
                cin >> palabra;
                pos = diccionario.busca( palabra );
                if ( pos == -1 )
                    cout << palabra << " no existe en el diccionario" << endl;
                else{
                    diccionario.eliminar( palabra );
                    cout << "Eliminado correctamente de la posicion " << pos << endl;
                }
            } else
                break;
        } while ( true );
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
=======
 * Created on October 10, 2017, 9:44 AM
 */

#include <cstdlib>

using namespace std;

/*
 * @brief Funcion principal
 * @param argc Numero de argumentos
 * @param argv Caracteres que forman dichos argumentos
 */
int main(int argc, char** argv) {
>>>>>>> origin/master

    return 0;
}

