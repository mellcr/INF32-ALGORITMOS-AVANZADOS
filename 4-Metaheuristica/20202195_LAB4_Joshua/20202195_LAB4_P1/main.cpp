/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alulab14
 *
 * Created on 8 de junio de 2024, 08:02 AM
 */

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <climits>

using namespace std;

int evaluarSolucion(int nuevaSolucion[],int N, int velocidadDisco[],
        int K, int velocidad[]){
    int velocidadRestante[K];
    copy(velocidadDisco,velocidadDisco+K,velocidadRestante);
    int menorVelocidad=INT_MAX;
    for(int i=0; i<N; i++){
        velocidadRestante[nuevaSolucion[i]]-=velocidad[i];
    }
    for(int i=0; i<K; i++)
        menorVelocidad=min(menorVelocidad,velocidadRestante[i]);
    return menorVelocidad;
}

void construccion(int velocidad[],int N,int velocidadDisco[],int nuevaSolucion[],
        int K){
    int numSeleccionados=0;
    int velocidadRestante[K];
    bool seleccionado[N]={false};
    copy(velocidadDisco,velocidadDisco+K,velocidadRestante);
    /*Ordenaremos las tablas segun las velocidades que requieran*/
    sort(velocidad,velocidad+K,greater<int>());
    /*Buscaremos llenar todas las tablas*/
    while(numSeleccionados<N){
        /*RCL para las tablas*/
        int RCLTablas[N];
        int tamanioRCLTablas=0;
        int limiteTablas=max(1,(int)(0.3*N));
        for (int i = 0, j = 0; i < N && tamanioRCLTablas < limiteTablas; i++) {
            if (!seleccionado[i]) {
                RCLTablas[tamanioRCLTablas++] = i;
            }
        }
        int indexTabla=rand()%tamanioRCLTablas;
        seleccionado[RCLTablas[indexTabla]]=true;
        /*Hacemos los RCL*/
        int RCL[K];
        int tamanioRCL=0;
        
        /*Ordenaremos la velocidad de los discos de mayor a menor*/
        sort(velocidadRestante,velocidadRestante+K,greater<int>());
        
        /*Calcularemos la velocidad restante*/
        int restante[K];
        for(int j=0; j<K; j++){
            restante[j]=velocidadRestante[j]-velocidad[RCLTablas[indexTabla]];
        }
        /*Construimos los RCL con los discos que menos haran que disminuyan la 
         * velocidad*/
        int limite=max(1,(int)(0.3*K));
        sort(restante,restante+K,greater<int>());
        int umbral=restante[limite-1];
        for(int j=0; j<K; j++){
            if(velocidadRestante[j]-velocidad[RCLTablas[indexTabla]]<=umbral)
                RCL[tamanioRCL++]=j;
        }
        int index=rand()%tamanioRCL;
        int discoSeleccionado=RCL[index];
        /*Lo agregamos a la solucion*/
        nuevaSolucion[numSeleccionados]=discoSeleccionado;
        velocidadRestante[discoSeleccionado]-=velocidad[RCLTablas[indexTabla]];
        numSeleccionados++;
    }
}

void imprimirSolucion(int mejorSolucion[],int N, int velocidadDisco[], int K, 
        int velocidad[]){
    for(int i=0; i<N; i++){
        cout<<"Tabla "<<i+1<<": Disco "<<mejorSolucion[i]+1<<endl;;
        velocidadDisco[mejorSolucion[i]]-=velocidad[i];
    }
    int minimaVelocidad=INT_MAX;
    int guardarDisco;
    for(int i=0;i<K; i++){
        if(velocidadDisco[i]<minimaVelocidad){
            minimaVelocidad=velocidadDisco[i];
            guardarDisco=i;
        }
    }
    cout<<"Esta solución tiene una velocidad mínima de grupo de "<<minimaVelocidad<<
            " IOPs que se da en el disco "<<guardarDisco+1<<"."<<endl;
}

void grasp(int capacidad[],int velocidad[],int N,
        int capacidadDisco[],int velocidadDisco[],int maxIteraciones, 
        int mejorSolucion[], int K){
    int mejorTiempo=0;
    for(int i=0; i<maxIteraciones; i++){
        int nuevaSolucion[N]={0};
        
        construccion(velocidad,N,velocidadDisco,nuevaSolucion,K);
        
        int nuevoTiempo=evaluarSolucion(nuevaSolucion,N,velocidadDisco, K, 
                velocidad);
        if(nuevoTiempo>mejorTiempo){
            mejorTiempo=nuevoTiempo;
            copy(nuevaSolucion,nuevaSolucion+N, mejorSolucion);
        }
    }
}

int main(int argc, char** argv) {
    int N=6;
    /*Informacion tablas*/
    int capacidad[N]={20,10,15,100,50,100};
    int velocidad[N]={150,100,80,50,120,10};
    int K=3;
    int capacidadDisco[N]={800,750,850};
    int velocidadDisco[N]={250,200,200};
    
    int maxIteraciones=100000;
    int mejorSolucion[N];
    
    grasp(capacidad,velocidad,N,capacidadDisco,velocidadDisco,
            maxIteraciones, mejorSolucion, K);
    imprimirSolucion(mejorSolucion,N,velocidadDisco,K,velocidad);
    return 0;
}

