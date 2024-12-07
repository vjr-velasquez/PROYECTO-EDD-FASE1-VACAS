#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <nlohmann/json.hpp>
#include "../untitled/listas/listaDobleCircular.h"
#include "../untitled/listas/Queue.h"
#include "../untitled/listas/pila.h"
using json = nlohmann::json;

using namespace std;
listaDobleCircular avionesLista;
listaDobleCircular avionesMantenimiento;
Queue colaPasajeros;
pila pilaEquipaje;

void cargaAviones() {
    std::ifstream archivo_json("C:/Users/velas/OneDrive/Escritorio/202100054_EDD_Practica-main/aviones.json");

    // Verifica si el archivo se pudo abrir

    if (!archivo_json) {
        std::cerr << "No se pudo abrir el archivo data.json" << std::endl;
        return;
    }
    // Lee el contenido del archivo en una cadena
    std::string json_data((std::istreambuf_iterator<char>(archivo_json)), std::istreambuf_iterator<char>());

    // Verifica si el contenido del archivo no está vacío
    if (json_data.empty()) {
        std::cerr << "El archivo data.json está vacío" << std::endl;
        return;
    }
    try {
        // Parsear el JSON
        nlohmann::json data = nlohmann::json::parse(json_data);


        // Acceso a los objetos dentro del JSON

        for (const auto& vuelo : data) {
            std :: string estado = vuelo["estado"];
            if(estado.compare("Disponible") == 0) {
                aviones avion = {vuelo["vuelo"],vuelo["numero_de_registro"],vuelo["modelo"],vuelo["fabricante"],vuelo["ano_fabricacion"],vuelo["capacidad"],vuelo["peso_max_despegue"],vuelo["aerolinea"],vuelo["estado"]};
                avionesLista.agregarAvion(avion);
            }else if (estado.compare("Mantenimiento") == 0) {
                aviones avion = {vuelo["vuelo"],vuelo["numero_de_registro"],vuelo["modelo"],vuelo["fabricante"],vuelo["ano_fabricacion"],vuelo["capacidad"],vuelo["peso_max_despegue"],vuelo["aerolinea"],vuelo["estado"]};
                avionesMantenimiento.agregarAvion(avion);
            }

        }
        avionesLista.imprimirLista();
        avionesMantenimiento.imprimirLista();

    } catch (nlohmann::json::parse_error& e) {
        std::cerr << "Error de análisis JSON: " << e.what() << std::endl;
    }

}

void cargaPasajeros() {
    cout << "Cargando pasajeros...." << endl;

    std::ifstream archivo_json("C:/Users/velas/OneDrive/Escritorio/202100054_EDD_Practica-main/pasajeros.json");

    // Verifica si el archivo se pudo abrir
    if (!archivo_json) {
        std::cerr << "No se pudo abrir el archivo data.json" << std::endl;
        return;
    }
    // Lee el contenido del archivo en una cadena
    std::string json_data((std::istreambuf_iterator<char>(archivo_json)), std::istreambuf_iterator<char>());

    // Verifica si el contenido del archivo no está vacío
    if (json_data.empty()) {
        std::cerr << "El archivo data.json está vacío" << std::endl;
        return;
    }
    try {
        // Parsear el JSON
        nlohmann::json data = nlohmann::json::parse(json_data);

        // Acceso a los objetos dentro del JSON
        for (const auto& pasajero : data) {
            pasajeros personas = {pasajero["nombre"], pasajero["nacionalidad"], pasajero["numero_de_pasaporte"], pasajero["vuelo"], pasajero["asiento"], pasajero["destino"], pasajero["origen"], pasajero["equipaje_facturado"]};
            colaPasajeros.enqueue(personas);
        }
        colaPasajeros.printQueue();

    } catch (nlohmann::json::parse_error& e) {
        std::cerr << "Error de análisis JSON: " << e.what() << std::endl;
    }
}

void cargaMovimientos() {
    cout << "Cargando movimientos" << endl;
    // Nombre del archivo
    std::string nombreArchivo = "C:/Users/velas/OneDrive/Escritorio/202100054_EDD_Practica-main/movimientos - copia.txt";

    // Crear un objeto ifstream para leer el archivo
    std::ifstream archivo(nombreArchivo);

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;

    }else {

        // Leer el contenido del archivo línea por línea
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::cout << linea << std::endl; // Imprimir cada línea en la consola
            if(linea.compare("IngresoEquipajes;") == 0) {
                pasajeros eliminar = colaPasajeros.dequeue();
                if(eliminar.equipaje_facturado != 0) {
                    equipaje x1 = {eliminar.nombre,eliminar.destino,eliminar.equipaje_facturado};
                    pilaEquipaje.apilar(x1);
                }

            }
        }
        std::cout << endl;
        pilaEquipaje.imprimirPila();
        std::cout << endl;
        colaPasajeros.printQueue();

        // Cerrar el archivo
        archivo.close();
    }

}

void consultaPasajeros() {
    cout << "Consultando la cantidad de pasajeros" << endl;
}

void visualizarReportes() {
    cout << "Visualizando reportes" << endl;
    pilaEquipaje.graficarPila("grafica1");
    colaPasajeros.visualizeQueue("grafica2");
    avionesLista.visualizarLista("grafica3");
    avionesMantenimiento.visualizarLista("grafica4");


}

int main() {

    int opcion;
    do {
        cout<< "------ MENU DE OPCIONES ------ "<< endl;
        cout << "1. Cargar aviones" << endl;
        cout << "2. Cargar de Pilotos" << endl;
        cout << "3. Carga de rutas" << endl;
        cout << "4. Carga de movimientos" << endl;
        cout << "5. Consulta de horas de vuelo (pilotos)" << endl;
        cout << "6. Recomendaciones de ruta " << endl;
        cout <<"7. Visualizar reportes "<< endl;
        cout<< "---------------------------------"<< endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cargaAviones();
            break;
            case 2:
                cargaPasajeros();
            break;
            case 3:
                cargaMovimientos();
            break;
            case 4:
                consultaPasajeros();
            break;
            case 5:
                visualizarReportes();
            break;
            case 6:
                cout << "Saliendo..." << endl;
            break;
            default:
                cout << "Opcion invalida" << endl;
            break;
        }
    } while (opcion != 6);
    return 0;
}

