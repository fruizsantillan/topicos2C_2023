#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "funciones_enunciado.h"
#include <math.h>
#define TRUE 1
#define FALSE 0
#include "funciones.h"
typedef char booleano;

/* aquí deben declarar sus prototipos de funciones */
//Definimos los 3 minutos del juego en milisegundos.
#define CANT_MILISEG 180000

float calculaVelDesdePeriodo(const float periodo);
float calculaAlturaDesdeVelocidad(const float velocidad);
float calculaVelDesdeAltura(const float alturaMaxima);
float calculaTiempoDesdeVelocidad(const float velocidad);
float calculaPendiente(const t_coordenada* coordenada1, const t_coordenada* coordenada2);
int calculaCantAlineamientos(t_juego* juegos);
double milisegASeg(double miliseg);
float calculaAlturaEnFuncionTiempo(const float tiempo, const float velocidad, const float alturaMaximaDeLaPelota, const float alturaGolpe);
#endif // FUNCIONES_H_INCLUDED
