/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 20 de setiembre de 2024, 4:51 p. m.
 */
#include <iostream>
#include <algorithm>

using namespace std;

// Función para encontrar el último índice que no se superpone con el índice actual
int encontrarNoConflictiva(const int fin[], const int inicio[], int i) {
    for (int j = i - 1; j >= 0; j--) {
        if (fin[j] <= inicio[i]) {
            return j;
        }
    }
    return -1;
}

// Función que encuentra la ganancia máxima usando una matriz para almacenar todo el DP
int maxBeneficio(int inicio[], int fin[], int beneficio[], int M, int N) {
    // Crear una matriz DP para almacenar la solución
    int dp[M][M]{}; 

    // Inicializamos la primera fila con los beneficios de la primera presentación
    dp[0][0] = beneficio[0];

    // Llenar la tabla dp usando la lógica de programación dinámica
    for (int i = 1; i < M; i++) {
        for (int j = 0; j <= i; j++) {
            // Caso 1: No incluimos la presentación i en la solución
            dp[i][j] = dp[i - 1][j];

            // Caso 2: Incluir la presentación i en la solución
            int incl = beneficio[i];
            int last = encontrarNoConflictiva(fin, inicio, i);
            if (last != -1) {
                incl += dp[last][last];
            }

            dp[i][j] = max(dp[i][j], incl);  // Tomamos la mejor opción
        }
    }

    // Obtener la máxima ganancia en la última fila de la matriz dp
    int maxGanancia = 0;
    for (int j = 0; j < M; j++) {
        maxGanancia = max(maxGanancia, dp[M - 1][j]);
    }

    // La ganancia máxima multiplicada por el número de troncos N
    return maxGanancia * N;
}

int main() {
    // Ejemplo de presentaciones (solo usando arreglos de enteros)
    int inicio[] = {5, 2, 6, 4};     // Inicios de las presentaciones
    int fin[] = {10, 4, 12, 15};     // Finales de las presentaciones
    int beneficio[] = {30, 40, 80, 100}; // Beneficios de las presentaciones
    int M = 4;  // Número de presentaciones
    int N = 10; // Número de troncos

    cout << "La ganancia máxima es: S/. " << maxBeneficio(inicio, fin, beneficio, M, N) << endl;

    return 0;
}
