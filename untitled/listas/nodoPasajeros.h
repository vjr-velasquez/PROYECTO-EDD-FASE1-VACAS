//
// Created by velas on 11/06/2024.
//

#ifndef NODOPASAJEROS_H
#define NODOPASAJEROS_H
#include "pasajeros.h"

struct nodoPasajeros {
    pasajeros data;
    nodoPasajeros* next;
    nodoPasajeros(pasajeros val) : data(val), next(nullptr) {}
};
#endif //NODOPASAJEROS_H
