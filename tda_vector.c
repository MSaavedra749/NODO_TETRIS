#include "tda_vector.h"
#include <string.h>

static bool AumentarCapacidad(Vector*);
static void Intercambiar(void*, void*,size_t);

bool VectorCrear(Vector* v, size_t tamElemt)
{

    v->ce = 0;
    v->cap = 0;
    v->tamElem = 0;
    v->vec = malloc(CAP_INI * tamElemt);

    if(!v->vec)
    {
        return false;
    }

    v->cap = CAP_INI;
    v->tamElem = tamElemt;

    return true;

}

bool AumentarCapacidad(Vector* v)
{
    size_t nueva_cap = FACT_INCREMENTO * v->cap;

    void* v_aux = realloc(v->vec, nueva_cap * v->tamElem);

    if(!v_aux)
    {
        return false;
    }

    v->vec = v_aux;
    v->cap = nueva_cap;

    return true;
}

int VectorCargarAlFinal(Vector* v, const void* dato)
{
    if(v->ce == v->cap)
    {
        if(!AumentarCapacidad(v))
        {
            return SIN_MEMORIA;
        }
    }

    memcpy(v->vec + v->ce * v->tamElem, dato, v->tamElem);

    v->ce++;

    return TODO_OK;
}

void Intercambiar(void* a, void* b, size_t tam)
{
    void* datoTemp = malloc(tam);

    memcpy(datoTemp,a,tam);
    memcpy(a,b,tam);
    memcpy(b,datoTemp,tam);

    free(datoTemp);
}

void VectorMezclarDatos(Vector* v)
{
    void* pini = v->vec;
    void* pact = v->vec + (v->ce - 1) * v->tamElem;
    void* pdesp;
    int desp_elementos;
    size_t tam_element = v->tamElem;

    while(pini < pact)
    {
        desp_elementos = rand()%(((pact - pini)/tam_element) +1);
        pdesp = pini + (desp_elementos * tam_element);

        Intercambiar(pdesp, pact,tam_element);
        pact -= tam_element;
    }
}
///No hacer realloc por el momento, sino se traba el juego por algunos segundos
void VectorVaciar(Vector* v)
{
    v->ce = 0;
}

void VectorDestruir(Vector* v)
{
    free(v->vec);
    v->ce = 0;
    v->cap = 0;
    v->tamElem = 0;
    v->vec = NULL;
}

void* VectorObtenerPos(Vector* v, int pos)
{
    void* dato;
    if(pos > (int)v->ce){
        printf("Error. Intentar acceder a posicion ilegal de vector\n");
        return NULL;
    }
    dato = v->vec + (v->tamElem * pos);
    return dato;
}

void VectorEliminarUltimo(Vector* v)
{
    v->ce -= 1; //asi nomas
    return;
}

void VectorOrdenarOffset(Vector* v, size_t posIni)
{
    char* pIni = (char*)v->vec + posIni;

    for(int i = 0; i < (int)v->ce; i++){
        for(char* j = pIni; j < pIni + ((v->ce-1-i)* v->tamElem); j+=v->tamElem){
            int* a = (int*)j;
            int* b = (int*)(j+v->tamElem);
            if(*a < *b){
                Intercambiar(j-posIni, j+v->tamElem-posIni, v->tamElem);
            }
        }
    }
    return;
}
