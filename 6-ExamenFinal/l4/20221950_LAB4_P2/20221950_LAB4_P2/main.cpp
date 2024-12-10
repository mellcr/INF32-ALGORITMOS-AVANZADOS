/* 
 * File:   main.cpp
 * Author: 20221950 Carrasco Villegas Nick
 *
 * Created on 9 de noviembre de 2024, 09:05 AM
 */

#include <iostream>
#include <climits>
#include <ctime>
#include <vector>
#include <algorithm>
#define maxitera 10000
#define alfa 0.4

using namespace std;
struct Pago{
    int destino;
    int pago;
};


bool compara(Pago a, Pago b){
    return a.pago > b.pago;
}

int verifica(vector<Pago> posiblesDestinos, double rcl){
    int cont=0;
    for(int i=0;i < posiblesDestinos.size();i++)
        if(rcl <= posiblesDestinos[i].pago)cont++;
    return cont;
}

int compruebaFin(vector<int> posibles){
    for(int i: posibles) if(i != 0) return 1;
    return 0;
}

void entregaPedidos(vector<vector<int>> rutas, vector<Pago> pagos, int n){
    int mejorGanancia = 0;
    vector<char> camino;
    for(int i = 0; i < maxitera; i++){
        srand(time(NULL));
        vector<char> solucion;
        int posicionActual = 0;
        int ganancia = 0;
        while(1){
            if(!compruebaFin(rutas[posicionActual])){
                break;
            }
            vector<Pago> posiblesDestinos;
            for(int i = 0; i < n; i++){
                if(rutas[posicionActual][i] != 0) posiblesDestinos.push_back(pagos[i]);
            }
            sort(posiblesDestinos.begin(), posiblesDestinos.end(), compara);
            int beta = posiblesDestinos[0].pago;
            int tau = posiblesDestinos[posiblesDestinos.size()-1].pago;
            double rcl = beta - alfa*(beta-tau);
            int ind = verifica(posiblesDestinos, rcl);
            int inda = rand()%ind;
            int posicion = posiblesDestinos[inda].destino;
            solucion.push_back('A' + posicion);
            ganancia += pagos[posicion].pago;
            posicionActual = posicion;
            
        }
        if(mejorGanancia < ganancia){
            mejorGanancia = ganancia;
            camino.erase(camino.begin(), camino.end());
            camino.insert(camino.begin(), solucion.begin(), solucion.end());
        }
    }
    cout << mejorGanancia << endl;
    for(char c: camino){
        cout << c << ' ';
    }
}

int main(int argc, char** argv) {
    vector<vector<int>> rutas = {
        {0,1,1,1,1,0,0,1},
        {0,0,1,1,0,1,0,1},
        {0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,1,0,0,1,1,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
    };
    int n=rutas.size();
    vector<Pago> pagos = {
        {0,0}, 
        {1,20}, 
        {2,30}, 
        {3,40}, 
        {4,40}, 
        {5,40}, 
        {6,10}, 
        {7,50}
        };
    entregaPedidos(rutas, pagos, n);
    return 0;
}

