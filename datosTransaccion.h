#ifndef DATOSTRANSACCION_H
#define DATOSTRANSACCION_H
#include <string>

class DatosTransaccion {
public:
    std::string id;
    std::string id_trans;
    std::string usuario;
    std::string depto;
    std::string empresa;
    std::string fecha;
    int dias;

    // Constructor
    DatosTransaccion(const std::string& id_, const std::string& id_trans_, const std::string& usuario_,
                     const std::string& depto_, const std::string& empresa_, const std::string& fecha_, int dias_)
        : id(id_), id_trans(id_trans_), usuario(usuario_), depto(depto_), empresa(empresa_), fecha(fecha_), dias(dias_) {}
};

#endif //DATOSTRANSACCION_H