/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 19 de setiembre de 2024, 4:15 p. m.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int minTiempoMaximo2(vector<int>& tiempos, int N, int R) ;
int calcularSuma(const vector<int>& tiempos, int inicio, int fin);


// Función que implementa la programación dinámica
int minTiempoMaximo(vector<int>& tiempos, int N, int R) {
    vector<int> suma(N+1, 0); // suma acumulada de tiempos
    vector<vector<int>> dp(N+1, vector<int>(R+1, INT_MAX)); // dp[i][r]

    // Calcular suma acumulada de tiempos
    for (int i = 1; i <= N; ++i) {
        suma[i] = suma[i-1] + tiempos[i-1];
    }

    // Caso base: con un solo robot, el tiempo máximo es hacer todas las tareas
    for (int i = 1; i <= N; ++i) {
        dp[i][1] = suma[i];
    }

    // Rellenar la tabla dp para varios robots
    for (int r = 2; r <= R; ++r) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 0; j < i; ++j) {
                dp[i][r] = min(dp[i][r], max(dp[j][r-1], suma[i] - suma[j]));
            }
        }
    }

    return dp[N][R];
}

int main() {
    int N = 5; // Número de tareas
    vector<int> tiempos = {15, 30, 60, 45, 10}; // Tiempos de cada tarea
    int R = 2; // Número de robots

    // Calcular el tiempo máximo mínimo usando programación dinámica
    int resultado = minTiempoMaximo(tiempos, N, R);
    cout << "El tiempo máximo mínimo que utilizarían " << R << " robots es: " << resultado << " minutos." << endl;

    R = 3;
    resultado = minTiempoMaximo(tiempos, N, R);
    cout << "El tiempo máximo mínimo que utilizarían " << R << " robots es: " << resultado << " minutos." << endl;

    return 0;
}


// Función para calcular la suma de tareas entre dos índices
int calcularSuma(const vector<int>& tiempos, int inicio, int fin) {
    int suma = 0;
    for (int i = inicio; i <= fin; ++i) {
        suma += tiempos[i];
    }
    return suma;
}

// Función que implementa la programación dinámica sin vector suma
int minTiempoMaximo2(vector<int>& tiempos, int N, int R) {
    vector<vector<int>> dp(N+1, vector<int>(R+1, INT_MAX)); // dp[i][r]

    // Caso base: con un solo robot, el tiempo máximo es hacer todas las tareas
    for (int i = 1; i <= N; ++i) {
        dp[i][1] = calcularSuma(tiempos, 0, i-1);
    }

    // Rellenar la tabla dp para varios robots
    for (int r = 2; r <= R; ++r) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 0; j < i; ++j) {
                dp[i][r] = min(dp[i][r], max(dp[j][r-1], calcularSuma(tiempos, j, i-1)));
            }
        }
    }

    return dp[N][R];
}