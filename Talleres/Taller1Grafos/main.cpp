#include <iostream>
#include<stdlib.h>      //librerias.
#define Max 100
using namespace std;

void menu();
//autores: Omar romaña
//fecha: 25/04/2016.

//matriz de adyacencia
int MatrizAdyacente[Max][Max]; //creamos una matriz para mostrar la matiz adyacente

class nodoa { //creamos una clase y le damos como nombre nodoa.
   public: //creamos nuestro acceso público.
// para que cualquier miembro del nodo accesible desde cualquier parte del progrma.

    int ady;
    int peso;  //nombramos variables enteras.
    nodoa *siguiente; //creamos un puntero.
    nodoa(int v,int p, nodoa *sig = NULL)
    {
       ady = v;
       peso=p;        //creamos un constructor para nuestro grafo.
       siguiente = sig;
    }
};


struct nodo { //creamos nuestro nodo principal.

   public: //creamos nuestro acceso
   // para que cualquier miembro del nodo accesible desde cualquier parte del progrma.
    int vertice; //creamos una varible entera.
    nodoa *puntero; //creamos un nuevo puntero utilizando la clase anteriormente creada
    nodo *siguiente; //creamos un nuevo puntero
    nodo(int v, nodo *sig = NULL,nodoa *punt=NULL)
    {
       vertice = v;
       siguiente = sig;   //creamos un primer nodo constructor.
	   puntero=punt;
    }

    class lista; //creamos una clase lista
};

typedef nodo *pnodo; //creamos un nuevo puntero.

class lista {
   public:	  //creamos nuestro acceso púbiclo
   // para que cualquier miembro del nodo accesible desde cualquier parte del progrma.
    pnodo primero;  //creamos un nuevo puntero de tipo pnodo

	lista() { primero =  NULL; }// crea la lista vacia

	//nuestras funciones pincipales.
	void Insertarv(int v); // función para insertar los datos.
    bool ListavVacia();  //función para revisar si nuestra lista esta vacio
     pnodo Buscarv( int v); //función para buscar.
    bool listavexiste(int i,int f);//función booleana para verificar si nuestro grafo esta vacio
	void creararco(int i,int f,int peso);//función para crear los arcos de nuestro grafo.
	void CrearMatriz(); //función para crear nuestra matriz adyacente.
	void mostrarmatriz();//función para mostrar nuestra matriz.
    int CantidadVertices();//función para contar nuestros vertices o nodos.
    int ExisteArco(int i,int f);//función para  verificar si nuestro grafo tiene arcos
    bool BuscarAdy(pnodo aux,int ad);//función booleana para verificar si nuestro grafo tiene arcos
    int distancia(int i, int f);//funcion para encontrar la distancia entre dos nodos


};

void lista::creararco(int i,int f,int peso){ //función para crear un nuevo arco
	pnodo pos; // creamos un nuevo puntero
	pos=primero;
	if(listavexiste(i,f)){
	while(pos!=NULL){ // se recorre la lista  hasta encontrar el valor buscado
		if(i == pos->vertice ){

			if(pos->puntero==NULL){	//sentencia if para verificar
				pos->puntero=new nodoa(f,peso); //creamos un nuevo constructor
			}
			else {
				nodoa *temp=pos->puntero; //creamos un nuevo puntero y lo igualamos
					while(temp->siguiente!=NULL){ //ciclo mientras
						temp=temp->siguiente; //guardamos los datos.
					}
					temp->siguiente=new nodoa(f,peso); //creamos un nuevo constructor
					temp=NULL; //lo igualamos a NULL
					delete temp; //eliminamos el
				}
				}
			pos=pos->siguiente;//guerdamos los datos.
			}
	}

//terminamos nuestra función para crear los arcos  de nuestro grafo.

}

bool lista::listavexiste(int i,int f){ //función booleana
	if(Buscarv(i)!=NULL&&Buscarv(f)!=NULL){ //sentencia if.
	return true; //retornamos verdadero o 1
	}
	else{ //sino
	return false; //retornamos falso o 0.
	}
// función para verificar si nuestro grafo tiene arcos.
}

void lista::Insertarv(int v){ //función para insertar los datos a nuestro grafo
   pnodo  anterior;   //creamos un nuevo puntero
   if(ListavVacia()) // Si la lista está vacía
   {
	  primero = new nodo(v, primero);   //creamos un nuevo nodo
   }else { if(v<=primero->vertice){ //si el valor a insertar es menor que el
	      primero =new nodo(v, primero) ;            //se inserta el nodo antes del primer dato de la lista
		}else{
			//en caso contrario se busca el nodo que tenga un dato menor a valor
			anterior = primero; // Avanzamos hasta que el siguiente tenga un valor mayor que valor
			while((anterior->siguiente) && (anterior->siguiente->vertice<=v)){
				anterior = anterior->siguiente; }
			   // Creamos un nuevo nodo después del nodo anterior, y cuyo siguiente
               // es el siguiente del anterior
			   anterior->siguiente = new nodo(v, anterior->siguiente);
			}

//función para insertar los datos a nuestro grafo
}
}

bool lista::ListavVacia(){ //función booleana.
	return primero == NULL; //verificamos si nuestro grafo esta vacio.
	//función para verificar si nuestro grafo tiene vertices o nodos.
}

int lista::CantidadVertices(){ //función para contar nuestro vertices o nodos
    pnodo nodo=primero; //creamos un nuevo nodo y lo igualamos a otro.
    int i=0;//creamo una nueva variable entera y la igualamos a 0
    while(nodo!=NULL){//ciclo mientras, si nuestro nodo es distinto de NULL
       i++;//le sumamos 1 a nuestra variable.
       nodo=nodo->siguiente;  //igualamos nuestro nodos, para poder sumar la cantidad de los mismos
    }
    return i; //retornamos i.
}

int lista::ExisteArco(int i,int f){//función para poder realizar la matriz adyacente
  pnodo nodo; //creamos un nuevo nodo.
  int a=1;//creamos una variable entera, y la inicializamos en 1
    nodo=Buscarv(i);//igualamos nuestro nodo a la función buscar.
    if(nodo){ //sentencia if, utilizando el nodo creado.
         if(BuscarAdy(nodo,f)){ //sentencia if, llamamos a nuestra función booleana.
		 return a; //retornamos a
		 }else{
		 return a=0; //retornamos a
		 }
    }
}

bool lista::BuscarAdy(pnodo aux,int ad){ //función booleana para poder realizar la matriz adyacente
     nodoa *temp=aux->puntero; //creamos un nuevo puntero.
     bool a;  //creamos un varible de tipo boolena.
     while(temp){ //ciclo while o mientras.
        if(ad==temp->ady){ //sentencia if.
           return a=true;} //retornamos a verdadero.
        temp=temp->siguiente;//igualamos nuestro puntero para que verifique todos los valores.
     }
	 return a=false;// sino retornamos a falso
}

pnodo lista::Buscarv(int valor){ //función para buscar valores dentro de nuestro grafo
	int z;
	pnodo indice,n=NULL; //creamos un nuevo nodo e igualamos a la varible n a NULL
	indice=primero; //igualamos nuestro
	while(indice!=NULL){ // se recorre la lista  hasta encontrar el valor buscado
	if(valor == indice->vertice ){
			return indice; // al encontar el valor  lo retorna
    	}
		indice=indice->siguiente; //igualamos nuestros nodos para que verifiquen nuestros datos
	}
    cout<<"\n\n\tEL VALOR BUSCADO NO ESTA EN EL GRAFO";
 return n; // si el valor buscado no esta en la lista retorna nulo
}

void lista::CrearMatriz(){ //función para crear nuestra matriz adyacente.
     pnodo nodo=primero,nodotemp; //creamos un nuevo puntero y lo igualamos.
     int i,j,inicio,fin; //creamos nuestras variables enteras.
     int cant=CantidadVertices(); //creamos un varibale entera y la igualamos a nuestra función cantidad de vertices.
     for(i=0;i<cant;i++){ //ciclo for
         nodotemp=primero;//igualamos nuestros punteros.
       for(j=0;j<cant;j++){//ciclos for
       //guardamos en la matriz creada anteriormente los datos de nuestra función existe arco.
         MatrizAdyacente[i][j]=ExisteArco(nodo->vertice,nodotemp->vertice);
         nodotemp=nodotemp->siguiente; //igualamos nuestros punteros para que verifiquen todos los datos.
       }
        nodo=nodo->siguiente;//igualamos nuestros punteros para que verifiquen todos los datos.
     }
     delete nodo; //eliminamos nodo  al terminar los ciclos for
     delete nodotemp;  //eliminamos nodotemp al terminar los ciclos for.
}

void lista::mostrarmatriz(){ //función para mostrar nuestra matriz adyacente.
    int i,j,cant; //creamos varibales enteras
    pnodo nodo=primero; //creamos un nuevo puntero.
    cant=CantidadVertices(); //igulamos  la varibale creada anteriormente a la cantidad de vertices.
	cout<<"   "; //espacios

    for(i=0;i<cant;i++){ //ciclo for.
	cout<<"\t"<<nodo->vertice<<" "; //mostramos los nodos o vertices del grafo.
	nodo=nodo->siguiente; //igualamos los punteros para que muestre todos los vertices

	}
    nodo=primero; //igualamos los punteros
	cout<<"\n\n"; //saltos de linea.

    for( i=0;i<cant;i++){ //ciclo for.

		 cout<<nodo->vertice; //mostramos los vertices de nuestro grafo.
         for(j=0;j<cant;j++){ //ciclo for
			cout<<"\t"<<MatrizAdyacente[i][j]<<" "; //mostramos los datos guardados en la matriz.
         }
         nodo=nodo->siguiente; //igualamos los punteros para que muestre todos los datos.
         cout<<"\n"; //salto de linea.
    }
}

int lista::distancia(int i, int f){//aque se planea inicialisar el primer puntero que corresponda al valor i (nodo inicial, y que sume los pesos de las aristas hasta que encuentre el nodo final
    int distancia=0;
    nodoa *temp;
    if(primero->puntero->ady==i){
        temp=primero->puntero;
    }

     while(temp->ady!=f){
        distancia=distancia+temp->peso;
        temp=temp->siguiente;
     }

    return distancia;
}




int main(){ //función principal.
menu();
return 0;//retornamos el control a nuestro sistema operativo.
}

void menu(){
	system("cls");
	int op1=0,valor=0; //creamos 2 varibles enteras.
	lista l; //creamos una nueva clase.
	  l.Insertarv(1);
		l.Insertarv(2);
		l.Insertarv(3);
		l.Insertarv(4);
		l.Insertarv(5);
		l.Insertarv(6);

		l.creararco(1,2,7);
		l.creararco(2,4,8);
		l.creararco(4,6,9);
		l.creararco(3,1,10);
		l.creararco(3,2,11);
		l.creararco(3,5,12);
		l.creararco(5,2,13);
		l.creararco(5,4,14);
		l.creararco(5,6,15);



		cout<<"\n"; //salto de linea
	cout<<"\n\n\tGRAFO DIRIGIDO ALGORITMOS"; //mensaje
	cout<<"\n";
    cout<<"\n\n\t1. Mostrar Matriz Adyacente";
    cout<<"\n\n\t2. Buscar";
    cout<<"\n\n\t3. Salir";
    cout<<"\n";
	cout<<"\n";
    cout<<"\nIngrese opcion: ";
	cin>>op1;
switch(op1){
case 1:
	system("cls");
    cout<<"\n"; //salto de liena
  	cout<<"\n\n\tMATRIZ DE ADYACENCIA"<<"\n\n"; //mensaje
	l.CrearMatriz(); //llamamos a nuestra función para que cree la matriz con los datos ingresados
	l.mostrarmatriz(); //mostramos la matriz adyacente.
    cout<<"\n";
    cout<<"\n";
    system("pause");
    menu();
break;

case 2:
	system("cls");
	cout<<"\nIngrese numero que desea buscar: ";
	cin>>valor;
	l.Buscarv(valor); //función para buscar valores en nuestro grafo
	cout<<"\n";
	cout<<"\n";
	system("pause");
	menu();
break;
case 3:
system("cls");
cout<<"\n";
cout<<"\n";
return;
break;
default:
        system("cls");
        cout<<"\n\n\tOPCION NO VALIDA"; //manejo de excepciones.
        cout<<"\n";
        system("pause");
		menu();
		break;
}
}
