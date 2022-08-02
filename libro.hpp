
#ifndef libro_hpp
#define libro_hpp

#include <iostream>
#include <stdio.h>

using namespace std;

class Libro{
    private:
        long long ISBN;
        int ano, num_capitulos;
        string titulo;
        string autores;
    public:
        Libro();
        void leer();
        void mostrarCorto();
        void mostrarLargo();
        int numero_capitulos();
        long long getISBN();
};


#endif /* libro_hpp */
