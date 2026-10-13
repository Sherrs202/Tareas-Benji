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

template <class T> class BST;

template <class T> 
class TreeNode {
private:
    T value;
    TreeNode *left, *right;

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
TreeNode<T>::TreeNode(T val) : value(val), left(0), right(0) {}

template <class T>
void TreeNode<T>::add(T val) {
    if (val < value) {
        if (left != 0) {
            left->add(val);
        } else {
            left = new TreeNode<T> (val);
        }
    } else {
        if (right != 0) {
            right->add(val);
        } else {
            right = new TreeNode<T>(val);
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
void TreeNode<T>::preorder(stringstream& aux) const {
    if (aux.tellp() != 1) {
        aux << " ";
    }
    aux  << value;
    if (left != 0) {
        left->preorder(aux);
    }
    if (right != 0) {
        right->preorder(aux);
    }
}

template <class T>
void TreeNode<T>::inorder(stringstream& aux) const {
    if (left != 0) {
        left->inorder(aux);
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }
    aux << value;
    if (right != 0) {
        right->inorder(aux);
    }
}

template <class T>
void TreeNode<T>::postorder(stringstream& aux) const {
    if (left != 0) {
        left->postorder(aux);
    }
    if (right != 0) {
        right->postorder(aux);
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }
    aux << value;
}

template <class T>
void TreeNode<T>::level_by_level(stringstream& aux, int level) const {
    if (level == 1) {
        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << value;
    } else {
        if (left != 0) {
            left->level_by_level(aux, level - 1);
        }
        if (right != 0) {
            right->level_by_level(aux, level - 1);
        }
    }
}


template <class T>
int TreeNode<T>::height() const {
    int lheight = 0, rheight = 0;

    if (left != 0) {
        lheight = left->height();
    }
    if (right != 0) {
        rheight = right->height();
    }
    return 1 + (lheight > rheight ? lheight : rheight);
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
void BST<T>::add(T val) {
    if (root != 0) {
        root->add(val);
    } else {
        root = new TreeNode<T>(val);
    }
}

template <class T>
string BST<T>::visit() const {
    stringstream pre, ino, post, levels;
    int h = height();

    pre << "[";
    ino << "[";
    post << "[";
    levels << "[";
    if (root != 0) {
        root->preorder(pre);
        root->inorder(ino);
        root->postorder(post);

        for (int i = 1; i <= h; i++) {
            root->level_by_level(levels, i);
        }
    }
    pre << "]";
    ino << "]";
    post << "]";
    levels << "]";

    return pre.str() + "\n" + ino.str() + "\n" + post.str() + "\n" + levels.str();
}

template <class T>
int BST<T>::height() const {
    if (root == 0) return 0;
    return root->height();
}

template <class T>
string BST<T>::ancestors(T val) const {
    stringstream aux;
    TreeNode<T>* actual = root;

    aux << "[";
    while (actual != 0 && actual->value != val) {
		if (aux.tellp() != 1) {
			aux << " ";
		}
		aux << actual->value;
		if (val < actual->value) {
			actual = actual->left;
		} else {
			actual = actual->right;
		}
	}
	if (actual == 0) {
		return "[]";
	}
	aux << "]";
	return aux.str();
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
	TreeNode<T> *actual = root;
	int level = 1;

	while (actual != 0) {
		if (actual->value == val) {
			return level;
		}
		if (val < actual->value) {
			actual = actual->left;
		} else {
			actual = actual->right;
		}
		level++;
	}
	return 0;
}

#endif