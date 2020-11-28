#ifndef ARBOLITO_HXX_INCLUDED
#define ARBOLITO_HXX_INCLUDED

#include "nodo.h"

void arbolBinario :: crear(int n) //crea el nodo
{
    nodo *temp=raiz, *nuevoNodo;
    nuevoNodo=new nodo(n);
    insertar(temp,nuevoNodo);
}


void arbolBinario :: insertar (nodo* &temp, nodo* nuevoNodo)//inserta un nodo creado
{

    if(temp==NULL) //arbol nuevo no habia raiz
    {
        temp=nuevoNodo;
        raiz=temp;
        cout<<"No habia raiz"<<endl;
    }
    else if(temp->datos<nuevoNodo->datos)
    {
        cout<<"crea hijo  a derecha"<<endl;
        insertar(temp->izquierdo, nuevoNodo);
        if(temp->izquierdo==NULL)
        {
            temp->izquierdo=nuevoNodo;
        }
    }
}

void arbolBinario:: pintarArbol (nodo *raiz)
{
    if(raiz==NULL)
    {
        return;
    }

    cout<<raiz->datos;
    pintarArbol(raiz->izquierdo);
    pintarArbol(raiz->derecho);
}

nodo* arbolBinario:: devRaiz (){
  return raiz;
}

#endif // ARBOLITO_HXX_INCLUDED
