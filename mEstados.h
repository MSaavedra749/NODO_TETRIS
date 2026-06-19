#ifndef MESTADOS_H_INCLUDED
#define MESTADOS_H_INCLUDED
#include <stdbool.h>
#include "dibujo.h"
#include <SDL3/SDL.h>

#define TAMANIO_NOMBRE 10

#define ARCHIVO_OP "opciones.bin"

typedef enum{
    PANTALLA_SPLASH,
    PANTALLA_NOMBRE,
    PANTALLA_MENU,
    PANTALLA_OPCIONES,
    PANTALLA_TETRIS,
    PANTALLA_DELUXE,
    PANTALLA_PERDER,
    PANTALLA_PAUSA,
    PANTALLA_CHEATS
}eEstadoJuego;

//
// Punteros a funcion genericos mas dato generico para animaciones (contador de frames)
//
typedef struct{
    void (*dibujar_escena)();
    void (*loop_escena)();
    int contador;
}Escena;

//  Maquina de estados
//  Contiene todos los estados posibles mas el estado actual
typedef struct{
    eEstadoJuego estadoActual;
    bool corriendo;
    Escena escenaSplash;
    Escena escenaNombre;
    Escena escenaTetris;
    Escena escenaOpciones;
    Escena escenaMenu;
    Escena escenaPerdiste;
    Escena escenaPausa;
    Escena escenaCheats;
    Escena *escenaActual;
    char nombreActual[TAMANIO_NOMBRE]; //Por el momento determinamos un rango "alto"
    int tamanioNombre;
    bool modo_tetris;
    SDL_Window* window;
    SDL_Renderer* renderer;
}Context;

Context* inicializar_contexto(SDL_Window* window, SDL_Renderer* renderer);

extern Context* contexto;

//Llamada por el bucle principal
//le encarga a los estados correr su propio bucle de video y logica
void correr();

void cambiar_contexto(eEstadoJuego);

void limpiar_contexto();

#endif // MESTADOS_H_INCLUDED
