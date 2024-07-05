#include "ListaEnlazada.h"

NodoLista::NodoLista(Transaccion* transaccion) : transaccion(transaccion), siguiente(nullptr) {}

ListaEnlazada::ListaEnlazada() : cabeza(nullptr), cola(nullptr) {}

void ListaEnlazada::insertar(Transaccion* transaccion) {
    NodoLista* nuevoNodo = new NodoLista(transaccion);
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

bool ListaEnlazada::contieneCuenta(const std::string& cuenta) const {
    NodoLista* actual = cabeza;
    while (actual != nullptr) {
        if (actual->transaccion->cuentaOrigen == cuenta || actual->transaccion->cuentaDestino == cuenta) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}
