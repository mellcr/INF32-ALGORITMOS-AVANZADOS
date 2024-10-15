/* 
 * File:   EX1.cpp
 * Author: BlueCod 
 *
 * Created on 14 de octubre de 2024, 11:19 p. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
#include "Headers.h"
struct Datos{
    int dimension;
    int cantidad;
    int ganancia;
};
struct Barra{
    int tamanho;        //tam original
    int desperdicio;    //tam desp de sus cortes 
};
bool comparador(struct Datos &a, struct Datos &b);
void hallaSolu(vector<Datos> &pedidos,int nPed,vector<Barra>&almacen,int nBarras, int &maxGanancia);

void examen1(){
    vector<Datos> pedidos = {{10,5,10},{20,10,20}, {1,18,15},{3,1,5},{1,1,2}};  
    int nPed = pedidos.size();
    vector<Barra> almacen(20, {10, 10}); //20 barras con inicializacion del struct
    
    int nBarras = almacen.size();
    int maxGanancia=0;
    
    hallaSolu(pedidos,nPed,almacen,nBarras,maxGanancia);
    cout << "Maxima ganancia: "<<maxGanancia<<endl; 
    /*es solo impresion*/
    cout << "Barras:     ";
    for (int i = 0; i < nBarras; i++) {
        cout << setw(4) << i + 1; 
    }
    cout <<endl<< "Desperdicio:";
    for (int i = 0; i < nBarras; i++) {
        cout << setw(4) << almacen[i].desperdicio; 
    }
    cout << endl;
    
}

void hallaSolu(vector<Datos> &pedidos,int nPed,vector<Barra>&almacen,int nBarras, int &maxGanancia){
    /*Ordeno para maximizar ganancia*/
    sort(pedidos.begin(),pedidos.end(),comparador);
    
    /* Atiendo cada pedido */
    for(int i=0; i<nPed;i++){
        /*Analizo las barras disponibles en almacen, minimizando desperdicios*/
		/*NOTA: No se atienden pedidos parciales -> proceso de copia para verificar ello*/
        int cant = 0;                       //cantidad de troncos del pedido
        vector<Barra> temp (almacen);       //copia del estado actual de las barras en el almacen 
        for(int j=0; j<nBarras;){
            /*Analizamos el sobrante desp del corte*/
            int sobrante = temp[j].desperdicio-pedidos[i].dimension ;
            if(sobrante >= 0){
                temp[j].desperdicio-=pedidos[i].dimension;
                cant++;
            }
            else j++;   // pasa a la sgte barra 
            /*El pedido se atendio, se procesa su ganancia y cambios en desperdicio*/
            if(cant == pedidos[i].cantidad){ /*Cada pedido tiene su cant de troncos con cierta dimension*/
                almacen.assign(temp.begin(), temp.end());
                maxGanancia+=pedidos[i].ganancia;
                break;
            } 
        }
    }
}

bool comparador(struct Datos &a, struct Datos &b){
    return a.ganancia> b.ganancia;
}