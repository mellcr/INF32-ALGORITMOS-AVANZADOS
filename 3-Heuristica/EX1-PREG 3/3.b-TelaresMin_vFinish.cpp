
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

struct Datos{
    int numeroTelar; 
    int tiempo;
    int tiempoTotal;
    vector<int> telas; 
};

struct Nodo{
    int telar; 
    int tiempoTotalSupuesto;
};

void minizaTiempoTotal(vector<int> &telas,int nTelas, vector<Datos> &telar, int nTelar,int &tiempoMax);
bool compara(struct Nodo &a, struct Nodo &b); 

/*
 
 */

int main() {
    vector<int> telas ={10,7,9,12,6,8};
    int nTelas = telas.size();
    vector<Datos> telar={{0,5,0},{1,4,0},{2,6,0}};
    int nTelar = telar.size(); 
    int tiempoMax=0; 
    
    minizaTiempoTotal(telas,nTelas, telar,nTelar,tiempoMax);
    

    return 0;
}


/*Quiero minimizar el tiempo que me tome */
void minizaTiempoTotal(vector<int> &telas,int nTelas, vector<Datos> &telar, int nTelar,int &tiempoMax){
    /*Por cada tela*/
    for(int i=0; i<nTelas;i++ ){
        /*Guardo la relacion: telar-tiempoQueTomaria por cada telar, lo ordeno y me quedo con el menor*/
        vector<Nodo> temp; 
        Nodo aux;
        for(int j=0; j<nTelar; j++){
            aux.telar = j; //guarda el telar
            aux.tiempoTotalSupuesto = telas[i] * telar[j].tiempo + telar[j].tiempoTotal; 
            temp.push_back(aux);
        }
        sort(temp.begin(),temp.end(),compara);
        /*Asigno la tela al telar que me genera menos tiempo*/
        Nodo ganador = temp[0];
        telar[ganador.telar].tiempoTotal = ganador.tiempoTotalSupuesto; 
        telar[ganador.telar].telas.push_back(telas[i]);
    }
    
    /*Impresion*/
    for(int i=0; i<nTelar; i++){
        cout << "Telar "<<telar[i].numeroTelar<<": "; 
        for(int k=0; k<telar[i].telas.size();k++){
            cout << telar[i].telas[k]<<" ";
        }
        cout << " - Tiempo total de trabajo: "<<telar[i].tiempoTotal<<" unidades de tiempo."<<endl; 
        
        if(telar[i].tiempoTotal>tiempoMax){
            tiempoMax = telar[i].tiempoTotal;
        }        
    }
    
    cout << " Tiempo total para terminar todas las telas: "<<tiempoMax<<" unidades de tiempo."<<endl; 
}

bool compara(struct Nodo &a, struct Nodo &b){
    return a.tiempoTotalSupuesto < b.tiempoTotalSupuesto; // de menor a mayor
}