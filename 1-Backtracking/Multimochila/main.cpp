/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 6 de setiembre de 2024, 10:41 p. m.
 */

#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

void mochilaMaxima(); 
int mochilaBacktracking(int pos, int valorActual, vector<int> &capacidadMochilas, vector<vector<int>> &mejorSolucion, int n, int &valorMaximo, vector<int> ganancias, vector<int> pesos, vector<vector<int>> &soluciones);

vector<vector<int>> soluciones;  // Guarda la configuración de cada mochila
vector<vector<int>> mejorSolucion;  // Solución que almacena la mejor configuración de objetos en cada mochila

/*
 * PROBLEMAS PROPUESTOS EN CLASE 
 * Resueltos by me 
 */

int main(int argc, char** argv) {
    cout << "Mochila múltiple con máximo valor: " << endl;
    mochilaMaxima(); 

    return 0;
}

void mochilaMaxima() {
    vector<int> ganancias = {80, 30, 100, 20, 10}; 
    vector<int> pesos = {10, 25, 50, 30, 20}; 
    vector<int> capacidadMochilas = {50, 30, 10, 80}; // Capacidades de cada mochila
    int valorMaximo = 0;
    int n = ganancias.size();  // número de elementos

    mejorSolucion = vector<vector<int>>(4, vector<int>()); // Vector que guarda la mejor solución
    soluciones = vector<vector<int>>(4, vector<int>()); // Vector que guarda las soluciones temporales

    mochilaBacktracking(0, 0, capacidadMochilas, mejorSolucion, n, valorMaximo, ganancias, pesos, soluciones);

    cout << "Valor máximo: " << valorMaximo << endl;
    cout << "Mejor solución (pesos seleccionados en cada mochila): " << endl;
    for (int i = 0; i < capacidadMochilas.size(); ++i) {
        cout << "Mochila " << i+1 << " con capacidad original " << capacidadMochilas[i] << ": ";
        for (int peso : mejorSolucion[i]) {
            cout << peso << " ";
        }
        cout << endl;
    }
}

int mochilaBacktracking(int pos, int valorActual, vector<int> &capacidadMochilas, vector<vector<int>> &mejorSolucion, int n, int &valorMaximo, vector<int> ganancias, vector<int> pesos, vector<vector<int>> &soluciones) {
    // Si hemos considerado todos los elementos
    if (pos == n) {
        if (valorActual > valorMaximo) {
            valorMaximo = valorActual;  // Actualizamos el valor máximo encontrado
            mejorSolucion = soluciones; // Guardamos la mejor configuración de objetos en las mochilas
        }
        return 1;
    }
    
    // Intentamos poner el objeto en alguna de las mochilas
    for (int i = 0; i < capacidadMochilas.size(); ++i) {
        if (capacidadMochilas[i] >= pesos[pos]) {  // Si cabe en la mochila
            capacidadMochilas[i] -= pesos[pos];  // Reducimos la capacidad disponible
            soluciones[i].push_back(pesos[pos]);  // Añadimos el objeto a esta mochila

            mochilaBacktracking(pos + 1, valorActual + ganancias[pos], capacidadMochilas, mejorSolucion, n, valorMaximo, ganancias, pesos, soluciones);

            capacidadMochilas[i] += pesos[pos];  // Retrocedemos y liberamos espacio
            soluciones[i].pop_back();  // Quitamos el objeto
        }
    }
    
    // También probamos no agregar el objeto a ninguna mochila
    mochilaBacktracking(pos + 1, valorActual, capacidadMochilas, mejorSolucion, n, valorMaximo, ganancias, pesos, soluciones);
    
    return 0;
}
