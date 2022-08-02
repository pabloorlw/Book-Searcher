#include "libro.hpp"
#include "TablaHash.hpp"
#include <list>
#include <math.h>

//Constructor de la tabla hash. Empezamos con tamaño 100, que irá aumentando con las sucesivas reestructuraciones.
TablaHash::TablaHash(){
    nElem = 0;
    tamanoArray = 100;
    tabla = new list<Libro *>[tamanoArray];
}

//Destructor de la tabla hash, libera la memoria de la tabla, que se reserva de forma dinamica.
TablaHash::~TablaHash(){
    delete [] tabla;
}
 
//Función de dispersíon de la tabla.
int TablaHash::funcionHash(long long isbn){
    long long parteEntera = (long long)(1.11*isbn);
    return parteEntera%tamanoArray;
}

//Inserta un libro en la tabla. Si hay demasiados, se realiza la reestructración.
void TablaHash::insertar (Libro * nuevo){
    long long isbn = nuevo->getISBN();
    tabla[funcionHash(isbn)].push_front(nuevo);
    nElem = nElem + 1;
    if (nElem > 2*tamanoArray){
        list<Libro *> * nuevo = new list<Libro *>[2*tamanoArray];
        tamanoArray = 2*tamanoArray;
        for (int i = 0; i < tamanoArray/2; i = i + 1){
            list<Libro *>::iterator itLista;
            itLista = tabla[i].begin();
            while (itLista != tabla[i].end()){
                nuevo[funcionHash((*itLista)->getISBN())].push_front(*itLista);
                itLista++;
            }
        }
        delete [] tabla;
        tabla = nuevo;
    }
}

//Consultar un libro en la tabla, haciendo uso de su ISBN.
Libro * TablaHash::consultar (long long isbn){
    int pos = funcionHash(isbn);
    list<Libro * >::iterator itLista;
    itLista = tabla[pos].begin();
    while (itLista != tabla[pos].end() && (*itLista)->getISBN() != isbn){
        itLista++;
    }
    if (itLista == tabla[pos].end()){
        return NULL;
    }
    return *itLista;
}

