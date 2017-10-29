/* 
 * File:   Diccionario.cpp
 * Author: aabedraba
 * 
 * Created on September 19, 2017, 9:55 AM
 */

#include "Diccionario.h"

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



void Diccionario::elimina( const std::string &palabra, unsigned int &pos ) {
    Palabra pal( palabra );
    std::vector<Palabra>::iterator iter = _vec.begin();
    for (unsigned int i = 0; i < _vec.size(); i++, iter++)
        if ( pal == _vec[i] ){
            _vec.erase( iter );
            pos = i;
            return;
        }
    throw std::invalid_argument("[Diccionario::elimina]Elemento no encontrado para eliminar");

}

//TODO mirar por qué me devuelve una pos superior
void Diccionario::inserta(const std::string &palabra, unsigned int& pos) {
    Palabra aInsertar( palabra );
    std::vector<Palabra>::iterator iter = std::lower_bound( _vec.begin(), _vec.end(), aInsertar ); 
    if ( aInsertar == (*(iter-1)) )
        throw std::invalid_argument ("[Diccionario::inserta]Palabra ya existe en diccionario");
    pos = iter - _vec.begin();
    _vec.insert( iter, aInsertar );
    iter = std::lower_bound( _vec.begin(), _vec.end(), aInsertar );
}



Palabra &Diccionario::busca( const std::string &termino, unsigned int &pos ) {
    Palabra aBuscar( termino );
    auto iter = std::lower_bound( _vec.begin(), _vec.end(), aBuscar );
    if ( iter == _vec.end() || aBuscar != (*(iter-1)) )
        throw std::invalid_argument ("[Diccionario::busca]Palabra no existe");
    iter--;
    pos = iter - _vec.begin();
    return (*iter);
}

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


