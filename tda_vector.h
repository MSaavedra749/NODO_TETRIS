#ifndef TDA_VECTOR_H_INCLUDED
#define TDA_VECTOR_H_INCLUDED

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define CAP_INI 7
#define FACT_INCREMENTO 1.5

#define TODO_OK 0
#define SIN_MEMORIA 1




typedef struct
{
    void* vec;
    size_t ce;
    size_t cap;
    size_t tamElem;
}Vector;


///Agregar los punteros a funcion necesario para los algoritmos
//Comparaciones


bool VectorCrear(Vector* v, size_t tamElem);

int VectorCargarAlFinal(Vector* v, const void* dato);

void VectorMezclarDatos(Vector* v);

void VectorVaciar(Vector* v);

void VectorDestruir(Vector* v);

void* VectorObtenerPos(Vector* v, int pos);

void VectorEliminarUltimo(Vector* v);

void VectorOrdenarOffset(Vector* v, size_t posIni);

#endif // TDA_VECTOR_H_INCLUDED
