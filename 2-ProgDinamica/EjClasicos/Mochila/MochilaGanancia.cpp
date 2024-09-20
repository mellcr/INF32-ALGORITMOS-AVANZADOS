/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "MochilaGanancia.h"

using namespace std;

void mochilaGanancia(vector<int> &pesos,vector<int> &ganancias, int capacidad, int n){
    int dp[n + 1][capacidad + 1];

    // INICIALIZACION
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0; // gananc 0 
    }
    for (int j = 1; j <= capacidad; j++) {
        dp[0][j] = 0;  // gananc 0 
    }

    // LLENADO DE LA TABLA DP
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= capacidad; j++) {
            if(j<pesos[i-1]){
                dp[i][j] = dp[i-1][j];
            }
            else{
                dp[i][j]=max(ganancias[i-1]+dp[i-1][j-pesos[i-1]],
                        dp[i-1][j]);
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


void mochilaMinima(vector<int> &pesos,vector<int> &ganancias, int capacidad, int n){
    int dp[n + 1][capacidad + 1];

    // INICIALIZACION
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0; // gananc 0 
    }
    for (int j = 1; j <= capacidad; j++) {
        dp[0][j] = j;  // gananc 0 
    }

    // LLENADO DE LA TABLA DP
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= capacidad; j++) {
            if(j<pesos[i-1]){
                dp[i][j] = dp[i-1][j];
            }
            else{
                //analizamos sobrante y el anterior
                dp[i][j]=min(dp[i-1][j-pesos[i-1]],
                        dp[i-1][j]);
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


