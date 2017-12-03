#include <iostream>
#include <string>
#include <map>

class Socio{
public:
    Socio()
     : _nombre("")
    {};
    Socio( const Socio& orig)
     : _nombre( orig._nombre )
    {};
    virtual ~Socio(){};
    std::string _nombre;
};

int main(int argc, char** argv) {
    std::map<int, Socio, std::greater<int> > socios; 
    
    return 0;
}

