#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <list>
#include <map>
using namespace std;
struct Grafo
{
    int V; // numero de vertices
// Lista de adyacencia como un arreglo de vertices
    list<int> *listaAdy;
    bool contCiclos;

public:
    Grafo(int V); // Constructor
    void insertaArista(int v, int w);
    void mostrarGrafo();
// Funcion recorrido en profundidad a partir de vertice v
    void DFS(int v);
// Funcion recorrido en amplitud a partir de vertice v
    void BFS(int s);
    bool ciclico( bool var);
};
//Constructor, inicializa el arreglo de listas enlazadas
Grafo::Grafo(int V)
{
    this->V = V;
    listaAdy = new list<int>[V];

    this->contCiclos=false;

}
// La lista de adyacencia es un contenedor de la STL
// push_back agrega un elemento al final de la lista
// Tambi´en se puede usar Vector
void Grafo::insertaArista(int v, int w)
{
// agrega vertice w a la lista de vertices adyacentes a v.
    listaAdy[v].push_back(w);
    listaAdy[w].push_back(v);
}

void Grafo::BFS(int s)
{
    bool *visitado = new bool[V];
    //int cont=0;
    for(int i = 0; i < V; i++)
        visitado[i] = false;
    list<int> cola;
    visitado[s] = true;
    cola.push_back(s);
    list<int>::iterator i;
    while(!cola.empty())
    {
        s = cola.front();
        cout << s << " ";
        cola.pop_front();
        for (i = listaAdy[s].begin(); i != listaAdy[s].end(); ++i)
        {
            if (!visitado[*i])
            {
                visitado[*i] = true;
                cola.push_back(*i);
            }
        }
        if(cola.front()==cola.back()){//aca se intenta verificar que si el elemento final despues de recorrer es el mismo que el inicial, entonces existe un ciclo
            contCiclos=true;
            ciclico(contCiclos);

        }
    }
}

//esta es la funcion que mostraba el grafo con los pesos
/*void Grafo::mostrarGrafo(){
    for(int i=0; i<V; i++){
        if(i>0){
            cout<<"Vertice "<<i<< " ";
        }
        for(auto v: listaAdy[i]){
            cout<<v.first<< "tiene de peso: "<<v.second<<endl;
        }
        cout<<endl;
    }
}*/
//si la funcion retorna true, significa que el grafo tiene al menos un ciclo, de lo contrario es un grafo aciclico
//se procedio a utilizar el recorrido en BFS para recorrer el grafo y se modifico para que si cumple la condicion de que su vertice final sea el mismo inicial daria como resultado un ciclo
bool Grafo::ciclico ( bool var){
    if(contCiclos==true){
        return true;
    }
}







#endif // GRAFO_H_INCLUDED
