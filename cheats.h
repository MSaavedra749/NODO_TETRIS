#ifndef CHEATS_H_INCLUDED
#define CHEATS_H_INCLUDED

#include <stdbool.h>

typedef struct{
    bool I_nfinita;
    bool modo_lento;
    bool shaker;
    bool invisible;
    bool turbo;
    bool invertido;
    unsigned long int tiempoTranscurrido;
}cheatsDat;

void inicializar_cheats();

void loop_dibujo_cheats();
void loop_logica_cheats();

void aplicar_cheats();

bool invisibilidad_bloques();
int sismo();
bool noMezclar();
bool lento();
bool rapido();
bool alrevez();

#endif
