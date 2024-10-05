
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
using namespace std;

struct Datos{
    int ganancia;
    int peso;
    int maximizar;
};

void hallaSolu(vector<Datos> &valores,int n,int capacidad, int &sobrante, 
        int &gananciaMax);
bool compara(struct Datos &a, struct Datos &b);


/*
 * MOCHILA GANANCIA  
 */

int main(int argc, char** argv) {
    vector<Datos> valores = {{10,2},{15,3} ,{10,5} , {24,12},{8,2}};  
    int n =  valores.size();
    int capacidad = 16;
    int sobrante=0, gananciaMax =0;
    hallaSolu(valores,n,capacidad,sobrante,gananciaMax);
    cout<<sobrante<<endl;
    cout<<gananciaMax<<endl;
    return 0;
}

/* GANANCIA MAXIMA, MINIMIZA EL PESO*/
void hallaSolu(vector<Datos> &valores,int n,int capacidad, int &sobrante, int &gananciaMax){
    //Maximizamos
    for(int i=0;i<n;i++){
        valores[i].maximizar = valores[i].ganancia / valores[i].peso;
    }
    
    //Ordenamos
    sort(valores.begin(),valores.end(),compara);
    
    sobrante = capacidad;
    for(int i=0; i<n;i++){
        //agarramos el paquete si entra
        //if(sobrante-valores[i].peso>=0){
        if(sobrante>=valores[i].peso){
            sobrante-=valores[i].peso;
            gananciaMax+=valores[i].ganancia;
        }
    }
}

bool compara(struct Datos &a, struct Datos &b){
    return a.maximizar > b.maximizar;
}