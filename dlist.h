/*
 * dlist.h
 *
 *  Created on: 10/01/2026
 *      Author: Gerardo Silva Esqueda
 */

#ifndef DLIST_H
#define DLIST_H

#include <string>
#include <sstream>

using namespace std;

template <class T>
class DList;

template <class T>
class DLink {
private:
    DLink(T);
    DLink(T, DLink<T>*, DLink<T>*);
    DLink(const DLink<T>&);

    T value;
    DLink<T>* previous;
    DLink<T>* next;

    friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T dato) : value(dato), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T dato, DLink<T>* anterior, DLink<T>* siguiente)
    : value(dato), previous(anterior), next(siguiente) {}

template <class T>
DLink<T>::DLink(const DLink<T>& origen)
    : value(origen.value), previous(origen.previous), next(origen.next) {}

template <class T>
class DList {
public:
    DList();
    ~DList();

    void insertion(T);
    int search(T) const;
    bool update(int, T);
    T deleteAt(int);

    string toStringForward() const;
    string toStringBackward() const;

    bool empty() const;
    void clear();

private:
    DLink<T>* head;
    DLink<T>* tail;
    int size;
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {
    clear();
}

template <class T>
bool DList<T>::empty() const {
    return head == 0;
}

template <class T>
void DList<T>::clear() {
    DLink<T>* actual = head;
    while (actual != 0) {
        DLink<T>* siguiente = actual->next;
        delete actual;
        actual = siguiente;
    }

    head = 0;
    tail = 0;
    size = 0;
}

template <class T>
void DList<T>::insertion(T dato) {
    DLink<T>* nuevo = new DLink<T>(dato);
    if (empty()) {
        head = nuevo;
        tail = nuevo;
    } else {
        tail->next = nuevo;
        nuevo->previous = tail;
        tail = nuevo;
    }
    size++;
}

template <class T>
int DList<T>::search(T dato) const {
    DLink<T>* actual = head;
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
bool DList<T>::update(int indice, T dato) {
    if (indice < 0 || indice >= size) {
        return false;
    }

    DLink<T>* actual = head;
    int posicion = 0;
    while (posicion != indice) {
        actual = actual->next;
        posicion++;
    }
    actual->value = dato;
    return true;
}

template <class T>
T DList<T>::deleteAt(int indice) {
    if (indice < 0 || indice >= size) {
        return T();
    }

    DLink<T>* eliminado;
    T dato;
    if (indice == 0) {
        eliminado = head;
        dato = eliminado->value;
        if (head == tail) {
            head = 0;
            tail = 0;
        } else {
            head = head->next;
            head->previous = 0;
        }
    } else if (indice == size - 1) {
        eliminado = tail;
        dato = eliminado->value;
        tail = tail->previous;
        tail->next = 0;
    } else {
        eliminado = head;
        int posicion = 0;
        while (posicion != indice) {
            eliminado = eliminado->next;
            posicion++;
        }
        dato = eliminado->value;
        eliminado->previous->next = eliminado->next;
        eliminado->next->previous = eliminado->previous;
    }

    delete eliminado;
    size--;
    return dato;
}

template <class T>
string DList<T>::toStringForward() const {
    stringstream salida;
    DLink<T>* actual = head;

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

template <class T>
string DList<T>::toStringBackward() const {
    stringstream salida;
    DLink<T>* actual = tail;

    salida << "[";
    while (actual != 0) {
        salida << actual->value;
        if (actual->previous != 0) {
            salida << ", ";
        }
        actual = actual->previous;
    }
    salida << "]";
    return salida.str();
}

#endif
