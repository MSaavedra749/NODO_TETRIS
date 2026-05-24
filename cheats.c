#include "cheats.h"
#include "dibujo.h"
#include "mEstados.h"
#include "pMenu.h"
#include <GBT/gbt_entrada.h>
#include <stdbool.h>
#include <math.h>

cheatsDat trucos;

int pos_marcadorC = 0;

void inicializar_cheats()
{
    trucos.I_nfinita = false;
    trucos.modo_lento = false;
    trucos.shaker = false;
    trucos.invisible = false;
    trucos.turbo = false;
    trucos.invisible = false;

    trucos.tiempoTranscurrido = 0;
}

void loop_dibujo_cheats()
{
    loopDibujoMenu();
    dibujar_rect(0, porc_a_pixel(10, pantalla->alto), pantalla->ancho/2, porc_a_pixel(80, pantalla->alto), 1);
    dibujar_rect(0, porc_a_pixel(11, pantalla->alto), (pantalla->ancho/2)-1, porc_a_pixel(78, pantalla->alto), 2);
    dibujar_rect(0, porc_a_pixel(12, pantalla->alto), (pantalla->ancho/2)-2, porc_a_pixel(76, pantalla->alto), 1);
    dibujar_texto("TRUCOS", 10, 25, 2, 0);

    dibujar_texto("> ", 0, 40 + (5 * pos_marcadorC), 1, 0);
    if(trucos.I_nfinita)
        dibujar_texto("[:] I_Nfinita", 2, 40, 1, 0);
    else
        dibujar_texto("[;] I_Nfinita", 2, 40, 1, 0);
    if(trucos.modo_lento)
        dibujar_texto("[:] Gravedad Lunar", 2, 45, 1, 0);
    else
        dibujar_texto("[;] Gravedad Lunar", 2, 45, 1, 0);
    if(trucos.shaker)
        dibujar_texto("[:] T_Rremoto", 2, 50, 1, 0);
    else
        dibujar_texto("[;] T_Rremoto", 2, 50, 1, 0);
    if(trucos.invisible)
        dibujar_texto("[:] Fe Ciega", 2, 55, 1, 0);
    else
        dibujar_texto("[;] Fe Ciega", 2, 55, 1, 0);
    if(trucos.turbo)
        dibujar_texto("[:] Hiperespacio", 2, 60, 1, 0);
    else
        dibujar_texto("[;] Hiperespacio", 2, 60, 1, 0);
    if(trucos.invertido)
        dibujar_texto("[:] Efecto Coriolis", 2, 65, 1, 0);
    else
        dibujar_texto("[;] Efecto Coriolis", 2, 65, 1, 0);
    //dibujar_texto("> [:] test1",0, 40, 1, 0);
    //dibujar_texto("  [;] test2", 0, 45, 1, 0);
    return;
}

void loop_logica_cheats(){
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    if(tecla == GBTK_ARRIBA){
        pos_marcadorC -= 1;
        pos_marcadorC = (pos_marcadorC + 6) % 6;
    }
    if(tecla == GBTK_ABAJO){
        pos_marcadorC += 1;
        pos_marcadorC = (pos_marcadorC + 6) % 6;
    }
    if(tecla == GBTK_ENTER){
        switch(pos_marcadorC){
            case 0:
                trucos.I_nfinita = !trucos.I_nfinita;
                break;
            case 1:
                trucos.modo_lento = !trucos.modo_lento;
                break;
            case 2:
                trucos.shaker = !trucos.shaker;
                break;
            case 3:
                trucos.invisible = !trucos.invisible;
                break;
            case 4:
                trucos.turbo = !trucos.turbo;
                break;
            case 5:
                trucos.invertido = !trucos.invertido;
        }
    }

    if(tecla == GBTK_ESCAPE){
        cambiar_contexto(PANTALLA_MENU);
    }
    return;
}

bool invisibilidad_bloques()
{
    return trucos.invisible;
}

int sismo()
{
    trucos.tiempoTranscurrido += 16;
    if(trucos.shaker)
        return sin(trucos.tiempoTranscurrido) * 6;
    else
        return 0;
}

bool noMezclar()
{
    return trucos.I_nfinita;
}

bool lento()
{
    return trucos.modo_lento;
}

bool rapido()
{
    return trucos.turbo;
}

bool alrevez()
{
    return trucos.invertido;
}

void aplicar_cheats();
