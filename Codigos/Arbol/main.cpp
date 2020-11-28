#include <iostream>
#include "arbolito.h"
using namespace std;



int main()
{

   arbolBinario a=arbolBinario();
   a.crear(12);
   a.devRaiz()->derecho=new nodo(25);
   a.pintarArbol(a.devRaiz());
     return 0;
}
