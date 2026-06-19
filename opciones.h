#ifndef OPCIONES_H_INCLUDED
#define OPCIONES_H_INCLUDED
#include <SDL3/SDL.h>

#include "dibujo.h"
#include "mEstados.h"

#define IZQUIERDA -1
#define DERECHA 1

#define CANT_COLOR 30

typedef struct
{
    int resolucion_elegida;
    int velocidad_elegida;
    int paleta_elegida;
    int escala_ventana;
    int ancho_dx_elegida;
}Configuracion;


bool guardar_configuraciones(const char* nombre_archivo);
bool cargar_crear_archivo(const char* nombre_archivo);

extern Configuracion config_actual;

void dibujar_opciones();
void loop_opciones();

float obtener_velocidad_actual_ms();
int obtener_ancho_actual();
int obtener_alto_actual();
int obtener_escala_actual();
int obtener_ancho_dx();
//void aplicar_paleta();
int obtener_dificultad_actual();
colorRGB obtener_color(int ind);

///Por el momento es medio auxiliar
void aplicar_cambios_graficos(SDL_Window* window);


#endif // OPCIONES_H_INCLUDED
