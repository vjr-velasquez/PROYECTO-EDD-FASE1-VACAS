#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

class Valor {
public:
    std::string toString() const {
        return "Valor como cadena"; // Modifica esto según la lógica de tu clase
    }

    friend std::ostream& operator<<(std::ostream& os, const Valor& valor) {
        os << valor.toString();
        return os;
    }
};

struct Nodo {
    std::string fila;
    std::string columna;
    Valor valor;
    Nodo* siguiente;
};

class matrizDispersa {
private:
    Nodo* cabeza;

public:
    matrizDispersa() : cabeza(nullptr) {}

    void agregarNodo(const std::string& fila, const std::string& columna, const Valor& valor) {
        Nodo* nuevo = new Nodo{fila, columna, valor, cabeza};
        cabeza = nuevo;
    }

    void generarGraphviz(const std::string& nombreArchivo) const {
        std::ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            std::cerr << "Error al abrir el archivo para escritura." << std::endl;
            return;
        }

        // Iniciar el grafo
        archivo << "digraph MatrizDispersa {\n";
        archivo << "    node [shape=box];\n";

        // Crear nodos de filas
        Nodo* actual = cabeza;
        archivo << "    // Nodos de filas\n";
        std::unordered_map<std::string, bool> filas;
        std::unordered_map<std::string, bool> columnas;
        while (actual != nullptr) {
            if (filas.find(actual->fila) == filas.end()) {
                archivo << "    fila_" << actual->fila << " [label=\"" << actual->fila << "\", style=filled, fillcolor=lightblue, group=1];\n";
                filas[actual->fila] = true;
            }
            if (columnas.find(actual->columna) == columnas.end()) {
                archivo << "    columna_" << actual->columna << " [label=\"" << actual->columna << "\", style=filled, fillcolor=lightgreen, group=2];\n";
                columnas[actual->columna] = true;
            }
            actual = actual->siguiente;
        }

        // Crear nodos de valores
        archivo << "    // Nodos de valores\n";
        actual = cabeza;
        while (actual != nullptr) {
            archivo << "    valor_" << actual->fila << "_" << actual->columna
                    << " [label=\"" << actual->valor << "\", style=filled, fillcolor=yellow, group=2];\n";
            actual = actual->siguiente;
        }

        // Conexiones entre filas y valores
        archivo << "    // Conexiones de filas a valores\n";
        actual = cabeza;
        while (actual != nullptr) {
            archivo << "    fila_" << actual->fila << " -> valor_" << actual->fila << "_" << actual->columna << " [dir=none];\n";
            actual = actual->siguiente;
        }

        // Conexiones entre valores y columnas
        archivo << "    // Conexiones de valores a columnas\n";
        actual = cabeza;
        while (actual != nullptr) {
            archivo << "    valor_" << actual->fila << "" << actual->columna << " -> columna" << actual->columna << " [dir=none];\n";
            actual = actual->siguiente;
        }

        // Organizar filas en un mismo rango
        archivo << "    { rank=same;\n";
        for (const auto& fila : filas) {
            archivo << "    fila_" << fila.first << "\n";
        }
        archivo << "    }\n";

        // Organizar valores y columnas en el mismo rango
        archivo << "    { rank=same;\n";
        for (const auto& columna : columnas) {
            archivo << "    columna_" << columna.first << "\n";
        }
        actual = cabeza;
        while (actual != nullptr) {
            archivo << "    valor_" << actual->fila << "_" << actual->columna << "\n";
            actual = actual->siguiente;
        }
        archivo << "    }\n";

        // Cerrar el grafo
        archivo << "}\n";
        archivo.close();

        std::cout << "Archivo Graphviz generado: " << nombreArchivo << std::endl;
    }
};