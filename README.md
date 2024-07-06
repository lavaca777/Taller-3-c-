Here's the updated README file for your financial transaction management system project, including examples of suspicious transactions and transaction records in text files:

---

# Sistema de Gestión de Transacciones Financieras

Este proyecto implementa un sistema de gestión de transacciones financieras en C++, diseñado para manejar registros de transacciones y detectar transacciones sospechosas basadas en ciertos criterios predefinidos.

## Funcionalidades

- **Registro y Gestión de Transacciones**: Permite registrar nuevas transacciones, buscar transacciones por ID y cargar/guardar transacciones desde/hacia archivos.
  
- **Detección de Transacciones Sospechosas**: Implementa criterios para identificar transacciones que podrían ser sospechosas, como montos elevados, ubicaciones inusuales, y patrones de transferencia rápida.

- **Gestión de Cuentas Sospechosas**: Permite cargar/guardar cuentas previamente marcadas como sospechosas y generar reportes detallados de estas cuentas.

## Descripción de los Objetos Principales

### 1. Clase `Transaccion`

Representa una transacción financiera con los siguientes atributos:

- **ID**: Identificador único de la transacción.
- **Cuenta Origen**: Cuenta desde donde se realiza la transacción.
- **Cuenta Destino**: Cuenta hacia donde se realiza la transacción.
- **Monto**: Monto de la transacción.
- **Ubicación**: Ubicación desde donde se realizó la transacción.
- **Fecha**: Fecha en que se realizó la transacción (formato YYYY-MM-DD).
- **Hora**: Hora en que se realizó la transacción (formato HH:MM).

### 2. Clase `ArbolAVL`

Implementa un árbol AVL para almacenar y gestionar las transacciones. Permite inserción, búsqueda y operaciones recursivas sobre el árbol.

### 3. Clase `ListaEnlazada`

Estructura de datos enlazada para almacenar cuentas sospechosas con la siguiente estructura:

- **Transacción**: Objeto de tipo `Transaccion`.
- **Motivo**: Razón por la cual la transacción fue marcada como sospechosa.

## Archivos de Datos de Ejemplo

### `sospechosos.txt`

```
10,pedro,pepe,7.77778e+06,u10,2040-05-06,12:04,Monto mayor a 1.000.000
10,pedro,pepe,777777,u1,2023-07-07,12:31,Transferencias altas en poco tiempo
11,ben,pedro,1500,u3,2023-07-08,11:11,Cuenta previamente sospechosa en el mismo mes y año
```

### `transacciones.txt`

```
1,CuentaOrigen1,CuentaDestino1,1500.75,Ubicacion1,2023-07-02,10:30
2,CuentaOrigen2,CuentaDestino2,200.5,Ubicacion2,2023-07-02,11:45
3,CuentaOrigen3,CuentaDestino3,1000,Ubicacion3,2023-07-02,12:15
4,CuentaOrigen4,CuentaDestino4,500.25,Ubicacion4,2023-07-02,13:00
5,CuentaOrigen5,CuentaDestino5,700.8,Ubicacion5,2023-07-02,14:30
```

## Compilación y Ejecución

### Método 1: Compilación desde la Línea de Comandos

1. **Compilar el código**:
    ```sh
    g++ src/Transaccion.cpp src/ArbolAVL.cpp src/ListaEnlazada.cpp src/Util.cpp main.cpp -I include -o gestion_transacciones
    ```

2. **Ejecutar el programa**:
    ```sh
    ./gestion_transacciones
    ```

### Método 2: Ejecución desde el Entorno de Desarrollo

1. **Abrir el Proyecto**:
    Abre el proyecto en tu entorno de desarrollo preferido (por ejemplo, Visual Studio Code).

2. **Compilar y Ejecutar**:
    Utiliza las funciones integradas de compilación y ejecución de tu entorno de desarrollo.

## Uso

1. **Menú Principal**:
    - `1. Registrar Transacción`: Permite registrar una nueva transacción.
    - `2. Buscar Transacción por ID`: Busca una transacción específica por su ID.
    - `3. Generar Reporte de Transacciones Sospechosas`: Muestra las transacciones marcadas como sospechosas y sus motivos.
    - `0. Salir`: Cierra el programa.

## Equipo de Desarrollo

- **Nombre del Desarrollador 1**
  - **Correo Electrónico**: desarrollador1@example.com

- **Nombre del Desarrollador 2**
  - **Correo Electrónico**: desarrollador2@example.com

---
