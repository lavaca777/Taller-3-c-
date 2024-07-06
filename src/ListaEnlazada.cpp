#include "ListaEnlazada.h"

ListaEnlazada::ListaEnlazada() : cabeza(nullptr), cola(nullptr) {}

void ListaEnlazada::insertar(Transaccion* transaccion, const string& motivo) {
    NodoLista* nuevoNodo = new NodoLista(transaccion, motivo);
    if (cola == nullptr) {
        cabeza = cola = nuevoNodo;
    } else {
        cola->siguiente = nuevoNodo;
        cola = nuevoNodo;
    }
}

NodoLista* ListaEnlazada::obtenerCabeza() const {
    return cabeza;
}

bool ListaEnlazada::contieneCuenta(const string& cuenta) const {
    NodoLista* actual = cabeza;
    while (actual != nullptr) {
        if (actual->transaccion->cuentaOrigen == cuenta || actual->transaccion->cuentaDestino == cuenta) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}
