#include "Transaccion.h"

Transaccion::Transaccion(int id, string cuentaOrigen, string cuentaDestino, double monto, string ubicacion, string fecha, string hora)
    : id(id), cuentaOrigen(cuentaOrigen), cuentaDestino(cuentaDestino), monto(monto), ubicacion(ubicacion), fecha(fecha), hora(hora) {}

void Transaccion::mostrarTransaccion() {
    cout << "ID: " << id << endl;
    cout << "Cuenta Origen: " << cuentaOrigen << endl;
    cout << "Cuenta Destino: " << cuentaDestino << endl;
    cout << "Monto: " << monto << endl;
    cout << "Ubicacion: " << ubicacion << endl;
    cout << "Fecha: " << fecha << endl;
    cout << "Hora: " << hora << endl;
}
