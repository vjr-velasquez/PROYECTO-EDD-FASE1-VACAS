#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>

struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;
    int altura;

    Nodo(int v) : valor(v), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

class ArbolAVL {
public:
    Nodo* insertar(Nodo* nodo, int valor);
    void preorden(Nodo* raiz);
    Nodo* getRaiz() const { return raiz; }

private:
    Nodo* raiz = nullptr;

    int obtenerAltura(Nodo* nodo);
    int obtenerBalance(Nodo* nodo);
    Nodo* rotacionDerecha(Nodo* y);
    Nodo* rotacionIzquierda(Nodo* x);
};

int ArbolAVL::obtenerAltura(Nodo* nodo) {
    return nodo ? nodo->altura : 0;
}

int ArbolAVL::obtenerBalance(Nodo* nodo) {
    return nodo ? obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho) : 0;
}

Nodo* ArbolAVL::rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierdo;
    Nodo* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    y->altura = std::max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;
    x->altura = std::max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;

    return x;
}

Nodo* ArbolAVL::rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecho;
    Nodo* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    x->altura = std::max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;
    y->altura = std::max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;

    return y;
}

Nodo* ArbolAVL::insertar(Nodo* nodo, int valor) {
    if (!nodo) return new Nodo(valor);

    if (valor < nodo->valor)
        nodo->izquierdo = insertar(nodo->izquierdo, valor);
    else if (valor > nodo->valor)
        nodo->derecho = insertar(nodo->derecho, valor);
    else
        return nodo;

    nodo->altura = 1 + std::max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && valor < nodo->izquierdo->valor)
        return rotacionDerecha(nodo);

    if (balance < -1 && valor > nodo->derecho->valor)
        return rotacionIzquierda(nodo);

    if (balance > 1 && valor > nodo->izquierdo->valor) {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }

    if (balance < -1 && valor < nodo->derecho->valor) {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

void ArbolAVL::preorden(Nodo* raiz) {
    if (raiz) {
        std::cout << raiz->valor << " ";
        preorden(raiz->izquierdo);
        preorden(raiz->derecho);
    }
}

#endif