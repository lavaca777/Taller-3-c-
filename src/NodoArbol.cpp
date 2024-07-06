#include "NodoArbol.h"

NodoArbol::NodoArbol(Transaccion* transaccion) : transaccion(transaccion), izquierda(nullptr), derecha(nullptr), altura(1) {}
