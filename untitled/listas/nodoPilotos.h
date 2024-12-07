//
// Created by velas on 20/06/2024.
//

#ifndef NODOPILOTOS_H
#define NODOPILOTOS_H
#include "pilotos.h"

struct nodoPilotos {
    pilotos pilots;
    nodoPilotos* siguiente;
    nodoPilotos* anterior;


};
#endif //NODOPILOTOS_H
