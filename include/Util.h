#pragma once
#include <string>
#include "Transaccion.h"
#include "ArbolAVL.h"
using namespace std;

void guardarTransacciones(ArbolAVL& arbol, const string& filename);
ArbolAVL cargarTransacciones(const string& filename, ListaEnlazada& cuentasSospechosas);
void guardarCuentasSospechosas(ListaEnlazada& cuentasSospechosas, const string& filename);
void cargarCuentasSospechosas(ListaEnlazada& cuentasSospechosas, const string& filename);
void mostrarMenu();
