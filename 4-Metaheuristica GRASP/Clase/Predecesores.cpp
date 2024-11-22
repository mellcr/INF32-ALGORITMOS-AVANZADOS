#include <iostream>
#include <climits>
#include <ctime>
#include <vector>
#include <algorithm>
#define maxitera 10000
#define alfa 0.3

using namespace std;

bool compara(int a, int b) {
    return a > b;
}

// Función para verificar si todos los predecesores de un objeto están en seleccionados
bool predecesoresCumplidos(const vector<int>& predecesores, const vector<int>& seleccionados) {
    for (int pre : predecesores) {
        if (find(seleccionados.begin(), seleccionados.end(), pre) == seleccionados.end()) {
            return false; // Un predecesor no ha sido seleccionado aún
        }
    }
    return true;
}

int verifica(const vector<int>& paq, double rcl) {
    int cont = 0;
    for (int i = 0; i < paq.size(); i++)
        if (rcl <= paq[i]) cont++;
    return cont;
}

void cargamochila(vector<int>& paq, int peso, const vector<vector<int>>& predecesores) {
    int mejor = INT_MAX;
    vector<int> maxsol;
    for (int k = 0; k < maxitera; k++) {
        // fase construcción
        srand(time(NULL));
        vector<int> soluciones;
        sort(paq.begin(), paq.end(), compara);
        vector<int> paquetes = paq;          // Copia del vector paq para manipulación
        vector<int> seleccionados;           // Vector de enteros para guardar los objetos seleccionados

        int residual = peso;
        while (!paquetes.empty()) {
            int beta = paquetes[0];
            int tau = paquetes[paquetes.size() - 1];
            double rcl = beta - alfa * (beta - tau);
            int ind = verifica(paquetes, rcl);

            // Selección aleatoria dentro de RCL
            int inda = rand() % ind;
            int objetoSeleccionado = paquetes[inda]; // Objeto seleccionado por valor

            // Verifica si los predecesores del objeto seleccionado han sido cumplidos
            if (predecesoresCumplidos(predecesores[inda], seleccionados)) {
                // Se encontró una solución
                if (residual - objetoSeleccionado >= 0) {
                    soluciones.push_back(objetoSeleccionado);
                    residual -= objetoSeleccionado;
                    seleccionados.push_back(objetoSeleccionado); // Guarda el objeto seleccionado
                }
                // Descarta el elemento seleccionado
                paquetes.erase(paquetes.begin() + inda);
            }
        }
        /* Selecciona la mejor solucion */
        if (residual < mejor) {
            mejor = residual;
            maxsol = soluciones;
        }
    }

    cout << "Residual: " << mejor << endl;
    cout << "Objetos seleccionados: ";
    for (int i = 0; i < maxsol.size(); i++)
        cout << maxsol[i] << " ";
    cout << endl;
}

int main(int argc, char** argv) {
    vector<int> paq = {10, 2, 1, 5, 9, 8}; // Cambiamos paq a un vector
    int n = paq.size(); // Eliminamos el cálculo de tamaño de arreglos
    int peso = 14;

    // Definir predecesores para cada objeto
    vector<vector<int>> predecesores = {
        {},       // Objeto 0 (sin predecesores)
        {10},     // Objeto 1 depende de 10
        {2},      // Objeto 2 depende de 2
        {},       // Objeto 3 (sin predecesores)
        {5, 1},   // Objeto 4 depende de 5 y 1
        {9}       // Objeto 5 depende de 9
    };

    cargamochila(paq, peso, predecesores);

    return 0;
}
