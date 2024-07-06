#include <iostream>
#include "ArbolAVL.h"
#include "Util.h"
#include "ListaEnlazada.h"

using namespace std;

void mostrarMenu() {
    cout << "Menu de opciones:" << endl;
    cout << "1. Registrar transaccion" << endl;
    cout << "2. Buscar transaccion por ID" << endl;
    cout << "3. Generar reporte de transacciones sospechosas" << endl;
    cout << "4. Guardar transacciones y sospechosos" << endl;
    cout << "0. Salir" << endl;
}

int main() {
    ArbolAVL arbolAVL;
    ListaEnlazada cuentasSospechosas;
    int opcion;

    arbolAVL = cargarTransacciones("data/transacciones.txt", cuentasSospechosas);
    cargarCuentasSospechosas(cuentasSospechosas, "data/sospechosos.txt");

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int id;
                string cuentaOrigen, cuentaDestino, ubicacion, fecha, hora;
                double monto;
                int nuevoId = arbolAVL.obtenerUltimoId() + 1;

                cout << "Ingrese cuenta origen: ";
                cin >> cuentaOrigen;
                cout << "Ingrese cuenta destino: ";
                cin >> cuentaDestino;
                cout << "Ingrese monto: ";
                cin >> monto;
                cout << "Ingrese ubicacion: ";
                cin >> ubicacion;
                cout << "Ingrese fecha (YYYY-MM-DD): ";
                cin >> fecha;
                cout << "Ingrese hora (HH:MM): ";
                cin >> hora;

                Transaccion* transaccion = new Transaccion(nuevoId, cuentaOrigen, cuentaDestino, monto, ubicacion, fecha, hora);
                arbolAVL.insertar(transaccion, cuentasSospechosas, arbolAVL);
                break;
            }
            case 2: {
                int id;
                cout << "Ingrese ID: ";
                cin >> id;
                Transaccion* transaccion = arbolAVL.buscar(id);
                if (transaccion) {
                    transaccion->mostrarTransaccion();
                } else {
                    cout << "No encontrada." << endl;
                }
                break;
            }
            case 3: {
                cout << "Transacciones sospechosas:" << endl;
                NodoLista* nodo = cuentasSospechosas.obtenerCabeza();
                while (nodo != nullptr) {
                    nodo->transaccion->mostrarTransaccion();
                    cout << "Motivo: " << nodo->motivo << endl;  // Mostrar motivo de sospecha
                    nodo = nodo->siguiente;
                }
                break;
            }
            case 4: {
                guardarTransacciones(arbolAVL, "data/transacciones.txt");
                guardarCuentasSospechosas(cuentasSospechosas, "data/sospechosos.txt");
                break;
            }
            case 0: {
                guardarTransacciones(arbolAVL, "data/transacciones.txt");
                guardarCuentasSospechosas(cuentasSospechosas, "data/sospechosos.txt");
                cout << "Saliendo..." << endl;
                break;
            }
            default: {
                cout << "Opcion no valida." << endl;
                break;
            }
        }
    } while (opcion != 0);

    return 0;
}
