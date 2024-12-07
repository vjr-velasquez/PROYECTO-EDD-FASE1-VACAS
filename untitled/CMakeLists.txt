cmake_minimum_required(VERSION 3.10)
project(ReadJSON)

set(CMAKE_CXX_STANDARD 11)

# Incluye el archivo de configuración de vcpkg
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Encuentra el paquete nlohmann_json
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(ReadJSON main.cpp
        listas/aviones.h
        listas/nodoAviones.h
        listas/listaDobleCircular.h
        listas/pasajeros.h
        listas/nodoPasajeros.h
        listas/Queue.h
        listas/pila.h
        listas/nodoEquipaje.h
        listas/equipaje.h
        listas/pilotos.h
        listas/nodoPilotos.h
        [EDD]Proyecto1_202100054.cpp
        [EDD]Proyecto1_202100054/main.cpp
)

# Enlaza la biblioteca nlohmann_json con tu ejecutable
target_link_libraries(ReadJSON PRIVATE nlohmann_json::nlohmann_json)
