#ifndef ARBOLITO_H_INCLUDED
#define ARBOLITO_H_INCLUDED
#include "nodo.h"

using namespace std;



struct arbolBinario
{
public:
    arbolBinario() //contructor
    {
        raiz=NULL;
    }

    void crear(int n);
    void insertar(nodo* &temp, nodo* nuevoNodo);
    void pintarArbol(nodo* raiz);
    nodo* devRaiz();
    //void eliminar(int);
    //void preorden(nodo*)
private:
    nodo* raiz;
};

#include "arbolito.hpp"
#endif // ARBOLITO_H_INCLUDED
