#include <iostream>
using namespace std;
#include "grafo.h"

//Corresponde a la primera parte de la tarea asignada de grafos

struct arista
{
    char uno;
    char dos;
};
char vect[5];
arista arr[7];
int main()
{
    // Crea el grafo
       Grafo g(10);
    //Inserta cinco aristas
        g.insertaArista(1, 2, 2);
        g.insertaArista(2, 2, 3);
        g.insertaArista(5, 4, 1);
        g.insertaArista(6, 1, 5);


        g.mostrarGrafo();




    /*
        arreglo_v[0]='a';
        arreglo_v[1]='b';
        arreglo_v[2]='c';
        arreglo_v[3]='d';
        arreglo_v[4]='e';



        arreglo_a[0].uno=arreglo_v[2];
        arreglo_a[0].dos=arreglo_v[1];
       arreglo_a[1].uno=arreglo_v[4];
        arreglo_a[1].dos=arreglo_v[1];
        arreglo_a[2].uno=arreglo_v[0];
        arreglo_a[2].dos=arreglo_v[1];
        arreglo_a[3].uno=arreglo_v[4];
        arreglo_a[3].dos=arreglo_v[2];
        arreglo_a[4].uno=arreglo_v[3];
        arreglo_a[4].dos=arreglo_v[4];
        arreglo_a[5].uno=arreglo_v[1];
        arreglo_a[5].dos=arreglo_v[1];
        arreglo_a[6].uno=arreglo_v[2];
        arreglo_a[6].dos=arreglo_v[4];
        //cout<<arreglo_a[0]->uno;


        for(int i=0; i<7; i++){
            cout<<"vertice "<<i+1<<arreglo_a[i].uno<<" "<<arreglo_a[i].dos<<endl;
        }*/
    return 0;
}
