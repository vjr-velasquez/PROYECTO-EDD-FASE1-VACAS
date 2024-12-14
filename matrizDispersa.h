#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "usuario.h"

struct NodoMatriz {
    std::string fila;
    std::string columna;
    Usuario valor;
    NodoMatriz* siguienteFila;  // Apunta al siguiente nodo en la misma fila
    NodoMatriz* siguienteColumna; // Apunta al siguiente nodo en la misma columna

    NodoMatriz(const std::string& f, const std::string& c, const Usuario& v)
        : fila(f), columna(c), valor(v), siguienteFila(nullptr), siguienteColumna(nullptr) {}
};

class matrizDispersa {
private:
    NodoMatriz* cabeza;

    NodoMatriz* buscarFila(const std::string& fila) const {
        NodoMatriz* actual = cabeza->siguienteFila;
        while (actual != nullptr && actual->fila != fila) {
            actual = actual->siguienteFila;
        }
        return actual;
    }

    NodoMatriz* buscarColumna(const std::string& columna) const {
        NodoMatriz* actual = cabeza->siguienteColumna;
        while (actual != nullptr && actual->columna != columna) {
            actual = actual->siguienteColumna;
        }
        return actual;
    }

public:
    matrizDispersa() : cabeza(new NodoMatriz("", "", Usuario())) {}

    void agregarNodo(const std::string& fila, const std::string& columna, const Usuario& valor) {
        NodoMatriz* nodoFila = buscarFila(fila);
        if (!nodoFila) {
            nodoFila = new NodoMatriz(fila, "", Usuario());
            nodoFila->siguienteFila = cabeza->siguienteFila;
            cabeza->siguienteFila = nodoFila;
        }

        NodoMatriz* nodoColumna = buscarColumna(columna);
        if (!nodoColumna) {
            nodoColumna = new NodoMatriz("", columna, Usuario());
            nodoColumna->siguienteColumna = cabeza->siguienteColumna;
            cabeza->siguienteColumna = nodoColumna;
        }

        NodoMatriz* nuevo = new NodoMatriz(fila, columna, valor);

        // Insertar en la fila correspondiente
        NodoMatriz* actual = nodoFila;
        while (actual->siguienteColumna != nullptr && actual->siguienteColumna->columna < columna) {
            actual = actual->siguienteColumna;
        }
        nuevo->siguienteColumna = actual->siguienteColumna;
        actual->siguienteColumna = nuevo;

        // Insertar en la columna correspondiente
        actual = nodoColumna;
        while (actual->siguienteFila != nullptr && actual->siguienteFila->fila < fila) {
            actual = actual->siguienteFila;
        }
        nuevo->siguienteFila = actual->siguienteFila;
        actual->siguienteFila = nuevo;
    }

    bool buscarValor(const std::string& fila, const std::string& columna , const std::string& user, const std::string& contra) const {
        NodoMatriz* nodoFila = buscarFila(fila);
        if (nodoFila) {
            NodoMatriz* actual = nodoFila->siguienteColumna;
            while (actual != nullptr) {
                if (actual->columna == columna) {
                    if(actual->valor.user == user && actual->valor.contra == contra) {
                        return true;
                    }
                    return false;
                }
                actual = actual->siguienteColumna;
            }
            return false ;
        }
        return false ;
    }

    void generarGraphviz(const std::string& nombreArchivo) const {
        std::ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            std::cerr << "Error al abrir el archivo para escritura." << std::endl;
            return;
        }

        archivo << "digraph MatrizDispersa {\n";
        archivo << "    node [shape=box];\n";

        NodoMatriz* actualFila = cabeza->siguienteFila;
        while (actualFila != nullptr) {
            archivo << "    fila_" << actualFila->fila
                    << " [label=\"" << actualFila->fila << "\", style=filled, fillcolor=lightblue];\n";
            actualFila = actualFila->siguienteFila;
        }

        NodoMatriz* actualColumna = cabeza->siguienteColumna;
        while (actualColumna != nullptr) {
            archivo << "    columna_" << actualColumna->columna
                    << " [label=\"" << actualColumna->columna << "\", style=filled, fillcolor=lightgreen];\n";
            actualColumna = actualColumna->siguienteColumna;
        }

        NodoMatriz* actual = cabeza->siguienteFila;
        while (actual != nullptr) {
            NodoMatriz* nodoValor = actual->siguienteColumna;
            while (nodoValor != nullptr) {
                archivo << "    valor_" << nodoValor->fila << "_" << nodoValor->columna
                        << " [label=\"" << nodoValor->valor.toString() << "\", style=filled, fillcolor=yellow];\n";
                nodoValor = nodoValor->siguienteColumna;
            }
            actual = actual->siguienteFila;
        }

        actualFila = cabeza->siguienteFila;
        while (actualFila != nullptr) {
            NodoMatriz* nodoValor = actualFila->siguienteColumna;
            while (nodoValor != nullptr) {
                archivo << "    fila_" << actualFila->fila << " -> valor_" << nodoValor->fila << "_" << nodoValor->columna
                        << " [dir=none];\n";
                nodoValor = nodoValor->siguienteColumna;
            }
            actualFila = actualFila->siguienteFila;
        }

        actualColumna = cabeza->siguienteColumna;
        while (actualColumna != nullptr) {
            NodoMatriz* nodoValor = actualColumna->siguienteFila;
            while (nodoValor != nullptr) {
                archivo << "    valor_" << nodoValor->fila << "" << nodoValor->columna << " -> columna" << actualColumna->columna
                        << " [dir=none];\n";
                nodoValor = nodoValor->siguienteFila;
            }
            actualColumna = actualColumna->siguienteColumna;
        }

        archivo << "}\n";
        archivo.close();
        std::cout << "Archivo Graphviz generado: " << nombreArchivo << std::endl;
    }
};

#endif //MATRIZDISPERSA_H