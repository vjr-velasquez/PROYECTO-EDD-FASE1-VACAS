//
// Created by velas on 10/06/2024.
//

#ifndef AVIONES_H
#define AVIONES_H
#include <string>

struct aviones {
    std::string vuelo;
    std::string numero_de_registro;
    std::string modelo;
    std::string fabricante;
    int ano_fabricacion;
    int capacidad;
    int peso_max_despegue;
    std::string aerolinea;
    std::string estado;
};
#endif //AVIONES_H
