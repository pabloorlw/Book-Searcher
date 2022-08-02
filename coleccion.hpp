
#ifndef coleccion_hpp
#define coleccion_hpp

#include <stdio.h>
#include <list>
#include <iostream>
#include "libro.hpp"
#include "TablaHash.hpp"
#include "arbol.hpp"

using namespace std;

class ColeccionLibros{
private:
    list<Libro> lista;
    TablaHash tabla;
    ArbolTrie arbol;
    int contador;
public:
    ColeccionLibros ();
    void insertar (Libro nuevo);
    Libro * consultar (long long isbn);
    void insertarPalabra (string cad, Aparicion ap){
        arbol.insertar(cad, ap);
    }
    list<Aparicion> * buscarPalabra (string cad){
        return arbol.buscar(cad);
    }
};

extern ColeccionLibros dic;

#endif /* coleccion_hpp */
