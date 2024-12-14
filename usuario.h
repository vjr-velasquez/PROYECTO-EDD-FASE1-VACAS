#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>
#include "avl_tree.h"

class Usuario {
public:
    std::string user;
    std::string contra;
    ArbolAVL avl;

    Usuario(const std::string& user = "", const std::string& contra = "", const ArbolAVL& avl = ArbolAVL())
    : user(user), contra(contra), avl(avl) {}

    std::string toString() const {
        return "Usuario: " + user + ", Contraseña: " + contra;
    }

    friend std::ostream& operator<<(std::ostream& os, const Usuario& usuario) {
        os << usuario.toString();
        return os;
    }
};

#endif //USUARIO_H