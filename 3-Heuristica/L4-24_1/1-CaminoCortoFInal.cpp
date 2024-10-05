/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 3 de octubre de 2024, 2:20 p. m.
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
#define NCIUDAD 8

struct Nodo{
    int ciudadVecina;
    int tiempoALlegar; 
};

void tiempoMinViaje(int ciudadIni,int ciudadFin,
        vector<vector<int>> &mapa,int &tiempoMin);
bool compara(struct Nodo &a, struct Nodo &b);

/*
 * 
 */

int main() {
    vector<vector<int>> mapa  = {   {0,4,5,6,0,0,0,0},
                                    {0,0,0,0,2,0,0,0},
                                    {0,0,0,0,0,0,0,3},
                                    {0,0,0,0,0,3,0,0},
                                    {0,0,0,0,0,0,10,0},
                                    {0,0,0,0,0,0,2,0},
                                    {0,0,0,0,0,0,0,0},
                                    {0,0,0,0,0,0,0,0},
    };
    int tiempoMin=0;
    
    tiempoMinViaje(2,6,mapa,tiempoMin);
    
    
    return 0;
}

void tiempoMinViaje(int ciudadIni,int ciudadFin,
        vector<vector<int>> &mapa, int &tiempoMin){
    
    int ciudadActual = ciudadIni; 
    while(ciudadActual!=ciudadFin){
        vector<Nodo> vecinosTemp; 
        struct Nodo aux;
        /* Reviso los vecinos y elijo el que tiene menor camino*/
        for(int i=0; i<NCIUDAD; i++){
            /*Agrego los vecinos*/
            if(mapa[ciudadActual][i]>0){
                aux.ciudadVecina = i; 
                aux.tiempoALlegar = mapa[ciudadActual][i];
                vecinosTemp.push_back(aux);
            }       
        }
        /*Ordeno vecinos de menor a mayor*/
        if (not vecinosTemp.empty()){
            sort(vecinosTemp.begin(),vecinosTemp.end(),compara);
            /*Elijo el vecino cuya distancia es menor*/
            ciudadActual = vecinosTemp[0].ciudadVecina;
            tiempoMin += vecinosTemp[0].tiempoALlegar;
        }
        else{
            tiempoMin=0;
            break;
        }
    }
    
    if(tiempoMin!=0)
        cout << "Tiempo de ciudad "<<ciudadIni<< " a "<<ciudadFin
            <<": "<<tiempoMin<<" min"<<endl;
    else cout << "No se ha encontrado una solucion"<<endl;
}

bool compara(struct Nodo &a, struct Nodo &b){
    return a.tiempoALlegar < b.tiempoALlegar;
}