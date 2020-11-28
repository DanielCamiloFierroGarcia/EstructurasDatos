#include <iostream>


using namespace std;
/*int suma (int n){
    int res=0;
    for(int i=0; i<=n;i++){
        res+=i;
    }
    return res;
}*/
bool buscar (int tam, int busqueda, int vetor[]){
    for(int i=0; i<tam; i++){
        if(vetor[i]==busqueda){
            return true;
        }
        else{
            return false;
        }
    }
}//returna true si lo encontro, false si no lo encuentra
int main()
{





    /*int num=0;
    cout<<"Ingrese la cantidad de numeros"<<endl;
    cin>>num;

    cout<<"La suma es: "<<suma(num);*/

    /*int matriz [100][100];
    int c=0;

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            c++;
            matriz[i][j]=c;
            cout<<matriz[i][j]<<"-";

        }
    }*/
    return 0;
}



