
#ifndef interprete_hpp
#define interprete_hpp

#include <iostream>
#include "interprete.hpp"
#include "libro.hpp"

using namespace std;

void procesarInsertar();

void procesarConsultar();

void interprete (string comando);

void LeerContenido(Libro libro, Libro * ptr);

void buscarAND();

void buscarOR();

#endif /* interprete_hpp */
