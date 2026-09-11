/*
 * sorts.h
 *
 *  Created on: 10/09/2026
 *      Author: Gerardo Silva Esqueda A01714794
 */

#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include <list>

using namespace std;

template <class T>
class Sorts {

private:
    void swap(vector<T>&, int, int);
    void copy_array(vector<T>&, vector<T>&, int, int);
    void merge_array(vector<T>&, vector<T>&, int, int, int);
    void merge_split(vector<T>&, vector<T>&, int, int);

public:
    vector<T> ordenaSeleccion(vector<T>&);
    vector<T> ordenaBurbuja(vector<T>&);
    vector<T> ordenaMerge(vector<T>&);
    int busqSecuencial(const vector<T>&, int);
    int busqBinaria(const vector<T>&, int);
};

template <class T>
void Sorts<T>::swap(vector<T>&v, int i, int j){
    T aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

template <class T>
vector<T> Sorts<T>::ordenaSeleccion(vector<T> &prueba){
    for (int i = 0; i < prueba.size() -1; i++) {
        int min = i;
        for (int j = i + 1; j < prueba.size(); j++) {
            if (prueba[j] < prueba[min]){
                min = j;
            }
        }
        if (min != i) {
            swap(prueba, i, min);
        }
    }
    return prueba;
}

template <class T>
vector<T> Sorts<T>::ordenaBurbuja(vector<T> &prueba){
    for (int i = prueba.size() - 1; i > 0; i--){
        for (int j = 0; j < i; j++) {
            if (prueba[j] > prueba[j + 1]) {
                swap(prueba, j, j + 1);
            }
        }
    }
    return prueba;
}

template <class T>
void Sorts<T>::copy_array(vector<T> &a, vector<T> &b, int low, int high) {
    for (int i = low; i <= high; i++){
        a[i] = b[i];
    }
}

template <class T>
void Sorts<T>::merge_array(vector<T> &a, vector<T> &b, int low, int mid, int high) {
    int i, j, k;

    i = low;
    j = mid + 1;
    k = low;

    while(i <= mid && j <= high){
        if (a[i] < a[j]){
            b[k] = a[i];
            i++;
        } else {
            b[k] = a[j];
            j++;
        }
        k++;
    }
    if (i > mid) {
        while(j <= high) {
            b[k++] = a[j];
            j++;
        }
    } else {
        while (i <= mid) {
            b[k++] = a[i];
            i++;
        }
    }
}

template <class T>
void Sorts<T>::merge_split(vector<T> &a, vector<T> &b, int low, int high) {
    int mid;

    if ((high - low) < 1) {
        return;
    }

    mid = (high + low) / 2;
    merge_split(a, b, low, mid);
    merge_split(a, b, mid + 1, high);
    merge_array(a, b, low, mid, high);
    copy_array(a, b, low, high);
}

template <class T>
vector<T> Sorts<T>::ordenaMerge(vector<T> &prueba){
    vector<T> tmp(prueba.size());
    merge_split(prueba, tmp, 0, prueba.size() - 1);
    return prueba;
}

template <class T>
int Sorts<T>::busqSecuencial(const vector<T> &prueba, int valor){
    int val = -1;
    for (int i = 0; i < prueba.size(); i++) {
        if (prueba[i] == valor) {
            val = i;
        }
    }
    return val;
}

template <class T>
int Sorts<T>::busqBinaria(const vector<T> &prueba, int valor) {
    int low, high, mid;
    low = 0;
    high = prueba.size() - 1;

    while (low <= high){
        mid = low + (high - low) / 2;
        
        if (prueba[mid] == valor) {
            return mid;
        } else if (valor < prueba[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return - 1;
}

#endif