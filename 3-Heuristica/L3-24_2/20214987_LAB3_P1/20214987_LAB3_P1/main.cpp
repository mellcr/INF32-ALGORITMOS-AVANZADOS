/* 
 * File:   main.cpp
 * Author: MELL ALESSANDRA CARBAJAL ROMAN 20214987
 *
 * Created on 5 de octubre de 2024, 08:11 AM
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Datos{
    int nProy; 
    int costo; 
    int ganancia; 
    int beneficio; 
    vector<int> predecesores; 
    double maximizador; //considerando Double para que la ordenación sea más exacta
};

struct Nodo{
    int gananciaTotal; 
    int costoTotal; 
    vector<int> proyectosSeleccionados; 
};

void seleccionaProyectos(int nProy,int Pres,vector<Datos> &proyectos);
bool compara(struct Datos &a, struct Datos &b);
bool proyectoAgregado(struct Nodo &aux,int numProy);
/*
 * 
 */
int main(int argc, char** argv) {
    int N=8;  //nProyectos
    int P = 250; 
    
    vector<Datos> proyectos = {{1,80,150,2},{2,20,80,5,{4}},
    {3,100,300,1,{1,2}},{4,100,150,4},{5,50,80,2},{6,10,50,1,{2}},{7,50,120,2,{6}},
    {8,50,150,4,{6}}};
    
    
//    for(int i=0; i<N; i++){
//        cout << "Proyecto "<<i+1<<": "<<proyectos[i].costo<<endl;
//        for(int j=0; j<proyectos[i].predecesores.size();j++){
//            cout << proyectos[i].predecesores[j]<<" "; 
//        }
//        cout <<endl; 
//    }
    
    //cout <<P<<endl; 
    seleccionaProyectos(N,P,proyectos);

    
    return 0;
}

/*Maximizar la ganancia, beneficio y minimizar el costo */
void seleccionaProyectos(int nProy,int Pres,vector<Datos> &proyectos){
    /*Hallo el maximizador por cada proyecto*/
    for(int i=0; i<nProy; i++){
        proyectos[i].maximizador = ((proyectos[i].ganancia *proyectos[i].beneficio) / (double)proyectos[i].costo );
        //cout << proyectos[i].maximizador<<" ";
    }
    
    /*Creo un vector copia de proyectos para no perder la relacion de indices 
     para los predecesores*/
   vector<Datos> proytemp(proyectos);
    
    /*Ordeno*/
    sort(proytemp.begin(),proytemp.end(),compara);
//    for(int i=0; i<8; i++){
//        cout << "Proyecto "<<proytemp[i].nProy<<": ";
//        for(int j=0; j<proytemp[i].predecesores.size();j++){
//            cout << proytemp[i].predecesores[j]<<" "; 
//        }
//        cout <<endl; 
//    }
    
    struct Nodo aux={0,0}; 
    for(int i=0; i<nProy; i++){
        int nProy = proytemp[i].nProy-1; 
        if(aux.costoTotal+ proyectos[nProy].costo<=Pres and !proyectoAgregado(aux,nProy)){
            aux.costoTotal+= proyectos[nProy].costo;
            aux.gananciaTotal+= proyectos[nProy].ganancia;
            aux.proyectosSeleccionados.push_back(nProy);  
            
            /*Guardo los proyectos predecesores*/
            for(int j=0; j<proyectos[nProy].predecesores.size(); j++){
                int nProyPredec = proyectos[nProy].predecesores[j]-1; //se le resta 1 por indice
                if(aux.costoTotal+proyectos[nProyPredec].costo<=Pres 
                        and  !proyectoAgregado(aux,nProyPredec)){
                    aux.costoTotal+=proyectos[nProyPredec].costo; 
                    aux.gananciaTotal+=proyectos[nProyPredec].ganancia; 
                    aux.proyectosSeleccionados.push_back(nProyPredec);
                }
            }
        }
    }
    
    cout << endl<<"Proyectos seleccionados: "; 
    for(int j=0; j<aux.proyectosSeleccionados.size();j++){
        cout <<aux.proyectosSeleccionados[j]+1<<" "; 
    }
    cout <<endl<<"Ganancia: "<<aux.gananciaTotal<<endl;
    //cout <<"Costo: "<<aux.costoTotal<<endl;
}

bool compara(struct Datos &a, struct Datos &b){
    return a.maximizador>b.maximizador; 
}

bool proyectoAgregado(struct Nodo &aux,int numProy){
    if(aux.proyectosSeleccionados.empty()){
        return false;
    }
    else{
        /*Si ya he agregado proyectos, verifico si esta*/
        for(int i=0; i<aux.proyectosSeleccionados.size();i++){
            if(numProy==aux.proyectosSeleccionados[i]){
                return true; 
            }
        }
        return false;
    }
}