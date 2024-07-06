#pragma once
#include <string>
#include "Transaccion.h"
#include "ArbolAVL.h"
using namespace std;

class Util {
public:
    static void guardarTransacciones(ArbolAVL& arbol, const string& filename);
    static ArbolAVL cargarTransacciones(const string& filename, ListaEnlazada& cuentasSospechosas);
    static void guardarCuentasSospechosas(ListaEnlazada& cuentasSospechosas, const string& filename);
    static void cargarCuentasSospechosas(ListaEnlazada& cuentasSospechosas, const string& filename);
    static void mostrarMenu();
private:
    static void guardarTransaccionesRecursivo(NodoArbol* nodo, ofstream& file);
};
