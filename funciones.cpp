#include "funciones.h"
using namespace std;


void menu(){



    while(true){
int opcion;
rlutil::locate(45,9);
cout<<"elija la opcion a seleccionar: "<<endl;
rlutil::locate(45,11);
cout<<"|1|- JUGAR"<<endl;
rlutil::locate(45,12);
cout<<"|2|- ESTADISTICAS"<<endl;
rlutil::locate(45,13);
cout<<"|3|- CREDITOS"<<endl;
rlutil::locate(45,14);
cout<<"|4|- SALIR"<<endl;

cartel();
dibujarMarco();

rlutil::locate(46,16);
cin>>opcion;

cin.ignore();

switch(opcion){

case 1:
    juego();
    break;

case 2:
    estadistica();

    break;

case 3:

    creditos();
    break;

case 4:

    if(salir()){
        exit(1);
    }
    break;

default:

    break;

}
    system("cls");


}

}




void juego(){
    system("cls");

    srand(time(0));



    std::string jugadores[2];
    int stock[2]= {6,6};
    int puntaje[2]= {0,0};
    int dados[12];


    dibujarMarco();
    rlutil::locate(44,12);
    cout<<"ingrese el nombre del jugador 1: ";
    getline(cin, jugadores[0]);
    rlutil::locate(44,13);
    cout<<"ingrese nombre del jugador 2 :";
    getline(cin, jugadores[1]);


    system("cls");
    int dado1;
    int dado2;

    do{
    dado1 = rand() % 6 + 1;
    dado2 = rand() % 6 + 1;

    rlutil::locate(30,11);
    cout<<"-el jugador que tire el dado con el numero mas grande comenzara-"<<endl;
    rlutil::locate(44,13);
    cout<<"el jugador: "<<jugadores[0] <<" tiro un: "<< dado1 <<endl;
    rlutil::locate(44,14);
    cout<<"el jugador: "<< jugadores[1] <<" tiro un: "<< dado2 <<endl;
    cout<<" "<<endl;

    if(dado1==dado2){
            rlutil::locate(44,15);
    cout<<"empataron, se volvera a lanzar los dados."<<endl;
    rlutil::locate(1,1);
    system("pause");
    rlutil::locate(44,15);
    cout<<"                                          "<<endl;

    }
    }while(dado1==dado2);




    int jugadorActual;
    if(dado1>dado2){
             jugadorActual = 0;
             rlutil::locate(44,16);
             cout<<"el jugador: "<<jugadores[0] <<" comenzara."<<endl;
    }else{
         jugadorActual = 1;
         rlutil::locate(44,16);
        cout<<"el jugador: "<<jugadores[1] <<" comenzara."<<endl;
    }
    rlutil::locate(1,1);
    system("pause");
    system("cls");



    for(float ronda=0;ronda<3;ronda+=0.5){

    if (stock[0]==0 || stock[1]==0){

        if(stock[0]==0){
            puntaje[0]+= 10000;
            break;
        }else {puntaje[1]+= 10000;
        break;
        }
    }




    marcoJuego();
    int contRonda=ronda;
    rlutil::locate(7,3);
    cout<<"Ronda: "<<(contRonda+1)<<" Turno de: "<<jugadores[jugadorActual];
    rlutil::locate(45,3);

    cout<<"cantidad de puntaje total: ";
    rlutil::setColor(rlutil::GREEN);
     cout<< puntaje[jugadorActual];
    rlutil::locate(85,3);
    rlutil::setColor(rlutil::WHITE);
    cout<<"cantidad de stock total ";
    rlutil::setColor(rlutil::GREEN);
    cout<<stock[jugadorActual]<<endl;
    rlutil::setColor(rlutil::WHITE);

    int sumaObjetivo = tiradaDadosObjetivo();
     rlutil::locate(42,6);
    cout << "la suma objetivo a conseguir es de: "<< sumaObjetivo<<endl;


    int dadosUsados=0;
    bool exito = false;
    //tiradaDeTurno(dados, stock, jugadorActual, jugadores, sumaObjetivo);
    int puntos= tiradaDeTurno(dados, stock, jugadorActual, jugadores, sumaObjetivo, dadosUsados,exito);

    int otroJugador = (jugadorActual+1)%2;

    puntaje[jugadorActual] += puntos;

    if(exito){
    stock[otroJugador] +=  dadosUsados;
    stock[jugadorActual] -= dadosUsados;
    }else if(stock[otroJugador]>1){
        stock[otroJugador]--;
        stock[jugadorActual]++;
    }else{
    cout<<"no hay suficientes dados para transferir, no hay penalidad"<<endl;
    }


    jugadorActual = otroJugador;
    rlutil::locate(40, 21);
    system("pause");
    system("cls");
    }

    cout<<"________________________________________________________________________________________________________________"<<endl;
    if(puntaje[0]>puntaje[1]){
         //   noHayPuntaje=false;
        cout<<"el jugador: "<<jugadores[0]<<" GANO el juego con "<<puntaje[0]<<" puntos"<<endl;
        cout<<"";
        cout<<"el jugador: "<<jugadores[1]<<" PERDIO el juego con "<<puntaje[1]<<" puntos"<<endl;
            system("pause");
            estadistica(jugadores[0],puntaje[0]);

    }else if(puntaje[1]>puntaje[0]){
      //  noHayPuntaje=false;
            cout<<"el jugador: "<<jugadores[1]<<" GANO el juego con "<<puntaje[1]<<" puntos"<<endl;
        cout<<"";
        cout<<"el jugador: "<<jugadores[0]<<" PERDIO el juego con "<<puntaje[0]<<" puntos"<<endl;
        system("pause");
       estadistica(jugadores[1],puntaje[1]);
        }else cout<<"el jugador: "<<jugadores[1]<<" y el jugador : "<<jugadores[0]<<" empataron con "<<puntaje[0]<<" puntos" <<endl;
    cout<<"________________________________________________________________________________________________________________"<<endl;

}

    /*

    falta:
    estadistica
    */

int tiradaDadosObjetivo(){

 int dadoDoce1= rand() % 12 +1;
 int dadoDoce2= rand() % 12 +1;
 rlutil::locate(28,5);
 cout<<"el primer dado objetivo es: "<<dadoDoce1<<endl;
  rlutil::locate(68,5);
 cout<<"el segundo dado objetivo es: "<<dadoDoce2<<endl;

 return dadoDoce1+dadoDoce2;
 }


int tiradaDeTurno(int dados[], int stock[], int jugadorActual, std::string jugadores[2], int sumaObjetivo, int& dadosUsados,bool& exito){





    int cantidad = stock[jugadorActual];
    int acumSeleccion = 0;
    int seleccion;


    bool dadoRepetido[12];





    for (int i = 0; i < cantidad; i++) {

        dados[i] = rand() % 6 + 1;

        rlutil::locate(6, 9);
        cout<<"TIRADA DE";
        rlutil::locate(6, 10);
        cout<<"  DADOS";

         rlutil::locate(6, 13+i);
        cout<<"DADO "<< i+1<<": "<< dados[i]<<endl;


        rlutil::locate(32, 9);
        cout<<"Seleccione los dados a sumar para llegar al objetivo."<<endl;
        rlutil::locate(43, 10);
        cout<<"Presiona 0 para finalizar."<<endl;
    }


     for(int i=0;i<12;i++){
        dadoRepetido[i]=true;
     }




    while(true){

        rlutil::locate(25, 14);
        cin>>seleccion;
        rlutil::locate(25, 14);cout<<"     ";


            if(seleccion!=0){
                    if(seleccion>0 && seleccion<=cantidad){

            if(dadoRepetido[seleccion-1]==true){
                dadoRepetido[seleccion-1]=false;
                acumSeleccion += dados[seleccion-1];
                dadosUsados++;
            rlutil::locate(40, 25);
            cout<<"la suma seleccionada es de: "<<acumSeleccion;


            if(acumSeleccion==sumaObjetivo){

                rlutil::setColor(rlutil::GREEN);
                rlutil::locate(40, 15);
                cout<<"la tirada de dados llego al objetivo"<<endl;

                rlutil::locate(40, 17);
                cout<<"la cantidad de dados utilizados fue de: "<<dadosUsados<<endl;

                int puntos= acumSeleccion*dadosUsados;
                rlutil::locate(40, 18);
                cout<<"la cantidad de puntos a sumar es de: "<<puntos<<endl;
                exito = true;

                rlutil::setColor(rlutil::YELLOW);
                  rlutil::locate(40, 19);
                cout<<"la cantidad de dados a transferir es de: "<<dadosUsados<<endl;
                rlutil::setColor(rlutil::WHITE);
                return puntos;
                }
                if(acumSeleccion>sumaObjetivo){
                        rlutil::locate(40, 15);
                rlutil::setColor(rlutil::RED);
                cout<<"la suma es mayor al dado objetivo y no suma puntos"<<endl;
                rlutil::locate(40, 16);
                cout<<"RECIBISTE UNA PENALIZACION DE 1 DADO"<<endl;
                exito = false;
                  rlutil::setColor(rlutil::WHITE);
                return 0;
                }

            }else{
                rlutil::locate(40, 15);
                rlutil::setColor(rlutil::YELLOW);
                cout<<"el dado ya fue seleccionado, elija otro"<<endl;
                rlutil::setColor(rlutil::WHITE);
                rlutil::locate(40, 17);
                system("pause");
                 rlutil::locate(40, 17);
                cout<<"                                        "<<endl;
                rlutil::locate(40, 15);
                cout<<"                                        "<<endl;
                }
            }else{
                rlutil::locate(40, 15);
                rlutil::setColor(rlutil::YELLOW);
                cout<<"el dado seleccionado no cumple los parametro permitidos"<<endl;
                rlutil::setColor(rlutil::WHITE);
                rlutil::locate(40, 17);
                system("pause");
                 rlutil::locate(40, 17);
                cout<<"                                                    "<<endl;
                rlutil::locate(40, 15);
                cout<<"                                                          "<<endl;
                }
            }else{
                    rlutil::setColor(rlutil::RED);
                cout<<"la suma es menor al dado objetivo y no suma puntos"<<endl;
                rlutil::locate(40, 16);
                cout<<"RECIBISTE UNA PENALIZACION DE 1 DADO"<<endl;
                  rlutil::setColor(rlutil::WHITE);

                break;}
            }

return 0;
}

void estadistica(string nombre, int puntaje) {
    system ("cls");
    dibujarMarco();
    static int mejorPuntaje = 0;
    static string mejorJugador = "";

    if (puntaje > mejorPuntaje && puntaje != -1) {
        mejorPuntaje = puntaje;
        mejorJugador = nombre;
    }
     if (mejorJugador != "") {
             rlutil::locate(50,12);
        cout << "Mejor jugador hasta ahora: "<<mejorJugador;
        rlutil::locate(57,13);
        cout<< "con: "<<mejorPuntaje<<" puntos."<< endl;
        rlutil::locate(1,1);
        system ("pause");
    } else {
        rlutil::locate(41,12);
        cout<<"Todavia no hay un jugador ganador para mostrar."<<endl;
        rlutil::locate(1,1);
        system ("pause");
    }

}










void creditos(){
    system("cls");


    dibujarMarco();

    rlutil::locate(44,11);
cout<<"juego hecho por Rodrigo Ezequiel Medina"<<endl;

 rlutil::locate(44,14);
cout<<"Legajo: 28167"<<endl;


    rlutil::locate(1,1);
    system("pause");


}

bool salir(){

string letra;
 system("cls");

dibujarMarco();
 rlutil::locate(44,10);
 cout<<"estas seguro que queres salir del juego?"<<endl;
  rlutil::locate(44,13);
cout<<"presiona |S| para salir "<<endl;
rlutil::locate(44,14);
cout<<"presiona |N| para quedarte"<<endl;
 rlutil::locate(44,16);
   cin>>letra;

    if(letra=="s"||letra=="S"){
            rlutil::locate(1,1);
        return true;
    }else if(letra=="n"||letra=="N"){
        rlutil::locate(1,1);
        return false;
    }
rlutil::locate(1,1);
return 0;}








void dibujarMarco(){

//verticales
rlutil::locate(40,8);
for(int i=8;i<19;i++){


    rlutil::locate(39, i); cout << char(186);
    rlutil::locate(89, i); cout << char(186);


}

//horizontales
for(int i=39;i<90;i++){
    rlutil::locate(i,7); cout<<char(205);
    rlutil::locate(i,18); cout<<char(205);
}
//esquinas
    rlutil::locate(39, 7); cout << char(201);
    rlutil::locate(89, 7); cout << char(187);

    rlutil::locate(39, 18); cout << char(200);
    rlutil::locate(89, 18); cout << char(188);

}

void marcoJuego(){
//marcos exteriores
for(int i=2;i<27;i++){
    rlutil::locate(4, i);cout <<char(186);
    rlutil::locate(119, i);cout <<char(186);
}

for(int i=2;i<21;i++){
    rlutil::locate(100, i+6);cout <<char(186);
    rlutil::locate(17, i+6);cout <<char(186);
}

for(int i=4;i<120;i++){
    rlutil::locate(i, 2);cout<< char(205);
    rlutil::locate(i, 7);cout<< char(205);

    rlutil::locate(i, 4);cout<< char(205);
    rlutil::locate(i, 27);cout<< char(205);
}

for(int i=18;i<100;i++){

    rlutil::locate(i, 23);cout<< char(205);

}


    rlutil::locate(4, 2);cout<< char(201);
    rlutil::locate(119, 2);cout << char(187);
    rlutil::locate(4, 27);cout << char(200);
    rlutil::locate(119, 27);cout<< char(188);



//marcos interiores
 rlutil::locate(4, 4);cout <<char(204);
 rlutil::locate(4, 7);cout <<char(204);
 rlutil::locate(119, 4);cout <<char(185);
 rlutil::locate(119, 7);cout <<char(185);
 rlutil::locate(100, 23);cout <<char(185);
 rlutil::locate(17, 23);cout <<char(204);
 rlutil::locate(119, 2);cout <<char(187);



//divisiones datos
 rlutil::locate(39, 4);cout <<char(202);
 rlutil::locate(80, 4);cout <<char(202);
 rlutil::locate(100, 27);cout <<char(202);

  rlutil::locate(17,27);cout <<char(202);

 rlutil::locate(39, 2);cout <<char(203);
 rlutil::locate(100, 7);cout <<char(203);
 rlutil::locate(80, 2);cout <<char(203);

 rlutil::locate(17, 7);cout <<char(203);

 rlutil::locate(39, 3);cout <<char(186);
 rlutil::locate(80, 3);cout <<char(186);



}

void cartel(){
    rlutil::setColor(rlutil::MAGENTA);
    rlutil::locate(29,22);
cout << R"(    _______   ____________  _______   ______  ___    ____  ____  _____)" << endl;
 rlutil::locate(29,23);
cout << R"(   / ____/ | / / ____/ __ \/ ____/ | / / __ \/   |  / __ \/ __ \/ ___/)" << endl;
 rlutil::locate(29,24);
cout << R"(  / __/ /  |/ / /_  / /_/ / __/ /  |/ / / / / /| | / / / / / / /\__ \)" << endl;
 rlutil::locate(29,25);
cout << R"( / /___/ /|  / __/ / _, _/ /___/ /|  / /_/ / ___ |/ /_/ / /_/ /___/ /)" << endl;
 rlutil::locate(29,26);
cout << R"(/_____/_/ |_/_/   /_/ |_/_____/_/ |_/_____/_/  |_/_____/\____//____/)" << endl;
 rlutil::setColor(rlutil::WHITE);
}




/*Hacer una función que reciba un array/vector booleano por parámetro y retorne la cantidad de elementos verdaderos que tiene. Tamaño del vector 20.*/

// 7 true
// 13 false

bool vect[20] {true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false};
int tamanio=20;

bool cantVerdaderos(bool vect[]){
    int contador = 0;

    for (int i=0;i<tamanio;i++){
        if(vect[i]){
            contador++;
        }

    }


    return contador;
}
