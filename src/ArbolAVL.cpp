#include "ArbolAVL.h"
#include <sstream>
#include <iostream>
#include <cmath> 

void ArbolAVL::insertar(Transaccion* transaccion, ListaEnlazada& cuentasSospechosas, ArbolAVL& tansacciones) {
    string motivo;
    if (esTransaccionSospechosa(transaccion, cuentasSospechosas, tansacciones, motivo)) {
        cout << "Transaccion sospechosa: " << motivo << ". No se puede procesar." << endl;
        cuentasSospechosas.insertar(transaccion, motivo);
    } else {
        raiz = insertarRecursivo(raiz, transaccion);
    }
}

Transaccion* ArbolAVL::buscar(int id) {
    return buscarRecursivo(raiz, id);
}

NodoArbol* ArbolAVL::insertarRecursivo(NodoArbol* nodo, Transaccion* transaccion) {
    if (nodo == nullptr) {
        return new NodoArbol(transaccion);
    }

    if (transaccion->id < nodo->transaccion->id) {
        nodo->izquierda = insertarRecursivo(nodo->izquierda, transaccion);
    } else if (transaccion->id > nodo->transaccion->id) {
        nodo->derecha = insertarRecursivo(nodo->derecha, transaccion);
    } else {
        return nodo; // No se permiten duplicados
    }

    nodo->altura = 1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));
    int balance = obtenerBalance(nodo);

    // Rotaciones para balancear el árbol AVL
    if (balance > 1 && transaccion->id < nodo->izquierda->transaccion->id) {
        return rotarDerecha(nodo);
    }
    if (balance < -1 && transaccion->id > nodo->derecha->transaccion->id) {
        return rotarIzquierda(nodo);
    }
    if (balance > 1 && transaccion->id > nodo->izquierda->transaccion->id) {
        nodo->izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo);
    }
    if (balance < -1 && transaccion->id < nodo->derecha->transaccion->id) {
        nodo->derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

Transaccion* ArbolAVL::buscarRecursivo(NodoArbol* nodo, int id) {
    if (nodo == nullptr || nodo->transaccion->id == id) {
        return nodo ? nodo->transaccion : nullptr;
    }

    if (id < nodo->transaccion->id) {
        return buscarRecursivo(nodo->izquierda, id);
    }

    return buscarRecursivo(nodo->derecha, id);
}

bool ArbolAVL::esTransaccionSospechosa(Transaccion* transaccion, ListaEnlazada& cuentasSospechosas, ArbolAVL& transacciones, string& motivo) {
    double montoMaximo = 1000000;

    if (transaccion->monto > montoMaximo) {
        motivo = "Monto mayor a 1.000.000";
        return true;
    }

    if (cuentasSospechosas.contieneCuenta(transaccion->cuentaOrigen, transaccion->fecha) ||
        cuentasSospechosas.contieneCuenta(transaccion->cuentaDestino, transaccion->fecha)) {
        motivo = "Cuenta previamente sospechosa en el mismo mes y año";
        return true;
    }

    if (ubicacionSospechosa(transaccion, transacciones)) {
        motivo = "Desplazamiento sospechoso";
        return true;
    }

    return false;
}

int ArbolAVL::obtenerUltimoId() const {
    return obtenerUltimoIdEnArbol(raiz);
}

int ArbolAVL::obtenerUltimoIdEnArbol(NodoArbol* nodo) const {
    if (nodo == nullptr) {
        return 0;
    }
    while (nodo->derecha != nullptr) {
        nodo = nodo->derecha;
    }
    return nodo->transaccion->id;
}

bool ArbolAVL::ubicacionSospechosa(Transaccion* transaccion, ArbolAVL& arbolAVL) {
    const int intervaloMinutos = 5;
    const int cantidadMinima = 3;
    string horaActual = transaccion->hora;
    int transaccionesSospechosas = 0;
    contarTransaccionesSospechosas(raiz, transaccion, horaActual, intervaloMinutos, transaccionesSospechosas);

    if (transaccionesSospechosas >= cantidadMinima) {
        return true;
    }

    return false;
}

void ArbolAVL::contarTransaccionesSospechosas(NodoArbol* nodo, Transaccion* transaccionActual, const string& horaActual, int intervaloMinutos, int& contador) {
    if (nodo == nullptr) {
        return;
    }

    contarTransaccionesSospechosas(nodo->izquierda, transaccionActual, horaActual, intervaloMinutos, contador);

    Transaccion* transaccionNodo = nodo->transaccion;

    if (transaccionNodo != transaccionActual &&
        (transaccionNodo->cuentaOrigen == transaccionActual->cuentaOrigen ||
         transaccionNodo->cuentaDestino == transaccionActual->cuentaDestino) &&
        diferenciaHoras(transaccionNodo->hora, horaActual) <= intervaloMinutos &&
        transaccionNodo->ubicacion != transaccionActual->ubicacion) {
        contador++;
    }

    contarTransaccionesSospechosas(nodo->derecha, transaccionActual, horaActual, intervaloMinutos, contador);
}

int ArbolAVL::diferenciaHoras(const string& hora1, const string& hora2) {
    int horas1, minutos1, horas2, minutos2;
    stringstream ss1(hora1);
    char separador = ':';
    if (!(ss1 >> horas1 >> separador >> minutos1)) {
        cerr << "Error al parsear hora1: " << hora1 << endl;
        return -1;
    }

    stringstream ss2(hora2);
    if (!(ss2 >> horas2 >> separador >> minutos2)) {
        cerr << "Error al parsear hora2: " << hora2 << endl;
        return -1;
    }

    int totalMinutos1 = horas1 * 60 + minutos1;
    int totalMinutos2 = horas2 * 60 + minutos2;

    int diferencia = abs(totalMinutos1 - totalMinutos2);

    return diferencia;
}

int ArbolAVL::obtenerAltura(NodoArbol* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->altura;
}

int ArbolAVL::obtenerBalance(NodoArbol* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return obtenerAltura(nodo->izquierda) - obtenerAltura(nodo->derecha);
}

NodoArbol* ArbolAVL::rotarDerecha(NodoArbol* y) {
    NodoArbol* x = y->izquierda;
    NodoArbol* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
    x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;

    return x;
}

NodoArbol* ArbolAVL::rotarIzquierda(NodoArbol* x) {
    NodoArbol* y = x->derecha;
    NodoArbol* T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
    y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;

    return y;
}
