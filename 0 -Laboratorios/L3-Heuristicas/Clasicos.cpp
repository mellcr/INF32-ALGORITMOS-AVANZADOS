/* 
 * File:   Clasicos.cpp
 * Author: BlueCod 
 *
 * Created on 14 de octubre de 2024, 6:45 p. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
#include "Headers.h"

void clasicos(){
    mochila();
    monedero();
}

void mochila(){
    vector<int> mochila = {1,2,0,10,20,50,100};
    int n = mochila.size();
    int capacidad = 15;
    
    cout << "La mochila queda con un resto de: "<<cargaMochila(mochila,n,capacidad)<<endl<<endl;
}

int cargaMochila(vector<int> &mochila,int n,int capacidad){
    /*1. Ordenar */
    sort(mochila.begin(), mochila.end(),compara);
    //for(int i=0;i<n;i++) cout<<mochila[i]<< " ";
    
    /*2. Despacho */
    int resto = capacidad;
    for(int i=0; i<n;i++){
        if(resto>=mochila[i]){
            resto -= mochila[i];
        }
    }
    
    return resto;
}

bool compara(int a, int b){
    return a>b; //  ASC: 100 50 20 ...
}


void monedero(){
    vector<int> monedero = {1,2,5,10,20,50,100};
    int n = monedero.size();
    int vuelto = 27;
    vector<int> solucion;
    
    cout<<"Para un vuelto de "<<vuelto<<" , se necesitan las monedas: ";
    obtieneMonedas(monedero,n,solucion,vuelto);
    cout<<endl<<endl;
}


void obtieneMonedas(vector<int> &monedero,int n,vector<int> &solucion,int vuelto){
    /*Ordenar para verificar las monedas/billetes mas grandes primero*/
    sort(monedero.begin(),monedero.end(),compara);
    
    /*Obtenemos monedas */
    int resto = vuelto;
    for(int i=0; i<n;i++){
        /*mientras se pueda usar esa moneda/billete lo usaremos*/
        while(resto>=monedero[i]){
            resto-=monedero[i];
            solucion.push_back(monedero[i]);
        }
    }
    
    for(int i=0;i<solucion.size();i++) cout<<solucion[i]<< " ";
}