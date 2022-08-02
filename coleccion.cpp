#include <iostream>
#include "libro.hpp"
#include "aparicion.hpp"
#include "TablaHash.hpp"
#include "arbol.hpp"
#include <list>

#include "coleccion.hpp"

//Unica variable global del programa, para la colección de libros.
ColeccionLibros dic;

//Constructor de la colección
ColeccionLibros::ColeccionLibros(){
    contador = 0;
}

//Insertar un libro a la colección.
void ColeccionLibros::insertar (Libro nuevo){
    lista.push_front(nuevo);
    tabla.insertar(&lista.front());
    contador = contador + 1;
}

//Consulta un libro mediante su ISBN en la colección.
Libro * ColeccionLibros::consultar(long long isbn){
    return tabla.consultar(isbn);
}


