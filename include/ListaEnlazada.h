#pragma once
#include "Transaccion.h"

// Declaración anticipada de NodoLista
class NodoLista;

class ListaEnlazada {
public:
    ListaEnlazada();
    void insertar(Transaccion* transaccion, const string& motivo);
    NodoLista* obtenerCabeza() const;
    bool contieneCuenta(const string& cuenta) const;

private:
    NodoLista* cabeza;
    NodoLista* cola;
};

class NodoLista {
public:
    Transaccion* transaccion;
    NodoLista* siguiente;
    string motivo;

    NodoLista(Transaccion* transaccion, const string& motivo = "")
        : transaccion(transaccion), siguiente(nullptr), motivo(motivo) {}
};
