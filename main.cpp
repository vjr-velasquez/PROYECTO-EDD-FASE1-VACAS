#include <iostream>
#include <string>
#include "matrizDispersa.h"

matrizDispersa matriz; // Creacion de matriz
using namespace std;

//Funcion para mostrar el menu Principal
void menuPrincipal() {
    cout << "====== RENTA DE ACTIVOS ======" << endl;
    cout << "1. Iniciar sesion" << endl;
    cout << endl;
    cout << "Ingrese una opcion:   ";
}

// Funcion del admin para crear usuario
void registroUsario() {
    string nombreUsuario, contrasena, departamento, empresa;
    system("cls");
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
        cout << "8. Ordenar Transacciones" << endl;
        cout << "9. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            registroUsario();
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
void menuOpciones(const string& usuario) {
    int opcion;
    while (true) {
        cout << "=========== Bienvenido " << usuario << endl;
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
            registroUsario();
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
                menuOpciones(username);
            }else {
                cout << "Contra incorrecta ......" << endl;
                cout << "Usuario incorrecto  ......" << endl;
                cout << "Depto incorrecto  ......" << endl;
                cout << "Empresa incorrecto  ......" << endl;
            }
        }
    }
}


// Función para agregar un activo
void agregarActivo() {

}

//Funcion para eliminar un activo
void eliminarActivo() {
    cout << "ELIMINANDO SU ARCHIVO" << endl;
}

//Funcion para modificar un archivo
void modificarActivo() {
    cout << "MODIFICANDO SU ARCHIVO" << endl;
}

//Funcion para rentar un activo
void rentarActivo() {
    cout << "RENTANDO UN ACITVO" << endl;
}

//Funcion para mostrar los activos rentados
void activosRentados() {
    cout << "SUS ACTIVOS RENTADOS SON ....... " << endl;
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