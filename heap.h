/*
 * heap.h
 * 
 * Created on: 3/11/2026
 * autor: Gerardo Silva Esqueda
 */
#ifndef HEAP_H_
#define HEAP_H_

#include <sstream>
#include <string>
#include "exception.h"

template <class T>
class Heap {
private:
    T* datos;
    unsigned int capacidad;
    unsigned int cantidad;

    unsigned int parent(unsigned int posicion) const;
    unsigned int left(unsigned int posicion) const;
    unsigned int right(unsigned int posicion) const;
    void swap(unsigned int primero, unsigned int segundo);
    void heapify(unsigned int posicion);

public:
    Heap(unsigned int limite);
    ~Heap();
    void push(T valor);
    void pop();
    T top() const;
    unsigned int size() const;
    bool empty() const;
    bool full() const;
    void add(T valor);
    T remove();
    void clear();
    std::string toString() const;
};

template <class T>
Heap<T>::Heap(unsigned int limite) : capacidad(limite), cantidad(0) {
    datos = new T[capacidad];
}

template <class T>
Heap<T>::~Heap() {
    delete[] datos;
}

template <class T>
unsigned int Heap<T>::size() const {
    return cantidad;
}

template <class T>
bool Heap<T>::empty() const {
    return cantidad == 0;
}

template <class T>
bool Heap<T>::full() const {
    return cantidad == capacidad;
}

template <class T>
unsigned int Heap<T>::parent(unsigned int posicion) const {
    return (posicion - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int posicion) const {
    return 2 * posicion + 1;
}

template <class T>
unsigned int Heap<T>::right(unsigned int posicion) const {
    return 2 * posicion + 2;
}

template <class T>
void Heap<T>::swap(unsigned int primero, unsigned int segundo) {
    T temporal = datos[primero];
    datos[primero] = datos[segundo];
    datos[segundo] = temporal;
}

template <class T>
void Heap<T>::push(T valor) {
    if (full()) {
        throw Overflow();
    }

    unsigned int posicion = cantidad;
    datos[posicion] = valor;
    cantidad++;
  
    while (posicion > 0 && datos[posicion] < datos[parent(posicion)]) {
        unsigned int padre = parent(posicion);
        swap(posicion, padre);
        posicion = padre;
    }
}

template <class T>
void Heap<T>::add(T valor) {
    push(valor);
}

template <class T>
void Heap<T>::heapify(unsigned int posicion) {

    if (posicion >= cantidad / 2) {
        return;
    }
    unsigned int menor = left(posicion);
    unsigned int derecho = right(posicion);
    if (derecho < cantidad && datos[derecho] < datos[menor]) {
        menor = derecho;
    }
    if (datos[menor] < datos[posicion]) {
        swap(posicion, menor);
        heapify(menor);
    }
}

template <class T>
T Heap<T>::top() const {
    if (empty()) {
        throw NoSuchElement();
    }
    return datos[0];
}

template <class T>
T Heap<T>::remove() {
    T minimo = top();
    cantidad--;
    if (cantidad > 0) {
        datos[0] = datos[cantidad];
        heapify(0);
    }
    return minimo;
}

template <class T>
void Heap<T>::pop() {
    remove();
}

template <class T>
void Heap<T>::clear() {
    cantidad = 0;
}

template <class T>
std::string Heap<T>::toString() const {
    std::stringstream salida;
    salida << "[";
    for (unsigned int i = 0; i < cantidad; i++) {
        if (i > 0) {
            salida << " ";
        }
        salida << datos[i];
    }
    salida << "]";
    return salida.str();
}

#endif
