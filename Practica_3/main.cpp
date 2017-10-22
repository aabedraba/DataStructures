/* 
 * File:   main.cpp
 * Author: aabedraba
 *
 * Created on September 19, 2017, 9:55 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "Diccionario.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    try {
        Diccionario diccionario("listado-sin-acentos_v2.txt");
        diccionario.usaCorpus("corpus_spanish.txt");
        
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

