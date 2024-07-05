#pragma once
#include <iostream>
#include <string>
using namespace std;

class Transaccion {
public:
    int id;
    string cuentaOrigen;
    string cuentaDestino;
    double monto;
    string ubicacion;
    string fecha;
    string hora;

    Transaccion(int id, string cuentaOrigen, string cuentaDestino, double monto, string ubicacion, string fecha, string hora);

    void mostrarTransaccion();
};
