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
#include <string>

using namespace std;

template <class T> class DList; 

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
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink<T>* prev, DLink<T>* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T>& source) : value(source.value), previous(source.previous), next(source.next) {}

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
    DLink<T> *head;
    DLink<T> *tail;
    int size;
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {clear();}

template <class T>
bool DList<T>::empty() const {return (head == 0);}

template <class T>
void DList<T>::clear() {
    DLink<T> *p = head;
    DLink<T> *q;

    while (p != 0) {
        q = p->next;
        delete p;
        p = q;
    }

    head = 0;
    tail = 0;
    size = 0;
}

template <class T>
void DList<T>::insertion(T val) {
    DLink<T> *newLink = new DLink<T>(val);

    if (empty()) {
        head = newLink;
        tail = newLink;
    } else {
        tail->next = newLink;
        newLink->previous = tail;
        tail = newLink;
    }
    size++;
}

template <class T>
int DList<T>::search(T val) const {
    DLink<T> *p = head;
    int index = 0;

    while (p != 0) {
        if (p->value == val) {return index;}
        p = p->next;
        index++;
    }
    return -1;
}

template <class T>
bool DList<T>::update(int index, T val) {
    if (index < 0 || index >= size) {return false;}
    DLink<T> *p = head;
    int pos = 0;

    while(pos != index) {
        p = p->next;
        pos++;
    }
    p->value = val;
    return true;
}

template <class T>
T DList<T>::deleteAt(int index) {
    if (index < 0 || index >= size) {
        return T();
    }
    DLink<T> *p;
    T val;

    if (index == 0) {
		p = head;
		val = p->value;
		if (head == tail) {
			head = 0;
			tail = 0;
		} else {
			head = head->next;
			head->previous = 0;
		}
		delete p;
	} else if (index == size - 1) {
		p = tail;
		val = p->value;
		tail = tail->previous;
		tail->next = 0;
		delete p;
	} else {
		p = head;
		int pos = 0;
		while (pos != index) {
			p = p->next;
			pos++;
		}
		val = p->value;
		p->previous->next = p->next;
		p->next->previous = p->previous;
		delete p;
	}

	size--;
	return val;
}

template <class T>
string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p = head;

	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p = tail;

	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

#endif