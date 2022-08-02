
#ifndef arbol_hpp
#define arbol_hpp

#include <stdio.h>
#include "iostream"
#include "aparicion.hpp"
#include <list>

using namespace std;

class NodoTrie{
private:
    char caracter;
    NodoTrie * sig;
    NodoTrie * ptr;
    list<Aparicion> l;
public:
    NodoTrie(char car, NodoTrie * siguiente, NodoTrie * puntero);
    ~NodoTrie();
    NodoTrie *consultar (char letra);
    void insertar(char l);
    bool HayMarca ();
    void PonMarca ();
    void QuitaMarca ();
    void insertarAparicion (Aparicion ap);
    list<Aparicion> * getLista();
};

class ArbolTrie {
private:
    NodoTrie * raiz;
    void insertar (NodoTrie *A, string cadena, Aparicion ap);
    bool buscar (NodoTrie *A, string cadena);

public:
    ArbolTrie ();
    ~ArbolTrie ();
    void insertar (string cadena, Aparicion ap){
        insertar(raiz, cadena, ap);
    }
    list<Aparicion> * buscar (string cadena);
};


#endif /* arbol_hpp */
