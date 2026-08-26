/*
 * main.cpp
 *
 *  Created on: 25/08/2026
 *      Author: Gerardo Silva
 */

 #ifndef FUNCIONES_H
 #define FUNCIONES_H

class Funciones {
    public :
    int long sumaIterativa (int n){
        int acum = 0;
        for (int i =0 ; i <= n ; i++){
            acum += i;
        }
        return acum ;
    }

    int long sumaRecursiva (int n){
        if (n == 1){
            return 1;
        }
        return n + sumaRecursiva (n-1);
    }

    int long sumaDirecta (int n){
        return (n * (n+1)) /2;
    }

};

 #endif