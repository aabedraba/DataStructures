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

#include "img.h"
#include "MallaRegular.h"
#include "CodigoPost.h"


using namespace std;

int main(int argc, const char * argv[]) {

    Img img(1280, 720);

//    try {
//        img = Img("./mapaUsa.ppm");
//    } catch (ErrorLecturaFichero &e) {
//        cout << "Error al leer imagen de entrada" << endl;
//        return 1;
//    }

    cout << "Imagen leida" << endl;

    int nfilas = img.numFilas();
    int ncol = img.numColumnas();

    // blue
    int r = 0;
    int g = 0;
    int b = 255;

    vector<CodigoPost> codigosPostales;
    fstream archivo ("./zipcode.csv", fstream::in | fstream::out );
    if ( !archivo.good() ){
        cerr << "Archivo no leído." << endl;
        return EXIT_FAILURE;
    }

    double minlat = -150;
    double maxlat = -50;
    double minlon = 20; //perfecto
    double maxlon = 70;

    MallaRegular<CodigoPost> malla( minlon, minlat, maxlon, maxlat, 370);

    vector<double> vlat, vlon;
    string linea;
    getline(archivo, linea);
    int nlineas = 0;
    while( !archivo.eof() ) {
        int tamanioLinea;
        string palabra;
        getline(archivo, linea);

        //codigoPostal
        tamanioLinea = linea.find(",", 0);
        if ( tamanioLinea == -1 ) continue;
        palabra = linea.substr(1, tamanioLinea - 2);
        int codigoPostal = stoi(palabra);
        linea = linea.substr(tamanioLinea+1, 255);

        //ciudad
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        std::string ciudad = palabra;
        linea = linea.substr(tamanioLinea+1, 255);

        //estado
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        std::string estado = palabra;
        linea = linea.substr(tamanioLinea+1, 255);

        //latitud
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        float longitud = stof(palabra);
        linea = linea.substr(tamanioLinea+1, 255);

        //longitud
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        float latitud = stof(palabra);
        linea = linea.substr(tamanioLinea+1, 255);


        //zonaHoraria
        tamanioLinea = linea.find(",", 0);
        palabra = linea.substr( 1, tamanioLinea-2);
        short zonaHoraria = stoi(palabra);
        linea = linea.substr(tamanioLinea+1, 255);

        //dst
        tamanioLinea = linea.find("\"", 0);
        palabra = linea.substr( 1, tamanioLinea-1);
        short dst = stoi(palabra);

        CodigoPost city( codigoPostal, ciudad, estado, longitud, latitud, zonaHoraria, dst );
        if ( malla.insertar(longitud, latitud, city) ) {
            vlon.push_back( longitud );
            vlat.push_back( latitud );
            if (longitud < minlon) minlon = longitud;
            if (longitud > maxlon) maxlon = longitud;
            if (latitud < minlat) minlat = latitud;
            if (latitud > maxlat) maxlat = latitud;
        };
    }


    cout << "lat: xmin = " << minlat << ", " << "xmax = " << maxlat << endl;
    cout << "lon: ymin = " << minlon << ", " << "ymax = " << maxlon << endl;

    double rangox = maxlat - minlat;
    double rangoy = maxlon - minlon;

    cout << "rango x = " << rangox << endl;
    cout << "rango y = " << rangoy << endl;

    cout << "nfilas = " << nfilas << endl;
    cout << "ncol = " << ncol << endl;

    double pixelPorGradoX = (double) (nfilas - 1) / rangox;
    double pixelPorGradoY = (double) (ncol - 1) / rangoy;

    cout << vlon.size()  << endl;
    for (int i = 0; i < vlon.size(); i++) {
        int posX = (vlat[i] - minlat) * pixelPorGradoX;
        int posY = ncol - 1 - ((vlon[i] - minlon) * pixelPorGradoY);
        img.pintarPixelGrande(posX,posY,255,0,30);
        //img.pintarPixel(posX, posY, r, g, b);
    }

    img.pintarPixelGrande(0, 0, r, g, b);


    double lat1 = -120.0;
    double lon1 = 30.0;

    double lat2 = -100.0;
    double lon2 = 40.0;


    img.pintarRecuadro((lat1 - minlat) * pixelPorGradoX, ncol - 1 - ((lon1 - minlon) * pixelPorGradoY),
                       (lat2 - minlat) * pixelPorGradoX, ncol - 1 - ((lon2 - minlon) * pixelPorGradoY), 255, 0, 0);

    // aqui se realiza el test del modo:
    // vector<CodigoPost> buscarRango (lat1, lon1, lat2, lon2);
    vector<CodigoPost> cods = malla.buscarPorRango( lon1, lat1, lon2, lat2);
    // luego se recorre dicho vector, y para las coordenadas de cada CodigoPost se vuelven a pintar
    //fichero en color verde

    for ( int i = 0; i < cods.size(); ++i ) {
        int posX = ( cods[i].x - minlat) * pixelPorGradoX;
        int posY = ncol - 1 - ((cods[i].y - minlon) * pixelPorGradoY);

        img.pintarPixelGrande(posX,posY,0,255,0);
        //img.pintarPixel(posX, posY, 0, 255, 0);
    }

    cout << "Maximo de elementos en celda: " << malla.maxElementosEnCelda() << endl;
    cout << "Promedio de elementos por celda: " << malla.promedioElementosPorCelda() << endl;
    cout << "Numero de elementos: " << malla.numElementos() << endl;

    try {
        img.guardar("./mapaUsaResult.ppm");
    } catch (ErrorEscrituraFichero &e) {
        cout << "Error al escribir fichero" << endl;
        return 1;
    }

    cout << "Operación realizada con exito" << endl;
    return EXIT_SUCCESS;
}