#pragma once
#include "NodoArbol.h"
#include "Transaccion.h"
#include "ListaEnlazada.h"

class ArbolAVL {
public:
    NodoArbol* raiz;

    ArbolAVL() : raiz(nullptr) {}

    void insertar(Transaccion* transaccion, ListaEnlazada& cuentasSospechosas);
    Transaccion* buscar(int id);

    bool esTransaccionSospechosa(Transaccion* transaccion, ListaEnlazada& cuentasSospechosas);

private:
    NodoArbol* insertarRecursivo(NodoArbol* nodo, Transaccion* transaccion);
    Transaccion* buscarRecursivo(NodoArbol* nodo, int id);
    int obtenerAltura(NodoArbol* nodo);
    int obtenerBalance(NodoArbol* nodo);
    NodoArbol* rotarDerecha(NodoArbol* y);
    NodoArbol* rotarIzquierda(NodoArbol* x);
};
