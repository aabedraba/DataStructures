/* 
 * File:   TextoPredictivo.cpp
 * Author: aabedraba
 * 
 * Created on November 10, 2017, 4:59 PM
 */

#include "TextoPredictivo.h"

/**
 * Constructor parametrizado de TextoPredictivo.
 * @param diccIdioma referencia a un objeto de tipo diccionario.
 */
TextoPredictivo::TextoPredictivo( Diccionario &diccIdioma ) 
    : _diccIdioma ( diccIdioma )
{}

/**
 * Contructor copia de TextoPredictivo.
 * @param orig TextoPredictivo que se quiere copiar.
 */
TextoPredictivo::TextoPredictivo( const TextoPredictivo& orig ) 
    : _diccIdioma ( orig._diccIdioma )
{}

TextoPredictivo::~TextoPredictivo()
{}

/**
 * Metodo que dado un termino, devuelve una lista con sus sucesores y otra con el numero de ocurrencias de estos sucesores.
 * @param termino string del que se quieren obtener sucesores.
 * @param ocurrencias referencia a lista de enteros que queremos rellenar con el numero de ocurrencias de los sucesores.
 * @return lista de string con los sucesores de termino.
 */
std::list<std::string> TextoPredictivo::sugerencia( const std::string& termino, std::list<int> &ocurrencias ) {
    return _diccIdioma.busca( termino ).sucesores( ocurrencias );
}

/**
 * Metodo que llama al entrena de diccionario y realiza su misma funcion.
 * @param frase string que contiene la frase que se usara.
 */
void TextoPredictivo::entrena( std::string& frase ) {
    _diccIdioma.entrena( frase );
}



