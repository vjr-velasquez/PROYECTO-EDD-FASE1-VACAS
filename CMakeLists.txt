cmake_minimum_required(VERSION 3.28)
project(CLionProjects)

set(CMAKE_CXX_STANDARD 17)

add_executable(CLionProjects main.cpp
        matrizDispersa.h
        usuario.h
        avl_tree.h
        activos.h)
