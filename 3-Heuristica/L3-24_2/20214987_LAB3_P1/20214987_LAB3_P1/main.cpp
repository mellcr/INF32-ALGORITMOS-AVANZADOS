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

struct Solu{
    int gananciaTotal; 
    int costoTotal; 
    vector<int> proyectosSeleccionados; 
};

void seleccionaProyectos(int N,int Pres,vector<Datos> &proyectos);
bool compara(struct Datos &a, struct Datos &b);
bool proyectoAgregado(struct Solu &aux,int numProy);
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

    seleccionaProyectos(N,P,proyectos);

    
    
    
    return 0;
}

/*Maximizar la ganancia, beneficio y minimizar el costo */
void seleccionaProyectos(int N,int Pres,vector<Datos> &proyectos){
    /*Hallo el maximizador por cada proyecto*/
    for(int i=0; i<N; i++){
        proyectos[i].maximizador = ((proyectos[i].ganancia *proyectos[i].beneficio) / (double)proyectos[i].costo );
        //cout << proyectos[i].maximizador<<" ";
    }
  
    /*Creo una copia del vector y luego la ordeno*/
    vector<Datos> proyectosPrioridad(proyectos);
    sort(proyectosPrioridad.begin(),proyectosPrioridad.end(),compara);
    
    /*Atiendo los proyectos*/
    struct Solu solu={0,0};
    for(int i=0;i<N;i++){
        /*dado que no se puede tener proyectos sin predecesores, copiamos solu a un temp*/
        struct Solu temp = solu; 
        
        int nProy = proyectosPrioridad[i].nProy - 1; 
        if(proyectos[nProy].costo <=Pres and !proyectoAgregado(temp,nProy)){
            temp.costoTotal+= proyectos[nProy].costo;
            temp.gananciaTotal+= proyectos[nProy].ganancia;
            temp.proyectosSeleccionados.push_back(nProy);  
            
            /*Añado sus predecesores*/
            bool entranPred=true;
            for(int j=0; j<proyectos[i].predecesores.size();j++){
                int proyPred = proyectos[i].predecesores[j] - 1; 
                if(proyectos[proyPred].costo <=Pres and !proyectoAgregado(temp,proyPred)){
                    temp.costoTotal+= proyectos[proyPred].costo;
                    temp.gananciaTotal+= proyectos[proyPred].ganancia;
                    temp.proyectosSeleccionados.push_back(proyPred); 
                }else{
                    entranPred=false;
                }
            }
            //falta logica en caso falle 
            if(entranPred){
                solu = temp;
            }
        }
    }
    
    cout << endl<<"Proyectos seleccionados: "; 
    for(int j=0; j<solu.proyectosSeleccionados.size();j++){
        cout <<solu.proyectosSeleccionados[j]+1<<" "; 
    }
    cout <<endl<<"Ganancia: "<<solu.gananciaTotal<<endl;
    //cout <<"Costo: "<<aux.costoTotal<<endl;
}

bool compara(struct Datos &a, struct Datos &b){
    return a.maximizador>b.maximizador; 
}

bool proyectoAgregado(struct Solu &aux,int numProy){
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