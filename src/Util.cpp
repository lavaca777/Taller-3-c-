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
    ifstream inputFile(filename);
    ofstream outputFile("temp.txt");  // Archivo temporal para almacenar nuevas cuentas sospechosas

    if (!inputFile) {
        cerr << "Error: No se pudo abrir el archivo de entrada " << filename << endl;
        return;
    }

    // Leer las cuentas sospechosas existentes y verificar duplicados
    string line;
    bool encontrado = false;

    while (getline(inputFile, line)) {
        stringstream ss(line);
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

        // Verificar si la cuenta sospechosa ya existe
        NodoLista* actual = cuentasSospechosas.obtenerCabeza();
        encontrado = false;

        while (actual != nullptr) {
            Transaccion* t = actual->transaccion;
            if (t->id == id &&
                t->cuentaOrigen == cuentaOrigen &&
                t->cuentaDestino == cuentaDestino &&
                t->monto == monto &&
                t->ubicacion == ubicacion &&
                t->fecha == fecha &&
                t->hora == hora &&
                actual->motivo == motivo) {
                encontrado = true;
                break;
            }
            actual = actual->siguiente;
        }

        // Si no se encuentra duplicado, escribir en el archivo temporal
        if (!encontrado) {
            outputFile << line << endl;
        }
    }

    // Agregar las nuevas cuentas sospechosas al archivo temporal
    NodoLista* actual = cuentasSospechosas.obtenerCabeza();
    while (actual != nullptr) {
        Transaccion* t = actual->transaccion;
        outputFile << t->id << "," << t->cuentaOrigen << "," << t->cuentaDestino << "," << t->monto << ","
                   << t->ubicacion << "," << t->fecha << "," << t->hora << "," << actual->motivo << endl;
        actual = actual->siguiente;
    }

    inputFile.close();
    outputFile.close();

    // Renombrar el archivo temporal al original
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
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