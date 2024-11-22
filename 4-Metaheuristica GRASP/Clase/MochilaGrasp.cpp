#include <iostream>
#include <climits>
#include <ctime>
#include <vector>
#include <algorithm>
#define maxitera 10000        // Número máximo de iteraciones
#define alfa 0.3              // Parámetro alfa para el RCL

using namespace std;

// Función de comparación para ordenar de mayor a menor
bool compara(int a, int b) {
    return a > b;
}

/* Cuenta cuántos elementos cumplen con la condición de pertenecer al RCL.
   Es decir, cuenta cuántos elementos en paquetes tienen un peso mayor o igual a rcl. */
int verifica(const vector<int>& paq, double rcl) {
    int cont = 0;
    for (int i = 0; i < paq.size(); i++)
        if (rcl <= paq[i]) cont++;
    return cont;
}

void cargamochila(vector<int>& paq, int peso) {
    int mejor = 999999;         // Mejor residuo
    vector<int> maxsol;         // Mejor solución encontrada

    for (int k = 0; k < maxitera; k++) {
        // Fase de construcción
        srand(time(NULL));
        vector<int> soluciones;
        sort(paq.begin(), paq.end(), compara);   // Ordena paquetes de mayor a menor
        vector<int> paquetes = paq;              // Copia de paq para trabajar en esta iteración
        int residual = peso;                     // Peso disponible restante en la mochila

        while (!paquetes.empty()) {
            int beta = paquetes[0];                // Mayor valor posible
            int tau = paquetes[paquetes.size() - 1]; // Menor valor posible
            double rcl = beta - alfa * (beta - tau); // Calcula el umbral para RCL

            int ind = verifica(paquetes, rcl);      // Cuenta elementos dentro del RCL
            int inda = rand() % ind;                // Selección aleatoria dentro del RCL

            // Si no excede la capacidad, se selecciona
            if (residual - paquetes[inda] >= 0) {
                soluciones.push_back(paquetes[inda]);
                residual -= paquetes[inda];
            }

            paquetes.erase(paquetes.begin() + inda); // Elimina el elemento seleccionado de paquetes
        }

        // Si el residual actual es mejor que el mejor residual guardado, actualiza
        if (residual < mejor) {
            mejor = residual;
            maxsol = soluciones; // Almacena la mejor solución
        }
    }

    // Imprimir el mejor residuo y la mejor solución encontrada
    cout << "Mejor residuo: " << mejor << endl;
    cout << "Mejor solución: ";
    for (int i = 0; i < maxsol.size(); i++)
        cout << maxsol[i] << " ";
    cout << endl;
}

int main(int argc, char** argv) {
    vector<int> paq = {10, 2, 1, 5, 9, 8}; // Vector de paquetes para llenar la mochila
    int peso = 14;                         // Peso máximo permitido en la mochila
    cargamochila(paq, peso);

    return 0;
}
