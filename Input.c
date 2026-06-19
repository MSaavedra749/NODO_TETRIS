#include "input.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_oldnames.h>

bool estados[50];
Tecla lastK = t_Desconocida;

void actualizar_input()
{
    lastK = t_Desconocida;
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_EVENT_KEY_DOWN){
            switch(event.key.key){
                case SDLK_UP:
                    estados[0] = true;
                    lastK = t_Arriba;
                    break;
                case SDLK_DOWN:
                    estados[1] = true;
                    lastK = t_Abajo;
                    break;
                case SDLK_RIGHT:
                    estados[2] = true;
                    lastK = t_Derecha;
                    break;
                case SDLK_LEFT:
                    estados[3] = true;
                    lastK = t_Izquierda;
                    break;
                case SDLK_RETURN:
                    estados[4] = true;
                    lastK = t_Enter;
                    break;
                case SDLK_ESCAPE:
                    estados[5] = true;
                    lastK = t_Escape;
                    break;
                case SDLK_A:
                    estados[6] = true;
                    lastK = t_a;
                    break;
                case SDLK_B:
                    estados[7] = true;
                    lastK = t_b;
                    break;
                case SDLK_C:
                    estados[8] = true;                    lastK = t_c;
                    break;
                case SDLK_D:
                    estados[9] = true;                    lastK = t_d;
                    break;
                case SDLK_E:
                    estados[10] = true;                    lastK = t_e;
                    break;
                case SDLK_F:
                    estados[11] = true;                    lastK = t_f;
                    break;
                case SDLK_G:
                    estados[12] = true;                    lastK = t_g;
                    break;
                case SDLK_H:
                    estados[13] = true;                    lastK = t_h;
                    break;
                case SDLK_I:
                    estados[14] = true;                    lastK = t_i;
                    break;
                case SDLK_J:
                    estados[15] = true;                    lastK = t_j;
                    break;
                case SDLK_K:
                    estados[16] = true;                    lastK = t_k;
                    break;
                case SDLK_L:
                    estados[17] = true;                    lastK = t_l;
                    break;
                case SDLK_M:    
                    estados[18] = true;                    lastK = t_m;
                    break;
                case SDLK_N:
                    estados[19] = true;                    lastK = t_n;
                    break;
                case SDLK_O:
                    estados[20] = true;                    lastK = t_o;
                    break;
                case SDLK_P:
                    estados[21] = true;                    lastK = t_p;
                    break;
                case SDLK_Q:
                    estados[22] = true;                    lastK = t_q;
                    break;
                case SDLK_R:
                    estados[23] = true;                    lastK = t_r;
                    break;
                case SDLK_S:    
                    estados[24] = true;                    lastK = t_s;
                    break;
                case SDLK_T:
                    estados[25] = true;                    lastK = t_t;
                    break;
                case SDLK_U:
                    estados[26] = true;                    lastK = t_u;
                    break;
                case SDLK_V:
                    estados[27] = true;                    lastK = t_v;
                    break;
                case SDLK_W:
                    estados[28] = true;                    lastK = t_w;
                    break;
                case SDLK_X:
                    estados[29] = true;                    lastK = t_x;
                    break;
                case SDLK_Y:
                    estados[30] = true;                    lastK = t_y;
                    break;
                case SDLK_Z:    
                    estados[31] = true;                    lastK = t_z;
                    break;
                case SDLK_0:
                    estados[32] = true;                    lastK = t_0;
                    break;
                case SDLK_1:
                    estados[33] = true;                    lastK = t_1;
                    break;
                case SDLK_2:
                    estados[34] = true;                    lastK = t_2;
                    break;
                case SDLK_3:
                    estados[35] = true;                    lastK = t_3;
                    break;
                case SDLK_4:
                    estados[36] = true;                    lastK = t_4;
                    break;
                case SDLK_5:
                    estados[37] = true;                    lastK = t_5;
                    break;
                case SDLK_6:
                    estados[38] = true;                    lastK = t_6;
                    break;
                case SDLK_7:
                    estados[39] = true;                    lastK = t_7;
                    break;
                case SDLK_8:
                    estados[40] = true;                    lastK = t_8;
                    break;
                case SDLK_9:
                    estados[41] = true;                    lastK = t_9;
                    break;
                case SDLK_BACKSPACE:
                    estados[42] = true;                    lastK = t_Retroceso;
                    break;
                case SDLK_SPACE:
                    estados[43] = true;                    lastK = t_Espacio;
                    break;
                default:
                    lastK = t_Desconocida;
            }
        }else if(event.type == SDL_EVENT_KEY_UP){
            switch(event.key.key){
                case SDLK_UP:
                    estados[0] = false;
                    break;
                case SDLK_DOWN:
                    estados[1] = false;
                    break;
                case SDLK_RIGHT:
                    estados[2] = false;
                    break;
                case SDLK_LEFT:
                    estados[3] = false;
                    break;
                case SDLK_RETURN:
                    estados[4] = false;
                    break;
                case SDLK_ESCAPE:
                    estados[5] = false;
                    break;
                case SDLK_A:
                    estados[6] = false;
                    break;
                case SDLK_B:
                    estados[7] = false;                   
                    break;
                case SDLK_C:
                    estados[8] = false;                    
                    break;
                case SDLK_D:
                    estados[9] = false;                    
                    break;
                case SDLK_E:
                    estados[10] = false;                    
                    break;
                case SDLK_F:
                    estados[11] = false;                    
                    break;
                case SDLK_G:
                    estados[12] = false;                    
                    break;
                case SDLK_H:
                    estados[13] = false;                    
                    break;
                case SDLK_I:
                    estados[14] = false;                    
                    break;
                case SDLK_J:
                    estados[15] = false;                    
                    break;
                case SDLK_K:
                    estados[16] = false;                    
                    break;
                case SDLK_L:
                    estados[17] = false;                    
                    break;
                case SDLK_M:    
                    estados[18] = false;                    
                    break;
                case SDLK_N:
                    estados[19] = false;                    
                    break;
                case SDLK_O:
                    estados[20] = false;                    
                    break;
                case SDLK_P:
                    estados[21] = false;                    
                    break;
                case SDLK_Q:
                    estados[22] = false;                    
                    break;
                case SDLK_R:
                    estados[23] = false;                    
                    break;
                case SDLK_S:    
                    estados[24] = false;                    
                    break;
                case SDLK_T:
                    estados[25] = false;                    
                    break;
                case SDLK_U:
                    estados[26] = false;                
                    break;
                case SDLK_V:
                    estados[27] = false;                    
                    break;
                case SDLK_W:
                    estados[28] = false;                    
                    break;
                case SDLK_X:
                    estados[29] = false;                    
                    break;
                case SDLK_Y:
                    estados[30] = false;                    
                    break;
                case SDLK_Z:    
                    estados[31] = false;                    
                    break;
                case SDLK_0:
                    estados[32] = false;                    
                    break;
                case SDLK_1:    
                    estados[33] = false;                    
                    break;
                case SDLK_2:
                    estados[34] = false;                    
                    break;
                case SDLK_3:
                    estados[35] = false;                    
                    break;
                case SDLK_4:
                    estados[36] = false;                    
                    break;
                case SDLK_5:
                    estados[37] = false;                    
                    break;
                case SDLK_6:
                    estados[38] = false;                    
                    break;
                case SDLK_7:
                    estados[39] = false;                    
                    break;
                case SDLK_8:
                    estados[40] = false;                
                    break;  
                case SDLK_9:
                    estados[41] = false;                    
                    break;
                case SDLK_BACKSPACE:
                    estados[42] = false;
                    break;
                case SDLK_SPACE:
                    estados[43] = false;
                    break;
            }
        }
    }
}

Tecla obtenerTeclaPresionada()
{
    if(lastK==-1)
        return t_Desconocida;
    else
        return lastK;
}

bool obtenerTeclaSostenida(Tecla t)
{
    return estados[t];
}
