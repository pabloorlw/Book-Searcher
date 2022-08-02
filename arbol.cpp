
#include "arbol.hpp"
#include "iostream"
#include "aparicion.hpp"

using namespace std;

//Constructor de la clase nodo
NodoTrie::NodoTrie(char car, NodoTrie * siguiente, NodoTrie * puntero){
    caracter = car;
    sig = siguiente;
    ptr = puntero;
}

//Destructor del nodo. Notese que es "recursivo"
NodoTrie::~NodoTrie(){
    delete sig;
    delete ptr;
}

//Metodo para insertar una aparicion en la lista de apariciones
void NodoTrie::insertarAparicion (Aparicion ap){
    list<Aparicion>::iterator itLista;
    itLista = l.begin();
    while (itLista != l.end() && *itLista < ap){
        itLista++;
    }
    if (itLista == l.end() || ! (*itLista == ap)){
        l.insert(itLista, ap);
    }
    
}

//Metodo para consultar si una letra está en el nodo.
NodoTrie * NodoTrie::consultar (char letra){
    NodoTrie * tmp = sig;
    while (tmp != NULL && tmp->caracter < letra){
        tmp = tmp->sig;
    }
    if (tmp != NULL && tmp->caracter == letra){
        return tmp->ptr;
    } else{
        return NULL;
    }
}

//Metodo de inserción de una letra en el nodo.
void NodoTrie::insertar(char l){
    NodoTrie * tmp = this;
    while (tmp->sig != NULL && tmp->sig->caracter < l){
        tmp = tmp->sig;
    }
    if (tmp->sig == NULL || tmp->sig->caracter != l){
        NodoTrie * aux = tmp->sig;
        tmp->sig = new NodoTrie(l, aux, new NodoTrie(' ', NULL, NULL));
    }
}

//Metodo para comprobar si hay marca de fin de palabra en el nodo.
bool NodoTrie::HayMarca(){
    return caracter == '$';
}

//Metodo que pone la marca de fin de palabra en el nodo.
void NodoTrie::PonMarca(){
    caracter = '$';
}

//Metodo que quita la marca de fin de palabra en el nodo.
void NodoTrie::QuitaMarca(){
    caracter = ' ';
}

//Metodo de consulta de la lista de apariciones.
list<Aparicion> * NodoTrie::getLista(){
    return &l;
}
 
//Constructor del arbol.
ArbolTrie::ArbolTrie(){
    raiz = new NodoTrie(' ', NULL, NULL);
}
 //Destructor del arbol.
ArbolTrie::~ArbolTrie(){
    delete raiz;
}

//Insertar un una palabra a partir de un nodo del arbol
void ArbolTrie::insertar(NodoTrie *A, string cadena, Aparicion ap){
    NodoTrie * pos = A;
    for (int i = 0; i < cadena.length(); i++){
        pos->insertar(cadena[i]);
        pos = pos->consultar(cadena[i]);
    }
    pos->PonMarca();
    pos->insertarAparicion(ap);
}

//Buscar una palabra a partir de un nodo del arbol.
bool ArbolTrie::buscar (NodoTrie *A, string cadena){
    NodoTrie * pos = A;
    for (int i = 0; i < cadena.length(); i++){
        if (pos->consultar(cadena[i]) == NULL){
            return false;
        }
        pos = pos->consultar(cadena[i]);
    }
    if (pos->HayMarca()){
        return true;
    }
    return false;
}

//Buscar una palabra en el arbol
list<Aparicion> * ArbolTrie::buscar (string cadena){
    NodoTrie * pos = raiz;;
    for (int i = 0; i < cadena.length(); i++){
        if (pos->consultar(cadena[i]) == NULL){
            return NULL;
        }
        pos = pos->consultar(cadena[i]);
    }
    if (pos->HayMarca()){
        return pos->getLista();
    }
    return NULL;
}
