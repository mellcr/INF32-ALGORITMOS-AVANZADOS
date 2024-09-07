/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 6 de setiembre de 2024, 3:41 p. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
#include "FuncionesKnightsTour.h"
void mochilaMaxima(); 
int mochilaBacktracking(int pos,int valorActual,int pesoActual,int n,int &valorMaximo,
        int capacidadMochila,vector<int> ganancias,vector<int> pesos,vector<int > solucion);
vector<int> mejorSolucion; 
vector<int> solucionAux; 
vector<int> gananciasAux; 
vector<int> mejorGanancia; 

/*
 * PROBLEMAS PROPUESTOS EN CLASE 
 * Resueltos by me 
 */

int main(int argc, char** argv) {
    cout<<"KNIGHT's tour "<<endl;
    //iniciaRecorridoCab();
    cout<<endl<<"Mochila con maximo valor: "<<endl;
    mochilaMaxima(); 
    
    
    
    
    return 0;
}

void mochilaMaxima(){
    vector<int> ganancias = {60,100,120}; 
    vector<int> pesos = {10,20,30}; 
    int capacidadMochila = 50; 
    int valorMaximo = 0; 
    int n=3; //num de elementos
    
    mochilaBacktracking(0,0,0,n,valorMaximo,capacidadMochila,ganancias,pesos,solucionAux); 
    for(int i=0; i<mejorSolucion.size();i++){
        cout << setw(3)<<mejorSolucion[i];
    }
    cout << " ---> " << valorMaximo;
}

int mochilaBacktracking(int pos,int valorActual,int pesoActual,int n,int &valorMaximo,
        int capacidadMochila,vector<int> ganancias,vector<int> pesos, 
        vector<int > solucion){
    //si el pesoAct supera la capacidad -> solucion no valida 
    if(pesoActual > capacidadMochila) return 0; 
    
    if(pos==n) { //evaluamos todas las ramas posibles para cada elemento 
        if(valorActual>=valorMaximo){
            valorMaximo = valorActual; 
            mejorSolucion = solucion;
            //mejorGanancia = gananciasAux;
        }
        return 1; 
    }
    
    //para cada elemento que agarre de la mochila verificare todas sus posibles soluciones
    solucion.push_back(pesos[pos]);
    //gananciasAux.push_back(ganancias[pos]);
    mochilaBacktracking(pos+1,valorActual+ganancias[pos],pesoActual+pesos[pos],
            n,valorMaximo,capacidadMochila,ganancias,pesos,solucion);
    
    solucion.pop_back(); 
    //gananciasAux.pop_back();
    mochilaBacktracking(pos+1,valorActual,pesoActual,n,valorMaximo,
            capacidadMochila,ganancias,pesos,solucion);
    
    return 0; 
}

