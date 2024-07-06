#pragma once
#include "NodoArbol.h"
#include "Transaccion.h"
#include "ListaEnlazada.h"

class ArbolAVL {
public:
    NodoArbol* raiz;

    ArbolAVL() : raiz(nullptr) {}

    void insertar(Transaccion* transaccion, ListaEnlazada& cuentasSospechosas, ArbolAVL& tansacciones);
    Transaccion* buscar(int id);
    int obtenerUltimoId() const;
    int obtenerUltimoIdEnArbol(NodoArbol* nodo) const;
    bool esTransaccionSospechosa(Transaccion* transaccion, ListaEnlazada& cuentasSospechosas, ArbolAVL& tansacciones, string& motivo);

private:
    NodoArbol* insertarRecursivo(NodoArbol* nodo, Transaccion* transaccion);
    Transaccion* buscarRecursivo(NodoArbol* nodo, int id);
    int obtenerAltura(NodoArbol* nodo);
    int obtenerBalance(NodoArbol* nodo);
    NodoArbol* rotarDerecha(NodoArbol* y);
    NodoArbol* rotarIzquierda(NodoArbol* x);

    bool ubicacionSospechosa(Transaccion* transaccion, ArbolAVL& arbolAVL);
    void contarTransaccionesSospechosas(NodoArbol* nodo, Transaccion* transaccionActual, const string& horaActual, int intervaloMinutos, int& contador); 
    int diferenciaHoras(const string& hora1, const string& hora2);

};
