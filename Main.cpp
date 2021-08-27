#include <iostream>
#include "Matriz.h"
using namespace std;

/*Matriz de teste*/

int main(){
    Matriz m;
    m.criarNosCabecaMatriz(2,2);
    m.insere(1, 1, 10);
    m.insere(2, 2, 15);
    m.imprime();
}
