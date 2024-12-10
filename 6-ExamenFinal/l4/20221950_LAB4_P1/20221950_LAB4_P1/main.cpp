/* 
 * File:   main.cpp
 * Author: 20221950 Carrasco Villegas Nick
 *
 * Created on 9 de noviembre de 2024, 08:02 AM
 */

#include <iostream>
#include <climits>
#include <ctime>
#include <vector>
#include <algorithm>
#define maxitera 10000
#define alfa 0.21

using namespace std;

struct Caja{
    int peso;
    vector<int> objetos;
};

bool compara(int a, int b){
    return a > b;
}

bool comparaCaja(Caja a, Caja b){
    return a.peso < b.peso;
}

int verifica(vector<Caja> cajas, double rcl){
    int count = 0;
    for(int i = 0; i < cajas.size(); i++){
        if(rcl >= cajas[i].peso) count++;
    }
    return count;
}

int betaCajas(vector<Caja> cajas, int peso){
    for(Caja aux: cajas) if(aux.peso >= peso) return aux.peso;
}

void cargaPaquetes(int *objetos, int n){
    int cantCajas = 11;
    vector<Caja> mejorCajas;
    for(int k = 0; k < maxitera; k++){
        vector<int> auxObjetos;
        auxObjetos.insert(auxObjetos.begin(),objetos, objetos + n); // Copia objetos
        srand(time(NULL));
        vector<Caja> cajas(10); // Crea las cajas
        for(Caja &aux:cajas) {
            aux.peso = 10; // Les da peso
        }
        int cC = 0;
        while(not auxObjetos.empty()){
            sort(cajas.begin(), cajas.end(), comparaCaja);
            int beta = betaCajas(cajas, auxObjetos[0]);
            int tau = cajas[cajas.size()-1].peso;
            double rcl = beta + alfa*(tau - beta);
            int ind = verifica(cajas, rcl);
            int inda = rand()%ind;
            if(cajas[inda].peso - auxObjetos[0] >= 0){
                if(cajas[inda].peso == 10) cC++; 
                cajas[inda].objetos.push_back(auxObjetos[0]);
                cajas[inda].peso -= auxObjetos[0];
                auxObjetos.erase(auxObjetos.begin());
            }
        }
        if(cantCajas > cC){
            cantCajas = cC;
            mejorCajas.erase(mejorCajas.begin(), mejorCajas.end());
            mejorCajas.insert(mejorCajas.begin(), cajas.begin(), cajas.end());
        }
    }
    cout << cantCajas << endl;
    for(int i = 0; i < cantCajas; i++){
        cout << "Contenedor " << i + 1 << ": [";
        for(int num:mejorCajas[i].objetos) cout << num << ' ';
        cout << ']' << endl;
    }
}

int main(int argc, char** argv) {
    
    int objetos[] = {
        4, 8, 1, 4, 2, 1
    };
    int n = sizeof(objetos)/sizeof(objetos[0]);
    sort(objetos, objetos+n, compara);
    cargaPaquetes(objetos, n);
    return 0;
}

