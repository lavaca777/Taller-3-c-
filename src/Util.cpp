#include "Util.h"
#include <fstream>
#include <sstream>

void guardarTransaccionesRecursivo(NodoArbol* nodo, ofstream& file) {
    if (nodo == nullptr) {
        return;
    }
    guardarTransaccionesRecursivo(nodo->izquierda, file);
    Transaccion* t = nodo->transaccion;
    file << t->id << "," << t->cuentaOrigen << "," << t->cuentaDestino << "," << t->monto << "," 
         << t->ubicacion << "," << t->fecha << "," << t->hora << endl;
    guardarTransaccionesRecursivo(nodo->derecha, file);
}

void guardarTransacciones(ArbolAVL& arbol, const string& filename) {
    ofstream file(filename, ios::out);  // Open in write mode
    guardarTransaccionesRecursivo(arbol.raiz, file);
    file.close();
}

ArbolAVL cargarTransacciones(const string& filename, ListaEnlazada& cuentasSospechosas) {
    ifstream file(filename);
    ArbolAVL arbol;
    string linea;

    while (getline(file, linea)) {
        stringstream ss(linea);
        string idStr, cuentaOrigen, cuentaDestino, montoStr, ubicacion, fecha, hora;
        getline(ss, idStr, ',');
        getline(ss, cuentaOrigen, ',');
        getline(ss, cuentaDestino, ',');
        getline(ss, montoStr, ',');
        getline(ss, ubicacion, ',');
        getline(ss, fecha, ',');
        getline(ss, hora, ',');

        int id = stoi(idStr);
        double monto = stod(montoStr);

        Transaccion* transaccion = new Transaccion(id, cuentaOrigen, cuentaDestino, monto, ubicacion, fecha, hora);
        arbol.insertar(transaccion, cuentasSospechosas, arbol);
    }

    file.close();
    return arbol;
}

void guardarCuentasSospechosas(ListaEnlazada& cuentasSospechosas, const string& filename) {
    ofstream file(filename, ios::app);
    NodoLista* actual = cuentasSospechosas.obtenerCabeza();

    while (actual != nullptr) {
        Transaccion* t = actual->transaccion;
        file << t->id << "," << t->cuentaOrigen << "," << t->cuentaDestino << "," << t->monto << ","
             << t->ubicacion << "," << t->fecha << "," << t->hora << "," << actual->motivo << endl;
        actual = actual->siguiente;
    }

    file.close();
}

void cargarCuentasSospechosas(ListaEnlazada& cuentasSospechosas, const string& filename) {
    ifstream file(filename);
    string linea;

    while (getline(file, linea)) {
        stringstream ss(linea);
        string idStr, cuentaOrigen, cuentaDestino, montoStr, ubicacion, fecha, hora, motivo;
        getline(ss, idStr, ',');
        getline(ss, cuentaOrigen, ',');
        getline(ss, cuentaDestino, ',');
        getline(ss, montoStr, ',');
        getline(ss, ubicacion, ',');
        getline(ss, fecha, ',');
        getline(ss, hora, ',');
        getline(ss, motivo, ',');

        int id = stoi(idStr);
        double monto = stod(montoStr);

        Transaccion* transaccion = new Transaccion(id, cuentaOrigen, cuentaDestino, monto, ubicacion, fecha, hora);
        cuentasSospechosas.insertar(transaccion, motivo);
    }

    file.close();
}

/*
criterios para transferencia sospechosa

si una misma cuenta hace transferencias en poco tiempo en ubicaciones diferentes
ej: juan t-> pedro  U: u1 H:12:15
    juan t-> javier U: u3 H:12:20
    sospechozo

si una cuenta hace una transferencia sobre 1.000.000
ej: juan t-> pedro M: 1.200.000
    sospechozo

si una cuenta tranfiere "montos altos" en poco tiempo

ej: juan t-> pedro  M:700.000  H:12:15
    juan t-> javier M:800.000  H:12:18
    juan t-> camila M:650.000  H:12:23

creacion de reportes:

los reportes tienen que tener el tipo de actividad sospechoza junto a las cuentas involucradas

ej: juan: fue sospechozo por hacer transferencias en ubicaciones diferentes en poco tiempo
    complices: pedro, javier

ej: juan fue sospechozo por hacer una transferencia por sobre el limite establesido(1.000.000)
    complice: pedro

ej: juan: fue sospechozo por transferir mucho dinero en poco tiempo
    complices: pedro, javier, camila

*/ 