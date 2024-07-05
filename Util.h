#pragma once
#include <string>
#include "Transaccion.h"
#include "ArbolAVL.h"
using namespace std;

void guardarTransacciones(ArbolAVL& arbol, const string& nombreArchivo);
ArbolAVL cargarTransacciones(const string& nombreArchivo, ListaEnlazada& cuentasSospechosas);
void mostrarMenu();
