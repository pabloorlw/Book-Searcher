
#ifndef TablaHash_hpp
#define TablaHash_hpp

#include "libro.hpp"
#include <stdio.h>
#include <list>

class TablaHash {
private:
    int tamanoArray;
    int nElem;
    list<Libro *> * tabla;
public:
    TablaHash();
    ~TablaHash();
    int funcionHash (long long isbn);
    void insertar (Libro * nuevo);
    Libro * consultar (long long isbn);
    int numELem (void) {return nElem ;}
    
};

#endif /* TablaHash_hpp */
