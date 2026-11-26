/*
 * splay.h
 *   Created on: 12/10/2026
 *      Author: Gerardo Silva Esqueda 
 */
#ifndef SPLAY_H
#define SPLAY_H

#include <sstream>
#include <string>

template <class T> class SplayTree;

template <class T>
class Node {
private:
    T valor;
    Node<T>* izquierda;
    Node<T>* derecha;
    Node<T>* padre;

    Node(T dato, Node<T>* padreInicial)
        : valor(dato), izquierda(0), derecha(0), padre(padreInicial) {}

    friend class SplayTree<T>;
};

template <class T>
class SplayTree {
private:
    Node<T>* raiz;

    Node<T>* buscarUltimo(T dato) const;
    void reemplazar(Node<T>* anterior, Node<T>* nuevo);
    void rotarDerecha(Node<T>* nodo);
    void rotarIzquierda(Node<T>* nodo);
    void splay(Node<T>* nodo);
    void liberar(Node<T>* nodo);
    void inorden(Node<T>* nodo, std::stringstream& salida) const;
    void preorden(Node<T>* nodo, std::stringstream& salida) const;
    void imprimirNodo(Node<T>* nodo, std::stringstream& salida) const;

public:
    SplayTree();
    ~SplayTree();
    bool empty() const;
    void add(T dato);
    bool find(T dato);
    void remove(T dato);
    void removeAll();
    std::string inorder() const;
    std::string preorder() const;
    std::string print_tree() const;
};

template <class T>
SplayTree<T>::SplayTree() : raiz(0) {}

template <class T>
SplayTree<T>::~SplayTree() {
    removeAll();
}

template <class T>
bool SplayTree<T>::empty() const {
    return raiz == 0;
}

template <class T>
Node<T>* SplayTree<T>::buscarUltimo(T dato) const {
    Node<T>* actual = raiz;
    Node<T>* ultimo = 0;
    while (actual != 0) {
        ultimo = actual;
        if (dato == actual->valor) {
            return actual;
        }
        if (dato < actual->valor) {
            actual = actual->izquierda;
        } else {
            actual = actual->derecha;
        }
    }
    return ultimo;
}

template <class T>
void SplayTree<T>::reemplazar(Node<T>* anterior, Node<T>* nuevo) {
    Node<T>* padre = anterior->padre;
    if (padre == 0) {
        raiz = nuevo;
    } else if (anterior == padre->izquierda) {
        padre->izquierda = nuevo;
    } else {
        padre->derecha = nuevo;
    }
    if (nuevo != 0) {
        nuevo->padre = padre;
    }
}

template <class T>
void SplayTree<T>::rotarDerecha(Node<T>* nodo) {
    Node<T>* sube = nodo->izquierda;
    nodo->izquierda = sube->derecha;
    if (nodo->izquierda != 0) {
        nodo->izquierda->padre = nodo;
    }
    reemplazar(nodo, sube);
    sube->derecha = nodo;
    nodo->padre = sube;
}

template <class T>
void SplayTree<T>::rotarIzquierda(Node<T>* nodo) {
    Node<T>* sube = nodo->derecha;
    nodo->derecha = sube->izquierda;
    if (nodo->derecha != 0) {
        nodo->derecha->padre = nodo;
    }
    reemplazar(nodo, sube);
    sube->izquierda = nodo;
    nodo->padre = sube;
}

template <class T>
void SplayTree<T>::splay(Node<T>* nodo) {
    while (nodo->padre != 0) {
        Node<T>* padre = nodo->padre;
        Node<T>* abuelo = padre->padre;
        if (abuelo == 0) {
      
            if (nodo == padre->izquierda) {
                rotarDerecha(padre);
            } else {
                rotarIzquierda(padre);
            }
        } else if (padre == abuelo->izquierda && nodo == padre->izquierda) {
        
            rotarDerecha(abuelo);
            rotarDerecha(padre);
        } else if (padre == abuelo->derecha && nodo == padre->derecha) {
            rotarIzquierda(abuelo);
            rotarIzquierda(padre);
        } else if (nodo == padre->derecha) {
    
            rotarIzquierda(padre);
            rotarDerecha(abuelo);
        } else {
            rotarDerecha(padre);
            rotarIzquierda(abuelo);
        }
    }
}

template <class T>
void SplayTree<T>::add(T dato) {
    Node<T>* padre = buscarUltimo(dato);
    if (padre != 0 && padre->valor == dato) {
        splay(padre);
        return;
    }
    Node<T>* nuevo = new Node<T>(dato, padre);
    if (padre == 0) {
        raiz = nuevo;
    } else if (dato < padre->valor) {
        padre->izquierda = nuevo;
    } else {
        padre->derecha = nuevo;
    }
    splay(nuevo);
}

template <class T>
bool SplayTree<T>::find(T dato) {
    Node<T>* ultimo = buscarUltimo(dato);
    if (ultimo == 0) {
        return false;
    }
    splay(ultimo);
    return raiz->valor == dato;
}

template <class T>
void SplayTree<T>::remove(T dato) {
    Node<T>* eliminado = buscarUltimo(dato);
    if (eliminado == 0) {
        return;
    }
    if (!(eliminado->valor == dato)) {
        splay(eliminado);
        return;
    }

    Node<T>* padre = eliminado->padre;
    if (eliminado->izquierda == 0) {
        reemplazar(eliminado, eliminado->derecha);
    } else if (eliminado->derecha == 0) {
        reemplazar(eliminado, eliminado->izquierda);
    } else {
    
        Node<T>* sucesor = eliminado->derecha;
        while (sucesor->izquierda != 0) {
            sucesor = sucesor->izquierda;
        }
        if (sucesor != eliminado->derecha) {
            reemplazar(sucesor, sucesor->derecha);
            sucesor->derecha = eliminado->derecha;
            sucesor->derecha->padre = sucesor;
        }
        reemplazar(eliminado, sucesor);
        sucesor->izquierda = eliminado->izquierda;
        sucesor->izquierda->padre = sucesor;
    }
    delete eliminado;


    if (padre != 0) {
        splay(padre);
    }
}

template <class T>
void SplayTree<T>::liberar(Node<T>* nodo) {
    if (nodo != 0) {
        liberar(nodo->izquierda);
        liberar(nodo->derecha);
        delete nodo;
    }
}

template <class T>
void SplayTree<T>::removeAll() {
    liberar(raiz);
    raiz = 0;
}

template <class T>
void SplayTree<T>::inorden(Node<T>* nodo, std::stringstream& salida) const {
    if (nodo != 0) {
        inorden(nodo->izquierda, salida);
        if (salida.tellp() != 1) {
            salida << " ";
        }
        salida << nodo->valor;
        inorden(nodo->derecha, salida);
    }
}

template <class T>
void SplayTree<T>::preorden(Node<T>* nodo, std::stringstream& salida) const {
    if (nodo != 0) {
        if (salida.tellp() != 1) {
            salida << " ";
        }
        salida << nodo->valor;
        preorden(nodo->izquierda, salida);
        preorden(nodo->derecha, salida);
    }
}

template <class T>
std::string SplayTree<T>::inorder() const {
    std::stringstream salida;
    salida << "[";
    inorden(raiz, salida);
    salida << "]";
    return salida.str();
}

template <class T>
std::string SplayTree<T>::preorder() const {
    std::stringstream salida;
    salida << "[";
    preorden(raiz, salida);
    salida << "]";
    return salida.str();
}

template <class T>
void SplayTree<T>::imprimirNodo(Node<T>* nodo, std::stringstream& salida) const {
    if (nodo == 0) {
        return;
    }
    if (nodo->padre == 0) {
        salida << "\n root " << nodo->valor;
    } else {
        salida << "\n node " << nodo->valor << " parent " << nodo->padre->valor;
    }
    if (nodo->izquierda != 0) {
        salida << " left " << nodo->izquierda->valor;
    }
    if (nodo->derecha != 0) {
        salida << " right " << nodo->derecha->valor;
    }
    salida << "\n";
    imprimirNodo(nodo->izquierda, salida);
    imprimirNodo(nodo->derecha, salida);
}

template <class T>
std::string SplayTree<T>::print_tree() const {
    std::stringstream salida;
    salida << "\n ================================ ";
    imprimirNodo(raiz, salida);
    salida << " ================================ \n";
    return salida.str();
}

#endif



