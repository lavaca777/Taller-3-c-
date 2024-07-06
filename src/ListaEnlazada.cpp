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

string obtenerAnioMes(const string& fecha) {
    return fecha.substr(0, 7); // Suponiendo que la fecha tiene el formato "YYYY-MM-DD"
}

bool ListaEnlazada::contieneCuenta(const string& cuenta, const string& fechaTransaccion) const {
    NodoLista* actual = cabeza;
    while (actual != nullptr) {
        Transaccion* t = actual->transaccion;
        if ((t->cuentaOrigen == cuenta || t->cuentaDestino == cuenta) &&
            obtenerAnioMes(t->fecha) == obtenerAnioMes(fechaTransaccion)) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}
