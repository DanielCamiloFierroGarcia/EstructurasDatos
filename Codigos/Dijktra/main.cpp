#include <iostream>
#include <queue>
#include <vector>
#define MAXV 100
#define lim 0x3f3f3f3f
using namespace std;


struct vertice{
	char nodo;
	int cost;
	//char etique;
	vertice(char _nodo, int _cost) : nodo(_nodo), cost(_cost) {}
	vertice() : nodo(-1), cost(-1) {}
};

struct Grafo{
	vector<vertice> G[MAXV];
	int V;
	int E;
};

struct Esta{
	char nodo;
	int cost;
	Esta(char _nodo, int _cost) : nodo(_nodo), cost(_cost) {}
	bool operator <(const Esta &b) const {

		return cost > b.cost;
	}
};

int algoritmo(const char begin, const char end, const Grafo grafo){
	priority_queue<Esta> pq;
	vector<int> Dist(grafo.V, lim);
	vector<bool> mark(grafo.V, false);

	Dist[begin] = 0;
	pq.push(Esta(begin, 0));
	while(!pq.empty()){

		Esta st = pq.top(); pq.pop();
		mark[st.nodo] = true;
		if (st.nodo == end){
			return st.cost;
		}
		int T = (int)grafo.G[st.nodo].size();
		//cout<<"Prueba1"<<!mark[grafo.G[st.nodo][0].nodo]<<endl;
		//cout<<"Prueba2"<<Dist[st.nodo] + grafo.G[st.nodo][0].cost<<endl;
		//cout<<"Prueba3"<<Dist[grafo.G[st.nodo][0].nodo]<<endl;
		for(int i = 0; i < T; ++i){
			if (!mark[grafo.G[st.nodo][i].nodo] && ((Dist[st.nodo] + grafo.G[st.nodo][i].cost) < Dist[grafo.G[st.nodo][i].nodo])){
//cout<<"entra";
				Dist[grafo.G[st.nodo][i].nodo] = st.cost + grafo.G[st.nodo][i].cost;
				pq.push(Esta(grafo.G[st.nodo][i].nodo, st.cost + grafo.G[st.nodo][i].cost));

			}
		}
	}
	return -1;
}

struct Programa{
	int V, E;
	char comienzo, fin;
	void definirGrafo(Grafo& grafo){
		cout << "Ingrese Cantidad de Vertices: " << endl;
		cin >> V;
		cout << "Ingrese Cantidad de Aristas: " << endl;
		cin >> E;

		grafo.V = V;
		grafo.E = E;
	}
	void cargarGrafo(Grafo & grafo){
		for (int i = 0; i < E; ++i){
			char Origen, Destino;
			int Peso;
			cout << "Ingrese Origen: " << endl;
			cin >> Origen;
			cout << "Ingrese Destino: " << endl;
			cin >> Destino;
			cout << "Ingrese Peso de la Arista: " << endl;
			cin >> Peso;

			grafo.G[Origen].push_back(vertice(Destino, Peso));
			grafo.G[Destino].push_back(vertice(Origen, Peso));
		}
	}
	void Dijkstra(Grafo grafo){
		cout << "Ingrese Vertice Inicial: " << endl;
		cin >> comienzo;
		cout << "Ingrese Vertice Final: " << endl;
		cin >> fin;
		int n = algoritmo(comienzo, fin, grafo);
		cout<<"El n es"<<n;
		cout << "Longitud del Camino mas Corto: " << n << endl;
	}
};

int main(){
	bool out=false;
	char salir;

	Programa programa;
	Grafo grafo;


	while (!out){
	programa.definirGrafo(grafo);
	programa.cargarGrafo(grafo);
	programa.Dijkstra(grafo);

	cout << "Salir? (S/N)" << endl;
	cin >> salir;
		if (salir == 'S'){
			out = true;
		}
	}
}
