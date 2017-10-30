/* 
 * File:   Diccionario.cpp
 * Author: aabedraba
 * 
 * Created on September 19, 2017, 9:55 AM
 */

#include "Diccionario.h"

/**
 * Constructor parametrizado de diccionario.
 * @param nomFich fichero con el que queremos crear nuestro diccionario.
 */
Diccionario::Diccionario( const std::string &nomFich )
    : _vec()
{
    std::ifstream fe;
    std::string linea;
    int total = 0;
    fe.open( nomFich.c_str() ); //convierte nomFich en legible por ifstream::open
    
    if ( !fe.good() ) {
        fe.close();
        throw std::invalid_argument("[Diccionario::cargaPalabras]No se pudo abrir"
                " el fichero. Sugerencia: ¿nombre de archivo invalido?");
    }
    
    while ( !fe.eof() ) {
        getline( fe, linea );
        if ( linea != "" ) {
            Palabra palabra(linea);
            _vec.push_back( palabra ); //La lista está ordenada
            total++;
        }
    }
    fe.close();
}

Diccionario::Diccionario( const Diccionario& orig ) {
    throw std::runtime_error("Vector de copia no implementado");
}

Diccionario::~Diccionario() {
}

/**
 * Metodo que busca y elimina una palabra del diccionario a través
 del atributo de tipo string de cada palabra.
 * @param palabra string que queremos buscar y eliminar.
 * @param pos posicion del elemento que queremos borrar y que se actualiza una vez eliminado.
 */
void Diccionario::elimina( const std::string &palabra, unsigned int &pos ) {
    Palabra pal( palabra );
    std::vector<Palabra>::iterator iter = _vec.begin();
    for (unsigned int i = 0; i < _vec.size(); i++, iter++)
        if ( pal == _vec[i] ){
            _vec.erase( iter );
            pos = i;
            return;
        }
    throw std::invalid_argument("[Diccionario::eliminar]Elemento no encontrado para eliminar");

}

//TODO mirar por qué me devuelve una pos superior
/**
 * Metodo que inserta una palabra en el diccionario a traves de un string.
 * @param palabra string de la nueva palabra que queremos introducir.
 * @param pos posicion donde colocaremos la nueva palabra y que se actualizará cuando se haga.
 * @throw lanza una excepcion de tipo invalid_argument si la palabra ya existe.
 */
void Diccionario::inserta(const std::string &palabra, unsigned int& pos) {
    Palabra pal( palabra );
    std::vector<Palabra>::iterator iter = _vec.begin();
    for ( pos = 0; pos < _vec.size(); pos++) {
        if ( pal == _vec[pos] ) //Evitamos duplicado
            throw std::invalid_argument("[Diccionario::insertar] Ya se encuentra en el diccionario");
        if ( pal < _vec[pos] ){
            _vec.insert( iter, pal ); //Insertar en la posición correspondiente
            return;
        }
        iter++;
    }
    
}

/**
 * Metodo que busca una palabra en el diccionario a traves de un string.
 * @param termino string de la palabra que queremos buscar.
 * @param pos posicion donde se encuentra dicha palabra y que se actualizara cuando se encuentre.
 * @return devuelve un objeto de tipo palabra con la palabra buscada.
 * @throw lanza una excepcion de tipo invalid_argument si la palabra no existe.
 */
Palabra &Diccionario::busca( const std::string &termino, unsigned int &pos ) {
    Palabra aBuscar( termino );
    std::vector<Palabra>::iterator iter;
    int posMaximo = _vec.size(); //Maximo de palabras declarado en VectorEstatico
    int posMinimo = 0;
    pos = (posMaximo - posMinimo) / 2;
    while ( (posMaximo - posMinimo) >= 0 ){
        if (  _vec[pos] != aBuscar ) {
            if ( _vec[pos] > aBuscar ) 
                posMaximo = pos - 1;
            else 
                posMinimo = pos + 1;
            pos = posMinimo + (posMaximo - posMinimo)/2;
        } else 
            return _vec[pos];
    } 
    throw std::invalid_argument ("[Diccionario::busca]Palabra no encontrada");
}

/**
 * Metodo que entrena el diccionario con un archivo repleto de frases.
 * @param nomFich string con el nombre del fichero que usaremos para entrenar.
 * @throw excepcion de tipo invalid_argument si el archivo no se puede abrir.
 */
void Diccionario::usaCorpus(std::string nomFich) {
    std::ifstream fe;
    std::string frase;
    fe.open( nomFich.c_str() );
    if ( !fe.good() ){
        fe.close();
        throw std::invalid_argument( "[Diccionario::usaCorpus] No se pudo abrir"
                " el archivo. (¿Archivo incorrecto?)");
    }
    while ( !fe.eof() ){
        getline( fe, frase );
        entrena( frase );
    }
    fe.close();
}

//TODO preguntar la parte del catch al profesor
/**
 * Metodo que a partir de una frase analizará las palabras que contiene y observará 
 el término que la precede y actualizará con él su lista de sucesores en el diccionario.
 * @param frase string que contiene la frase que usaremos.
 */
void Diccionario::entrena(const std::string frase) {
    std::stringstream ss( frase );
    std::string palabra, sucesor;
    
    ss >> palabra; 
    while ( !ss.eof() ){
        ss >> sucesor;
        if ( sucesor != "" ){
            unsigned int posP;
            try {
                busca( palabra, posP );
            } catch (std::invalid_argument  &e) {
                inserta( palabra, posP);
            }
            _vec[posP].introducirSucesor( sucesor );
            palabra = sucesor;
            sucesor = "";
        }
        
    }
}


