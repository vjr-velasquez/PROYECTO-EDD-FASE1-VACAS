//
// Created by velas on 14/12/2024.
//

#ifndef ACTIVOS_H
#define ACTIVOS_H
#include <string>
#include <iostream>

class Activos {
public:
    std::string id;
    std::string nombre;
    std::string descripcion;
    int dias;

    Activos(const std::string& id="" , const std::string& nombre="" , std::string& descripcion="" , int dias = 0)
        :id(id),nombre(nombre ),descripcion(descripcion),dias(dias)
    {}
};

#endif //ACTIVOS_H
