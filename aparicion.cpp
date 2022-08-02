#include <iostream>
#include "libro.hpp"
#include "aparicion.hpp"
#include <sstream>
#include <stdio.h>
using namespace std;

//Funcion para pasar a minusculas una letra.
char convertir_a_minuscula(char c){
    return tolower(c);
};

//Normalizar una cadena, siguiendo el algoritmo de las diapositivas.
string normalizar(string s){
    unsigned char especiales[] = {0x81, 0xA1, 0x89, 0xA9, 0x8D, 0xAD, 0x93, 0xB3, 0x9A, 0xBA, 0x91, 0xB1, 0x9C, 0xBC};
    string salida;
    for (unsigned i = 0; i < s.length(); i = i + 1){
        if (s[i] >= 'a' && s[i] <= 'z'){
            salida = salida + s[i];
        } else if (s[i] >= 'A' && s[i] <= 'Z'){
                salida = salida + convertir_a_minuscula(s[i]);
        } else if (s[i] == (char)0xC3){
            int j = 0;
            while (j < 14 && (char)especiales[j] != s[i + 1]){
                j = j + 1;
            }
            if (j < 14){
                if (j == 0 || j == 1){
                    salida = salida + "a";
                } else if (j == 2 || j == 3){
                    salida = salida + "e";
                } else if (j == 4 || j == 5){
                    salida = salida + "i";
                } else if (j == 6 || j == 7){
                    salida = salida + "o";
                } else if (j == 10 || j == 11){
                    salida = salida + (char)0xC3;
                    salida = salida + (char)0xB1;
                } else {
                    salida = salida + "u";
                }
            } else {
                salida = salida + " ";
            }
            i = i + 1;
        } else {
            salida = salida + " ";
        }
    }
    return salida;
}


string procesar_linea (string linea){
    string resultado="";
    istringstream iss (linea);
    string palabra;
    while (iss >> palabra){
        resultado=resultado+palabra+"\n";
    }
    resultado=resultado+"FL\n";
    return resultado;
}

//Constructor de la aparicion
Aparicion::Aparicion(Libro *pl_, int nc, int np){
	pl=pl_;
    num_capitulo=nc;
    num_parrafo=np;
}

//Mostrar una aparicion haciendo uso de mostrar corto de un libro.
void Aparicion::mostrar(){
    pl->mostrarCorto();
    cout << ", Cap. " << num_capitulo << ", par. " << num_parrafo << endl;
}

//Operador < para ver si una aparicion es menor a otra. (Orden de ISBN. A gualdad, menor numero de capitulo y parrafo).
bool Aparicion::operator< (const Aparicion &otra) const{
    if (pl->getISBN() < otra.pl->getISBN()){
        return true;
    } else if (pl->getISBN() > otra.pl->getISBN()){
        return false;
    } else if (num_capitulo < otra.num_capitulo){
        return true;
    } else if (num_capitulo == otra.num_capitulo){
        return num_parrafo < otra.num_parrafo;
    }
    return false;
}

//Operador == para ver si dos apariciones son iguales.
bool Aparicion::operator== (const Aparicion &otra) const{
    return pl->getISBN() == otra.pl->getISBN() && num_capitulo == otra.num_capitulo && num_parrafo == otra.num_parrafo;
}

