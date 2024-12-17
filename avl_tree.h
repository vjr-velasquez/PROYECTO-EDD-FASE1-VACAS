#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <string>
#include "activos.h"

// Estructura para un nodo del árbol AVL
struct Nodo {
    Activos valor;
    Nodo* izquierdo;
    Nodo* derecho;
    int altura;

    Nodo(const Activos& v) : valor(v), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

// Clase para implementar un árbol AVL
class ArbolAVL {
public:
    ArbolAVL() : raiz(nullptr) {}

    void insertar(const Activos& valor); // Método público para insertar un valor
    void eliminar(const std::string& id); // Método público para eliminar un nodo por ID
    void preorden() const;               // Método público para recorrido preorden
    void enOrden() const;                // Método público para recorrido en orden
    void mostrarActivos(const std::string& user) const;         // Método público para mostrar todos los activos (inorden)
    void modificarDescripcion(const std::string& id, const std::string& nuevaDescripcion); // Método público para modificar la descripción
    void rentarActivo(const std::string& user, const std::string& id, const std::string& estado, const int& dias); // Método público para rentar activo
    void enOrdenRentado() const;                // Método público para recorrido en orden
    void devolverActivo(const std::string& id); // Método público para devolver activo
    void mostrarActivosEliminar() const;
private:
    Nodo* raiz;                          // Nodo raíz del árbol

    Nodo* insertar(Nodo* nodo, const Activos& valor); // Método interno recursivo
    Nodo* eliminar(Nodo* nodo, const std::string& id); // Método interno recursivo para eliminar
    Nodo* obtenerMinimo(Nodo* nodo);                  // Encuentra el nodo con el menor valor
    void preorden(Nodo* nodo) const;                  // Método interno recursivo
    void enOrden(Nodo* nodo) const;                   // Método interno recursivo
    void mostrarActivos(Nodo* nodo, const std::string& user) const;            // Método interno recursivo para mostrar activos
    void modificarDescripcion(Nodo* nodo, const std::string& id, const std::string& nuevaDescripcion); // Método interno para modificar la descripción
    void rentarActivo(Nodo* nodo, const std::string& user, const std::string& id, const std::string& estado, const int& dias); // Método interno para rentar activo
    void enOrdenRentado(Nodo* nodo) const;                   // Método interno recursivo
    void devolverActivo(Nodo* nodo, const std::string& id);
    void mostrarActivosEliminar(Nodo* nodo) const;
    int obtenerAltura(Nodo* nodo);
    int obtenerBalance(Nodo* nodo);
    Nodo* rotacionDerecha(Nodo* y);
    Nodo* rotacionIzquierda(Nodo* x);
    int maximo(int a, int b);                         // Función para calcular el máximo entre dos valores
};

// Implementación de la función maximo
int ArbolAVL::maximo(int a, int b) {
    return (a > b) ? a : b;
}

// Implementación de obtenerAltura
int ArbolAVL::obtenerAltura(Nodo* nodo) {
    return nodo ? nodo->altura : 0;
}

// Implementación de obtenerBalance
int ArbolAVL::obtenerBalance(Nodo* nodo) {
    return nodo ? obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho) : 0;
}

// Implementación de la rotación a la derecha
Nodo* ArbolAVL::rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierdo;
    Nodo* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    y->altura = maximo(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;
    x->altura = maximo(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;

    return x;
}

// Implementación de la rotación a la izquierda
Nodo* ArbolAVL::rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecho;
    Nodo* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    x->altura = maximo(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;
    y->altura = maximo(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;

    return y;
}

// Implementación de la inserción recursiva
Nodo* ArbolAVL::insertar(Nodo* nodo, const Activos& valor) {
    if (!nodo) return new Nodo(valor);

    if (valor.id < nodo->valor.id)
        nodo->izquierdo = insertar(nodo->izquierdo, valor);
    else if (valor.id > nodo->valor.id)
        nodo->derecho = insertar(nodo->derecho, valor);
    else
        return nodo; // No permitir duplicados

    nodo->altura = 1 + maximo(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && valor.id < nodo->izquierdo->valor.id)
        return rotacionDerecha(nodo);

    if (balance < -1 && valor.id > nodo->derecho->valor.id)
        return rotacionIzquierda(nodo);

    if (balance > 1 && valor.id > nodo->izquierdo->valor.id) {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }

    if (balance < -1 && valor.id < nodo->derecho->valor.id) {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

// Método público para insertar un valor
void ArbolAVL::insertar(const Activos& valor) {
    raiz = insertar(raiz, valor); // Llama al método recursivo privado
}

// Implementación del recorrido en orden recursivo, filtrando por estado "disponible"
void ArbolAVL::enOrden(Nodo* nodo) const {
    if (nodo) {
        enOrden(nodo->izquierdo); // Recorrer el subárbol izquierdo
        if (nodo->valor.estado == "disponible") { // Mostrar solo si el estado es "disponible"
            std::cout << "ID: " << nodo->valor.id
                      << ", Nombre: " << nodo->valor.nombre
                      << ", Descripcion: " << nodo->valor.descripcion
                      << ", Días: " << nodo->valor.dias
                      << ", Estado: " << nodo->valor.estado << std::endl;
        }
        enOrden(nodo->derecho); // Recorrer el subárbol derecho
    }
}

// Método público para el recorrido en orden
void ArbolAVL::enOrden() const {
    enOrden(raiz); // Llama al método recursivo privado
}

// Método interno para mostrar todos los activos en orden (sin filtrar por estado)
void ArbolAVL::mostrarActivos(Nodo* nodo, const std::string& user) const {
    if (nodo) {
        mostrarActivos(nodo->izquierdo, user); // Recorrer el subárbol izquierdo
        if(nodo->valor.comprador == user) {
            std::cout << "ID: " << nodo->valor.id
                  << ", Nombre: " << nodo->valor.nombre
                  << ", Descripcion: " << nodo->valor.descripcion
                  << ", Días: " << nodo->valor.dias
                  << ", Estado: " << nodo->valor.estado << std::endl;
        }
        mostrarActivos(nodo->derecho, user); // Recorrer el subárbol derecho
    }
}

// Método público para mostrar todos los activos
void ArbolAVL::mostrarActivos(const std::string& user) const {
    mostrarActivos(raiz, user); // Llama al método recursivo privado
}

// Método interno para modificar la descripción buscando por ID
void ArbolAVL::modificarDescripcion(Nodo* nodo, const std::string& id, const std::string& nuevaDescripcion) {
    if (!nodo) return;

    if (id < nodo->valor.id) {
        modificarDescripcion(nodo->izquierdo, id, nuevaDescripcion);
    } else if (id > nodo->valor.id) {
        modificarDescripcion(nodo->derecho, id, nuevaDescripcion);
    } else {
        nodo->valor.descripcion = nuevaDescripcion;
        std::cout << "Descripción modificada correctamente para el ID: " << id << std::endl;
    }
}

// Método público para modificar la descripción
void ArbolAVL::modificarDescripcion(const std::string& id, const std::string& nuevaDescripcion) {
    modificarDescripcion(raiz, id, nuevaDescripcion);
}

// Método interno para rentar activo buscando por ID
void ArbolAVL::rentarActivo(Nodo* nodo, const std::string& user, const std::string& id, const std::string& estado, const int& dias) {
    if (!nodo) return;

    if (id < nodo->valor.id) {
        rentarActivo(nodo->izquierdo, user, id, estado, dias);
    } else if (id > nodo->valor.id) {
        rentarActivo(nodo->derecho, user, id, estado, dias);
    } else {
        if(dias <= nodo->valor.dias) {
            nodo->valor.estado = estado;
            nodo->valor.comprador = user;
            std::cout << "Activo Rentado: " << id << std::endl;
        }else {
            std::cout << "Se passa de días rentados" << id << std::endl;
        }

    }
}

// Método público para rentar activo
void ArbolAVL::rentarActivo(const std::string& user, const std::string& id, const std::string& estado, const int& dias) {
    rentarActivo(raiz, user, id, estado, dias);
}

// Implementación del recorrido en orden recursivo, filtrando por estado "rentado"
void ArbolAVL::enOrdenRentado(Nodo* nodo) const {
    if (nodo) {
        enOrdenRentado(nodo->izquierdo); // Recorrer el subárbol izquierdo
        if (nodo->valor.estado == "rentado") { // Mostrar solo si el estado es "disponible"
            std::cout << "ID: " << nodo->valor.id
                      << ", Nombre: " << nodo->valor.nombre
                      << ", Descripcion: " << nodo->valor.descripcion
                      << ", Días: " << nodo->valor.dias
                      << ", Estado: " << nodo->valor.estado << std::endl;
        }
        enOrdenRentado(nodo->derecho); // Recorrer el subárbol derecho
    }
}

// Método público para el recorrido en orden
void ArbolAVL::enOrdenRentado() const {
    enOrdenRentado(raiz); // Llama al método recursivo privado
}

// Método interno para rentar activo buscando por ID
void ArbolAVL::devolverActivo(Nodo* nodo, const std::string& id) {
    if (!nodo) return;

    if (id < nodo->valor.id) {
        devolverActivo(nodo->izquierdo, id);
    } else if (id > nodo->valor.id) {
        devolverActivo(nodo->derecho, id);
    } else {
        nodo->valor.estado = "disponible";
        nodo->valor.comprador = "";
        std::cout << "Activo devuelto: " << id << std::endl;
    }
}

// Método público para rentar activo
void ArbolAVL::devolverActivo(const std::string& id) {
    devolverActivo(raiz, id);
}

// Método interno para mostrar todos los activos en orden (sin filtrar por estado)
void ArbolAVL::mostrarActivosEliminar(Nodo* nodo) const {
    if (nodo) {
        mostrarActivosEliminar(nodo->izquierdo); // Recorrer el subárbol izquierdo
        std::cout << "ID: " << nodo->valor.id
              << ", Nombre: " << nodo->valor.nombre
              << ", Descripcion: " << nodo->valor.descripcion
              << ", Días: " << nodo->valor.dias
              << ", Estado: " << nodo->valor.estado << std::endl;
        mostrarActivosEliminar(nodo->derecho); // Recorrer el subárbol derecho
    }
}

// Método público para mostrar todos los activos
void ArbolAVL::mostrarActivosEliminar() const {
    mostrarActivosEliminar(raiz); // Llama al método recursivo privado
}

// Método para encontrar el nodo con el valor mínimo en un subárbol
Nodo* ArbolAVL::obtenerMinimo(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual->izquierdo) {
        actual = actual->izquierdo;
    }
    return actual;
}

// Implementación del método para eliminar un nodo
Nodo* ArbolAVL::eliminar(Nodo* nodo, const std::string& id) {
    if (!nodo) return nullptr;

    // Buscar el nodo a eliminar
    if (id < nodo->valor.id) {
        nodo->izquierdo = eliminar(nodo->izquierdo, id);
    } else if (id > nodo->valor.id) {
        nodo->derecho = eliminar(nodo->derecho, id);
    } else {
        // Nodo encontrado
        if (!nodo->izquierdo || !nodo->derecho) {
            Nodo* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;
            delete nodo;
            return temp;
        } else {
            // Encontrar el sucesor en orden (el menor del subárbol derecho)
            Nodo* temp = obtenerMinimo(nodo->derecho);
            nodo->valor = temp->valor;
            nodo->derecho = eliminar(nodo->derecho, temp->valor.id);
        }
    }

    // Actualizar altura del nodo actual
    nodo->altura = 1 + maximo(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));

    // Obtener balance del nodo actual
    int balance = obtenerBalance(nodo);

    // Balancear el árbol
    if (balance > 1 && obtenerBalance(nodo->izquierdo) >= 0)
        return rotacionDerecha(nodo);

    if (balance > 1 && obtenerBalance(nodo->izquierdo) < 0) {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }

    if (balance < -1 && obtenerBalance(nodo->derecho) <= 0)
        return rotacionIzquierda(nodo);

    if (balance < -1 && obtenerBalance(nodo->derecho) > 0) {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}


// Método público para eliminar un nodo
void ArbolAVL::eliminar(const std::string& id) {
    raiz = eliminar(raiz, id);
}

#endif