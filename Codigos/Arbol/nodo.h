#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED
using namespace std;

struct nodo{
    int datos;
    nodo *izquierdo;
    nodo *derecho;
    nodo(int d){//constructor
        datos=d;
        izquierdo=NULL;
        derecho=NULL;
    }
};


#endif // NODO_H_INCLUDED
