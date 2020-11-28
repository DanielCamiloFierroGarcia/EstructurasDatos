#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include<stdio.h>
#include<string.h>
#include <unordered_map>
#include <queue>
#include <map>
#include <climits>
#include <iterator>
#include <algorithm>

using namespace std;



struct bus{
  string codigo;
  string tipo;
  int capacidad;
  int disponibilidad;
};

struct ruta {  //estructura de ruta
    string rutaid;
    string dia;
    string origen;
    string destino;
    //int hora;
    int km;
};

struct viaje { //estructura de viaje
    string rutaid;
    string busid;
    string viajeid;
    int fecha;
    int hora;
    string conductor;
    double costo;
    bus busviaje;
};
struct reserva{
    string agenciaid;//id de la agencia
    int silla;// silla del tiquete
    int codreserva;//id del codigo de reserva
    string rutaid;//id de la ruta
    string busid;// id del bus
    string viajeid;// id viaje
    string nombre;// nombre pasajer
    int fecha;//fecha de compra tiquete
    int hora;//hora compra de reserva
    double precio;//precio de la reserva
};
struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};
reserva *res;
//Prototipo de funciones
vector <string> pedirComando(); //Pide y tokeniza los comandos escritos
vector <string> leerPass(); //Obtiene todos los usuarios y contraseñas en un vector de string
void ayuda(); //Lista de ayuda de todos los comandos
void listar_buses(string nombre);//Imprime pantallazos de los buses de la agencia
void listar_rutas();
void listar_viajes();
//funciones segunda entrega
bool reservacion(string origen, string destino, int fecha, int hora, string pasajero, string agencia);//genera la reserva
void reporte_ventas(int fechainicial, int fechafinal);//genera el reporte de ventas
int fechas(int fechainicial, int fechafinal, int fecha);//verifica las fechas
void cancelar( string viajeid, int silla );
void disponibilidad (string ciudadOrigen, string ciudadDestino, string nombre); //Genera un reporte de todos los viajes que cubren la ruta entre el origen y el destino
void cambiar(int codreserva,string newviajeid,string nombre);

//funciones para comprimir
Node* getNode(char ch, int freq, Node* left, Node* right);
void encode(Node* root, string str,unordered_map<char, string> &huffmanCode);
void decode(Node* root, int &index, string str);
void buildHuffmanTree(string text);
#endif // GUI_HPP_INCLUDED
