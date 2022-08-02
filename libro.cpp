#include <iostream>
#include "libro.hpp"

using namespace std;

//Constructor del libro.
Libro::Libro(){
	ISBN = 0;
    ano = 0;
    num_capitulos = 0;
    titulo = "";
    autores = "";
}

//Metodo de consulta de los capitulos de un libro.
int Libro::numero_capitulos(){
    return num_capitulos;
}

//Metodo de consulta del ISBN de un libro.
long long Libro::getISBN(){
    return ISBN;
}

//Metodo que lee la información de un libro.
void Libro::leer(){
    //string c;
    //cin >> c;
    long long ISBN_leido;
    cin >> ISBN_leido;
    ISBN = ISBN_leido;
    int ano_leido;
    cin >> ano_leido;
    ano=ano_leido;
    int capitulos;
    cin >> capitulos;
    num_capitulos=capitulos;
    cin.ignore();
    getline(cin, titulo);
    getline(cin, autores);
}

//Muestra de forma "corta" la información de un libro.
void Libro::mostrarCorto(){
    cout << titulo << ", " << autores << ", " << ano;
}

//Muestra de forma "larga" la información de un libro.
void Libro::mostrarLargo(){
    cout << titulo << endl;
    cout << autores << ", " << ano << endl;
    cout << num_capitulos << " capítulos" << endl;
}
