
#ifndef aparicion_hpp
#define aparicion_hpp

#include "libro.hpp"
#include <stdio.h>

char convertir_a_minuscula(char c);

string normalizar(string s);

string procesar_linea (string linea);

class Aparicion{
private:
    Libro* pl;
    int num_capitulo;
    int num_parrafo;
public:
    Aparicion(Libro *pl_, int nc, int np);
    void mostrar();
    //bool esMenor (Aparicion &otra);
    //bool esIgual (Aparicion &otra);
    bool operator< (const Aparicion &otra) const;
    bool operator== (const Aparicion &otra) const;

};


#endif /* aparicion_hpp */
