#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <stdbool.h>

typedef enum{
    t_Arriba,
    t_Abajo,
    t_Izquierda,
    t_Derecha,
    t_Enter,
    t_Escape,
    t_Desconocida,
    t_a,
    t_b,
    t_c,
    t_d,
    t_e,
    t_f,
    t_g,
    t_h,
    t_i,
    t_j,
    t_k,
    t_l,
    t_m,
    t_n,
    t_o,
    t_p,
    t_q,
    t_r,
    t_s,
    t_t,
    t_u,
    t_v,
    t_w,
    t_x,
    t_y,
    t_z,
    t_0,
    t_1,
    t_2,
    t_3,
    t_4,
    t_5,
    t_6,
    t_7,
    t_8,
    t_9,
    t_Retroceso,
    t_Espacio
}Tecla;

void actualizar_input();
Tecla obtenerTeclaPresionada();
bool obtenerTeclaSostenida(Tecla t);

#endif
