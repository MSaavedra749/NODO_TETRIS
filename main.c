#include <SDL3/SDL_render.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include "cheats.h"
#include "mEstados.h"
#include <stdbool.h>
#include "dibujo.h"
#include "opciones.h"
#include <time.h>
#include "puntos.h"
#include "sonido.h"

int main(int argc, char* argv[])
{
    cargar_crear_archivo(ARCHIVO_OP);
    int ESCALA_VENTANA = 2;
    int ESCALA_V = 1;
    //Permitir al usuario elegir modo de video
    if(argc > 1){
        for(int i = 1; i < argc; i++)
            {
                if(argv[i][0] == '-'){
                    if(argv[i][1] == 'v' || argv[i][1] == 'V'){
                        config_actual.resolucion_elegida = 1;
                    }else if(argv[i][1] == 'c' || argv[i][1] == 'C'){
                        config_actual.resolucion_elegida = 0;
                    }else if(argv[i][1] > '0' && argv[i][1] <= '9'){
                        config_actual.escala_ventana = argv[i][1] - '0';
                    }else{
                        printf("Opcion %s desconocida\n",argv[i]);
                        printf("Modo de uso Ventana.exe <argumentos>\n");
                        printf("Argumentos:\n");
                        printf(" -v Resolucion logica VGA (640x480)\n");
                        printf(" -c Resolucion logica CGA (320x200)\n");
                        printf(" -N Escala de resolucion en N pixeles. Ej -2\n");
                    }
                }
            }
        guardar_configuraciones(ARCHIVO_OP);
    }

    int ANCHO_VENTANA = obtener_ancho_actual();
    int ALTO_VENTANA = obtener_alto_actual();
    ESCALA_V = (ANCHO_VENTANA == 640) ? 2: 1;
    ESCALA_VENTANA = obtener_escala_actual();

    //
    // inicializacion SDL
    //
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window;
    SDL_Renderer* renderer;

    if(!SDL_CreateWindowAndRenderer("NODO TETRIS", ANCHO_VENTANA, ALTO_VENTANA, SDL_WINDOW_OPENGL, &window, &renderer)){
        printf("Error al crear ventana y renderizador SDL\n");
        SDL_Quit();
        return 1;
    }

    //aplicar_paleta();

    //
    // entorno juego
    //
    if(inicializar_contexto(window, renderer) == NULL){
        printf("Error al crear contexto\n");
        return -1;
    }
    if(inicializar_helper_dibujo(ANCHO_VENTANA, ALTO_VENTANA, ESCALA_V) == NULL){
        printf("Error al crear memoria para funciones de pantalla\n");
        return -1;
    }
    srand(time(NULL));

    
    inicializarLeaderboard();
    if(!cargarArchivo()){
        printf("Error al cargar archivo de estadisticas\n");
        return -1;
    }

    
    inicializar_cheats();

    audio_init();
    

    semilla_fondo(time(NULL));
    //bucle principal
    while(contexto->corriendo == true){

        correr();

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    //Funciones de cierre
    guardarArchivo();
    limpiar_contexto();
    limpiar_helper_pantalla();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
