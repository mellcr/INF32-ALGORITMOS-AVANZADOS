/* 
 * File:   main.cpp
 * Author: alulab14
 *
 * Created on 19 de septiembre de 2024, 11:48 AM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
int funlis(vector<int>&num, int n);
int funlisOptimizado(vector<int>& num, int n) ; 
/*
 * 
 */
int main(int argc, char** argv) {
    vector<int> numero = {-7, 10, 9, 2, 10, 15, 3, 20};
    int n = numero.size();

    //devuelve el maximo de elementos 
    cout << setw(3)<<funlis(numero, n);
    //cout << setw(3)<<funlisOptimizado(numero, n);

    return 0;
}

int funlis(vector<int>&num, int n) {
    int max = 1; //guardar el maximo (valor inicial 1)
    int Fn[n]; //lista resultante F(n)

    for (int i = 0; i < n; i++) {
        Fn[i] = 1;
        for (int j = 0; j < i; j++) {
            //busca la mejor solucion -> sirve para agarrar el cuadrado maximo 
            //(cumple que sea menor y su Fn es el mas alto hasta ese momento)
            if (num[i] > num[j] and Fn[j] + 1 > Fn[i]) //y vamos comparando la longitud anterior 
                Fn[i] = Fn[j] + 1; //aumentamos 1 
            //Fn[i]++; -> no es PD, no usa las anteriores
        }
        //guardamos el maximo 
        if (Fn[i] > max) max = Fn[i]; //variable importante para recordar el max valor obtenido 
    }

    /*Muestra las souciones parciales*/
    for (int i = 0; i < n; i++) {
        cout << setw(3) << Fn[i];
    }
    cout << endl;
    
    return max; //no necesariamente es el último Fn
}


int funlisOptimizado(vector<int>& num, int n) {
    vector<int> Fn(n, 1); // Inicializar Fn[] con 1 directamente
    int max_lis = 1;      // Guarda el valor máximo de LIS

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (num[i] > num[j]) {
                Fn[i] = max(Fn[i], Fn[j] + 1); // Actualiza Fn[i] directamente
            }
        }
        max_lis = max(max_lis, Fn[i]); // Actualiza el valor máximo
    }

    // Muestra las soluciones parciales
    for (int i = 0; i < n; i++) {
        cout << setw(3) << Fn[i];
    }
    cout << endl;

    return max_lis; // Retorna la longitud de la secuencia creciente más larga
}