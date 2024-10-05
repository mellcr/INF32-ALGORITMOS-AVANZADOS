/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 2 de setiembre de 2024, 2:20 p. m.
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void buscambio(int monto, int *deno, int n);

/*
 * HEURISTICA     
 */

int main(int argc, char** argv) {
    int monto = 27; 
    //vector<int> denominacion = {50,100,2,1,5,10,20};
    int denominacion[] = {50,100,2,1,5,10,20};
    int n=sizeof(denominacion) / sizeof(denominacion[0]); 
    
    //buscambio(monto, denominacion, denominacion.size());
    buscambio(monto, denominacion, n);
    
    return 0;
}

void buscambio(int monto, int *deno, int n){
    //como no se sabe que tamaño tendrá el arreglo solución -> vector 
    vector<int> sol; 
    sort(deno,deno+1); 
    
    //para no crear el compara, empezamos desde atras
    for(int i=n-1; i>=0; i--){
        //mientras que el monto sea mayor que la moneda que estoy evaluando 
        //para que pruebe muchas veces la moneda actual 
        while(monto >= deno[i]) {
            monto -= deno[i]; 
            sol.push_back(deno[i]);
        }
    }
    
    for(int i=0; i<sol.size() ; i++){
        cout << setw(3)<< sol[i]; 
    }
    
//    for(int cambio: sol){
//                cout << setw(3)<< cambio; 
//    }
}