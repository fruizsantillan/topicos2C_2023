#include "funciones.h"

/* aquí deben declarar sus funciones */

char obtenerValorPorTeclado(const char *opcionesValidas, const char* primerMensaje, const char* segundoMensaje)
{
    char teclaIngresada='n';


    printf("%s ", primerMensaje);
    scanf("%c", &teclaIngresada);
    fflush(stdin);

    while (teclaIngresada != opcionesValidas[0] && teclaIngresada != opcionesValidas[1])
    {
        printf("%s\n", segundoMensaje);
        printf("%s ", primerMensaje);
        scanf("%c", &teclaIngresada);
        fflush(stdin);
    }

    return teclaIngresada;
}

void solucionTP(t_juego* juegos)
{
    //Datos del enunciado
    const float periodosMessiSegundos[CANT_JUEGOS] = {1.5, 3.0, 5.0};
    const float alturaTotalAcunaMetros[CANT_JUEGOS] = {3.0, 11.11, 14.14};
    const int frecuenciasDiMariaMinuto[CANT_JUEGOS] = {10, 15, 30};

    for(int i = 0; i < CANT_JUEGOS; i++)
    {
        for(int j = 0; j < CANT_JUGADORES; j++)
        {
            switch(j)
            {
                case 0: //MESSI
                    calcularDatosJugadorConPeriodo(&(juegos + i)->jugadores[j], i, j, periodosMessiSegundos[i]);
                    break;
                case 1: //DI MARIA
                    calcularDatosJugadorConFrecuencia(&(juegos + i)->jugadores[j], i, j, frecuenciasDiMariaMinuto[i]);
                    break;
                case 2: //ACUNA
                    calcularDatosJugadorConAltura(&(juegos + i)->jugadores[j], i, j, alturaTotalAcunaMetros[i]);
                    break;
            }
            calculaDistancia(&(juegos + i)->jugadores[j]); //Mismo calculo para todos
        }
        calculaCantAlineamientos(juegos + i);
    }
  /* Aquí deben estar los llamados a las funciones creadas por ustedes */
}

void calcularDatosJugadorConPeriodo(t_jugador *jugador, int juegoIndex, int jugadorIndex, float periodo)
{//DATOS MESSI
    jugador->golpesPorMinuto = 60 / periodo;
    jugador->velocidadInicial = calculaVelDesdePeriodo(periodo);
    float alturaTemp = calculaAlturaDesdeVelocidad(jugador->velocidadInicial);
    jugador->alturaGolpe = calculaAlturaGolpe(alturaTemp, jugador->estatura);
    jugador->alturaMaximaDeLaPelota = alturaTemp + jugador->alturaGolpe;
}

void calcularDatosJugadorConFrecuencia(t_jugador *jugador, int juegoIndex, int jugadorIndex, float frecuencia)
{//DATOS DI MARIA
    jugador->golpesPorMinuto = frecuencia;
    jugador->velocidadInicial = calculaVelDesdePeriodo(60 / frecuencia);
    float alturaTemp = calculaAlturaDesdeVelocidad(jugador->velocidadInicial);
    jugador->alturaGolpe = calculaAlturaGolpe(alturaTemp, jugador->estatura);
    jugador->alturaMaximaDeLaPelota = alturaTemp + jugador->alturaGolpe;
}

void calcularDatosJugadorConAltura(t_jugador *jugador, int juegoIndex, int jugadorIndex, float alturaMaxima)
{//DATOS ACUNA
    jugador->alturaMaximaDeLaPelota = alturaMaxima;
    jugador->alturaGolpe = calculaAlturaGolpe(alturaMaxima, jugador->estatura);
    jugador->velocidadInicial = calculaVelDesdeAltura(alturaMaxima - jugador->alturaGolpe);
    jugador->golpesPorMinuto = 60 / (calculaTiempoDesdeVelocidad(jugador->velocidadInicial) * 2);
}

//ECUACIONES
void calculaDistancia(t_jugador* jugador)
{
    jugador->distanciaRecorrida = (jugador->golpesPorMinuto * 3) * ((jugador->alturaMaximaDeLaPelota - jugador->alturaGolpe) * 2);
}

float calculaAlturaGolpe(const float alturaMaxima, const float estaturaJugador)
{
    return (alturaMaxima > 1.5) ? estaturaJugador * 0.15 : estaturaJugador * 0.1;
}

float calculaVelDesdePeriodo(const float periodo)
{
    return GRAVEDAD * (periodo / 2);
}

float calculaAlturaDesdeVelocidad(const float velocidad)
{
    return (pow(velocidad, 2)) / (2 * GRAVEDAD);
}

float calculaVelDesdeAltura(const float alturaMaxima)
{
    return sqrt(2 * alturaMaxima * GRAVEDAD);
}

float calculaTiempoDesdeVelocidad(const float velocidad)
{
    return velocidad / GRAVEDAD;
}

//ALINEAMIENTOS
void calculaCantAlineamientos(t_juego* juegos)
{
    t_coordenada posiciones[CANT_JUGADORES];
    booleano estaSubiendo[CANT_JUGADORES];
    float tiempoAAlturaMax[CANT_JUGADORES];
    float tiempoAct[CANT_JUGADORES];

    for(int i = 0; i < CANT_JUGADORES; i++)
    {
        posiciones[i].x = juegos->jugadores[i].posicion;
        posiciones[i].y = juegos->jugadores[i].alturaGolpe;
        estaSubiendo[i] = TRUE;
        tiempoAAlturaMax[i] = calculaTiempoDesdeVelocidad(juegos->jugadores[i].velocidadInicial);
        tiempoAct[i] = 0;
    }

    booleano esAlineacion = FALSE;
    juegos->cantidadAlineamientos = 0;
    juegos->alineamientos[0].duracion = 0;
    booleano esPendienteAlineamiento = FALSE;

    for(int j = 0; j < CANT_MILISEG; j++)
    {
        for(int k = 0; k < CANT_JUGADORES; k++)
        {
            posiciones[k].y = calculaAlturaParaAlineamiento(&estaSubiendo[k], tiempoAAlturaMax[k], &tiempoAct[k], juegos->jugadores[k].alturaGolpe, juegos->jugadores[k].velocidadInicial);
        }

        float pendienteAB = calculaPendiente(&posiciones[2], &posiciones[1]);
        float pendienteBC = calculaPendiente(&posiciones[1], &posiciones[0]);

        if(fabs(pendienteAB - pendienteBC) < DELTA)
            esPendienteAlineamiento = TRUE;
        else
            esPendienteAlineamiento = FALSE;

        if(esPendienteAlineamiento && !esAlineacion)
        {//Caso de primer alineamiento
            esAlineacion = TRUE;
            juegos->alineamientos->duracion++;

            juegos->alineamientos[juegos->cantidadAlineamientos].instanteInicial.minuto = milisegAMinutos(j);
            juegos->alineamientos[juegos->cantidadAlineamientos].instanteInicial.segundo = milisegASegundos(j);
            juegos->alineamientos[juegos->cantidadAlineamientos].instanteInicial.milisegundo = j % 1000; //Mantiene de 0 a 999

            juegos->alineamientos[juegos->cantidadAlineamientos].pos1.x = posiciones[2].x;
            juegos->alineamientos[juegos->cantidadAlineamientos].pos1.y = posiciones[2].y;

            juegos->alineamientos[juegos->cantidadAlineamientos].pos2.x = posiciones[1].x;
            juegos->alineamientos[juegos->cantidadAlineamientos].pos2.y = posiciones[1].y;

            juegos->alineamientos[juegos->cantidadAlineamientos].pos3.x = posiciones[0].x;
            juegos->alineamientos[juegos->cantidadAlineamientos].pos3.y = posiciones[0].y;

            juegos->alineamientos[juegos->cantidadAlineamientos].pendiente = (pendienteAB + pendienteBC) / 2;
        }

        if(esAlineacion && !esPendienteAlineamiento)
        {//Caso de fin de alineamiento
            juegos->alineamientos[juegos->cantidadAlineamientos].duracion = juegos->alineamientos->duracion;
            juegos->alineamientos->duracion = 0;
            juegos->cantidadAlineamientos++;
            esAlineacion = FALSE;
        }

        if(esAlineacion && esPendienteAlineamiento)
        {//Caso de alineamiento continuo
            juegos->alineamientos->duracion++;
        }
    }
}

float calculaAlturaParaAlineamiento(booleano* estaSubiendo, float tiempoAAlturaMax, float* tiempoAct, float alturaGolpe, float velocidadInicial)
{
    //Contemplamos los casos de borde
    if(redondearTiempo(*tiempoAct) == redondearTiempo(tiempoAAlturaMax))
    {//Pelota llega a la altura maxima
        *estaSubiendo = FALSE;
        *tiempoAct = redondearTiempo(tiempoAAlturaMax);

    } else if(redondearTiempo(*tiempoAct) == 0)
    {//Pelota llega al punto donde se la patea
        *estaSubiendo = TRUE;
        *tiempoAct = 0;
    }

    float alturaTemp = velocidadInicial * (*tiempoAct) + 0.5 * GRAVEDAD * pow(*tiempoAct, 2);

    if(*estaSubiendo)
        *tiempoAct += 0.001;
    else
        *tiempoAct -= 0.001;

    return alturaTemp + alturaGolpe;
}

//Funciones de tiempo y pendientes

float redondearTiempo(float tiempoAct)
{//Redondea a 3 decimales. Ej: 5.3413415 -> 5.341
    return round(tiempoAct * 1000.0) / 1000.0;
}

float calculaPendiente(const t_coordenada* coordenada1, const t_coordenada* coordenada2)
{
    return (coordenada2->y - coordenada1->y)/(coordenada2->x - coordenada1->x);
}

float milisegAMinutos(int milisegundo)
{
    return milisegundo / (60 * 1000);
}

float milisegASegundos(int milisegundo)
{
    return (milisegundo % (60 * 1000))/ 1000; //Mantiene dentro del rango de 0 a 59.999
}
