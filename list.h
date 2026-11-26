/*
 * list.h
 *
 *  Created on: 28/09/2026
 *      Author: Gerardo Silva Esqueda
 */

#ifndef LIST_H
#define LIST_H

#include <sstream>
#include <string>

using namespace std;

template <class T>
class List;

template <class T>
class Link {
private:
    T value;
    Link<T>* next;

    Link(T);
    Link(T, Link<T>*);

    friend class List<T>;
};

template <class T>
class List {
private:
    Link<T>* head;
    int size;

public:
    List();
    ~List();

    void insertion(T);
    int search(T) const;
    void update(int, T);
    void deleteAt(int);
    string toString() const;

    bool empty() const;
    void clear();
};

template <class T>
Link<T>::Link(T dato) : value(dato), next(0) {}

template <class T>
Link<T>::Link(T dato, Link<T>* siguiente) : value(dato), next(siguiente) {}

template <class T>
List<T>::List() : head(0), size(0) {}

template <class T>
List<T>::~List() {
    clear();
}

template <class T>
bool List<T>::empty() const {
    return head == 0;
}

template <class T>
void List<T>::clear() {
    Link<T>* actual = head;
    while (actual != 0) {
        Link<T>* siguiente = actual->next;
        delete actual;
        actual = siguiente;
    }
    head = 0;
    size = 0;
}

template <class T>
void List<T>::insertion(T dato) {
    Link<T>* nuevo = new Link<T>(dato);
    if (empty()) {
        head = nuevo;
    } else {
        Link<T>* actual = head;
        while (actual->next != 0) {
            actual = actual->next;
        }
        actual->next = nuevo;
    }
    size++;
}

template <class T>
int List<T>::search(T dato) const {
    const Link<T>* actual = head;
    int indice = 0;
    while (actual != 0) {
        if (actual->value == dato) {
            return indice;
        }
        actual = actual->next;
        indice++;
    }
    return -1;
}

template <class T>
void List<T>::update(int indice, T dato) {
    if (indice < 0 || indice >= size) {
        return;
    }

    Link<T>* actual = head;
    int posicion = 0;
    while (posicion < indice) {
        actual = actual->next;
        posicion++;
    }
    actual->value = dato;
}

template <class T>
void List<T>::deleteAt(int indice) {
    if (indice < 0 || indice >= size) {
        return;
    }

    Link<T>* eliminado;
    if (indice == 0) {
        eliminado = head;
        head = head->next;
    } else {
        Link<T>* anterior = head;
        int posicion = 0;
        while (posicion < indice - 1) {
            anterior = anterior->next;
            posicion++;
        }
        eliminado = anterior->next;
        anterior->next = eliminado->next;
    }
    delete eliminado;
    size--;
}

template <class T>
string List<T>::toString() const {
    stringstream salida;
    const Link<T>* actual = head;
    salida << "[";
    while (actual != 0) {
        salida << actual->value;
        if (actual->next != 0) {
            salida << ", ";
        }
        actual = actual->next;
    }
    salida << "]";
    return salida.str();
}

#endif
