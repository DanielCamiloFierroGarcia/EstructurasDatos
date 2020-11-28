#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED



#include <stack>
#include <fstream>




#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include "arbol.h"
using namespace std;

struct nodo{
    char dato;
    nodo *izq;
    nodo *der;
    nodo *padre;
};

void menu();

void lectura();

nodo *crearNodo (char n);
void insertarNodo (nodo *&arbol, char d);
void insertarIzq (nodo *&arbol, char d);
void insertarDer (nodo *&arbol, char d);
void mostrarArbol (nodo *arbol, int cont);

void preOrden (nodo *arbol);
void inOrden (nodo *arbol);

//Funciones para la eliminacion
void eliminar (nodo *arbol, char ele);
void eliminarNodo(nodo *eli);
nodo *minimoNodo(nodo *arbol);
void reemplazar (nodo* arbol, nodo *nuevo);
void destruirNodo (nodo *dest);

nodo *arbol=NULL;



//funciones

void menu(){
    int  resp, cont=0;
    char dato;
    string resp2;
    do{
        cout<<"MENU"<<endl;
        cout<<"1. Insertar nodo"<<endl;
        cout<<"2. Inserciones manuales"<<endl;
        cout<<"3. MOstrar arbol"<<endl;
        cout<<"4. Recorrido preorden"<<endl;
        cout<<"5. Recorrido inorden"<<endl;
        cout<<"6. Elimidar nodo"<<endl;
        cout<<"7. Salir"<<endl;
        cin>>resp;

        switch (resp){
        case 1:

               cout<<"Digite dato a insertar"<<endl;
                cin>>dato;
                insertarNodo(arbol, dato);//inserta el dato al nodo
                cout<<endl;


            system ("pause");
            break;
        case 2:/*

               insertarNodo(arbol, '/');
               insertarIzq(arbol, '*');
               insertarDer(arbol, '-');
               if(arbol->dato=='*'){
                insertarIzq(arbol, '+');
               }*/


              /*

               insertarDer(arbol, '2');
               insertarIzq(arbol, 'x');
               insertarDer(arbol, '*');
               insertarIzq(arbol, '2');
               insertarDer(arbol, 'y');*/


            system ("pause");
            break;
        case 3:
            cout<<"Mostrar arbol"<<endl;
            mostrarArbol(arbol, cont);
            cout<<endl;
            system("pause");
            break;

        case 4:
            cout<<"Se recorre arbol en preorden"<<endl;
            preOrden(arbol);
            system("pause");
            break;
        case 5:
            cout<<"Se recorre arbol en inorden"<<endl;
            inOrden(arbol);
            system("pause");
            break;

        case 6:
            cout<<"Que numero a eliminar"<<endl;
            cin>>dato;
            eliminar(arbol, dato);
            system("pause");
            break;
        }
        system("cls");
    }while(resp!=7);
}

/*void lectura(){
    char s;
    int i=0;
    ifstream elArchivo;
    elArchivo.open("calificaciones.txt", ios::in);

if (elArchivo.is_open())
  {
      //elArchivo.open("archivo.txt", ios::in);
    while(!elArchivo.eof()){
        getline(elArchivo, s);

        vect[i]=s;
        i++;
    }
  }

   elArchivo.close();
}*/

nodo *crearNodo (char n){
    nodo *nuevoNodo=new nodo();
    nuevoNodo->dato=n;
    nuevoNodo->der=NULL;
    nuevoNodo->izq=NULL;
    //nuevoNodo->padre=padre;
    return nuevoNodo;
}

void insertarNodo (nodo *&arbol, char d){
    if(arbol==NULL){
        nodo *nuevoNodo= crearNodo(d);
        arbol=nuevoNodo;
    }

    else{
       int valorRaiz= arbol->dato;
       if(d=='/' || d=='*' || d=='^' || d=='+' || d=='/'){//si el elemento es un operador siga por izq
        insertarNodo(arbol->izq, d);
       }
       else{
        insertarNodo(arbol->der, d);
       }
    }
}/*
void insertarIzq (nodo *&arbol, char d, nodo *padre){


    if(arbol==NULL){
        nodo *nuevoNodo= crearNodo(d);
        arbol=nuevoNodo;
    }

    else{
       insertarIzq(arbol->izq, d);
    }
}*/

void insertarDer (nodo *&arbol, char d){
    if(arbol==NULL){
        nodo *nuevoNodo= crearNodo(d);
        arbol=nuevoNodo;
    }

    else{
       insertarDer(arbol->der, d);
    }
}
void mostrarArbol (nodo *arbol, int cont){
    if(arbol==NULL){
        return;
    }
    else{
        mostrarArbol(arbol->der, cont+1);
        for(int i=0; i<cont; i++){
            cout<<"   ";
        }
        cout<<arbol->dato<<endl;
        mostrarArbol(arbol->izq, cont+1);
    }
}



void preOrden (nodo *arbol){//recorrer en preorden
    if(arbol==NULL){
        return;
    }
    else{
        cout<<arbol->dato<<" - ";
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}
void inOrden (nodo *arbol){
    if(arbol==NULL){
        return;
    }
    else{
        inOrden(arbol->izq);
        cout<<arbol->dato<<" - ";
        inOrden(arbol->der);
    }
}

//implementacion funciones eliminar
void eliminar (nodo *arbol, char ele){//el ele corresponde a el elemento a buscar y eliminar del arbol
    if(arbol==NULL){
        return;
    }
    else if(ele<arbol->dato){//si el ele es menor, busqueda por izquierda
        eliminar(arbol->izq, ele);
    }
    else if(ele>arbol->dato){//ahora por la derecha
        eliminar(arbol->der, ele);
    }
    else{//valor encontrado
        eliminarNodo(arbol);
    }
}
void eliminarNodo(nodo *eli){//elimina el nodo
    if(eli->izq && eli->der){//evalua si el nodo tiene parte derecha e izquierda
        nodo *menor=minimoNodo(eli->der);
        eli->dato=menor->dato;
        eliminarNodo(menor);
    }
    else if(eli->izq){//tiene hijo izq
        reemplazar(eli,eli->izq);
        destruirNodo(eli);
    }
    else if(eli->der){
        reemplazar(eli, eli->der);
        destruirNodo(eli);
    }
    else{//nodo hoja
         reemplazar(eli, NULL);
         destruirNodo(eli);
    }
}
nodo *minimoNodo(nodo *arbol){//determina el nodo mas a la izquierda
    if(arbol==NULL){
        return NULL;
    }
    if(arbol->izq){//si hay hijo izq
        return minimoNodo(arbol->izq);//se busca lo mas a la izq
    }
    else{
        return arbol;// al no haber mas hijo a izq retornaria el nodo
    }
}
void reemplazar (nodo* arbol, nodo *nuevo){
     if(arbol->padre){
        //se asigna arbol->padre su nuevo hijo
        if(arbol->dato==arbol->padre->izq->dato){
            arbol->padre->izq=nuevo;
        }
        else if(arbol->dato==arbol->padre->der->dato){
            arbol->padre->der=nuevo;
        }
     }
     if(nuevo){//si ese ndo existe
        //se asigna nuevo padre
        nuevo->padre=arbol->padre;
     }
}
void destruirNodo (nodo *dest){//elimina el nodo
    dest->izq=NULL;
    dest->der=NULL;
    delete dest;
}




#endif // ARBOL_H_INCLUDED
