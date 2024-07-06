#include "Util.h"
#include <fstream>
#include <sstream>

void guardarTransaccionesRecursivo(NodoArbol* nodo, std::ofstream& file) {
    if (nodo == nullptr) {
        return;
    }
    guardarTransaccionesRecursivo(nodo->izquierda, file);
    Transaccion* t = nodo->transaccion;
    file << t->id << "," << t->cuentaOrigen << "," << t->cuentaDestino << "," << t->monto << "," 
         << t->ubicacion << "," << t->fecha << "," << t->hora << std::endl;
    guardarTransaccionesRecursivo(nodo->derecha, file);
}

void guardarTransacciones(ArbolAVL& arbol, const std::string& filename) {
    std::ofstream file(filename, std::ios::out);  // Open in write mode
    guardarTransaccionesRecursivo(arbol.raiz, file);
    file.close();
}

ArbolAVL cargarTransacciones(const std::string& filename, ListaEnlazada& cuentasSospechosas) {
    std::ifstream file(filename);
    ArbolAVL arbol;
    std::string linea;

    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::string idStr, cuentaOrigen, cuentaDestino, montoStr, ubicacion, fecha, hora;
        std::getline(ss, idStr, ',');
        std::getline(ss, cuentaOrigen, ',');
        std::getline(ss, cuentaDestino, ',');
        std::getline(ss, montoStr, ',');
        std::getline(ss, ubicacion, ',');
        std::getline(ss, fecha, ',');
        std::getline(ss, hora, ',');

        int id = std::stoi(idStr);
        double monto = std::stod(montoStr);

        Transaccion* transaccion = new Transaccion(id, cuentaOrigen, cuentaDestino, monto, ubicacion, fecha, hora);
        arbol.insertar(transaccion, cuentasSospechosas);
    }

    file.close();
    return arbol;
}

void mostrarMenu() {
    std::cout << "Menu de opciones:" << std::endl;
    std::cout << "1. Registrar transaccion" << std::endl;
    std::cout << "2. Buscar transaccion por ID" << std::endl;
    std::cout << "3. Generar reporte de transacciones sospechosas" << std::endl;
    std::cout << "4. Guardar transacciones" << std::endl;
    std::cout << "0. Salir" << std::endl;
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