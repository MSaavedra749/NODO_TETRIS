#include "Perder.h"
#include "input.h"
#include "dibujo.h"
#include "graficos.h"
#include "mEstados.h"
#include "opciones.h"
#include "puntos.h"
#include "tetris.h"
#include <stdbool.h>
#include "sonido.h"

int pos_punteroG = 0;

void loop_dibujar_perder()
{

    int columnas_totales = pantalla->ancho/ pantalla->mino_tamanio;
    int mitad_pantalla = (columnas_totales/2) + 1;

    int columnas_tapadas = contexto->escenaPerdiste.contador / 5;

    if(columnas_tapadas > mitad_pantalla)
    {
        columnas_tapadas = mitad_pantalla;
    }

    bool filtro_completo = columnas_tapadas >= mitad_pantalla;

    if(filtro_completo)
        dibujar_rect(0, 0, pantalla->ancho, pantalla->alto, 24);

    for(int i = 0; i < columnas_tapadas; i++)
    {
        int posX_izq = i * pantalla->mino_tamanio;
        int posx_der = pantalla->ancho - ((i + 1)*pantalla->mino_tamanio);

        for(int y = 0; y < pantalla->alto; y += pantalla->mino_tamanio)
        {
            dibujar_mino_pantalla(posX_izq,y,7);
            dibujar_mino_pantalla(posx_der,y,7);
        }
    }

    if(filtro_completo)
    {
        dibujar_filtro_dither(1);
        dibujar_texto("PERDISTE",33.5f,10.5f,2*pantalla->escala_v,1);
        dibujar_texto("PERDISTE",33,10,2*pantalla->escala_v,0);
        //dibujar_texto("<agregar estadistica>",33,50,pantalla->escala_v,0);
        // llegaron las estadisticas
        int cant = pedirCant(contexto->modo_tetris, obtener_dificultad_actual());
        for(int i = 0; i < cant; i++){
            char text[40];
            char tempNum[9];
            jugador* dato = pedirPos(contexto->modo_tetris, obtener_dificultad_actual(), i);
            sprintf(tempNum,"%d",dato->puntos);
            sprintf(text, "%s - %s", dato->nombre, tempNum);
            dibujar_texto(text, CENTRADO+0.5f, 20.5f + (5*i), 1.5f*pantalla->escala_v, 1);
            dibujar_texto(text, CENTRADO, 20 + (5 * i), 1.5f*pantalla->escala_v, 0);

        }
        char textosPerder[2][20] = {"VOLVER A JUGAR", "SALIR"};
        char tex[40];
        for(int i = 0; i < 2; i++){
            if(pos_punteroG == i){
                sprintf(tex, "> %s",textosPerder[i]);
            }else {
                sprintf(tex, " %s",textosPerder[i]);
            }
            dibujar_texto(tex, CENTRADO+0.5f, 85.5f + (i * 5), pantalla->escala_v, 1);
            dibujar_texto(tex, CENTRADO, 85 + (i * 5), pantalla->escala_v, 0);
        }
    }


}

void loop_logica_perder()
{
    //Todo esto me sirve para evitar que el contador se sume hasta el infinito

    //Dato de color, si no controlamos eso no pasa nada, en teoria tendriamos que estar en la pantalla de perdiste un tiempo muy largo (414 dias)
    //Para que recien explote
    int columnas_totales = pantalla->ancho/ pantalla->mino_tamanio;
    int mitad_pantalla = (columnas_totales/2) + 1;

    int frames_final = mitad_pantalla * 5;

    if(contexto->escenaPerdiste.contador <= frames_final)
    {
        contexto->escenaPerdiste.contador++;
    }

    Tecla tecla = obtenerTeclaPresionada();

    if(tecla == t_Arriba){
        pos_punteroG -= 1;
        pos_punteroG = (pos_punteroG + 2) % 2;
    }
    if(tecla == t_Abajo){
        pos_punteroG += 1;
        pos_punteroG = (pos_punteroG + 2) % 2;
    }
    if(tecla == t_Enter){
        limpiar_tetris();
        limpiarLB(contexto->modo_tetris, obtener_dificultad_actual());
        remove("partida.bin");
        switch(pos_punteroG){
            case 0:
                inicializar_tetris(contexto->modo_tetris);
                cambiar_contexto(PANTALLA_TETRIS);
                audio_switch_loop();
                break;
            case 1:
                cambiar_contexto(PANTALLA_MENU);
                audio_stop_loop();
                break;
        }
    }
}
