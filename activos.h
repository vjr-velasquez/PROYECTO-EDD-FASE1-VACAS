#ifndef ACTIVOS_H
#define ACTIVOS_H
#include <string>
#include <iostream>

class Activos {
public:
    std::string comprador;
    std::string id;
    std::string nombre;
    std::string descripcion;
    int dias;
    std::string estado;

    // Constructor actualizado con inicialización de 'comprador'
    Activos(const std::string& comprador = "", const std::string& id = "", const std::string& nombre = "",
            const std::string& descripcion = "", int dias = 0, const std::string& estado = "")
        : comprador(comprador), id(id), nombre(nombre), descripcion(descripcion), dias(dias), estado(estado) {}
};

#endif //ACTIVOS_H