//
// Created by velas on 12/06/2024.
//

#ifndef PILA_H
#define PILA_H

#include "nodoEquipaje.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <string>

class pila {
private:
    nodoEquipaje* tope;

public:
    pila() : tope(nullptr) {}

    bool estaVacia() const {
        return tope == nullptr;
    }

    void apilar(const equipaje& valor) {
        nodoEquipaje* nuevoNodo = new nodoEquipaje(valor);
        nuevoNodo->siguiente = tope;
        tope = nuevoNodo;
    }

    equipaje desapilar() {
        if (estaVacia()) {
            throw std::out_of_range("La pila está vacía");
        }
        equipaje valor = tope->valor;
        nodoEquipaje* nodoAEliminar = tope;
        tope = tope->siguiente;
        delete nodoAEliminar;
        return valor;
    }

    void imprimirPila() const {
        nodoEquipaje* actual = tope;
        while (actual) {
            std::cout << actual->valor.nombre << " - " << actual->valor.destino << " - "
                      << actual->valor.cantidadEquipaje << std::endl;
            actual = actual->siguiente;
        }
    }

    void graficarPila(const std::string& nombreArchivo) const {
        std::ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo para escribir");
        }

        archivo << "digraph G {\n";
        archivo << "    rankdir=LR;\n";
        archivo << "    node [shape=record];\n";

        nodoEquipaje* actual = tope;
        int contador = 0;
        while (actual) {
            archivo << "    nodo" << contador << " [label=\"{"
                    << actual->valor.nombre << " | "
                    << actual->valor.destino << " | "
                    << actual->valor.cantidadEquipaje << "}\"];\n";
            if (actual->siguiente) {
                archivo << "    nodo" << contador << " -> nodo" << contador + 1 << ";\n";
            }
            actual = actual->siguiente;
            contador++;
        }

        archivo << "}\n";
        archivo.close();

        // Opcional: Generar la imagen automáticamente (requiere que Graphviz esté instalado)
        std::string comando = "dot -Tpng " + nombreArchivo + " -o " + nombreArchivo + ".png";
        system(comando.c_str());
    }

    ~pila() {
        while (!estaVacia()) {
            desapilar();
        }
    }
};

#endif // PILA_H



