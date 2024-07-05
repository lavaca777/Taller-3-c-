#pragma once
#include "Transaccion.h"

class NodoLista {
public:
    Transaccion* transaccion;
    NodoLista* siguiente;

    NodoLista(Transaccion* transaccion);
};

class ListaEnlazada {
private:
    NodoLista* cabeza;
    NodoLista* cola;

public:
    ListaEnlazada();

    void insertar(Transaccion* transaccion);
    NodoLista* obtenerCabeza() const;
    bool contieneCuenta(const std::string& cuenta) const;
};
