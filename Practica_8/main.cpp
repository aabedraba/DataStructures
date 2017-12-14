//
//  main.cpp
//  ImgQuad
//
//  Created by Antonio Jesús Rueda Ruiz on 09/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "CodigoPost.h"


using namespace std;

int main(int argc, const char * argv[]) {
    vector<CodigoPost> codigosPostales;
    ifstream archivo;
    archivo.open("/home/aabedraba/Github/EstructurasDeDatos/Practica_8/zipcode.csv");
    if ( !archivo.good() ){
        cout << "te follen" << endl;
        return 1;
    }
    string linea;

    int codigoPostal;
    string ciudad, estado;
    float latitud, longitud;
    short zonaHoraria;
    short dst;


    string palabra;
    getline(archivo, linea);
    int i = 0;
    while( !archivo.eof() ) {
        int tamanioLinea;
        getline(archivo, linea);

        //codigoPostal
        tamanioLinea = linea.find(",", 0);
        if ( tamanioLinea == -1 ) continue;
        palabra = linea.substr(1, tamanioLinea - 2);
        codigoPostal = stoi(palabra);
        linea = linea.substr(tamanioLinea+1, 255);

        //ciudad
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        ciudad = palabra;
        linea = linea.substr(tamanioLinea+1, 255);

        //estado
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        estado = palabra;
        linea = linea.substr(tamanioLinea+1, 255);

        //latitud
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        latitud = stof(palabra);
        linea = linea.substr(tamanioLinea+1, 255);

        //longitud
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        longitud = stof(palabra);
        linea = linea.substr(tamanioLinea+1, 255);

        //zonaHoraria
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        zonaHoraria = stoi(palabra);
        linea = linea.substr(tamanioLinea+1, 255);

        //dst
        tamanioLinea = linea.find("\"", 0);
        palabra = linea.substr( 1, tamanioLinea-1);
        dst = stoi(palabra);

        CodigoPost codigoPost( codigoPostal, ciudad, estado, latitud, longitud, zonaHoraria, dst );
        codigosPostales.push_back(codigoPost);

    }

    float minimoLongitud, maximoLongitud;
    maximoLongitud = minimoLongitud = codigosPostales[0].get_longitud();
    float minimoLatitud, maximoLatitud;
    minimoLatitud = maximoLatitud = codigosPostales[0].get_latitud();
    for (int j = 1; j < codigosPostales.size(); ++j) {
        float latitud = codigosPostales[j].get_latitud();
        float longitud = codigosPostales[j].get_longitud();

        if ( latitud < minimoLatitud ) minimoLatitud = latitud;
        else if ( latitud > maximoLatitud ) maximoLatitud = latitud;

        if ( longitud < minimoLongitud ) minimoLongitud = longitud;
        else if ( longitud > maximoLongitud ) maximoLongitud = longitud;
    }

    cout << "Minimo latitud: " << minimoLatitud << ", maximo latitud: " << maximoLatitud << endl;
    cout << "Minimo longitud: " << minimoLongitud << ", maximo longitud: " << maximoLongitud << endl;

    cout << "Prueba" << endl;
    return 0;




}

