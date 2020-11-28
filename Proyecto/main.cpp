#include "GUI.hpp"


//Función principal
int main()
{
    bool menu = 1, menu2 = 1, encontro = 0;
    string nombre;
    int fecha=0, fecha2=0, hora=0;
    int finicial=0, ffinal=0;
    struct tm tiempoLocal;
    // El lugar en donde se pondrá la fecha y hora formateadas
    char fechaHora[70];
    // El formato. Mira más en https://en.cppreference.com/w/c/chrono/strftime
    char *formato = "%Y%m%d";
    int bytesEscritos;


    vector <string> comando,usuarios;//Guardar los tokens del comando y guardar todos los usuarios junto a sus contraseñas respectivamente.
    string pass; //Donde se guardara la contraseña digitada por el usuario
    string newidviaje;
    int newsilla;
    int usuario; //Guarda el numero del usuario para comprobar si su contraseña es equivalente
    //variables para comprimir
     string text ;
    string ayu=" ";
    char *ptr;
    char buffer[100];
    reserva res[4];
    int fechainicial=0, fechafinal=0;
    ifstream docu;


    do{
        comando = pedirComando();
        if (comando[0]=="login"){
            //Trae todos los usuarios y contraseñas
            usuarios = leerPass();

            //Comprueba si el nombre de usuario existe
            for (unsigned int i = 0; i<usuarios.size();i+=2)
                if (usuarios[i] == comando[1]){
                    encontro = 1;
                    usuario = i;
                }

            if (encontro){ //If exists
                cout<<"Por favor ingrese su contrasenia: \n";
                getline (cin,pass); //Guarda la contraseña digitada por el usuario en pass

                if (usuarios[usuario+1] == pass){ //If is correct
                    system("clear");

                    cout<<"Bienvenido al sistema de la agencia "<<comando[1]<<"!\n\n";
                    cout<<"A continuacion escriba el comando deseado"<<endl;
                    nombre=comando[1];
                    menu2=1;

                    //Menú dentro de la agencia.
                    do{
                        comando = pedirComando();
                        if(comando[0]=="listar_buses"){
                            listar_buses(nombre);
                        }
                        else if(comando[0]=="listar_rutas"){
                            listar_rutas();
                        }
                        else if(comando[0]=="listar_viajes"){
                            listar_viajes();
                        }
                        else if(comando[0]=="logout"){
                            //Cerrar sesión
                            cout<<"Cerrando sesion...";
                            menu2=0;
                        }
                        else if (comando[0]=="disponibilidad"){
                          disponibilidad(comando[1], comando [2], nombre);
                        }
                        else if (comando[0]=="reserva"){
                          system ("clear");

                          fecha2=atoi(comando[3].c_str());
                          hora=atoi(comando[4].c_str());


                          if(reservacion(comando[1], comando[2], fecha2, hora, comando[5], comando[6])==true){
                            cout<<"Se creo la reserva con existo!!!"<<endl;
                        }
                          else{
                              cout<<"No fue posible realizar su reserva"<<endl;
                          }

                        }
                        else if (comando[0]=="reporte_ventas"){
                          finicial=atoi(comando[1].c_str());

                          if(comando[2]=="0"){

                              time_t t = time(NULL);
                              tiempoLocal = *localtime(&t);

                              // Intentar formatear
                              bytesEscritos =
                                  strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);
                              if (bytesEscritos != 0) {
                                // Si no hay error, los bytesEscritos no son 0
                                ffinal=atoi(fechaHora);


                              } else {
                                printf("Error en fecha");
                              }
                          }
                          else{
                            ffinal=atoi(comando[2].c_str());
                          }
                          reporte_ventas(finicial, ffinal);
                        }
                        else if (comando[0]=="cancelar"){
                          cout<<"Por favor ingrese el ID del Viaje: \n";
                          cin>>newidviaje;
                          cout<<"Por favor ingrese el # de la Silla: \n";
                          cin>>newsilla;
                          cancelar(newidviaje,newsilla);
                        }
                        else if( comando[0]=="comprimir"){



                            if(comando.size()==1){
                                fechainicial=20201125;
                                fechafinal=20201125;
                            }
                            else{
                                fechainicial=atoi(comando[1].c_str());
                                fechafinal=stoi(comando[2].c_str());

                            }

                          docu.open("reservas.dat", ios::in);
                          if(docu.fail()){
                            cout<<"Algo anda mal ";
                            exit(EXIT_FAILURE);
                          }

                            for(int i=0; i<3; i++){
                                getline (docu, text);
                                strcpy(buffer, text.c_str());

                                //cout<<buffer<<endl;
                                //cout<<txt<<endl;

                                ptr=strtok(buffer, ";");
                                res[i].agenciaid=ptr;


                                ptr=strtok(NULL, ";");
                                res[i].codreserva=atoi(ptr);


                                ptr=strtok(NULL, ";");
                                res[i].rutaid=ptr;

                                ptr=strtok(NULL, ";");
                                res[i].busid=ptr;

                                ptr=strtok(NULL, ";");
                                res[i].viajeid=ptr;

                                ptr=strtok(NULL, ";");
                                res[i].nombre=ptr;

                                ptr=strtok(NULL, ";");
                                res[i].fecha=atoi(ptr);

                                ptr=strtok(NULL, ";");
                                res[i].hora=atoi(ptr);

                                ptr=strtok(NULL, ";");
                                res[i].precio=atof(ptr );

                                cout<<"fec"<<res[i].fecha;

                                if(res[i].fecha<=fechafinal&&res[i].fecha>=fechainicial){
                                  ayu=ayu+text;
                                }

                            }
                            docu.close();
                            buildHuffmanTree(ayu);

                        }
                        else if (comando[0]=="cambiar"){
                          cambiar(atoi(comando[1].c_str()),comando[2],comando[3]);
                        }
                        else if(comando[0]=="ayuda"){
                            ayuda();
                        }
                        else{
                            cout<<"Comando incorrecto, por favor consulte el comando \"ayuda\" para obtener una lista de comandos\n";
                        }
                        cout<<"Presione enter para continuar...";
                        cin.get();
                        system("clear");
                    }while(menu2);
                }
                else{
                    cout<<"Error de autenticacion, no es posible ingresar al sistema, intentelo otra vez."<<endl;
                }
            }
            else{
                //Si en la comparación con el file es incorrecta
                cout<<"La agencia escrita no existe, intentelo otra vez."<<endl;
            }
        }
        else if (comando[0]=="ayuda"){
            ayuda(); //Abre ayuda
        }
        else if (comando[0]=="exit"){
            menu=0; //Sale del programa
        }
        else{
            cout<<"Comando incorrecto, por favor consulte el comando \"ayuda\" para obtener una lista de comandos\n";
        }
    }while(menu==1);

    cout<<"Apagando sistema...\n";

    return 0;
}

//Pide un comando.
vector <string> pedirComando(){
    string comando, intermediate;
    vector <string> comandos;
    cout<<"\n$";
    getline (cin,comando);
    cout<<endl;
    //Tokenización.
    stringstream check1(comando);
    while(getline(check1, intermediate, ' '))
        comandos.push_back(intermediate);
    return comandos;
}

//Obtiene todos los usuarios y contraseñas en un vector de string
vector <string> leerPass(){
    ifstream users;
    vector <string> usuarios;
    string temp, intermediate;
    char* pch;
    char str[5000];

    //Abre el archivo
    users.open("contraseñas.dat");

    //Comprobación de error al abrir el archivo.
    if(users.fail()){
        cout<<"No se pudo abrir el archivo";
        return usuarios;
    }

    //Transfiere todo el archivo al string "temp".
    while(!users.eof()){
        getline(users,temp);
        intermediate+=temp;
        intermediate+="\n";
    }
    //Copia el contenido del string al char[] ya que no se puede hacer de forma directa
    intermediate.copy(str,intermediate.length(),0);
    str[intermediate.length()]='\0';

    //Cierra el archivo
    users.close();

    //Tokenización
    pch = strtok (str,";\n");
    while (pch != NULL)
    {
        usuarios.push_back(pch);
        pch = strtok (NULL, ";\n");
    }

    return usuarios;
}

//Lista de ayuda de todos los comandos
void ayuda()
{
    //Introducción del bloque de ayuda
    cout<<"A continuacion se describen cada uno de los comandos. Los comandos pueden tener\n";
    cout<<"parametros (entradas) obligatorias, encerradas con los simbolos < >, y/o entradas opcionales,\n\n\n";



    //Bloque para de ayuda para el comando de login
    cout<<"login <id_agencia>\n";
    cout<<"Descripcion: Este comando pregunta al usuario por una contrasenia para el identificador\n";
    cout<<"de la agencia dado en el comando, y activa la sesion si la contrasenia es igual a la guardada\n";
    cout<<"en el registro correspondiente para la agencia dada, en caso contrario muestra un mensaje de error.\n\n";

    //Bloque de ayuda para el comando de logout
    cout<<"logout\n";
    cout<<"Descripcion: Este comando termina la sesion activa de la agencia y vuelve a la consola o\n";
    cout<<"terminal del sistema.\n\n";

    //Bloque de ayuda para el comando de listar_buses
    cout<<"listar_buses\n";
    cout<<"Descripcion: Imprime, con una visualizacion agradable, los registros de los buses (uno por\n";
    cout<<"linea) con la informacion ya definida para este tipo de registro, en grupos o \"pantallazos\"\n";
    cout<<"de maximo 20 registros a la vez, informando al usuario si hay mas registros para visualizar.\n\n";

    //Bloque de ayuda para el comando de listar_rutas
    cout<<"listar_rutas\n";
    cout<<"Descripcion: Imprime, con una visualizacion agradable, los registros de las\n";
    cout<<"rutas (una por linea) con la informacion ya definida para este tipo de registro, en grupos o\n";
    cout<<"\"pantallazos\" de maximo 20 registros a la vez, informando al usuario si hay mas registros\n";
    cout<<"para visualizar.\n\n";

    //Bloque de ayuda para el comando de listar_viajes
    cout<<"listar_viajes\n";
    cout<<"Descripcion: Imprime, con una visualizacion agradable, los registros de los\n";
    cout<<"viajes (uno por linea) con la informacion ya definida para este tipo de registro, en grupos o\n";
    cout<<"\"pantallazos\" de maximo 20 registros a la vez, informando al usuario si hay mas registros\n";
    cout<<"para visualizar.\n\n";

    //Bloque de ayuda para el comando de disponibilidad
    cout<<"disponibilidad  <ciudad origen> <ciudad destino>\n";
    cout<<"Descripción: Este comando genera un reporte de todos los viajes que cubren la ruta entre\n";
    cout<<"las ciudades origen y destino que tienen disponibilidad de sillas, mostrando la fecha y hora\n";
    cout<<"de salida y las sillas disponibles.\n";

    //Bloque de ayuda para el comando de reserva
    cout<<"reserva <ciudad origen> <ciudad destino> <fecha> <hora> <pasajero>\n";
    cout<<"Descripción: Este comando crea una reserva para un viaje para la ruta entre las ciudades\n";
    cout<<"origen y destino para la fecha y hora indicada y asignada al pasajero que se da como\n";
    cout<<"argumento del comando. Se debe validar que esa ruta exista y haya un viaje con sillas\n";
    cout<<"disponibles para reservar.\n";
    cout<<"Salida en pantalla:\n";
    cout<<"Si no hay sillas disponibles se informa al usuario, de los contrario, se muestra una matriz\n";
    cout<<"de 4 columnas y 8 filas ( para bus corriente) o 7 filas (para bus especial) con los números\n";
    cout<<"de sillas y al frente de cada una las palabras Reservada o Disponible, para que el usuario\n";
    cout<<"escoja la silla para reservar, se valida que la silla escogida esté disponible, sino se muestra mensaje de error\n";

    //Bloque de ayuda para el comando de reporte_ventas
    cout<<"reporte_ventas [fecha inicial] [fecha final] \n";
    cout<<"Descripción: Genera un reporte con una visualización agradable de las reservas hechas\n";
    cout<<"entre el rango de fechas dado como argumentos, si no hay argumentos el reporte lo\n";
    cout<<"genera para el día de hoy. Al final informa el total de dinero que la agencia facturó por\n";
    cout<<"reservas vendidas, pero teniendo en cuenta si hubo cambios o cancelaciones. En los\n";
    cout<<"cambios se calcula la diferencia entre los precios del viaje original y el nuevo viaje: si la\n";
    cout<<"diferencia es negativa, se le reintegra al cliente; si no, el cliente paga la diferencia. Ahora,\n";
    cout<<"si el cliente cancela su reserva, se le reintegra un 85% del valor del tiquete. \n";

    //Bloque de ayuda para el comando de cancelar
    cout<<"cancelar <id viaje> <silla>\n";
    cout<<"Descripción: Actualiza el registro de la reserva para el viaje con Id dado y numero de silla\n";
    cout<<"dados como argumentos, además de actualizar el viaje como “VI000”, actualiza el valor del\n";
    cout<<"tiquete al 15% del contenido en el registro. \n";

    //Bloque de ayuda para el comando de cambiar
    cout<<"cambiar <número reserva> <id viaje nuevo> <pasajero>\n";
    cout<<"Descripción: Actualiza el registro de la reserva actual identificada con el número dado\n";
    cout<<"como argumento con el nuevo id de viaje para el pasajero indicado, valida si hay sillas\n";
    cout<<"disponibles y asigna una al usuario y le informa. \n";

    cout<<"FIN DE COMANDOS\n";
}

//------------------------------------------------------------------------------------------------------------------------

void listar_buses(string nombre){
  system("clear");
  cout<<"=====================================\n";
  cout<<"      Buses de agencia "<<nombre<<"   \n";
  cout<<"-------------------------------------\n";
  cout<<"   Codigo ; Tipo ; Capacidad         \n";
  cout<<"=====================================\n";

  ifstream documento;
  string txt;

  if(nombre=="AG111"){
    documento.open("Buses1.dat",ios::in);
  }
  else if(nombre=="AG222"){
    documento.open("Buses2.dat",ios::in);
  }
  else if(nombre=="AG333"){
    documento.open("Buses3.dat",ios::in);
  }


  if(documento.fail()){
    cout<<"Algo anda mal ";
    exit(EXIT_FAILURE);
  }

  int a = 0, opcion = 1, b = 1;
  while (opcion == 1 && !documento.eof()){
    if(opcion == 1)
    {
      cout<<"-------------------------------------------\n";
      cout<<b<<". ";
      getline (documento, txt);
      cout<<txt;
      cout<<"\n";
      a++;
      b++;
    }
    if(a == 20)
    {
      a = 0;
      cout<<"======================================================================================\n";
      cout<<"Hay mas registros por visualizar, desea pasar a la siguiente pagina(0=NO   1=SI)? :   \n";
      cout<<"======================================================================================\n";
      cin>>opcion;
      system("clear");

    }
  }
  documento.close();
}



void listar_rutas(){
  system("clear");
  cout<<"==============================================\n";
  cout<<"              Rutas Programadas             \n";
  cout<<"----------------------------------------------\n";
  cout<<"     No.Ruta ; Dia ; origen ; destino ; km\n";
  cout<<"==============================================\n";

  ifstream documento;
  string txt;

  documento.open("Rutas.dat",ios::in);

  if(documento.fail()){
    cout<<"Algo anda mal ";
    exit(EXIT_FAILURE);
  }

  int a = 0, opcion = 1, b = 1;
  while (opcion == 1 && !documento.eof()){
    if(opcion == 1)
    {
      cout<<"----------------------------------------------\n";
      cout<<b<<". ";
      getline (documento, txt);
      cout<<txt;
      cout<<"\n";
      a++;
      b++;
    }
    if(a == 20)
    {
      a = 0;
      cout<<"======================================================================================\n";
      cout<<"Hay mas registros por visualizar, desea pasar a la siguiente pagina(0=NO   1=SI)? :   \n";
      cout<<"======================================================================================\n";
      cin>>opcion;
      system("clear");
    }
  }
  documento.close();
}


void listar_viajes(){
    system("clear");
  cout<<"=====================================================================\n";
  cout<<"                          Viajes Programadas              \n";
  cout<<"---------------------------------------------------------------------\n";
  cout<<"      No.Ruta ; Bus ; Viaje ; Fecha ; Hora ; Conductor ; Precio   \n";
  cout<<"=====================================================================\n";

  ifstream documento;
  string txt;

  documento.open("Viajes.dat",ios::in);

  if(documento.fail()){
    cout<<"Algo anda mal ";
    exit(EXIT_FAILURE);
  }

  int a = 0, opcion = 1, b = 1;
  while (opcion == 1 && !documento.eof()){
    if(opcion == 1)
    {
      cout<<"---------------------------------------------------------------------\n";
      cout<<b<<". ";
      getline (documento, txt);
      cout<<txt;
      cout<<"\n";
      a++;
      b++;
    }
    if(a == 20)
    {
      a = 0;
      cout<<"======================================================================================\n";
      cout<<"Hay mas registros por visualizar, desea pasar a la siguiente pagina(0=NO   1=SI)? :   \n";
      cout<<"======================================================================================\n";
      cin>>opcion;
      system("clear");
    }
  }
  documento.close();
}


//Funciones de la segunda entrega

bool reservacion(string origen, string destino, int fecha, int hora, string pasajero, string agencia){

    //variables primera parte funcion
    ifstream rutas;
    string txt;

    char *ptr;
    char buffer[100];
    ruta resu[5];
    string codigo;
    int cont =0;

    //variables segunda parte de la funcion
    ifstream viajes;
    string txt2;
    ifstream buses;
    string txt3;
    char *ptr2;
    char buffer2[100];
    char *ptr3;
    char buffer3[100];
    viaje travel[4];

    bus busesito[22];


    //variables tercera parte
    reserva *r=new reserva[3];




    // segunda parte de la funcion
    rutas.open("Rutas.dat", ios::in);

    if(rutas.fail()){
        cout<<"Algo anda mal ";
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<5; i++){//!rutas.eof()
        getline (rutas, txt);
        //cout<<txt<<endl;
        strcpy(buffer, txt.c_str());
        //cout<<buffer<<endl;
        //cout<<txt<<endl;
        ptr=strtok(buffer, ";");
        resu[i].rutaid=ptr;

        ptr=strtok(NULL, ";");
        resu[i].dia=ptr;

        ptr=strtok(NULL, ";");
        resu[i].origen=ptr;

        ptr=strtok(NULL, ";");
        resu[i].destino=ptr;

        ptr=strtok(NULL, ";");
        resu[i].km=atoi(ptr);

    }

    rutas.close();
    for(int i=0; i<5; i++){
        if(origen==resu[i].origen&&destino==resu[i].destino){
            codigo=resu[i].rutaid;

            cout<<"Si existe una ruta con estas ciudades"<<endl;
            cout<<codigo;
        }
        else if(origen!=resu[i].origen||destino!=resu[i].destino){
            cont++;
        }

        if(cont==5){
            cout<<"No hay ninguna ruta con esa ciudad origen/destino";
        }
    }
    /*cout<<endl;
    cout<<endl;
    cout<<endl;*/

    //segunda parte de la funcion (valida los viajes y buses)

/*
    buses.open("Buses1.dat", ios::in);

    if(buses.fail()){
        cout<<"Algo anda mal ";
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<10; i++){//!rutas.eof()

        getline (buses, txt3);
        //cout<<txt<<endl;
        strcpy(buffer3, txt3.c_str());
        //cout<<buffer<<endl;
        //cout<<txt<<endl;
        ptr3=strtok(buffer3, ";");
        busesito[i].codigo=ptr3;

        ptr3=strtok(NULL, ";");
        busesito[i].tipo=ptr3;
cout<<"aca";
        ptr3=strtok(NULL, ";");
        busesito[i].capacidad=atoi(ptr3);

        int capacity=atoi(ptr3);

       busesito[i].capacidad=capacity;
       busesito[i].disponibilidad=capacity;


    }

    buses.close();*/




    viajes.open("Viajes.dat", ios::in);//se connfigura la partde de viajes

    if(viajes.fail()){
        cout<<"Algo anda mal ";
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<3; i++){//!rutas.eof()
        getline (viajes, txt2);
        //cout<<txt<<endl;
        strcpy(buffer2, txt2.c_str());
        //cout<<buffer<<endl;
        //cout<<txt<<endl;
        ptr2=strtok(buffer2, ";");
        travel[i].rutaid=ptr2;

        ptr2=strtok(NULL, ";");
        travel[i].busid=ptr2;

        ptr2=strtok(NULL, ";");
        travel[i].viajeid=ptr2;

        ptr2=strtok(NULL, ";");
        travel[i].fecha=atoi(ptr2);

        ptr2=strtok(NULL, ";");
        travel[i].hora=atoi(ptr2);

        ptr2=strtok(NULL, ";");
        travel[i].conductor=ptr2;

        ptr2=strtok(NULL, ";");
        travel[i].costo=atoi(ptr2);

    }
    viajes.close();
    //tercera parte de la funcion (crear reserva, verificar sillas)
    int fechatemp, horatemp;
    int auxi=1000;
    double precioaux;
    string codigoaux, viajeaux;

    for(int i=0; i<3; i++){
        if(travel[i].fecha==fecha&&travel[i].hora==hora&&travel[i].rutaid==codigo){
            fechatemp=fecha;
            horatemp=hora;
            codigoaux=travel[i].busid;
            viajeaux=travel[i].viajeid;
            precioaux=travel[i].costo;
            break;
        }
        /*else{
            cout<<"No se encuentran coincidencias con los datos proporcionados"<<endl;
        }*/
    }
    for(int i=0; i<3; i++){
        //if(r[i].codreserva==0){
            r[i].agenciaid=agencia;
            r[i].codreserva=auxi+1;
            r[i].rutaid=codigo;
            r[i].busid=codigoaux;
            r[i].viajeid=viajeaux;
            r[i].nombre=pasajero;
            r[i].fecha=fechatemp;
            r[i].hora=horatemp;
            r[i].precio=precioaux;
        //}
    }
ofstream archivo;
    archivo.open("reservas.dat", ios::out);

    if(archivo.fail()){
        cout<<"no se pudo crear";
    }

    //seccion de pruebas

    r[1].agenciaid="AG222";
    r[1].codreserva=auxi+2;
    r[1].rutaid="RT446";
    r[1].busid=codigoaux;
    r[1].viajeid="VI669";
    r[1].nombre="Pablin Rodrigo";
    r[1].fecha=20201128;
    r[1].hora=0745;
    r[1].precio=130000;

    r[2].agenciaid="AG333";
    r[2].codreserva=auxi+3;
    r[2].rutaid="RT445";
    r[2].busid=codigoaux;
    r[2].viajeid="VI666";
    r[2].nombre="Maria Sofia Fi";
    r[2].fecha=20201028;
    r[2].hora=1830;
    r[2].precio=200000;

//fin seccion pruebas
    int tam=sizeof(r)/sizeof(res);
    for(int i=0; i<(3*tam); i++){
        archivo<<r[i].agenciaid<<";"<<r[i].codreserva<<";"<<r[i].rutaid<<";"<<r[i].busid<<";"<<r[i].viajeid<<";"<<r[i].nombre<<";"<<r[i].fecha<<";"<<r[i].hora<<";"<<r[i].precio<<endl;
cout<<endl;
    }


return true;
delete []r;

//ultima parte = imprimir en archivo
    /*ofstream archivo;
    archivo.open("reservas.dat", ios::out);

    int conti=0;
    while(conti < 1){
        archivo<<r[conti].agenciaid<<";"<<r[conti].codreserva<<";"<<r[conti].rutaid<<";"<<r[conti].viajeid<<";"<<r[conti].nombre<<";"<<r[conti].hora<<";"<<r[conti].precio<<endl;
        cont++;
    }
    archivo.close();*/

}

void reporte_ventas(int fechainicial, int fechafinal){
    ifstream reservas;
    string txt;
    char *ptr;
    char buffer[100];
    reserva res[4];

    int cont=0;

     reservas.open("reservas.dat", ios::in);

    if(reservas.fail()){
        cout<<"Algo anda mal ";
        exit(EXIT_FAILURE);
    }
    /*while(reservas.eof()==false){
        cont++;
    }
    cout<<"cont"<<cont;
    reserva res[cont];*/

    for(int i=0; i<3; i++){//rutas.eof()
        getline (reservas, txt);

        //cout<<txt<<endl;
        strcpy(buffer, txt.c_str());

        //cout<<buffer<<endl;
        //cout<<txt<<endl;

        ptr=strtok(buffer, ";");
        res[i].agenciaid=ptr;


        ptr=strtok(NULL, ";");
        res[i].codreserva=atoi(ptr);


        ptr=strtok(NULL, ";");
        res[i].rutaid=ptr;

        ptr=strtok(NULL, ";");
        res[i].busid=ptr;

        ptr=strtok(NULL, ";");
        res[i].viajeid=ptr;

        ptr=strtok(NULL, ";");
        res[i].nombre=ptr;

        ptr=strtok(NULL, ";");
        res[i].fecha=atoi(ptr);

        ptr=strtok(NULL, ";");
        res[i].hora=atoi(ptr);

        ptr=strtok(NULL, ";");
        res[i].precio=atof(ptr );


    }
    reservas.close();

    //system("clear");
  cout<<"===================================================================================================================\n";
  cout<<"                                                Reservas              \n";
  cout<<"-------------------------------------------------------------------------------------------------------------------\n";
  cout<<"      Cod. Agencia ; Num. Reserva ; Num. Ruta ;  Bus  ; Num. Viaje ;      Nombre      ;  Fecha  ; Hora ; Precio   \n";
  cout<<"===================================================================================================================\n";
  cout<<endl;
int b=1;
    int total=0;
    for(int i=0; i<3;i++){
        if(fechas(fechainicial, fechafinal,res[i].fecha)==1){
           cout<<b<<".       "<<res[i].agenciaid<<",         "<<res[i].codreserva<<",         "<<res[i].rutaid<<",   "<<res[i].busid<<",   "<<res[i].viajeid<<",       "<<res[i].nombre<<",   "<<res[i].fecha<<", "<<res[i].hora<<",  "<<res[i].precio<<endl;

            b++;
            total=total+res[i].precio;
        }
    }
    cout<<"-------------------------------------------------------------------------------------------------------------------\n";
    cout<<"El total de ingresos que la empresa factura por ventas es de: "<<total<<" pesos"<<endl;
    cout<<"===================================================================================================================\n";


}
int fechas(int fechainicial, int fechafinal, int fecha){

    int resp=0;
    int a=fechainicial;
    int b=fechafinal;
    int c=fecha;

    int diai=0, mesi=0, anioi=0;
    int diaf=0, mesf=0, aniof=0;
    int dia=0, mes=0, anio=0;

    int cont=0;

    //se separa la fecha inicial
        diai=a%100;
        a=a/100;
        mesi=a%100;
        a=a/100;
        anioi=a%100;
        a=a/100;

        //se separa la fecha final
        diaf=b%100;
        b=b/100;
        mesf=b%100;
        b=b/100;
        aniof=b%100;
        b=b/100;

        //se separa la fecha a comparar
        dia=c%100;
        c=c/100;
        mes=c%100;
        c=c/100;
        anio=c%100;
        c=c/100;


        if(anio<=aniof&&anio>=anioi){//se considera si el año es el mismo que el de ambos parametros
            cont++;
            if(mes<=mesf&&mes>=mesi){//se considera si el mes es el mismo que el de ambos parametros
                cont++;
                if(dia<=diaf&&dia>=diai){//se considera si el dia es el mismo que el de ambos parametros
                    cont++;
                }
                else{
                    cont++;
                }
            }
            else if(mesf<mesi&&aniof>anioi){
                cont++;
                if(dia<=diaf&&dia>=diai){//se considera si el dia es el mismo que el de ambos parametros
                    cont++;
                }
                else if(diaf<diai&&dia<=diai){
                    cont++;
                }

            }
        }
        if(dia>diaf&&mes>=mesf){
            cont=1;
        }
        resp=cont;


        if(cont==3){
            return 1;
        }
        else{
            return 0;
        }
}

void cancelar( string viajeid, int silla )
{
  ifstream reservas;
  string txt;
  char *ptr;
  char buffer[100];
  reserva res[100];

  int cont=0;

   reservas.open("reservas.dat", ios::in);

  if(reservas.fail()){
      cout<<"Algo anda mal ";
      exit(EXIT_FAILURE);
  }

  for(int i=0; i<3; i++){//rutas.eof()
      getline (reservas, txt);

      strcpy(buffer, txt.c_str());
      ptr=strtok(buffer, ";");
      res[i].agenciaid=ptr;


      ptr=strtok(NULL, ";");
      res[i].codreserva=atoi(ptr);


      ptr=strtok(NULL, ";");
      res[i].rutaid=ptr;

      ptr=strtok(NULL, ";");
      res[i].busid=ptr;

      ptr=strtok(NULL, ";");
      res[i].viajeid=ptr;

      ptr=strtok(NULL,";");
      res[i].silla=atoi(ptr);

      ptr=strtok(NULL, ";");
      res[i].nombre=ptr;

      ptr=strtok(NULL, ";");
      res[i].fecha=atoi(ptr);

      ptr=strtok(NULL, ";");
      res[i].hora=atoi(ptr);

      ptr=strtok(NULL, ";");
      res[i].precio=atof(ptr );
      cont++;
    }

  bool flag = false;
  for(int i=0;i<cont;i++)
  {
    if(res[i].viajeid==viajeid && res[i].silla == silla)
    {
      flag = true;
      res[i].viajeid="VI000";
      res[i].silla=0;
      double valor = res[i].precio*0.15;
      res[i].precio=res[i].precio-valor;
    }
  }
  ofstream documento("reservas.dat", ios::out);
  for(int j=0;j<cont;j++)
  {
        documento<<res[j].agenciaid<<";"<<res[j].codreserva<<";"<<res[j].rutaid<<";"<<res[j].busid<<";"<<res[j].viajeid<<";"<<res[j].silla<<";"<<res[j].nombre<<";"<<res[j].fecha<<";"<<res[j].hora<<";"<<res[j].precio;
        if(j!=cont-1)
        {
            documento<<endl;
        }
  }
  if(flag==true)
  {
    cout<<"La reserva ha sido eliminada"<<endl;
  }
  else
  {
    cout<<"La reserva no fue encontrada"<<endl;
  }
  reservas.close();
}

void disponibilidad (string ciudadOrigen, string ciudadDestino, string nombre){
  ifstream documento;
  vector <string> viajes, reservas, rutas, buses, disponible;
  vector <int> sillas;
  string temp, intermediate;
  char* pch;
  char str[5000];
  int a=0, b = 0, contador=0;

  //ARCHIVO DE RUTAS ---------------------------------------------------------------------------------------
  //Abre el archivo
  documento.open("Rutas.dat");
  //Comprobación de error al abrir el archivo.
  if(documento.fail()){
      cout<<"No se pudo abrir el archivo";
      exit(EXIT_FAILURE);
  }
  //Transfiere todo el archivo al string "temp".
  while(!documento.eof()){
      getline(documento,temp);
      intermediate+=temp;
      intermediate+="\n";
  }
  //Cierra el archivo
  documento.close();
  //Copia el contenido del string al char[] ya que no se puede hacer de forma directa
  intermediate.copy(str,intermediate.length(),0);
  str[intermediate.length()]='\0';

  //Tokenización
  pch = strtok (str,";\n");
  while (pch != NULL)
  {
      rutas.push_back(pch);
      pch = strtok (NULL, ";\n");
  }
  intermediate = "";
  //ARCHIVO DE VIAJES------------------------------------------------------------------------------------
  documento.open("Viajes.dat");
  if(documento.fail()){
      cout<<"No se pudo abrir el archivo";
      exit(EXIT_FAILURE);
  }
  while(!documento.eof()){
      getline(documento,temp);
      intermediate+=temp;
      intermediate+="\n";
  }
  documento.close();
  intermediate.copy(str,intermediate.length(),0);
  str[intermediate.length()]='\0';
  pch = strtok (str,";\n");
  while (pch != NULL)
  {
      viajes.push_back(pch);
      pch = strtok (NULL, ";\n");
  }
  intermediate = "";

  //ARCHIVO DE BUSES------------------------------------------------------------------------------------
  if(nombre=="AG111"){
    documento.open("Buses1.dat");
  }
  else if(nombre=="AG222"){
    documento.open("Buses2.dat");
  }
  else if(nombre=="AG333"){
    documento.open("Buses3.dat");
  }
  if(documento.fail()){
      cout<<"No se pudo abrir el archivo";
      exit(EXIT_FAILURE);
  }
  while(!documento.eof()){
      getline(documento,temp);
      intermediate+=temp;
      intermediate+="\n";
  }
  documento.close();
  intermediate.copy(str,intermediate.length(),0);
  str[intermediate.length()]='\0';
  pch = strtok (str,";\n");
  while (pch != NULL)
  {
      buses.push_back(pch);
      pch = strtok (NULL, ";\n");
  }
  intermediate = "";

  //ARCHIVO DE RESERVAS------------------------------------------------------------------------------------
  documento.open("reservas.dat");
  if(documento.fail()){
      cout<<"No se pudo abrir el archivo";
      exit(EXIT_FAILURE);
  }
  while(!documento.eof()){
      getline(documento,temp);
      intermediate+=temp;
      intermediate+="\n";
  }
  documento.close();
  intermediate.copy(str,intermediate.length(),0);
  str[intermediate.length()]='\0';
  pch = strtok (str,";\n");
  while (pch != NULL)
  {
      reservas.push_back(pch);
      pch = strtok (NULL, ";\n");
  }
  intermediate = "";

  //PROCEDIMIENTO----------------------------------------------------------------------------------------
  //For para recorrer las rutas
  for (int i = 0; i<rutas.size(); i+=5){
    if (rutas[i+2] == ciudadOrigen && rutas [i+3] == ciudadDestino){
      //For para recorrer los viajes
      for (int j = 0; j<viajes.size(); j+=7){
        if (rutas[i]==viajes[j]){
          //For para recorrer los buses
          for (int k = 0; k<buses.size();k+=3){
            if (viajes[j+1]==buses[k]){
              //For para recorrer las reservas
              for (int l = 0; l<reservas.size();l+=10){
                if (reservas[l]==nombre && reservas[l+2]==rutas[i] && reservas[l+3]==buses[k] && reservas[l+4] == viajes[j+2]){
                  contador++;
                }
              }
              //Ver si el bus tiene disponibilidad o no
              if (atoi(buses[k+2].c_str())>contador){
                disponible.push_back(rutas[i+1]);
                disponible.push_back(viajes[j+4]);
                sillas.push_back(atoi(buses[k+2].c_str())-contador);
                contador=0;
              }
            }
          }
        }
      }
    }
  }


  //IMPRIMIR----------------------------------------------------------------------------------------------
  system("clear");
  cout<<"==============================================\n";
  cout<<"              Viajes disponibles             \n";
  cout<<"----------------------------------------------\n";
  cout<<"     Dia ; Hora ; Sillas disponibles\n";
  cout<<"==============================================\n";
  while (a<sillas.size()){
    cout<<"----------------------------------------------\n";
    cout<<b+1<<". ";
    cout<<disponible[a];
    cout<<" ; "<<disponible[a+1];
    cout<<" ; "<<sillas[b];
    cout<<"\n";
    b++;
    a+=2;
  }
}

void cambiar(int codreserva,string newviajeid,string nombre)
{
  ifstream rutas;
  string txt;
char *ptr;
char buffer[100];
ruta resu[5];
string codigo;
int cont =0;
ifstream viajes;
string txt2;
bus busesito[22];

char *ptr2;
char buffer2[100];
viaje travel[4];
for(int i=0; i<5; i++){
        getline (rutas, txt);
        strcpy(buffer, txt.c_str());

        ptr=strtok(buffer, ";");
        resu[i].rutaid=ptr;

        ptr=strtok(NULL, ";");
        resu[i].dia=ptr;

        ptr=strtok(NULL, ";");
        resu[i].origen=ptr;

        ptr=strtok(NULL, ";");
        resu[i].destino=ptr;

        ptr=strtok(NULL, ";");
        resu[i].km=atoi(ptr);
    }


viajes.open("Viajes.dat", ios::in);//se connfigura la partde de viajes

    if(viajes.fail()){
        cout<<"Algo anda mal ";
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<3; i++){//!rutas.eof()
        getline (viajes, txt2);

        strcpy(buffer2, txt2.c_str());

        ptr2=strtok(buffer2, ";");
        travel[i].rutaid=ptr2;

        ptr2=strtok(NULL, ";");
        travel[i].busid=ptr2;

        ptr2=strtok(NULL, ";");
        travel[i].viajeid=ptr2;

        ptr2=strtok(NULL, ";");
        travel[i].fecha=atoi(ptr2);

        ptr2=strtok(NULL, ";");
        travel[i].hora=atoi(ptr2);

        ptr2=strtok(NULL, ";");
        travel[i].conductor=ptr2;

        ptr2=strtok(NULL, ";");
        travel[i].costo=atoi(ptr2);

    }
  double precio2;
  for(int a=0;a<3;a++)
    {
        if(travel[a].viajeid==newviajeid)
        {
            busesito[a].codigo = travel[a].busid;
            resu[a].rutaid=travel[a].rutaid;
            precio2=travel[a].costo;

        }
    }
viajes.close();

}


//Funciones de comprimir

Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};

void encode(Node* root, string str,
			unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int &index, string str)
{
	if (root == nullptr) {
		return;
	}

	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] =='0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

void buildHuffmanTree(string text)
{
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	priority_queue<Node*, vector<Node*>, comp> pq;

	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	Node* root = pq.top();
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	/**Registro al archivo
*/
    ofstream fina;
	fina.open("reporte.huff", ios::out);

	if(fina.fail()){
        cout<<"no se pudo crear";
    }

	fina << "Los codigos comprimidos por Huffman son :\n" << '\n';
	for (auto pair: huffmanCode) {
		fina << pair.first << " " << pair.second << '\n';
	}
    fina.close();
	/**Fin de registro en archivo
	*/
/*
	cout << "\nCadena que se comprime            :\n" << text << '\n';

	// print encoded string
	string str = "";
	for (char ch: text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n" << str << '\n';

	// traverse the Huffman Tree again and this time
	// decode the encoded string
	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}*/
}
