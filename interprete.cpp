#include <iostream>
#include "libro.hpp"
#include "interprete.hpp"
#include "coleccion.hpp"
#include <sstream>

using namespace std;

//Unica variable global del programa, para la colección de libros.
extern ColeccionLibros dic;

//Leer el contenido de un libro, llevando la cuenta de los parrafos, los capitulos y las palabras. También se crean las apariciones.
void LeerContenido(Libro libro, Libro * ptr){
    int num_capitulo=1;
    int num_parrafo=1;
    int num_parrafo_cap = 1;
    int num_palabras=0;
    string palabra_ant="";
    bool nuevo_parrafo = false;
    while (num_capitulo <= libro.numero_capitulos()){
        string linea;
        getline(cin, linea);
        istringstream iss (procesar_linea(normalizar(linea)));
        string palabra;
        while (iss >> palabra){
            if (palabra == "findecapitulo"){
                if (num_capitulo < libro.numero_capitulos()){
                    num_parrafo=num_parrafo+1;
                }
                num_capitulo=num_capitulo+1;
                num_parrafo_cap = 1;
                nuevo_parrafo = false;
            } else if (palabra == "FL"){
                if (palabra_ant == "FL") nuevo_parrafo = true;
            } else {
                if (nuevo_parrafo) {
                    num_parrafo=num_parrafo+1;
                    num_parrafo_cap = num_parrafo_cap + 1;
                }
                nuevo_parrafo = false;
                num_palabras=num_palabras+1;
                dic.insertarPalabra(palabra, Aparicion(ptr, num_capitulo, num_parrafo_cap));
            }
            palabra_ant = palabra;
        }
    }
    libro.mostrarLargo();
    cout << num_parrafo << " párrafos" << endl;
    cout << num_palabras << " palabras" << endl;
}


//Metodo que procesa la accion de insertar un libro.
void procesarInsertar(){
    Libro nuevo;
    nuevo.leer();
    dic.insertar(nuevo);
    LeerContenido(nuevo, dic.consultar(nuevo.getISBN()));
}

//Metodo que procesa la accion de consultar un libro.
void procesarConsultar(){
    long long isbn;
    cin >> isbn;
    Libro *pl = dic.consultar(isbn);
    if (pl == NULL){
        cout << "ISBN " << isbn << " no encontrado" << endl;
    } else{
        cout << "ISBN " << isbn << " encontrado" << endl;
        pl->mostrarLargo();
    }
}

//Metodo que devuelve la intersección de dos listas de apariciones.
list<Aparicion> * interseccionLista(list<Aparicion> * lista1, list<Aparicion> * lista2){
    list<Aparicion> * resultado = new list<Aparicion>();
    if ((lista1 == NULL) || (lista2 == NULL)) return resultado;
    list<Aparicion>::iterator it1;
    list<Aparicion>::iterator it2;
    it1 = lista1->begin();
    it2 = lista2->begin();
    while ((it1 != lista1->end()) && (it2 != lista2->end())){
        if (*it1 < *it2) {
            it1++;
        } else if (*it2 < *it1){
            it2++;
        }else {
            resultado->push_back(*it1);
            it1++;
            it2++;
        }
    }
    return resultado;
}

//Devuelve la union de dos listas de apariciones.
list<Aparicion> * unionLista(list<Aparicion> * lista1, list<Aparicion> * lista2){
    list<Aparicion> * resultado = new list<Aparicion>();
    if (lista1 == NULL && lista2 == NULL) return resultado;
    if (lista1 == NULL){
        list<Aparicion>::iterator it2;
        it2 = lista2->begin();
        while (it2 != lista2->end()){
            resultado->push_back(*it2);
            it2++;
        }
        return resultado;
    }
    if (lista2 == NULL){
        list<Aparicion>::iterator it1;
        it1 = lista1->begin();
        while (it1 != lista1->end()){
            resultado->push_back(*it1);
            it1++;
        }
        return resultado;
    }
    list<Aparicion>::iterator it1;
    list<Aparicion>::iterator it2;
    it1 = lista1->begin();
    it2 = lista2->begin();
    while (it1 != lista1->end() && it2 != lista2->end()){
        if (*it1 < *it2) {
            resultado->push_back(*it1);
            it1++;
        } else if (*it2 < *it1){
            resultado->push_back(*it2);
            it2++;
        }else {
            resultado->push_back(*it1);
            it1++;
            it2++;
        }
    }
    if (it1 != lista1->end()){
        while (it1 != lista1->end()){
            resultado->push_back(*it1);
            it1++;
        }
    }
    if (it2 != lista2->end()){
        while (it2 != lista2->end()){
            resultado->push_back(*it2);
            it2++;
        }
    }
    
    return resultado;
}


//Metodo que procesa la accion de "buscarAND" una serie de palabras.
void buscarAND(){
    string palabras;
    getline(cin, palabras);
    istringstream iss (normalizar(palabras));
    string palabra;
    bool primera = true;
    list<Aparicion> * resultado = NULL;
    while (iss >> palabra){
        if (primera){
            list<Aparicion> * lista = dic.buscarPalabra(palabra);
            if (lista != NULL){
                resultado = new list<Aparicion>;
                list<Aparicion>::iterator it;
                it = lista->begin();
                while (it != lista->end()){
                    resultado->push_back(*it);
                    it++;
                }
            }
            primera = false;
        } else {
            list<Aparicion> * aux = resultado;
            resultado = interseccionLista (resultado, dic.buscarPalabra(palabra));
            delete aux;
        }
    }
    if (resultado == NULL || resultado->size() == 0){
        cout << "a" << normalizar(palabras) << endl;
        cout << "Total: 0 resultados" << endl;
        delete resultado;
    } else {
        int numero = resultado->size();
        cout << "a" << normalizar(palabras) << endl;
        cout << "Total: " << numero << " resultados" << endl;
        list<Aparicion>::iterator it;
        int i = 1;
        for (it = resultado->begin(); it != resultado->end(); it++){
            cout << i << ". ";
            it->mostrar();
            i++;
        }
        delete resultado;
    }
}

//Metodo que procesa la accion de "buscarOR" una serie de palabras.
void buscarOR(){
    string palabras;
    getline(cin, palabras);
    istringstream iss (normalizar(palabras));
    string palabra;
    bool primera = true;
    list<Aparicion> * resultado = NULL;
    while (iss >> palabra){
        if (primera){
            list<Aparicion> * lista = dic.buscarPalabra(palabra);
            if (lista != NULL){
                resultado = new list<Aparicion>;
                list<Aparicion>::iterator it;
                it = lista->begin();
                while (it != lista->end()){
                    resultado->push_back(*it);
                    it++;
                }
            }
            primera = false;
        } else {
            list<Aparicion> * aux = resultado;
            resultado = unionLista (resultado, dic.buscarPalabra(palabra));
            delete aux;
        }
    }
    if (resultado == NULL || resultado->size() == 0){
        cout << "o" << normalizar(palabras) << endl;
        cout << "Total: 0 resultados" << endl;
        delete resultado;
    } else {
        int numero = resultado->size();
        cout << "o" << normalizar(palabras) << endl;
        cout << "Total: " << numero << " resultados" << endl;
        list<Aparicion>::iterator it;
        int i = 1;
        for (it = resultado->begin(); it != resultado->end(); it++){
            cout << i << ". ";
            it->mostrar();
            i++;
        }
        delete resultado;
    }
}




//Interprete de comandos del buscador.
void interprete (string comando){
    
    if (comando == "i")procesarInsertar();
    else if (comando == "c") procesarConsultar();
    else if (comando == "a") buscarAND();
    else if (comando == "o") buscarOR();
    
}
