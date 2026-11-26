/*
 * sorts.h
 *
 *  Created on: 10/09/2026
 *      Author: Gerardo Silva Esqueda A01714794
 */

#ifndef SORTS_H
#define SORTS_H

#include <cstddef>
#include <vector>

using namespace std;

template <class T>
class Sorts {
private:
    void swap(vector<T>&, size_t, size_t);
    void copy_array(vector<T>&, vector<T>&, size_t, size_t);
    void merge_array(vector<T>&, vector<T>&, size_t, size_t, size_t);
    void merge_split(vector<T>&, vector<T>&, size_t, size_t);

public:
    vector<T> ordenaSeleccion(vector<T>&);
    vector<T> ordenaBurbuja(vector<T>&);
    vector<T> ordenaMerge(vector<T>&);
    int busqSecuencial(const vector<T>&, int);
    int busqBinaria(const vector<T>&, int);
};

template <class T>
void Sorts<T>::swap(vector<T>& datos, size_t i, size_t j) {
    T temporal = datos[i];
    datos[i] = datos[j];
    datos[j] = temporal;
}

template <class T>
vector<T> Sorts<T>::ordenaSeleccion(vector<T>& datos) {
    for (size_t i = 0; i + 1 < datos.size(); i++) {
        size_t indiceMenor = i;
        for (size_t j = i + 1; j < datos.size(); j++) {
            if (datos[j] < datos[indiceMenor]) {
                indiceMenor = j;
            }
        }
        if (indiceMenor != i) {
            swap(datos, i, indiceMenor);
        }
    }
    return datos;
}

template <class T>
vector<T> Sorts<T>::ordenaBurbuja(vector<T>& datos) {
    for (size_t limite = datos.size(); limite > 1; limite--) {
        for (size_t j = 0; j + 1 < limite; j++) {
            if (datos[j] > datos[j + 1]) {
                swap(datos, j, j + 1);
            }
        }
    }
    return datos;
}

template <class T>
void Sorts<T>::copy_array(vector<T>& datos, vector<T>& auxiliar,
                          size_t inicio, size_t fin) {
    for (size_t i = inicio; i <= fin; i++) {
        datos[i] = auxiliar[i];
    }
}

template <class T>
void Sorts<T>::merge_array(vector<T>& datos, vector<T>& auxiliar,
                           size_t inicio, size_t medio, size_t fin) {
    size_t izq = inicio;
    size_t der = medio + 1;
    size_t pos = inicio;

    while (izq <= medio && der <= fin) {
        if (datos[izq] < datos[der]) {
            auxiliar[pos] = datos[izq];
            izq++;
        } else {
            auxiliar[pos] = datos[der];
            der++;
        }
        pos++;
    }
auxiliar[pos++] = datos[der++];
    }
}

template <class T>
void Sorts<T>::merge_split(vector<T>& datos, vector<T>& auxiliar,
                           size_t inicio, size_t fin) {
    if (inicio >= fin) {
        return;
    }

    size_t medio = inicio + (fin - inicio) / 2;
    merge_split(datos, auxiliar, inicio, medio);
    merge_split(datos, auxiliar, medio + 1, fin);
    merge_array(datos, auxiliar, inicio, medio, fin);
    copy_array(datos, auxiliar, inicio, fin);
}

template <class T>
vector<T> Sorts<T>::ordenaMerge(vector<T>& datos) {
    if (datos.size() > 1) {
        vector<T> auxiliar(datos.size());
        merge_split(datos, auxiliar, 0, datos.size() - 1);
    }
    return datos;
}

template <class T>
int Sorts<T>::busqSecuencial(const vector<T>& datos, int valor) {
    int posicion = -1;
    for (size_t i = 0; i < datos.size(); i++) {
        if (datos[i] == valor) {
            posicion = static_cast<int>(i);
        }
    }
    return posicion;
}

template <class T>
int Sorts<T>::busqBinaria(const vector<T>& datos, int valor) {
    ptrdiff_t inicio = 0;
    ptrdiff_t fin = static_cast<ptrdiff_t>(datos.size()) - 1;

    while (inicio <= fin) {
        ptrdiff_t medio = inicio + (fin - inicio) / 2;
        if (datos[medio] == valor) {
            return static_cast<int>(medio);
        } else if (valor < datos[medio]) {
            fin = medio - 1;
        } else {
            inicio = medio + 1;
        }
    }
    return -1;
}

#endif

    while (izq <= medio) {
        auxiliar[pos++] = datos[izq++];
    }
    while (der <= fin) {
