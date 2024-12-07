//
// Created by velas on 11/06/2024.
//

#ifndef QUEUE_H
#define QUEUE_H
#include "nodoPasajeros.h"
#include <iostream>

class Queue {
private:
    nodoPasajeros* front;
    nodoPasajeros* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        while (front != nullptr) {
            nodoPasajeros* temp = front;
            front = front->next;
            delete temp;
        }
    }

    // Encolar un elemento
    void enqueue(pasajeros val) {
        nodoPasajeros* newNode = new nodoPasajeros(val);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    // Desencolar un elemento
    pasajeros dequeue() {
        if (front == nullptr) {
            std::cout << "Queue is empty!" << std::endl;
            return pasajeros(); // Retornar un objeto pasajeros vacío para indicar que la cola está vacía
        }
        nodoPasajeros* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        pasajeros data = temp->data;
        delete temp;
        size--;
        return data;
    }

    // Obtener el primer elemento
    pasajeros getFront() {
        if (front == nullptr) {
            std::cout << "Queue is empty!" << std::endl;
            return pasajeros(); // Retornar un objeto pasajeros vacío para indicar que la cola está vacía
        }
        return front->data;
    }

    // Verificar si la cola está vacía
    bool isEmpty() {
        return front == nullptr;
    }

    // Obtener el tamaño de la cola
    int getSize() {
        return size;
    }

    // Imprimir todos los elementos de la cola
    void printQueue() {
        if (isEmpty()) {
            std::cout << "Queue is empty!" << std::endl;
            return;
        }
        nodoPasajeros* temp = front;
        while (temp != nullptr) {
            std::cout << "Nombre: " << temp->data.nombre << ", "
                      << "Nacionalidad: " << temp->data.nacionalidad << ", "
                      << "Numero de Pasaporte: " << temp->data.numero_de_pasaporte << ", "
                      << "Vuelo: " << temp->data.vuelo << ", "
                      << "Asiento: " << temp->data.asiento << ", "
                      << "Destino: " << temp->data.destino << ", "
                      << "Origen: " << temp->data.origen << ", "
                      << "Equipaje Facturado: " << temp->data.equipaje_facturado
                      << std::endl;
            temp = temp->next;
        }
    }
    // Función para visualizar la cola usando Graphviz
    void visualizeQueue(const std::string& filename) {
        std::ofstream file(filename); // Abrir archivo para escritura
        if (!file.is_open()) {
            std::cerr << "Error al abrir el archivo para escritura: " << filename << std::endl;
            return;
        }

        // Escribir el encabezado del archivo DOT
        file << "digraph Queue {" << std::endl;
        file << "\trankdir=LR;" << std::endl; // Para que los nodos estén de izquierda a derecha

        // Escribir los nodos y conexiones
        nodoPasajeros* temp = front;
        while (temp != nullptr) {
            file << "\t\"" << temp << "\" [label=\"" << temp->data.nombre << "\"];" << std::endl;
            if (temp->next != nullptr) {
                file << "\t\"" << temp << "\" -> \"" << temp->next << "\";" << std::endl;
            }
            temp = temp->next;
        }

        // Escribir el cierre del archivo DOT
        file << "}" << std::endl;

        file.close(); // Cerrar el archivo
        std::cout << "Archivo DOT generado exitosamente: " << filename << std::endl;
    }
};

#endif //QUEUE_H
