#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "piezas.h"
#include "dibujo.h"

#define TABLERO_FILAS 20
#define TAMANIO_BLOQUE 9

typedef struct
{
    uint8_t** matriz;
    int columnas;
}Tablero;


void inicialiar_tablero(Tablero* t, int columnas);
void dibujar_tablero(Tablero* t, uint16_t offsetX, uint16_t offsetY, bool* fila_marcada, bool destello);
void dibujar_tablero_bizarro(Tablero* t, uint16_t offsetX, uint16_t offsetY);
void limpiar_filas(Tablero* t);
bool colision(Tablero* t, Pieza* p, int ox, int oy, bool modo_dx);
void anclar_pieza(Tablero* t, Pieza* p, bool modo_dx);
void destruir_tablero(Tablero* t, int filas);
bool hay_lineas_llenas(Tablero* t, bool marcadas[TABLERO_FILAS], int* cant_lineas);


#endif // TABLERO_H_INCLUDED
