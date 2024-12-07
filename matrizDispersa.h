//
// Created by velas on 6/12/2024.
//

#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H
#include <iostream>
#include <string>

class Nodo {
public:
    std::string fila, columna, valor;  // Ahora fila y columna son de tipo string
    Nodo* siguiente;

    Nodo(const std::string& fila, const std::string& columna, const std::string& valor)
        : fila(fila), columna(columna), valor(valor), siguiente(nullptr) {}
};

class matrizDispersa {
private:
    Nodo* cabeza;

public:
    // Constructor
    matrizDispersa() : cabeza(nullptr) {}

    // Destructor para liberar memoria
    ~matrizDispersa() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    // Método para agregar un elemento
    void agregarElemento(const std::string& fila, const std::string& columna, const std::string& valor) {
        if (cabeza == nullptr) {
            if (!valor.empty()) {
                cabeza = new Nodo(fila, columna, valor);
            }
            return;
        }

        Nodo* actual = cabeza;
        Nodo* anterior = nullptr;

        // Buscar si ya existe el nodo con la posición dada
        while (actual != nullptr && (actual->fila < fila || (actual->fila == fila && actual->columna < columna))) {
            anterior = actual;
            actual = actual->siguiente;
        }

        // Si ya existe, actualizar o eliminar
        if (actual != nullptr && actual->fila == fila && actual->columna == columna) {
            if (!valor.empty()) {
                actual->valor = valor;
            } else {
                // Eliminar el nodo si el valor está vacío
                if (anterior == nullptr) {
                    cabeza = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                delete actual;
            }
            return;
        }

        // Insertar un nuevo nodo
        if (!valor.empty()) {
            Nodo* nuevo = new Nodo(fila, columna, valor);
            if (anterior == nullptr) {
                nuevo->siguiente = cabeza;
                cabeza = nuevo;
            } else {
                nuevo->siguiente = anterior->siguiente;
                anterior->siguiente = nuevo;
            }
        }
    }

    // Método para obtener un elemento
    std::string obtenerElemento(const std::string& fila, const std::string& columna) const {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->fila == fila && actual->columna == columna) {
                return actual->valor;
            }
            actual = actual->siguiente;
        }
        return ""; // Retorna una cadena vacía si no existe el elemento
    }

    // Método para mostrar los datos almacenados
    void mostrarDatos() const {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            std::cout << "Posición (" << actual->fila << ", "
                      << actual->columna << "): "
                      << actual->valor << std::endl;
            actual = actual->siguiente;
        }
    }
};




#endif //MATRIZDISPERSA_H
