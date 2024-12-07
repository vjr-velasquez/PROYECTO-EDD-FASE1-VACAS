//
// Created by velas on 12/06/2024.
//

#ifndef NODOEQUIPAJE_H
#define NODOEQUIPAJE_H
#include "equipaje.h"
struct nodoEquipaje {
    equipaje valor;


    nodoEquipaje* siguiente;

    nodoEquipaje(equipaje v) : valor(v), siguiente(nullptr) {}
};

#endif // NODOEQUIPAJE_H
