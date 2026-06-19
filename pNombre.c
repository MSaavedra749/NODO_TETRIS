#include "pNombre.h"
#include "dibujo.h"
#include "pNombre.h"
#include "graficos.h"
#include "input.h"
#include "mEstados.h"
#include <math.h>
#include <stdio.h>

void dibujar_pantalla_nombre(){
    //Texto fijo
    limpiar(9);
    dibujar_fondo();
    //
    // REEMPLAZAR POR UNA FUNCION MEJOR
    // VINO LA FUNCION MEJOR
    dibujar_texto("escribe tu nombre", 10, 10, 2 * pantalla->escala_v, 0);
    if(contexto->tamanioNombre > 0)
    {
        dibujar_texto(contexto->nombreActual, CENTRADO, 40, 3*pantalla->escala_v, 0);
    }


}

///Por el momento solo toma nombres en minuscula, y por el momento no se acepta espacios
void loop_pantalla_nombre(){
    Tecla tecla = obtenerTeclaPresionada();
    char* pchar = contexto->nombreActual + contexto->tamanioNombre;
    char letra;

    if(tecla == t_Escape){
        printf("Esto hay que sacarlo\n");
        cambiar_contexto(PANTALLA_SPLASH);
    }
    if( contexto->tamanioNombre < 10)
    {
        if(tecla >= t_a && tecla <= t_z)
        {
            letra = tecla - t_a + 'a';
            *pchar = letra;
            pchar++;
            contexto->tamanioNombre++;
        }
        if(tecla >= t_0 && tecla <= t_9)
        {
            letra = tecla - t_0 + '0';
            *pchar = letra;
            pchar++;
            contexto->tamanioNombre++;
        }
    }
    if(tecla == t_Retroceso && contexto->tamanioNombre > 0)
    {
        pchar--;
        contexto->tamanioNombre--;
    }
    if(tecla == t_Enter && contexto->tamanioNombre > 0)
    {
        cambiar_contexto(PANTALLA_MENU);
        return;
    }
    *pchar = '\0';
}
