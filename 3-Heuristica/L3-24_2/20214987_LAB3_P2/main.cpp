/* 
 * File:   main.cpp
 * Author:  MELL ALESSANDRA CARBAJAL ROMAN 20214987
 *
 * Created on 5 de octubre de 2024, 08:11 AM
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Datos{
    int nProducto; 
    int cantReq; 
    int longitud; 
    int altura; 
    int areaPorLata;
    int areaTotal; 
};

struct Placa{
    int longitud; 
    int altura; 
    int areaTotal; 
    int areaRestante; 
};

void cortaLatas(int nProd,vector<Datos> &latas,vector<Placa> &almacen, int &nPlacasUsadas);
bool compara(struct Datos &a, struct Datos &b);
/*
 * 
 */
int main(int argc, char** argv) {
    
    vector<Datos> latas = {{1,5,2,4,0,0},
    {2,10,9,3,0,0},
    {3,15,14,7,0,0},
    {4,20,15,20,0,0},
    {5,20,22,18,0,0}};
    
    
    /*Llenamos un vector de placas y luego analizaremos cuantas se usaron*/
    vector<Placa> almacen; 
    for(int i=0; i<100; i++){
        struct Placa placa = {50,50,2500,2500}; 
        almacen.push_back(placa);
    }
    
    /*algoritmo Voraz*/
    int nPlacasUsadas=0; 
    cortaLatas(latas.size(),latas,almacen,nPlacasUsadas); 
    

    
    return 0;
}

void cortaLatas(int nProd,vector<Datos> &latas,vector<Placa> &almacen, int &nPlacasUsadas){
    /*Calculo el area para cada lata*/
    for(int i=0; i<nProd; i++){
        latas[i].areaPorLata = latas[i].longitud * latas[i].altura; 
        latas[i].areaTotal= latas[i].areaPorLata*latas[i].cantReq; 
    }
    /*Ordeno */
    sort(latas.begin(),latas.end(),compara); 
    
    /*Atiendo las que me ocupan mas area para minimizar el desperdicio*/
    for(int i=0; i<nProd;i++){
        
        /*Atiendo los requerimientos de cada producto*/
        int cant=0; 
        while(true){
            /*Por cada requisito recorro mi vector de barras en busca de una placa 
                con espacio sobrante >= latas[i].areaPorLata*/
            int nPlacaConEspacio=0; 
            while(true){
                if(latas[i].areaPorLata <= almacen[nPlacaConEspacio].areaRestante) break;
                nPlacaConEspacio++; 
                if(nPlacaConEspacio>=nPlacasUsadas){
                    nPlacasUsadas = nPlacaConEspacio;
                }
            }
            /*Resto el area que utilizare*/
            almacen[nPlacaConEspacio].areaRestante -=latas[i].areaPorLata; 
            cant++;
            
            if(cant==latas[i].cantReq) break;
        }
       
    }
    
    
    /*Impresion - PARTE B y C*/
    cout << "Numero de laminas usadas: "<<nPlacasUsadas<<endl;
    /*Hallamos el porcentaje de merma residual total*/
    int mermaTotal=0; 
    double porcMerma;
    for(int i=0; i<nPlacasUsadas;i++){
        mermaTotal+=almacen[i].areaRestante;
    }
    cout << nPlacasUsadas*2500<<"   "<<mermaTotal<<endl; 
    porcMerma = mermaTotal / (double)nPlacasUsadas;
    cout << "Procentaje de merma: "<<setw(4)<<porcMerma<<"%"<<endl; 
        
}

bool compara(struct Datos &a, struct Datos &b){
    return a.areaPorLata > b.areaPorLata; 
}

