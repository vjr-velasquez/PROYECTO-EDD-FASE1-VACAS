#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include <string>
#include <fstream>
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

    void agregarActivo(const std::string& fila, const std::string& columna , const std::string& user, const std::string& id, const std::string& nombre, const std::string& descripcion, const int& dias) const {
        NodoMatriz* nodoFila = buscarFila(fila);
        if (nodoFila) {
            NodoMatriz* actual = nodoFila->siguienteColumna;
            while (actual != nullptr) {
                if (actual->columna == columna) {
                    if(actual->valor.user == user) {
                        actual->valor.avl.insertar(Activos("",id,nombre,descripcion,dias,"disponible"));
                        break;
                    }
                }
                actual = actual->siguienteColumna;
            }
        }
    }

    void buscarEliminarActivo(const std::string& fila, const std::string& columna , const std::string& user, const std::string& id) const {
        NodoMatriz* nodoFila = buscarFila(fila);
        if (nodoFila) {
            NodoMatriz* actual = nodoFila->siguienteColumna;
            while (actual != nullptr) {
                if (actual->columna == columna) {
                    if(actual->valor.user == user) {
                        actual->valor.avl.eliminar(id);
                        break;
                    }
                }
                actual = actual->siguienteColumna;
            }
        }
    }

    void modificarActivo(const std::string& fila, const std::string& columna , const std::string& user, const std::string& id, const std::string& desc) const {
        NodoMatriz* nodoFila = buscarFila(fila);
        if (nodoFila) {
            NodoMatriz* actual = nodoFila->siguienteColumna;
            while (actual != nullptr) {
                if (actual->columna == columna) {
                    if(actual->valor.user == user) {
                        actual->valor.avl.modificarDescripcion(id,desc);
                        break;
                    }
                }
                actual = actual->siguienteColumna;
            }
        }
    }

    void rentarActivo(const std::string& user, const std::string& id, const std::string& estado, const int dias) const {
        NodoMatriz* filaActual = cabeza->siguienteFila;
        while (filaActual != nullptr) {
            NodoMatriz* columnaActual = filaActual->siguienteColumna;
            while (columnaActual != nullptr) {
                columnaActual->valor.avl.rentarActivo(user,id, estado, dias);
                columnaActual = columnaActual->siguienteColumna;
            }
            filaActual = filaActual->siguienteFila;
        }
    }

    void mostarActivo(const std::string& fila, const std::string& columna, const std::string& user, const std::string& es) const {
        NodoMatriz* nodoFila = buscarFila(fila);
        if (nodoFila) {
            NodoMatriz* actual = nodoFila->siguienteColumna;
            while (actual != nullptr) {
                if (actual->columna == columna) {
                    if(actual->valor.user == user) {
                        if(es == "rentado") {
                            actual->valor.avl.enOrdenRentado();
                            break;
                        }
                        if(es == "todo") {
                            std::cout << "modificando......";
                            actual->valor.avl.mostrarActivosEliminar();
                            break;
                        }
                    }
                }
                actual = actual->siguienteColumna;
            }
        }
    }

    void devolverActivo(const std::string& id) const {
        NodoMatriz* filaActual = cabeza->siguienteFila;
        while (filaActual != nullptr) {
            NodoMatriz* columnaActual = filaActual->siguienteColumna;
            while (columnaActual != nullptr) {
                columnaActual->valor.avl.devolverActivo(id);
                columnaActual = columnaActual->siguienteColumna;
            }
            filaActual = filaActual->siguienteFila;
        }
    }

    void mostarActivoRentados(const std::string& user) const {
        NodoMatriz* filaActual = cabeza->siguienteFila;
        while (filaActual != nullptr) {
            NodoMatriz* columnaActual = filaActual->siguienteColumna;
            while (columnaActual != nullptr) {
                columnaActual->valor.avl.mostrarActivos(user);
                columnaActual = columnaActual->siguienteColumna;
            }
            filaActual = filaActual->siguienteFila;
        }
    }

    void mostrarActivos(const std::string& user) const {
        NodoMatriz* filaActual = cabeza->siguienteFila;
        while (filaActual != nullptr) {
            NodoMatriz* columnaActual = filaActual->siguienteColumna;
            while (columnaActual != nullptr) {
                if(columnaActual->valor.user != user) {
                    columnaActual->valor.avl.enOrden();
                }
                columnaActual = columnaActual->siguienteColumna;
            }
            filaActual = filaActual->siguienteFila;
        }
    }

};

#endif //MATRIZDISPERSA_H