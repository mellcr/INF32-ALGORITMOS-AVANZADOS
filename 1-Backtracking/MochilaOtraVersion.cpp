/* 
 * File:   main.cpp
 * Author: BlueCod 
 * Created on 2 de setiembre de 2024, 2:20 p. m.
 */
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define N 4

void imprimesol(int sol[N], int n, int *paq) {
    for(int i = 0; i < n; i++) {
        if(sol[i] == 1) {
            cout << paq[i] << " ";
        }
    }
    cout << endl; // Asegúrate de que la salida sea legible
}

int empaca(int i, int n, int peso, int *paq, int sol[N]) {
    
    if(i == n || peso < 0) return 0;
    
    int num = paq[i]; 
    
    // encuentra solucion posible
    if(num == peso) {
        sol[i] = 1;
        imprimesol(sol, n, paq); // Imprimir la solución encontrada
        sol[i] = 0; // Limpia el estado antes de regresar
        return 1;
    }

    // peso - paq[i] -> usa el paquete
    sol[i] = 1; // marcamos este paquete
    if(empaca(i + 1, n, peso - paq[i], paq, sol)) {
        return 1; // es una posible solución usar este paquete
    }

    // ya no considera el paquete
    sol[i] = 0; // desmarcamos este paquete
    if(empaca(i + 1, n, peso, paq, sol)) {
        return 1;    
    }
    
    return 0; // no se encontró solución
}

int main(int argc, char** argv) {
    int n = 4, peso = 15;
    int paq[] = {1, 3, 12, 5};
    int sol[N] = {};  // Inicializamos el array de solución

    empaca(0, n, peso, paq, sol);
    
    return 0;
}
