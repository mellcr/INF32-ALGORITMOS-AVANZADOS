
/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 3 de octubre de 2024, 2:20 p. m.
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#define MAX 8
using namespace std;


struct Datos{
    int ciudadVecina;
    int distancia;
};

void minimaRuta(int ini,int fin,vector<vector<int>> &mapa, int &minDis);
bool compara(struct Datos &a, struct Datos &b);
/*
 * MOCHILA GANANCIA  
 */

int main(int argc, char** argv) {
    vector<vector<int>> mapa={{0,4,5,6,0,0,0,0},    //A - 0
                     {0,0,0,0,2,0,0,0},             //B - 1 
                     {0,0,0,0,0,0,0,3},             //C - 2
                     {0,0,0,0,0,3,0,0},             //D - 3
                     {0,0,0,0,0,0,10,0},            //E - 4
                     {0,0,0,0,0,0,2,0},             //F - 5 
                     {0,0,0,0,0,0,0,0},             //G - 6 
                     {0,0,0,0,0,0,0,0}};            //H - 7
    
    int n =  mapa.size();
    int minDis =0;
    
    minimaRuta(0,6,mapa,minDis);
    if(minDis!=0)cout<<"Tiempo de viaje: "<<minDis<<endl;
    else cout << "No se encontro ninguna solucion"<<endl;
    
    return 0;
}

void minimaRuta(int ini,int fin,vector<vector<int>> &mapa, int &minDis){
    int ciudadActual=ini;
    
    while(true){
        /*Por cada ciudad actual cargo sus vecinos*/
        vector<Datos> vecinos;
        Datos aux;
        for(int i=0;i<mapa[ciudadActual].size();i++){
            if(mapa[ciudadActual][i]>0){
                aux.ciudadVecina = i;
                aux.distancia = mapa[ciudadActual][i];
                vecinos.push_back(aux);           //añade el struct aux
            } 
        }
        
        if(not vecinos.empty()){
            /*Ordeno los vecinos y tomo el menor*/
            sort(vecinos.begin(),vecinos.end(),compara);
            ciudadActual = vecinos[0].ciudadVecina; //pasa a la ste ciudad
            minDis+=vecinos[0].distancia;
        }
        else{
            minDis=0;
            break;
        }
        if(ciudadActual==fin) break;
    }
}

bool compara(struct Datos &a, struct Datos &b){
    return a.distancia < b.distancia;  // ASC: 1 2 3
}