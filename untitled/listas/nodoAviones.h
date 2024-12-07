//
// Created by velas on 10/06/2024.
//

#ifndef NODOAVIONES_H
#define NODOAVIONES_H
#include "aviones.h"

struct nodoAviones {
    aviones avion;
    nodoAviones* siguiente;
    nodoAviones* anterior;

    nodoAviones(aviones a) : avion(a), siguiente(nullptr), anterior(nullptr) {}
};
#endif //NODOAVIONES_H
