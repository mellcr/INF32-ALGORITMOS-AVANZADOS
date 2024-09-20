/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 19 de setiembre de 2024, 6:03 p. m.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
int versionBooleana(vector<int>& A, int n) ;
int sumaSubConjMinimaAcumulado(vector<int>& A, int n);

int main() {
    vector<int> A = {3, 7, 13, 6};
    int n = A.size();
    
    cout << "La diferencia mínima es: " << sumaSubConjMinimaAcumulado(A, n) << endl;
    //cout << "La diferencia mínima es: " << versionBooleana(A, n) << endl;

    return 0;
}


int sumaSubConjMinimaAcumulado(vector<int>& A, int n) {
    int sumaTotal = 0;
    
    // Calculamos la suma total del conjunto
    for (int i = 0; i < n; i++) {
        sumaTotal += A[i];
    }

    // Capacidad máxima del "subconjunto" es la mitad de la suma total
    int capacidad = sumaTotal / 2;
    // Matriz DP para almacenar si se puede lograr un subconjunto con una suma dada
    vector<vector<int>> dp(n + 1, vector<int>(capacidad + 1, 0));
    

    // Llenado de la tabla DP
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= capacidad; j++) {
            // cap > peso 
            if (j >= A[i-1]) { //el peso entra 
                // cap (j) >= peso
                dp[i][j] = max(dp[i-1][j],A[i-1]+dp[i-1][j-A[i-1]]);
            } else { 
                // cap (j) < peso 
                dp[i][j] = dp[i-1][j]; //simplemente el anterior
            }
        }
    }

    // La diferencia mínima entre los dos subconjuntos
    int sumaMaximaSubconjunto = dp[n][capacidad]; 
    int diferenciaMinima = sumaTotal - 2 * sumaMaximaSubconjunto;

    return diferenciaMinima;
}

int versionBooleana(vector<int>& A, int n) {
    int sumaTotal = 0;
    
    // Calculamos la suma total del conjunto
    for (int i = 0; i < n; i++) {
        sumaTotal += A[i];
    }

    // Capacidad máxima del "subconjunto" es la mitad de la suma total
    int capacidad = sumaTotal / 2;
    
    // Matriz DP para almacenar si se puede lograr un subconjunto con una suma dada
    vector<vector<bool>> dp(n + 1, vector<bool>(capacidad + 1, false));
    
    // Inicialización: con suma 0 siempre se puede hacer con el subconjunto vacío
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    // Llenado de la tabla DP
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= capacidad; j++) {
            if (A[i-1] <= j) {
                dp[i][j] = dp[i-1][j] || dp[i-1][j - A[i-1]];
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    // Encontramos la mayor suma posible del primer subconjunto
    int sumaMaximaSubconjunto = 0;
    for (int j = capacidad; j >= 0; j--) {
        if (dp[n][j]) {
            sumaMaximaSubconjunto = j;
            break;
        }
    }

    // La diferencia mínima entre los dos subconjuntos
    int diferenciaMinima = sumaTotal - 2 * sumaMaximaSubconjunto;

    return diferenciaMinima;
}