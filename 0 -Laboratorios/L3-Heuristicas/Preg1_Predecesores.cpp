/* 
 * File:   Preg1_Predecesores.cpp
 * Author: BlueCod 
 *
 * Created on 14 de octubre de 2024, 10:39 p. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;
#include "Headers.h"

struct Datos{
    int ind;
    int costo;
    int ganancia;
    int beneficio;
    double maximizador;
    vector<int> predecesores;
    
};

struct Solu{
    int costoTotal;
    int gananciaTotal;
    vector<int> proySeleccionados;
};

void seleccionaProyecto(vector<Datos> &proyectos,int nProy,int P);
bool cmp(struct Datos &a, struct Datos &b);
void imprimeProyectos( vector<Datos> &proyectos) ;
/*
 * PROYECTOS CON PREDECESORES
 */
void pregunta1(){
    vector<Datos> proyectos = {
        {1,80,150,2,0.0,{}},
        {2,20,80,5,0.0,{4}},
        {3,100,300,1,0.0,{ 1,2}},
        {4,100,150,4,0.0,{}}, 
        {5,50,80,2,0.0,{}},
        {6,10,50,1,0.0,{2}},
        {7,50,120,2,0.0,{6}},
        {8,50,150,4,0.0,{6}}
    };
    int N=8, P =250;
    
    seleccionaProyecto(proyectos,N,P);
}

void seleccionaProyecto(vector<Datos> &proyectos,int nProy,int P){
    /*Obtener el maximizador*/
    for(int i=0; i<nProy-1;i++){
        if(proyectos[i].costo!=0)proyectos[i].maximizador = (double)(proyectos[i].beneficio * proyectos[i].ganancia) / (double)proyectos[i].costo;
    }
    
    imprimeProyectos(proyectos);
    
    
    
    /*Creo una copia del vector y luego la ordeno*/
    //vector<Datos> proyectosPrioridad(proyectos);
    //sort(proyectosPrioridad.begin(),proyectosPrioridad.end(),comparar);
    
    /*Atiendo los proyectos*/
    //struct Solu solu={0,0};
//    for(int i=0;i<nProy;i++){
//        /*dado que no se puede tener proyectos sin predecesores, copiamos solu a un temp*/
//        struct Solu temp = solu; 
//        
//        int proyActual = proyectosPrioridad[i].ind - 1; 
//        if(proyectos[proyActual].costo <=P ){
//            temp.costoTotal+= proyectos[nProy].costo;
//            temp.gananciaTotal+= proyectos[nProy].ganancia;
//            temp.proySeleccionados.push_back(nProy);  
//            
//            /*Añado sus predecesores*/
//            bool entranPred=true;
//            for(int j=0; j<proyectos[i].predecesores.size();j++){
//                int proyPred = proyectos[i].predecesores[j] - 1; 
//                if(proyectos[proyPred].costo <=P){
//                    temp.costoTotal+= proyectos[nProy].costo;
//                    temp.gananciaTotal+= proyectos[nProy].ganancia;
//                    temp.proySeleccionados.push_back(nProy); 
//                }else{
//                    entranPred=false;
//                }
//            }
//            //falta logica en caso falle 
//            if(entranPred){
//                solu = temp;
//            }
//        }
//    }
    
}

bool cmp(struct Datos &a, struct Datos &b){
    // quiero atender primero a los que tienen mayor maximizador:)
    return a.maximizador>b.maximizador;
}

void imprimeProyectos( vector<Datos> &proyectos) {
    for (const Datos &proyecto : proyectos) {
        cout << "Proyecto " << proyecto.ind << ": " << endl;
        cout << "Costo: " << proyecto.costo << endl;
        cout << "Ganancia: " << proyecto.ganancia << endl;
        cout << "Beneficio: " << proyecto.beneficio << endl;
        cout << "Predecesores: ";
        if (proyecto.predecesores.empty()) {
            cout << "Ninguno";
        } else {
            for (int pred : proyecto.predecesores) {
                cout << pred << " ";
            }
        }
        cout << endl;
        cout << "Maximizador: " << proyecto.maximizador << endl << endl;
    }
}
