#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "funciones_enunciado.h"
#include <math.h>
#define TRUE 1
#define FALSE 0
#define CANT_MILISEG 180000
#include "funciones.h"
typedef char booleano;

/* aquí deben declarar sus prototipos de funciones */
//Funciones principales
void solucionTP(t_juego* juegos);
char obtenerValorPorTeclado(const char *opcionesValidas, const char* primerMensaje, const char* segundoMensaje);
void calculaCantAlineamientos(t_juego* juegos);

//Para datos brindados por el ejercicio
void calcularDatosJugadorConPeriodo(t_jugador *jugador, int juegoIndex, int jugadorIndex, float periodo);
void calcularDatosJugadorConFrecuencia(t_jugador *jugador, int juegoIndex, int jugadorIndex, float frecuencia);
void calcularDatosJugadorConAltura(t_jugador *jugador, int juegoIndex, int jugadorIndex, float alturaMaxima);

//Ecuaciones
void calculaDistancia(t_jugador* jugador);
float calculaAlturaGolpe(const float alturaMaxima, const float estaturaJugador);
float calculaAlturaParaAlineamiento(booleano* estaSubiendo, float tiempoAAlturaMax, float* tiempoAct, float alturaGolpe, float velocidadInicial);
float calculaVelDesdePeriodo(const float periodo);
float calculaAlturaDesdeVelocidad(const float velocidad);
float calculaVelDesdeAltura(const float alturaMaxima);
float calculaTiempoDesdeVelocidad(const float velocidad);

//Funciones de tiempo y pendientes
float redondearTiempo(float tiempoAct);
float calculaPendiente(const t_coordenada* coordenada1, const t_coordenada* coordenada2);
float milisegAMinutos(int milisegundo);
float milisegASegundos(int milisegundo);

#endif // FUNCIONES_H_INCLUDED
