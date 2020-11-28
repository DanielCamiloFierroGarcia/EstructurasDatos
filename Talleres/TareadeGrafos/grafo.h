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
    list<pair<int, int>> *listaAdy;
    int tam;
public:
    Grafo(int V); // Constructor
    void insertaArista(int v, int w, int peso);
    void mostrarGrafo();
// Funcion recorrido en profundidad a partir de vertice v
    void DFS(int v);
// Funcion recorrido en amplitud a partir de vertice v
    void BFS(int s);
};
//Constructor, inicializa el arreglo de listas enlazadas
Grafo::Grafo(int V)
{
    this->V = V;
    listaAdy = new list<pair<int, int>>[V];
    this->tam=0;


}
// La lista de adyacencia es un contenedor de la STL
// push_back agrega un elemento al final de la lista
// Tambi´en se puede usar Vector
void Grafo::insertaArista(int v, int w, int peso)
{
// agrega vertice w a la lista de vertices adyacentes a v.
    listaAdy[v].push_back(make_pair(w, peso));
    listaAdy[w].push_back(make_pair(v, peso));
}

/*void Grafo::BFS(int s)//esta es la funcion de recorrido BFS de las diapositivas, pero ahora me da error no se porque
{
    bool *visitado = new bool[V];
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
    }
}*/
void Grafo::mostrarGrafo(){
    for(int i=0; i<V; i++){
        if(i>0){
            cout<<"Vertice "<<i<< " ";
        }
        for(auto v: listaAdy[i]){
            cout<<v.first<< "tiene de peso: "<<v.second<<endl;
        }
        cout<<endl;
    }
}







#endif // GRAFO_H_INCLUDED
