#include "interprete.hpp"
#include <iostream>

using namespace std;


//En el main se van leyendo los comandos, que se procesan en el interprete.
int main(){
    string comando;
    while (cin >> comando && comando != "s"){
        interprete(comando);
    }
    
}
