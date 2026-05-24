#include "tetris.h"
#include <stdlib.h>
#include "GBT/gbt_entrada.h"
#include "cheats.h"
#include "dibujo.h"
#include "graficos.h"
#include "piezas.h"
#include "puntos.h"
#include "tablero.h"
#include "mEstados.h"
#include "opciones.h"
#include <stdio.h>

int framesTecla = 0;
int framesAbajo = 0;
eGBT_Tecla ultimaTecla;

Tetris* tetris = NULL;

//SRS
typedef struct{
    int dx;
    int dy;
}desplazamiento;

const desplazamiento srs[5] = {{0,0},{-1,0},{-1,-1},{0,2},{-1,2}};

void predecirPieza(Pieza* p);

Tetris* inicializar_tetris(bool modo_dx){

    tetris = malloc(sizeof(Tetris));
    if(!tetris){
        return NULL;
    }

    tetris->ancho_tablero = (modo_dx) ? obtener_ancho_dx() : TABLERO_CLASICO_COLS;

    inicialiar_tablero(&tetris->tablero, tetris->ancho_tablero);

    if(!tetris->tablero.matriz)
    {
        free(tetris);
        return NULL;
    }

    ///Verificar la condicion de null y como eso afecta al tablero
    VectorCrear(&tetris->bolsa,sizeof(int));


    //aca porque si
    cargar_combinaciones_minos();

    tetris->modo_dx = modo_dx;
    rellenar_mezclar_bolsa();

    if(noMezclar())
        tetris->tipo_pieza = 0;
    else
        tetris->tipo_pieza = *((int*)tetris->bolsa.vec + tetris->indice_bolsa );
    tetris->indice_bolsa++;
    int variante = rand() % 4;
    int textura = (variante * 7) + (tetris->tipo_pieza % 7);
    cargar_pieza(&tetris->pieza, tetris->tipo_pieza, textura+1);
    cargar_pieza(&tetris->piezaFutura, tetris->tipo_pieza, textura+1);
    predecirPieza(&tetris->piezaFutura);

    tetris->puntos = 0;
    tetris->contador_frames = 0;
    tetris->velocidad_ms = obtener_velocidad_actual_ms();
    tetris->cant_piezas = 0;
    tetris->umbral_frames = 30 * (tetris->velocidad_ms / 1000);
    tetris->cont_fijacion = 0;
    tetris->contacto = false;
    tetris->cantidad_lineas = 0;

    tetris->pieza_anterior = -1;
    tetris->textura_siguiente = -1;
    tetris->textura_anterior = -1;

    tetris->animacion_borrar = false;
    tetris->frames_animacion = 0;
    tetris->lineas_borradas = 0;
    memset(tetris->filas_marcadas, false, sizeof(tetris->filas_marcadas));


    int tipo_sig = *((int*)tetris->bolsa.vec + tetris->indice_bolsa);
    int variante_sig = rand() % 4;
    tetris->textura_siguiente = (variante_sig * 7) + (tipo_sig % 7) + 1;

    tetris->record_puntos = 0;
    int cant_jugadores = pedirCant(tetris->modo_dx,obtener_dificultad_actual());
    for(int i=0; i < cant_jugadores; i++)
    {
        jugador* j = pedirPos(tetris->modo_dx,obtener_dificultad_actual(),i);
        if(j->puntos > tetris->record_puntos)
        {
            tetris->record_puntos = j->puntos;
        }
    }

    return tetris;
}

void loop_dibujar_tetris()
{
    limpiar(7);
    dibujar_fondo();
    //Aca se dibuja el tablero
    dibujar_rect(pantalla->tab_offsetX, pantalla->tab_offsetY, pantalla->tam_tabX-1, pantalla->tam_tabY-1, 1);
    pantalla->tab_offsetX += sismo();

    bool en_peligro = false;
    for(int y = 0; y < 6; y++) {
        for(int x = 0; x < tetris->tablero.columnas; x++) {
            if(tetris->tablero.matriz[y][x] != 0) {
                en_peligro = true;
            }
        }
    }

    int color_marco;
    bool destello = false;

    if (tetris->animacion_borrar)
    {
        //Destello de línea completada
        destello = (tetris->frames_animacion / 4) % 2 == 0;
        color_marco = destello ? 0 : 1;
    }
    else if (en_peligro)
    {
        // Alerta de pérdida inminente
        int colores_piezas[7] = {9, 18, 27, 15, 12, 21, 24};
        static int frame_peligro = 0;
        frame_peligro++;
        color_marco = ((frame_peligro / 10) % 2 == 0) ? colores_piezas[tetris->tipo_pieza % 7] : 1;
    }
    else
    {
        //Color normal de la pieza que cae
        int colores_piezas[7] = {9, 18, 27, 15, 12, 21, 24};
        color_marco = colores_piezas[tetris->tipo_pieza % 7];
    }
    int grosor = 2;
    dibujar_rect(pantalla->tab_offsetX - grosor,
                 pantalla->tab_offsetY - grosor,
                 pantalla->tam_tabX - 1 + (grosor * 2),
                 pantalla->tam_tabY - 1 + (grosor * 2),
                 color_marco);

    //Dibujar el fondo hueco del tablero
    dibujar_rect(pantalla->tab_offsetX,
                 pantalla->tab_offsetY,
                 pantalla->tam_tabX-1,
                 pantalla->tam_tabY-1,
                 1);
    if(tetris->animacion_borrar)
    {
        if(!invisibilidad_bloques())
            dibujar_tablero(&tetris->tablero, pantalla->tab_offsetX, pantalla->tab_offsetY, tetris->filas_marcadas,destello);
        else
            dibujar_tablero_bizarro(&tetris->tablero, pantalla->tab_offsetX, pantalla->tab_offsetY);
    }
    else
    {
        if(!invisibilidad_bloques())
            dibujar_tablero(&tetris->tablero, pantalla->tab_offsetX, pantalla->tab_offsetY, NULL,false);
        else
            dibujar_tablero_bizarro(&tetris->tablero, pantalla->tab_offsetX, pantalla->tab_offsetY);
        dibujar_pieza(&tetris->pieza, pantalla->tab_offsetX, pantalla->tab_offsetY, tetris->modo_dx, tetris->ancho_tablero, false);
    }

    int ancho_caja = porc_a_pixel(14, pantalla->ancho);
    int alto_caja = porc_a_pixel(12, pantalla->alto);

    int anclaDer_x = pantalla->tab_offsetX + pantalla->tam_tabX + porc_a_pixel(2, pantalla->ancho);
    int posicion_y = pantalla->tab_offsetY;

    // --- 1. CAJA PUNTOS ---
    int ptos_box_x = anclaDer_x + 3;
    int ptos_box_y = posicion_y;
    char points[12];
    sprintf(points,"%d",tetris->puntos);
    dibujar_rect(ptos_box_x - grosor, ptos_box_y - grosor, porc_a_pixel(16, pantalla->ancho) + (grosor*2) +8, porc_a_pixel(11, pantalla->alto)+(grosor*2), color_marco);
    dibujar_rect(ptos_box_x, ptos_box_y, porc_a_pixel(16, pantalla->ancho) + 8, porc_a_pixel(11, pantalla->alto), 1);

    dibujar_texto("Puntos", pixel_a_porc(ptos_box_x, pantalla->ancho) + 1.5f, pixel_a_porc(ptos_box_y, pantalla->alto) + 1.5f, pantalla->escala_v, 0);
    dibujar_texto(points, pixel_a_porc(ptos_box_x, pantalla->ancho) + 1.5f, pixel_a_porc(ptos_box_y, pantalla->alto) + 5.5f, pantalla->escala_v, 0);

    int anclaIzq_x = pantalla->tab_offsetX - porc_a_pixel(18, pantalla->ancho);

    // --- 2. CAJA PREVIEWS ---
    if(!noMezclar()){
        int offsetY_preview = posicion_y + porc_a_pixel(35, pantalla->alto);

        // Anterior
        int ant_box_x = anclaIzq_x - 12;
        int ant_box_y = offsetY_preview - 10;
        dibujar_rect(ant_box_x - grosor - 8, ant_box_y - grosor, ancho_caja + (grosor * 2) + 23, alto_caja + (grosor * 2) + 25, color_marco);
        dibujar_rect(ant_box_x - 8, ant_box_y, ancho_caja + 23, alto_caja + 25, 1);

        dibujar_texto("Anterior", pixel_a_porc(ant_box_x, pantalla->ancho) - 1, pixel_a_porc(ant_box_y, pantalla->alto) + 1.5f, pantalla->escala_v, 0);
        dibujar_previsualizacion_pieza(tetris->pieza_anterior, tetris->textura_anterior, ant_box_x + 15, ant_box_y + 9);

        // Siguiente
        int sig_box_x = anclaDer_x + 3;
        int sig_box_y = offsetY_preview - 10;
        dibujar_rect(sig_box_x - grosor, sig_box_y - grosor, ancho_caja + (grosor * 2) + 23, alto_caja + (grosor * 2) + 25, color_marco);
        dibujar_rect(sig_box_x, sig_box_y, ancho_caja + 23, alto_caja + 25, 1);

        dibujar_texto("Siguiente", pixel_a_porc(sig_box_x, pantalla->ancho) + 1.0f, pixel_a_porc(sig_box_y, pantalla->alto) + 1.5f, pantalla->escala_v, 0);
        int siguiente = obtener_tipo_siguiente_pieza();
        dibujar_previsualizacion_pieza(siguiente, tetris->textura_siguiente, sig_box_x + 15, sig_box_y + 9);
    }

    // --- 3. CAJA VELOCIDAD ---
    int vel_box_x = anclaDer_x + 3;
    int vel_box_y = posicion_y + porc_a_pixel(65, pantalla->alto);
    dibujar_rect(vel_box_x - grosor, vel_box_y - grosor, porc_a_pixel(19, pantalla->ancho)+(grosor*2), porc_a_pixel(12, pantalla->alto)+(grosor*2), color_marco);
    dibujar_rect(vel_box_x, vel_box_y, porc_a_pixel(19, pantalla->ancho), porc_a_pixel(12, pantalla->alto), 1);

    dibujar_texto("Velocidad", pixel_a_porc(vel_box_x, pantalla->ancho) + 1.5f, pixel_a_porc(vel_box_y, pantalla->alto) + 1.5f, pantalla->escala_v, 0);
    char velocidad[10];
    sprintf(velocidad,"%2.0f ms",tetris->velocidad_ms);
    dibujar_texto(velocidad, pixel_a_porc(vel_box_x, pantalla->ancho) + 1.5f, pixel_a_porc(vel_box_y, pantalla->alto) + 5.5f, pantalla->escala_v, 0);

    // --- 4. CAJA LINEAS ---
    int lin_box_x = anclaIzq_x - 13;
    int lin_box_y = posicion_y + porc_a_pixel(65, pantalla->alto);
    dibujar_rect(lin_box_x - grosor, lin_box_y - grosor, porc_a_pixel(19, pantalla->ancho)+(grosor*2), porc_a_pixel(12, pantalla->alto)+(grosor*2), color_marco);
    dibujar_rect(lin_box_x, lin_box_y, porc_a_pixel(19, pantalla->ancho), porc_a_pixel(12, pantalla->alto), 1);

    dibujar_texto("Lineas", pixel_a_porc(lin_box_x, pantalla->ancho) + 1.5f, pixel_a_porc(lin_box_y, pantalla->alto) + 1.5f, pantalla->escala_v, 0);
    char lineas[10];
    sprintf(lineas,"%d",tetris->cantidad_lineas);
    dibujar_texto(lineas, pixel_a_porc(lin_box_x, pantalla->ancho) + 1.5f, pixel_a_porc(lin_box_y, pantalla->alto) + 5.5f, pantalla->escala_v, 0);

    // --- 5. CAJA RECORD ---
    int rec_box_x = anclaIzq_x - 3;
    int rec_box_y = posicion_y;
    dibujar_rect(rec_box_x - grosor - 8, rec_box_y - grosor, porc_a_pixel(16, pantalla->ancho) + (grosor * 2) + 8, porc_a_pixel(11, pantalla->alto) + (grosor * 2), color_marco);
    dibujar_rect(rec_box_x - 8, rec_box_y, porc_a_pixel(16, pantalla->ancho) + 8, porc_a_pixel(11, pantalla->alto), 1);

    dibujar_texto("Record", pixel_a_porc(rec_box_x, pantalla->ancho) -1, pixel_a_porc(rec_box_y, pantalla->alto) + 1.5f, pantalla->escala_v, 0);
    uint32_t record_a_mostrar = (tetris->puntos > tetris->record_puntos) ? tetris->puntos : tetris->record_puntos;
    char record_str[12];
    sprintf(record_str, "%u", record_a_mostrar);
    dibujar_texto(record_str, pixel_a_porc(rec_box_x, pantalla->ancho) -1, pixel_a_porc(rec_box_y, pantalla->alto) + 5.5f, pantalla->escala_v, 0);

    //////////////////////////////////////////////////////////////
    //Velocidad de caida y Cheat
    dibujar_pieza(&tetris->piezaFutura, pantalla->tab_offsetX, pantalla->tab_offsetY, tetris->modo_dx, tetris->ancho_tablero, true);

    if(alrevez())
        invertir_pantalla();
}

void loop_logica_tetris()
{
    if(tetris->animacion_borrar)
    {
        tetris->frames_animacion++;
        if(tetris->frames_animacion > 30)
        {
            limpiar_filas(&tetris->tablero);
            calculo_puntos(tetris->lineas_borradas);
            actualizar_datos_tetris();
            obtener_nueva_pieza();
            tetris->cantidad_lineas += tetris->lineas_borradas;
            tetris->animacion_borrar = false;
            tetris->lineas_borradas = 0;
            memset(tetris->filas_marcadas, false, sizeof(tetris->filas_marcadas));
        }
    }
    else
    {
        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();
        //////////
        //Caso de HARD DROP anclamos la pieza en la pposiccion de prediccion (Hace que la pieza se dispare de una al tablero?)
        if(tecla == GBTK_ESPACIO){
            tetris->pieza = tetris->piezaFutura;
            anclar_pieza(&tetris->tablero, &tetris->pieza, tetris->modo_dx);
            procesar_impacto();
        }


        /*if(tecla == GBTK_ESCAPE)
        {
            //printf("Volver a pantalla inicial\n");    Ahora vuelve al menu
            cambiar_contexto(PANTALLA_MENU);
            return;
            }*/
        if(tecla == GBTK_p || tecla == GBTK_ESCAPE)
        {
            //printf("Tecla P apretada\n");
            cambiar_contexto(PANTALLA_PAUSA);
            return;
        }

        if(tecla == GBTK_x)
        {
            rotar_pieza_activa(SENTIDO_HORARIO);
        }
        if(tecla == GBTK_z)
        {
            rotar_pieza_activa(SENTIDO_ANTIHORARIO);
        }
        if(tecla == GBTK_TAB)
        {
            tetris->puntos += 1000;
        }

        mover_pieza(tecla);

        bool pieza_anclada = procesar_caida();

        if(pieza_anclada)
        {
            procesar_impacto();
        }

        if(!tetris->animacion_borrar)
        {
            if(perder())
            {
                jugador actual =
                {
                    .puntos = tetris->puntos
                };
                sprintf(actual.nombre, "%s", contexto->nombreActual);
                cargarLB(tetris->modo_dx, obtener_dificultad_actual(), &actual);
                contexto->modo_tetris = tetris->modo_dx;
                cambiar_contexto(PANTALLA_PERDER);
                return;
            }

        }
    }
}
void limpiar_tetris()
{
    if(!tetris)
        return;
    VectorDestruir(&tetris->bolsa);
    destruir_tablero(&tetris->tablero,TABLERO_FILAS);
    free(tetris);
    tetris = NULL;
}


void rotar_pieza_activa(uint8_t sentido)
{
    //Pieza aux que va estar rotada
    Pieza pieza_rotar = tetris->pieza;

    if(sentido == SENTIDO_HORARIO)
    {
        sentido_horario(pieza_rotar.matriz, tetris->pieza.matriz); //Esta funcion vive en pieza.h
    }
    else
    {
        sentido_antihorario(pieza_rotar.matriz, tetris->pieza.matriz); //Esta funcion vive en pieza.h
    }

    //Implementacion SRS
    bool rotacion_exitosa = false;
    int nueva_x = pieza_rotar.x;
    int nueva_y = pieza_rotar.y;
    for(int i = 0; i < 5; i++){
        int offset_x = (sentido == SENTIDO_HORARIO)? srs[i].dx : -srs[i].dx;
        int offset_y = srs[i].dy;
        int test_x = pieza_rotar.x + offset_x;
        int test_y = pieza_rotar.y + offset_y;
        if(!colision(&tetris->tablero, &pieza_rotar, test_x, test_y, tetris->modo_dx)){
            nueva_x = test_x;
            nueva_y = test_y;
            rotacion_exitosa = true;
            break;
        }
    }
    //si la pieza aux rotada no choca con nada entonces se la copiamos a nuestra pieza tetris

    if(rotacion_exitosa)
    {
        tetris->pieza.x = nueva_x;
        tetris->pieza.y = nueva_y;
        if(tetris->contacto) //Verificamos si hay o no contacto para saber si tenemos que resetear el cont_fijacion
        {
            tetris->cont_fijacion = 0;
        }
        for(int y = 0; y < ORDEN_PIEZA; y++)
        {
            for(int x = 0; x < ORDEN_PIEZA; x++)
            {
                tetris->pieza.matriz[y][x] = pieza_rotar.matriz[y][x];
            }
        }
    }

    predecirPieza(&tetris->piezaFutura);

}

void mover_pieza(eGBT_Tecla tecla)
{
    int x = 0;
    int y = 0;

    if(gbt_tecla_sostenida(GBTK_DERECHA))
    {
        if(ultimaTecla != GBTK_DERECHA){
            ultimaTecla = GBTK_DERECHA;
            framesTecla = 0;
        }
        if(framesTecla == 0)
            x=1;
        framesTecla++;
        if(framesTecla>9)
            framesTecla=0;
    }else if(gbt_tecla_sostenida(GBTK_IZQUIERDA))
    {
        if(ultimaTecla != GBTK_IZQUIERDA){
            ultimaTecla = GBTK_IZQUIERDA;
            framesTecla = 0;
        }
        if(framesTecla == 0)
            x=-1;
        framesTecla++;
        if(framesTecla>9)
            framesTecla=0;
    }else
        framesTecla = 0;

    if(gbt_tecla_sostenida(GBTK_ABAJO))
    {
        if(framesAbajo==0)
            y=1;
        framesAbajo++;
        if(framesAbajo>9)
            framesAbajo=0;
    }

    if(x != 0 || y != 0)
    {
        //En caso que no haya colision, le actualizamos las posiciones a nuestra pieza
        if(!colision(&tetris->tablero, &tetris->pieza, tetris->pieza.x +x, tetris->pieza.y + y,tetris->modo_dx))
        {
            tetris->pieza.x += x;
            tetris->pieza.y += y;
             //Este if verifica si bajamos la pieza manualmente o cae por si sola
            if(y == 1)
            {
                tetris->puntos += 1;
            }

            if(tetris->contacto)
            {
                tetris->cont_fijacion = 0;
            }
        }
    }

    predecirPieza(&tetris->piezaFutura);
}
// Fucion que quizas se puede limpiar un poquito mas
bool procesar_caida()
{
    //Bandera para saber si la pieza se anclo al tablero o si sigue cayendo
    bool pieza_anclada = false;

    //Si no hay colicion, entonces estamos en el caso de que la pieza esta haciendo caida libre
    if(!colision(&tetris->tablero, &tetris->pieza, tetris->pieza.x , tetris->pieza.y +1,tetris->modo_dx))
    {
        tetris->contacto = false;
        tetris->contador_frames++;

        //Actualizamos sus frames
        if(tetris->contador_frames >= (int32_t)tetris->umbral_frames)
        {
            tetris->pieza.y++;
            if(lento())
                tetris->contador_frames = -5000;
            else if(rapido())
                tetris->contador_frames = 9999;
            else
                tetris->contador_frames = 0;
        }
    }
    //Caso que la pieza choco con el fondo del tablero o una pieza ya colocada
    else
    {
        tetris->contacto = true;
        tetris->cont_fijacion ++;

        if(tetris->cont_fijacion >= (uint32_t)tetris->umbral_frames * 0.5)
        {
            anclar_pieza(&tetris->tablero, &tetris->pieza, tetris->modo_dx);
            pieza_anclada = true;
        }
    }
    predecirPieza(&tetris->piezaFutura);
    return pieza_anclada;
}

void calculo_puntos(int lineas_borradas)
{
    uint32_t puntos = 0;
    float multiplicador;

    if(lineas_borradas > 0)
    {
        switch(lineas_borradas)
        {
            case 1: puntos = 100; break;
            case 2: puntos = 300; break;
            case 3: puntos = 500; break;
            default: puntos =800; break;
        }
        multiplicador = 1000/tetris->velocidad_ms;
        tetris->puntos += (uint32_t)(puntos * multiplicador);
    }
}

void obtener_nueva_pieza()
{
    //Solo dios sabe como funciona, pero funciona
    tetris->pieza_anterior = tetris->tipo_pieza;
    tetris->textura_anterior = tetris->pieza.color;

    tetris->tipo_pieza = *((int*)tetris->bolsa.vec + tetris->indice_bolsa);
    tetris->indice_bolsa++;

    if(noMezclar()){
        tetris->tipo_pieza = 0;
    }
    cargar_pieza(&tetris->pieza, tetris->tipo_pieza, tetris->textura_siguiente);
    cargar_pieza(&tetris->piezaFutura, tetris->tipo_pieza, tetris->textura_siguiente);

    if(tetris->indice_bolsa >= tetris->bolsa.ce)
    {
        VectorVaciar(&tetris->bolsa);
        rellenar_mezclar_bolsa();
    }
    int variante_sig = rand() % 4;
    int tipo_sig = *((int*)tetris->bolsa.vec + tetris->indice_bolsa);

    tetris->textura_siguiente = (variante_sig * 7) + (tipo_sig % 7) +1;

}

void actualizar_datos_tetris()
{
    tetris->cant_piezas++;

    if(tetris->cant_piezas % 10 == 0)
    {
        tetris->velocidad_ms *= 0.97;
        tetris->umbral_frames *= 0.97;
    }

    tetris->contador_frames = 0;
    tetris->cont_fijacion = 0;
    tetris->contacto = false;

}

bool perder()
{
    if(colision(&tetris->tablero,&tetris->pieza,tetris->pieza.x,tetris->pieza.y,tetris->modo_dx))
    {
        printf("Perdiste\n");
        return true;
    }
    return false;
}

void procesar_impacto()
{
    if(hay_lineas_llenas(&tetris->tablero, tetris->filas_marcadas,&tetris->lineas_borradas))
    {
        tetris->animacion_borrar = true;
        tetris->frames_animacion = 0;
    }
    else
    {
        actualizar_datos_tetris();
        obtener_nueva_pieza();
    }
}


bool guardar_partida(const char* nombre_archivo)
{
    if(!tetris)
    {
        printf("Error: no tetris para guardar\n");
        return false;
    }
    FILE* pf = fopen(nombre_archivo,"wb");

    if(!pf)
    {
        printf("Error al crear el archivo\n");
        return false;
    }

    PartidaGuardada save;

    save.ancho_tablero = tetris->ancho_tablero;

    for(int y = 0; y < TABLERO_FILAS; y++)
    {
        for(int x = 0; x < tetris->ancho_tablero; x++)
        {
            save.matriz_tablero[y][x] = tetris->tablero.matriz[y][x];
        }
    }

    save.Pieza = tetris->pieza;
    save.cant_piezas = tetris->cant_piezas;
    save.tipo_pieza = tetris->tipo_pieza;
    save.puntos = tetris->puntos;
    save.velocidad_ms = tetris->velocidad_ms;
    save.modo_dx = tetris->modo_dx;
    save.cantidad_lineas = tetris->cantidad_lineas;

    fwrite(&save,sizeof(PartidaGuardada),1,pf);
    fclose(pf);

    printf("Partida guardada\n");
    return true;

}

bool cargar_partida(const char* nombre_archivo)
{
    FILE* pf = fopen(nombre_archivo,"rb");

    if(!pf)
    {
        printf("No existe el archivo\n");
        return false;
    }

    PartidaGuardada save;
    fread(&save,sizeof(PartidaGuardada),1,pf);
    fclose(pf);

    destruir_tablero(&tetris->tablero, TABLERO_FILAS);

    inicialiar_tablero(&tetris->tablero, save.ancho_tablero);
    tetris->ancho_tablero = save.ancho_tablero;

    for(int y = 0; y < TABLERO_FILAS; y++)
    {
        for(int x = 0; x < tetris->tablero.columnas; x++)
        {
            tetris->tablero.matriz[y][x] = save.matriz_tablero[y][x];
        }
    }

    tetris->pieza = save.Pieza;
    tetris->tipo_pieza = save.tipo_pieza;
    tetris->puntos = save.puntos;
    tetris->cant_piezas = save.cant_piezas;
    tetris->velocidad_ms = save.velocidad_ms;
    tetris->modo_dx = save.modo_dx;
    tetris->contador_frames = 0;
    tetris->cont_fijacion = 0;
    tetris->contacto = false;
    tetris->cantidad_lineas = save.cantidad_lineas;

    tetris->umbral_frames = 30 * (tetris->velocidad_ms / 1000);

    printf("Partida restaurada\n");
    return true;
}


void rellenar_mezclar_bolsa()
{
    int cant_piezas = tetris->modo_dx ? 11 : 7;

    for(int i = 0; i < cant_piezas; i++)
    {
        VectorCargarAlFinal(&tetris->bolsa,&i);
    }

    VectorMezclarDatos(&tetris->bolsa);

    tetris->indice_bolsa = 0;
}

int obtener_tipo_siguiente_pieza()
{
    if(tetris->indice_bolsa >= tetris->bolsa.ce)
    {
        return -1;
    }

    return *((int*)tetris->bolsa.vec + tetris->indice_bolsa);
}

void dibujar_previsualizacion_pieza(int tipo, int textura ,int posX, int posY)
{
    if(tipo == -1) return;

    Pieza temp_pieza;

    cargar_pieza(&temp_pieza,tipo,textura);


    for(int y = 0; y < ORDEN_PIEZA; y++)
    {
        for(int x = 0; x < ORDEN_PIEZA; x++)
        {
            if(temp_pieza.matriz[y][x] != 0)
            {
                int px = posX + (x * pantalla->mino_tamanio);
                int py = posY + (y * pantalla->mino_tamanio);

                dibujar_mino_pantalla(px,py,temp_pieza.color);
            }
        }
    }
}

void predecirPieza(Pieza* p)
{
    p->y = tetris->pieza.y;
    p->x = tetris->pieza.x;
    memcpy(p->matriz, tetris->pieza.matriz, sizeof(tetris->pieza.matriz));
    //printf("Posy:%d",p->y);
    while(!colision(&tetris->tablero, p, p->x, p->y+1, tetris->modo_dx) && p->y < TABLERO_FILAS-2){
        p->y += 1;
        //printf("posy:%d\n",p->y);
    }
    return;
}
