#include "ArbolAVL.h"

void ArbolAVL::insertar(Transaccion* transaccion, ListaEnlazada& cuentasSospechosas) {
    if (esTransaccionSospechosa(transaccion, cuentasSospechosas)) {
        cout << "Transacción sospechosa. No se puede procesar." << endl;
        cuentasSospechosas.insertar(transaccion);
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

bool ArbolAVL::esTransaccionSospechosa(Transaccion* transaccion, ListaEnlazada& cuentasSospechosas) {
    double montoMaximo = 1000000;
    string ubicacionSospechosa = "ubicacion_sospechosa"; // Ejemplo de ubicación sospechosa

    if (transaccion->monto > montoMaximo) {
        return true;
    }

    if (cuentasSospechosas.contieneCuenta(transaccion->cuentaOrigen) || cuentasSospechosas.contieneCuenta(transaccion->cuentaDestino)) {
        return true;
    }

    return transaccion->ubicacion == ubicacionSospechosa;
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
