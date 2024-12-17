#ifndef LISTADOBLECIRCULAR_H
#define LISTADOBLECIRCULAR_H

#include <iostream>
#include <string>
#include "datosTransaccion.h"
using namespace std;

// Definición del nodo
struct NodoLD {
    DatosTransaccion dato;
    NodoLD* siguiente;
    NodoLD* anterior;

    NodoLD(const DatosTransaccion& valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};

// Definición de la lista doble circular
class ListaDobleCircular {
private:
    NodoLD* cabeza;

public:
    // Constructor
    ListaDobleCircular() : cabeza(nullptr) {}

    // Método para agregar un nodo al final
    void agregar(const DatosTransaccion& dato) {
        NodoLD* nuevoNodo = new NodoLD(dato);
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
            cabeza->siguiente = cabeza;
            cabeza->anterior = cabeza;
        } else {
            NodoLD* ultimo = cabeza->anterior;
            ultimo->siguiente = nuevoNodo;
            nuevoNodo->anterior = ultimo;
            nuevoNodo->siguiente = cabeza;
            cabeza->anterior = nuevoNodo;
        }
    }

    // Método para mostrar la lista
    void mostrar() {
        if (cabeza == nullptr) {
            cout << "La lista está vacía." << endl;
            return;
        }
        NodoLD* actual = cabeza;
        do {
            cout << "====================================" << endl;
            cout << "ID: " << actual->dato.id
                 << ", ID_Trans: " << actual->dato.id_trans
                 << ", Usuario: " << actual->dato.usuario
                 << ", Departamento: " << actual->dato.depto
                 << ", Empresa: " << actual->dato.empresa
                 << ", Fecha: " << actual->dato.fecha
                 << ", Días: " << actual->dato.dias << endl;
            actual = actual->siguiente;
        } while (actual != cabeza);
        cout << endl;
        cout << "====================================" << endl;
    }

    // Método para eliminar un nodo con un valor específico
    void eliminar(const std::string& id_trans) {
        if (cabeza == nullptr) {
            cout << "La lista está vacía." << endl;
            return;
        }
        NodoLD* actual = cabeza;
        do {
            if (actual->dato.id_trans == id_trans) {
                if (actual == cabeza && actual->siguiente == cabeza) {
                    // Si es el único nodo en la lista
                    cabeza = nullptr;
                } else {
                    // Ajustar punteros
                    actual->anterior->siguiente = actual->siguiente;
                    actual->siguiente->anterior = actual->anterior;
                    if (actual == cabeza) {
                        cabeza = actual->siguiente;
                    }
                }
                delete actual;
                cout << "Nodo con ID_Trans " << id_trans << " eliminado." << endl;
                return;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);
        cout << "Nodo con ID_Trans " << id_trans << " no encontrado." << endl;
    }

    // Método para ordenar la lista por id_trans
    void ordenarPorIdTrans() {
        if (cabeza == nullptr || cabeza->siguiente == cabeza) {
            // Lista vacía o con un solo elemento, ya está ordenada
            return;
        }

        bool huboIntercambio;
        do {
            huboIntercambio = false;
            NodoLD* actual = cabeza;

            do {
                NodoLD* siguiente = actual->siguiente;
                if (actual->dato.id_trans > siguiente->dato.id_trans) {
                    // Intercambiar datos
                    std::swap(actual->dato, siguiente->dato);
                    huboIntercambio = true;
                }
                actual = actual->siguiente;
            } while (actual->siguiente != cabeza);

        } while (huboIntercambio);
    }

    // Destructor para liberar memoria
    ~ListaDobleCircular() {
        if (cabeza != nullptr) {
            NodoLD* actual = cabeza;
            do {
                NodoLD* siguiente = actual->siguiente;
                delete actual;
                actual = siguiente;
            } while (actual != cabeza);
        }
    }
};

#endif //LISTADOBLECIRCULAR_H