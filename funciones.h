#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <iostream>
#include <time.h>
#include <ctime>
#include "rlutil.h"


const int MAX_DADOS=12;


void creditos();

void juego();

int tiradaDadosObjetivo();


int tiradaDeTurno(int dados[], int stock[], int jugadorActual, std::string jugadores[2], int sumaObjetivo, int &dadosUsados,bool& exito);

void menu();

void estadistica(std::string nombre = "", int puntaje = -1);

void dibujarMarco();
void marcoJuego();
void cartel();

bool salir();
#endif // FUNCIONES_H_INCLUDED
