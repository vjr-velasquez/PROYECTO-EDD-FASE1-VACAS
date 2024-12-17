#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "matrizDispersa.h"
#include "listaDobleCircular.h"

matrizDispersa matriz; // Creacion de matriz
ListaDobleCircular lisD;
using namespace std;

std::string generarID(int longitud) {
    const std::string caracteres = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;  // Fuente de entropía
    std::mt19937 generador(rd()); // Generador de números aleatorios
    std::uniform_int_distribution<> distribucion(0, caracteres.size() - 1);

    std::string id;
    for (int i = 0; i < longitud; ++i) {
        id += caracteres[distribucion(generador)];
    }

    return id;
}

//Funcion para mostar mis activos rentados
void misActivosRentados(const string& usuario, const string& depto, const string& empresa) {
    cout << "============ MIS ACTIVOS RENTADOS ============ " << endl;
    matriz.mostarActivo(empresa, depto, usuario, "rentado");
    cout << "========================================== " << endl;
}

//Funcion para mostrar los activos rentados
void activosRentados(const string& usuario, const string& depto, const string& empresa) {
    int opcion = 0;
    cout << "============ ACTIVOS RENTADOS ============ " << endl;
    matriz.mostarActivoRentados(usuario);
    cout << "========================================== " << endl;
    cout << "1. Para devolver Activo" << endl;
    cin >> opcion;
    if(opcion == 1) {
        std:: string id = "";
        cout << "Ingrese Id que quiere devolver: " << endl;
        cin >> id;
        matriz.devolverActivo(id);
    }
}

//Funcion para mostrar el menu Principal
void menuPrincipal() {
    cout << "====== RENTA DE ACTIVOS ======" << endl;
    cout << "1. Iniciar sesion" << endl;
    cout << endl;
    cout << "Ingrese una opcion:   ";
}

//Funcion para rentar un activo
void rentarActivo(const string& usuario, const string& depto, const string& empresa) {
    // Obtener el tiempo actual como un objeto time_t
    std::time_t tiempoActual = std::time(nullptr);
    // Convertir el tiempo a una estructura de tiempo local
    std::tm* tiempoLocal = std::localtime(&tiempoActual);
    // Formatear la fecha en una cadena
    char buffer[11]; // Espacio suficiente para "YYYY-MM-DD\0"
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", tiempoLocal);
    // Guardar la fecha en una variable tipo std::string
    std::string fechaActual = buffer;
    int longitud = 15; // Longitud del ID
    std::string id_trans = generarID(longitud);
    std:: string id = "";
    int dias = 0;
    cout << "======RENTANDO UN ACITVO======" << endl;
    matriz.mostrarActivos(usuario);
    cout << "====================================" << endl;
    cout << "Ingrese Id que quiere rentar: " << endl;
    cin >> id;
    cout << "Cuantos dias: " << endl;
    cin >> dias;
    matriz.rentarActivo(usuario, id, "rentado", dias);
    lisD.agregar(DatosTransaccion(id,id_trans,usuario,depto,empresa,fechaActual,dias));
}

// Función para modificar un activo
void modificarActivo(const string& usuario, const string& depto, const string& empresa) {
    std::string id = "";
    std::string desc = "";

    cout << "====== MODIFICANDO SU ACTIVO ======" << endl;
    matriz.mostarActivo(empresa, depto, usuario, "todo");
    cout << "====================================" << endl;

    cout << "Ingrese el ID del activo que desea modificar: ";
    cin >> id; // Leer el ID (puede no contener espacios)

    cout << "Ingrese la nueva descripción: ";
    std::cin.ignore(); // Limpiar el búfer antes de usar getline
    std::getline(std::cin, desc); // Usar getline para leer la descripción con espacios

    matriz.modificarActivo(empresa, depto, usuario, id, desc);
}

//Funcion para eliminar un activo
void eliminarActivo(const string& usuario, const string& depto, const string& empresa) {
    std:: string id = "";
    cout << "====== ELIMINACION DE ACTIVOS ======" << endl;
    matriz.mostarActivo(empresa, depto, usuario, "todo");
    cout << "====================================" << endl;
    cout << "Ingrese Id que desea eliminar: " << endl;
    cin >> id;
    matriz.buscarEliminarActivo(empresa,depto,usuario,id);
}

// Función para agregar un activo
void agregarActivo(const string& usuario, const string& depto, const string& empresa) {
    int longitud = 15; // Longitud del ID
    std::string id = generarID(longitud);

    std::string nombreActivo, descripcion;
    int dias = 0;

    cout << " ================= CREACION DE ACTIVO ================= " << endl;
    cout << endl;

    cout << "Ingrese el nombre del Activo: ";
    std::cin.ignore(); // Limpiar el búfer antes de usar getline
    std::getline(std::cin, nombreActivo); // Usar getline para leer con espacios

    cout << "Descripcion: ";
    std::getline(std::cin, descripcion); // Usar getline para leer con espacios

    cout << "Ingrese cantidad de días: ";
    cin >> dias;

    matriz.agregarActivo(depto, empresa, usuario, id, nombreActivo, descripcion, dias);
}

// Funcion del admin para crear usuario
void registroUsario() {
    string nombreUsuario, contrasena, departamento, empresa;
    cout << " ================= CREACION DE USUARIO ================= " <<endl;
    cout << endl;
    cout << "Ingrese el nombre de usuario: ";
    cin >> nombreUsuario;
    cout << "Ingrese la contraseña: ";
    cin >> contrasena;
    cout << "Ingrese el departamento: ";
    cin >> departamento;
    cout << "Ingrese la empresa: ";
    cin >> empresa;
    matriz.agregarNodo(empresa,departamento,Usuario(nombreUsuario,contrasena)); // Estamos agregando a la matriz
}

// Funcion para agrefar el menu del admin
void menuAdmin() {
    int opcion;
    while (true) {
        cout << "============= MENU ADMINISTRADOR =============" << endl;
        cout << "1. Registrar un usuario " << endl;
        cout << "2. Reporte de matriz dispersa " << endl;
        cout << "3. Reporte de activos disponibles de un Depto" << endl;
        cout << "4. Reporte de activos disponibles de una empresa" << endl;
        cout << "5. Reporte de transacciones" << endl;
        cout << "6. Reporte de activos de un usuario" << endl;
        cout << "7. Activos rentados por un Usuario" << endl;
        cout << "8. Ordenar transacciones" << endl;
        cout << "9. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            registroUsario();
        }
        else if(opcion == 8) {
            lisD.ordenarPorIdTrans();
            lisD.mostrar();
        }
        else if(opcion == 9) {
            break;
        }
        else {
            cout << "Opcion no valida. Solo se permite la opcion 1. Por favor intente de nuevo." << endl;
        }
    }
}

//Funcion para mostrar el menu de las opciones del usario
void menuOpciones(const string& usuario, const string& depto, const string& empresa) {
    int opcion;
    while (true) {
        cout << "=========== Bienvenido ===========" << usuario << endl;
        cout << endl;
        cout << "========= MENU DE OPCIONES =========" << endl;
        cout << endl;
        cout << "1. AGREGAR ACTIVO " << endl;
        cout << "2. ELIMINAR ACTIVO " << endl;
        cout << "3. MODIFICAR ACTIVO " << endl;
        cout << "4. RENTAR ACTIVO " << endl;
        cout << "5. ACTIVOS RENTADOS " << endl;
        cout << "6. MIS ACTIVOS RENTADOS " << endl;
        cout << "7. CERRAR SESION " << endl;
        cin >> opcion;
        if (opcion == 1) {
            agregarActivo(usuario,depto,empresa);
        }
        else if(opcion == 2) {
            eliminarActivo(usuario,depto,empresa);
        }
        else if(opcion == 3) {
            modificarActivo(usuario,depto,empresa);
        }
        else if(opcion == 4) {
            rentarActivo(usuario,depto,empresa);
        }
        else if(opcion == 5) {
            activosRentados(usuario,depto,empresa);
        }
        else if (opcion == 6) {
            misActivosRentados(usuario,depto,empresa);
        }
        else if(opcion == 7) {
            break;
        }
        else {
            cout << "Opcion no valida. Solo se permite la opcion 1. Por favor intente de nuevo." << endl;
        }
    }
}

// Función para mostrar el menú de login
void menuLogeo() {
    string username, password, depto, company;
    while (true) {

        cout << "============ MENÚ DE LOGIN ============" << endl;
        cout << ">> Ingrese su nombre de usuario: ";
        cin >> username;
        cout << endl << ">> Ingrese su contraseña: ";
        cin >> password;

        if (username == "admin" && password == "edd123") {
            menuAdmin();
        } else {
            cout << endl << ">> Ingrese un Departamento: ";
            cin >> depto;
            cout << endl << ">> Ingrese la empresa a la que pertenece: ";
            cin >> company;
            bool usuarioExistente = matriz.buscarValor(company , depto , username , password);        /* Aqui buscamos el user en la matriz dispersa */
            cout << usuarioExistente << endl;
            if(usuarioExistente) {
                menuOpciones(username, depto, company);
            }else {
                cout << "Contra incorrecta ......" << endl;
                cout << "Usuario incorrecto  ......" << endl;
                cout << "Depto incorrecto  ......" << endl;
                cout << "Empresa incorrecto  ......" << endl;
            }
        }
    }
}

//Funcion para mostar mis activos rentados
void misActivosRentados() {
    cout << "MIS ACTIVOS RENTADOS SON ...... " << endl;
}


int main() {
    int opcion;

    while (true) {
        //Mostrar el menu principal
        system("cls");
        menuPrincipal();
        cin >> opcion;

        if(opcion == 1) {
            //mostrar el menu de login
            system("cls");
            menuLogeo();

        }else {
            break;
        }
    }
    return 0;
}