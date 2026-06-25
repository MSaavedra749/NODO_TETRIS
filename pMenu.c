#include "pMenu.h"
#include "dibujo.h"
#include "mEstados.h"
#include <stdio.h>
#include "graficos.h"
#include "tetris.h"
#include "input.h"
#include "sonido.h"


#define CANTIDAD_ELEMENTOS_MENU 5

int pos_puntero = 0;

Tecla listaTeclas[10];
int cantTeclas = 0;
Tecla konamiCode[10] = {t_Arriba, t_Arriba, t_Abajo, t_Abajo, t_Izquierda, t_Derecha,
                            t_Izquierda, t_Derecha, t_b, t_a};

void shift_left(Tecla*, int*, Tecla);

void prepararEstados(bool);

bool existe_partida()
{
    FILE* pf = fopen("partida.bin","rb");
    if(pf)
    {
        fclose(pf);
        return true;
    }
    return false;
}

void loopDibujoMenu(){
    limpiar(0);

    dibujar_fondo();

    char text[50];
    sprintf(text, "Bienvenido %s", contexto->nombreActual);
    dibujar_texto(text, 10.5, 10.5, 2*pantalla->escala_v, 1);
    dibujar_texto(text, 10, 10, 2*pantalla->escala_v, 2);
    // desde donde empezamos a dibujar ( 0 = CONTINUAR ; 1 = JUGAR)
    int inicio = existe_partida() ? 0: 1;

    //Para evitar que pos_puntero este en cero cuando no hay una partida
    if(pos_puntero < inicio)
        pos_puntero = inicio;
    /*
    dibujar_texto("ABCDEFGHIJKLMNOPQRSTUVWXYZ",0, 20,1,0);
    dibujar_texto("0123456789", 0, 26, 1, 0);
    dibujar_texto("abcdefghijklmnopqrstuvwxyz", 0, 32, 1, 0);
    */
    //Menu
    char tMenu[CANTIDAD_ELEMENTOS_MENU][20] = {"CONTINUAR","JUGAR","DELUXE" , "OPCIONES", "SALIR"};
    for(int i = inicio; i < CANTIDAD_ELEMENTOS_MENU; i++)
    {
        char linea[40];
        if(i==pos_puntero)
            sprintf(linea, "> %s", tMenu[i]);
        else
            sprintf(linea, "  %s", tMenu[i]);

        int pos_y = i - inicio;

        dibujar_texto(linea, CENTRADO + 0.5f, 46 + (pos_y * 10), 2*pantalla->escala_v, 1);
        dibujar_texto(linea, CENTRADO, 45 + (pos_y * 10), 2*pantalla->escala_v, 2);
    }

    dibujar_texto(".NODO 2026", 0, 95, 1*pantalla->escala_v, 2);
}

void loopLogicaMenu(){
    //Lo mismo que arriba
    int inicio = existe_partida() ? 0 : 1;
    if(pos_puntero < inicio)
        pos_puntero = inicio;

    Tecla tecla = obtenerTeclaPresionada();

    //cheat menu
    int coincidencias = 0;
    if(tecla != t_Desconocida){
        shift_left(listaTeclas, &cantTeclas, tecla);
        if(cantTeclas == 10){
            for(int i = 0; i < 10; i++){
                if(listaTeclas[i] == konamiCode[i])
                    coincidencias++;
            }
        }
        if(coincidencias == 10)
            cambiar_contexto(PANTALLA_CHEATS);
    }

    if(tecla == t_Arriba)
    {
        pos_puntero -= 1;
        if(pos_puntero < inicio)
            pos_puntero = CANTIDAD_ELEMENTOS_MENU-1;
    }else if(tecla == t_Abajo)
    {
        pos_puntero += 1;
        if(pos_puntero > CANTIDAD_ELEMENTOS_MENU-1)
            pos_puntero = inicio;
    }else if(tecla == t_Enter)
    {
        switch(pos_puntero)
        {
            case 0:
            {
                FILE* pf = fopen("partida.bin","rb");
                if(pf)
                {
                    PartidaGuardada save;
                    fread(&save, sizeof(PartidaGuardada),1,pf);
                    fclose(pf);
                    if(save.modo_dx)
                        prepararEstados(true);
                    else
                        prepararEstados(false);
                    cambiar_contexto(PANTALLA_TETRIS);
                    cargar_partida("partida.bin");
                }
                break;
            }
            case 1:
                prepararEstados(false);
                cambiar_contexto(PANTALLA_TETRIS);
                break;
            case 2:
                prepararEstados(true);
                cambiar_contexto(PANTALLA_TETRIS);
                break;
            case 3:
                cambiar_contexto(PANTALLA_OPCIONES);
                break;
            case 4:
                contexto->corriendo = false;
                break;
        }
    }
}

void prepararEstados(bool modo_dx)
{
    if(!inicializar_tetris(modo_dx)){
        printf("Error al iniciar estados tetris");
        contexto->corriendo = false;
    }
    if(!modo_dx)
        audio_select_loop("Sonidos/themeA.mp3");
    else
        audio_select_loop("Sonidos/themeB.mp3");
    //audio_switch_loop();
}

void shift_left(Tecla* tecla, int* cant, Tecla ent)
{
    if(cantTeclas < 10){
        tecla[*cant] = ent;
        *cant += 1;
    }
    else{
        for(int i = 0; i < 9; i++){
            tecla[i] = tecla[i+1];
        }
        tecla[*cant-1] = ent;
    }
}
