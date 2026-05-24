#include "puntos.h"
#include <stdio.h>
#include <stdbool.h>
#include "tda_vector.h"
#include <stddef.h>

tabla normal[3];
tabla deluxe[3];

void inicializarLeaderboard()
{
    for(int i = 0; i < 3; i++)
    {
        VectorCrear(&normal[i].lista, sizeof(jugador));
        VectorCrear(&deluxe[i].lista, sizeof(jugador));
    }
}

bool cargarArchivo()
{
    //Verificar si archivo existe
    FILE* fp;
    fp = fopen("puntos.dat","rb");
    if(fp == NULL){
        //El archivo no existe. crear vacio
        printf("El archivo de estadisticas no existe...\nCreando puntos.dat\n");
        fp = fopen("puntos.dat", "wb+");
        if(fp == NULL){
            printf("El archivo de estadisticas no se puede crear...\n");
            return false;
        }

        //Crear tabla generica
        for(int i = 0; i < 3; i++){
            normal[i].cant = 2;
            deluxe[i].cant = 2;
            jugador temp= {
                .nombre = "alexei",
                .puntos = 5000
            };
            VectorCargarAlFinal(&normal[i].lista, &temp);
            VectorCargarAlFinal(&deluxe[i].lista, &temp);
            jugador temp2 = {
                .nombre = "pajitnov",
                .puntos = 3000
            };
            VectorCargarAlFinal(&normal[i].lista, &temp2);
            VectorCargarAlFinal(&deluxe[i].lista, &temp2);
        }

        //Serializar y guardar datos
        for(int i=0; i < 3; i++){
            //loop normal
            fwrite(&normal[i].cant, sizeof(int), 1, fp);
            for(int n = 0; n < normal[i].cant; n++){
                jugador* dato = VectorObtenerPos(&normal[i].lista, n);
                if(dato != NULL){
                    int cant = fwrite(dato, sizeof(jugador), 1, fp);
                    if(cant == 0){
                        printf("Error al escribir dato\n");
                        fclose(fp);
                        return false;
                    }
                }
            }
            fwrite(&deluxe[i].cant, sizeof(int), 1, fp);
            for(int d = 0; d < deluxe[i].cant; d++){
                jugador* dato = VectorObtenerPos(&deluxe[i].lista, d);
                if(dato!=NULL){
                    int cant = fwrite(dato, sizeof(jugador), 1, fp);
                    if(cant == 0){
                        printf("Error al escribir dato\n");
                        fclose(fp);
                        return false;
                    }
                }
            }
        }
        //se guardo un archivo de ejemplo
        fclose(fp);
        return true;
    }
    printf("Cargado puntos.dat\n");
    //si el archivo existe cargar datos existentes

    for(int i = 0; i < 3; i++){
        // CICLO MODO NORMAL
        int cant;
        fread(&cant, sizeof(int), 1, fp);
        if(cant <= 0){
            printf("Error al leer entrada del archivo\n");
            fclose(fp);
            return false;
        }
        normal[i].cant = cant;
        for(int n = 0; n < cant;n++){
            jugador dato;
            int c = fread(&dato, sizeof(jugador), 1,fp);
            if(c != 1){
                printf("Error al leer entrada del archivo\n");
                fclose(fp);
                return false;
            }
            VectorCargarAlFinal(&normal[i].lista, &dato);
        }
        // CICLO MODO DELUXE
        fread(&cant, sizeof(int), 1, fp);
        if(cant <= 0){
            printf("Error al leer entrada del archivo\n");
            fclose(fp);
            return false;
        }
        deluxe[i].cant = cant;
        for(int n = 0; n < cant;n++){
            jugador dato;
            int c = fread(&dato, sizeof(jugador), 1,fp);
            if(c != 1){
                printf("Error al leer entrada del archivo\n");
                fclose(fp);
                return false;
            }
            VectorCargarAlFinal(&deluxe[i].lista, &dato);
        }
    }

    fclose(fp);
    return true;
}

void guardarArchivo()
{
    //Intentar abrir archivo
    FILE* fp;
    fp = fopen("puntos.dat", "wb");
    if(fp == NULL){
        printf("Error al abrir archivo de estadisticas\nContinuando sin guardar...\n");
        return;
    }

    //El archivo existe. guardar entradas
    int i, cant;
    for(i = 0; i < 3; i++){
        //CICLO NORMAL
        cant = normal[i].cant;
        fwrite(&cant, sizeof(int), 1, fp);
        for(int n = 0; n < cant; n++){
            jugador* dato = VectorObtenerPos(&normal[i].lista, n);
            if(dato == NULL){
                printf("Error al solicitar dato de vector. carga truncada\n");
                return;
            }
            fwrite(dato, sizeof(jugador), 1, fp);
        }
        //CICLO DELUXE
        cant = deluxe[i].cant;
        fwrite(&cant, sizeof(int), 1, fp);
        for(int n = 0; n < cant; n++){
            jugador* dato = VectorObtenerPos(&deluxe[i].lista, n);
            if(dato == NULL){
                printf("Error al solicitar dato de vector. carga truncada\n");
                return;
            }
            fwrite(dato, sizeof(jugador), 1, fp);
        }

    }
    //Cerrar archivo y volver
    fclose(fp);
    return;
}

void cargarLB(bool dx, int dif, jugador* ent)
{
    if(dx){
        deluxe[dif].cant ++;
        VectorCargarAlFinal(&deluxe[dif].lista, ent);
        VectorOrdenarOffset(&deluxe[dif].lista, offsetof(jugador, puntos));
    }else{
        normal[dif].cant ++;
        VectorCargarAlFinal(&normal[dif].lista, ent);
        VectorOrdenarOffset(&normal[dif].lista, offsetof(jugador, puntos));
    }
    return;
}

void limpiarLB(bool dx, int dif)
{
    if(dx){
        if(deluxe[dif].cant > 10){
            deluxe[dif].cant = 10;
            VectorEliminarUltimo(&deluxe[dif].lista);
        }
    }else {
        if(normal[dif].cant > 10){
            normal[dif].cant = 10;
            VectorEliminarUltimo(&normal[dif].lista);
        }
    }
    return;
}

int pedirCant(bool dx, int dif)
{
    if(dx)
        return deluxe[dif].cant;
    else
        return normal[dif].cant;
}

jugador* pedirPos(bool dx, int dif, int n)
{
    if(dx){
        return VectorObtenerPos(&deluxe[dif].lista, n);
    }
    else {
        return VectorObtenerPos(&normal[dif].lista, n);
    }
}
