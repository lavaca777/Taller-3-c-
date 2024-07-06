#pragma once
#include "Transaccion.h"

class NodoArbol {
public:
    Transaccion* transaccion;
    NodoArbol* izquierda;
    NodoArbol* derecha;
    int altura;

    NodoArbol(Transaccion* transaccion);
};
