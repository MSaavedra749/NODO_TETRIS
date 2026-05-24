#ifndef PUNTOS_H_INCLUDED
#define PUNTOS_H_INCLUDED

#include <stdbool.h>
#include "mEstados.h"
#include "tda_vector.h"

typedef struct{
    char nombre[TAMANIO_NOMBRE];
    int puntos;
}jugador;

typedef struct{
    int cant;
    Vector lista;
}tabla;

extern tabla normal[3];
extern tabla deluxe[3];

void inicializarLeaderboard();

bool cargarArchivo();
void guardarArchivo();

void cargarLB(bool dx, int dif, jugador* ent);
void limpiarLB(bool dx, int dif);

int pedirCant(bool dx, int dif);
jugador* pedirPos(bool dx, int dif, int n);

#endif
