/* 
 * File:   main.cpp
 * Author: alulab14
 *
 * Created on 19 de septiembre de 2024, 09:44 AM
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include "MochilaGanancia.h"

using namespace std;

void mochilaNormal(vector<int> &pesos, int capacidad, int n);

int main(int argc, char** argv) {
    vector<int> pesos = {1, 3, 4, 5};
    vector<int> ganancia = {10, 20, 50, 15};
    int n = pesos.size();
    int capacidad = 5; 

    //mochilaNormal(pesos, capacidad, n);
    //mochilaGanancia(pesos,ganancia,capacidad,n);
    mochilaMinima(pesos,ganancia,capacidad,n);
    return 0;
}

void mochilaNormal(vector<int> &pesos, int capacidad, int n) {
    int dp[n + 1][capacidad + 1];

    // INICIALIZACION
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1; // Siempre es posible hacer una suma de 0 con el subconjunto vacío
    }
    for (int j = 1; j <= capacidad; j++) {
        dp[0][j] = 0; // No es posible hacer una suma positiva sin elementos
    }

    // LLENADO DE LA TABLA DP
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= capacidad; j++) {
            dp[i][j] = dp[i - 1][j]; // No tomar el elemento actual
            if (pesos[i - 1] <= j and dp[i][j]==0) {
                dp[i][j] = dp[i - 1][j - pesos[i - 1]]; // Tomar el elemento si cabe
            }
        }
    }

    // IMPRESION DE LA MATRIZ DP
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= capacidad; j++) {
            cout << setw(5)<< dp[i][j];
        }
        cout << endl;
    }
}
