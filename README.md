Para crear un README que describa tu proyecto de forma clara y completa, puedes estructurarlo de la siguiente manera:

---

# Sistema de Gestión de Farmacia

Este proyecto implementa un sistema de gestión para una farmacia en C++, permitiendo gestionar el inventario de productos y la atención prioritaria a clientes. Facilita la generación de boletas de compra y la actualización automática del inventario.

## Funcionalidades

- **Gestión de Inventario**: Agregar, buscar y mostrar productos en el inventario.
- **Atención de Clientes**: Manejo de una cola prioritaria para clientes según su categoría.
- **Generación de Boletas**: Creación detallada de boletas de compra para los clientes atendidos.
- **Actualización de Inventario**: Actualización automática del archivo de productos después de cada transacción.

## Descripción de los Objetos Principales

### 1. Inventario (`Inventario`)

La clase `Inventario` gestiona todas las operaciones relacionadas con los productos de la farmacia, incluyendo agregar, buscar, y mostrar productos en el inventario, así como actualizar el archivo de productos.

### 2. Producto (`Producto`)

La clase `Producto` representa un producto en el inventario, con atributos como ID, categoría, nombre, precio y cantidad. Permite restar y sumar cantidades del stock disponible.

### 3. Cliente (`Cliente`)

La clase `Cliente` modela a los clientes en la cola de atención, con atributos como nombre, rut y prioridad basada en su condición (tercera edad, discapacitado, embarazada, normal).

### 4. Gestión de Clientes (`GestionClientes`)

La clase `GestionClientes` maneja la cola de clientes, permitiendo agregar clientes con prioridad y atenderlos en orden de llegada. Incluye funciones para agregar clientes y atender al siguiente cliente en la cola.

### Archivos de Datos

- `clientes.txt`: Archivo que almacena información de los clientes.
- `productos.txt`: Archivo que almacena información de los productos en el inventario.

## Compilación y Ejecución

### Método 1: Compilación desde la Línea de Comandos

1. **Compilar el código**:
    ```sh
    g++ src/Inventario.cpp src/Producto.cpp src/ListaEnlazada.cpp src/HashMap.cpp src/GestionClientes.cpp src/Cliente.cpp src/Nodo.cpp main.cpp -I include -o farmacia
    ```

2. **Ejecutar el programa**:
    ```sh
    ./farmacia
    ```

### Método 2: Ejecución desde el Entorno de Desarrollo

1. **Abrir el Proyecto**:
    Abre el proyecto en tu entorno de desarrollo preferido.

2. **Compilar y Ejecutar**:
    Utiliza la función de compilación y ejecución integrada en tu entorno de desarrollo.

## Uso

1. **Menú Principal**:
    - `1. Ingresar cliente a la cola`: Añade un cliente a la cola de atención con su respectiva prioridad.
    - `2. Atender cliente`: Atiende al siguiente cliente en la cola y genera una boleta de compra.
    - `3. Agregar producto a bodega`: Añade un nuevo producto al inventario.
    - `4. Aumentar Stock`: Incrementa la cantidad disponible de un producto existente.
    - `5. Salir`: Guarda los datos y cierra el programa.

2. **Atención de Clientes**:
    - Al atender a un cliente, se muestra el inventario actualizado y se genera una boleta detallada.

## Equipo de Trabajo

- **Inti Bautista Santibáñez Walker**
  - **RUT**: 21.275.258-4
  - **Correo**: inti.santibanez@alumnos.ucn.cl

- **Carlos Andres Tapia Paredes**
  - **RUT**: 21.458.544-8
  - **Correo**: carlos.tapia03@alumnos.ucn.cl

---

Puedes usar este esquema como base para crear tu README, asegurándote de personalizarlo con los detalles específicos de tu proyecto y ajustando la información según sea necesario.
