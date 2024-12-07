//
// Created by velas on 10/06/2024.
//

#ifndef LISTADOBLECIRCULAR_H
#define LISTADOBLECIRCULAR_H
#include "nodoAviones.h"
#include <iostream>

class listaDobleCircular {
private:
    nodoAviones* cabeza;

public:
    listaDobleCircular() : cabeza(nullptr) {}

    ~listaDobleCircular() {
        if (!cabeza) return;

        nodoAviones* actual = cabeza;
        do {
            nodoAviones* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);
    }

    void agregarAvion(aviones a) {
        nodoAviones* nuevo = new nodoAviones(a);

        if (!cabeza) {
            cabeza = nuevo;
            cabeza->siguiente = cabeza;
            cabeza->anterior = cabeza;
        } else {
            nodoAviones* ultimo = cabeza->anterior;
            ultimo->siguiente = nuevo;
            nuevo->anterior = ultimo;
            nuevo->siguiente = cabeza;
            cabeza->anterior = nuevo;
        }
    }

    void imprimirLista() {
        if (!cabeza) return;

        nodoAviones* actual = cabeza;
        do {
            std::cout << "Vuelo: " << actual->avion.vuelo << std::endl;
            std::cout << "Número de Registro: " << actual->avion.numero_de_registro << std::endl;
            std::cout << "Modelo: " << actual->avion.modelo << std::endl;
            std::cout << "Fabricante: " << actual->avion.fabricante << std::endl;
            std::cout << "Año de Fabricación: " << actual->avion.ano_fabricacion << std::endl;
            std::cout << "Capacidad: " << actual->avion.capacidad << std::endl;
            std::cout << "Peso Máximo de Despegue: " << actual->avion.peso_max_despegue << std::endl;
            std::cout << "Aerolínea: " << actual->avion.aerolinea << std::endl;
            std::cout << "Estado: " << actual->avion.estado << std::endl;

            actual = actual->siguiente;
        } while (actual != cabeza);
    }
    // Función para visualizar la lista doble circular usando Graphviz
    void visualizarLista(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error al abrir el archivo para escritura: " << filename << std::endl;
            return;
        }

        file << "digraph ListaDobleCircular {" << std::endl;
        file << "\trankdir=LR;" << std::endl; // Para que los nodos estén de izquierda a derecha

        if (cabeza) {
            nodoAviones* actual = cabeza;
            do {
                file << "\t\"" << actual << "\" [label=\"" << "Vuelo: " << actual->avion.vuelo << "\\n"
                     << "Número de Registro: " << actual->avion.numero_de_registro << "\\n"
                     << "Modelo: " << actual->avion.modelo << "\\n"
                     << "Fabricante: " << actual->avion.fabricante << "\\n"
                     << "Año de Fabricación: " << actual->avion.ano_fabricacion << "\\n"
                     << "Capacidad: " << actual->avion.capacidad << "\\n"
                     << "Peso Máximo de Despegue: " << actual->avion.peso_max_despegue << "\\n"
                     << "Aerolínea: " << actual->avion.aerolinea << "\\n"
                     << "Estado: " << actual->avion.estado << "\"];" << std::endl;

                if (actual->siguiente != cabeza) {
                    file << "\t\"" << actual << "\" -> \"" << actual->siguiente << "\";" << std::endl;
                    file << "\t\"" << actual->siguiente << "\" -> \"" << actual << "\";" << std::endl;
                }

                actual = actual->siguiente;
            } while (actual != cabeza);
        }

        file << "}" << std::endl;

        file.close();

        std::cout << "Archivo DOT generado exitosamente: " << filename << std::endl;
    }
};
#endif //LISTADOBLECIRCULAR_H
