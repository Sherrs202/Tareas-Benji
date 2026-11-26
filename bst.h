/*
 * bst.h
 *
 *  Created on: 12/10/2026
 *      Author: Gerardo Silva Esqueda
 */

#ifndef BST_H
#define BST_H

#include <string>
#include <sstream>

using namespace std;

template <class T>
class BST;

template <class T>
class TreeNode {
private:
    T value;
    TreeNode<T>* left;
    TreeNode<T>* right;

public:
    TreeNode(T);
    void add(T);
    void removeChilds();
    void preorder(stringstream&) const;
    void inorder(stringstream&) const;
    void postorder(stringstream&) const;
    void level_by_level(stringstream&, int) const;
    int height() const;

    friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T dato) : value(dato), left(0), right(0) {}

template <class T>
void TreeNode<T>::add(T dato) {
    if (dato < value) {
        if (left != 0) {
            left->add(dato);
        } else {
            left = new TreeNode<T>(dato);
        }
    } else {
        if (right != 0) {
            right->add(dato);
        } else {
            right = new TreeNode<T>(dato);
        }
    }
}

template <class T>
void TreeNode<T>::removeChilds() {
    if (left != 0) {
        left->removeChilds();
        delete left;
        left = 0;
    }
    if (right != 0) {
        right->removeChilds();
        delete right;
        right = 0;
    }
}

template <class T>
void TreeNode<T>::preorder(stringstream& salida) const {
    if (salida.tellp() != 1) {
        salida << " ";
    }
    salida << value;
    if (left != 0) {
        left->preorder(salida);
    }
    if (right != 0) {
        right->preorder(salida);
    }
}

template <class T>
void TreeNode<T>::inorder(stringstream& salida) const {
    if (left != 0) {
        left->inorder(salida);
    }
    if (salida.tellp() != 1) {
        salida << " ";
    }
    salida << value;
    if (right != 0) {
        right->inorder(salida);
    }
}

template <class T>
void TreeNode<T>::postorder(stringstream& salida) const {
    if (left != 0) {
        left->postorder(salida);
    }
    if (right != 0) {
        right->postorder(salida);
    }
    if (salida.tellp() != 1) {
        salida << " ";
    }
    salida << value;
}

template <class T>
void TreeNode<T>::level_by_level(stringstream& salida, int nivel) const {
    if (nivel == 1) {
        if (salida.tellp() != 1) {
            salida << " ";
        }
        salida << value;
    } else {
        if (left != 0) {
            left->level_by_level(salida, nivel - 1);
        }
        if (right != 0) {
            right->level_by_level(salida, nivel - 1);
        }
    }
}

template <class T>
int TreeNode<T>::height() const {
    int alturaIzquierda = 0;
    int alturaDerecha = 0;
    if (left != 0) {
        alturaIzquierda = left->height();
    }
    if (right != 0) {
        alturaDerecha = right->height();
    }
    return 1 + (alturaIzquierda > alturaDerecha ? alturaIzquierda : alturaDerecha);
}

template <class T>
class BST {
private:
    TreeNode<T>* root;

public:
    BST();
    ~BST();

    void add(T);
    string visit() const;
    int height() const;
    string ancestors(T) const;
    int whatlevelamI(T) const;
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
    if (root != 0) {
        root->removeChilds();
        delete root;
        root = 0;
    }
}

template <class T>
void BST<T>::add(T dato) {
    if (root != 0) {
        root->add(dato);
    } else {
        root = new TreeNode<T>(dato);
    }
}

template <class T>
string BST<T>::visit() const {
    stringstream preorden, inorden, postorden, porNiveles;
    int altura = height();

    preorden << "[";
    inorden << "[";
    postorden << "[";
    porNiveles << "[";
    if (root != 0) {
        root->preorder(preorden);
        root->inorder(inorden);
        root->postorder(postorden);
        for (int nivel = 1; nivel <= altura; nivel++) {
            root->level_by_level(porNiveles, nivel);
        }
    }
    preorden << "]";
    inorden << "]";
    postorden << "]";
    porNiveles << "]";

    return preorden.str() + "\n" + inorden.str() + "\n" +
           postorden.str() + "\n" + porNiveles.str();
}

template <class T>
int BST<T>::height() const {
    if (root == 0) {
        return 0;
    }
    return root->height();
}

template <class T>
string BST<T>::ancestors(T dato) const {
    stringstream salida;
    TreeNode<T>* actual = root;

    salida << "[";
    while (actual != 0 && actual->value != dato) {
        if (salida.tellp() != 1) {
            salida << " ";
        }
        salida << actual->value;
        if (dato < actual->value) {
            actual = actual->left;
        } else {
            actual = actual->right;
        }
    }
    if (actual == 0) {
        return "[]";
    }
    salida << "]";
    return salida.str();
}

template <class T>
int BST<T>::whatlevelamI(T dato) const {
    TreeNode<T>* actual = root;
    int nivel = 1;
    while (actual != 0) {
        if (actual->value == dato) {
            return nivel;
        }
        if (dato < actual->value) {
            actual = actual->left;
        } else {
            actual = actual->right;
        }
        nivel++;
    }
    return 0;
}

#endif
