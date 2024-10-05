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
    int numPaq; 
    int ganancia; 
    int peso;
    int maximizar;
};

struct Almacen{
    int capacidad; 
    int sobrante;
    int gananciaTotal; 
};

void llenadoDeContenedor(vector<Datos> &paquetes,
        int nPaq,struct Almacen &almacen);
bool compara(struct Datos &a, struct Datos&b);

/*
 * 
 */

int main() {
    vector<Datos> paquetes = {{1,10,2},{2,15,3},{3,10,5},
                              {4,24,12},{5,8,2}};
    Almacen almacen = {16,16,0};
    
    llenadoDeContenedor(paquetes,paquetes.size(),almacen);
     

    return 0;
}

void llenadoDeContenedor(vector<Datos> &paquetes,
        int nPaq,struct Almacen &almacen){
    /*Hallo el maximizar de cada paquete*/
    for(int i=0; i<nPaq;i++){
        paquetes[i].maximizar = paquetes[i].ganancia / paquetes[i].peso;
    }
    /*Ordeno los paquetes -> maximizar ganancia y minimizar peso*/
    sort(paquetes.begin(),paquetes.end(),compara);
    
    /*Añado los paquetes a la mochila (contenedor)*/
    for(int i=0; i<nPaq; i++){
        if(almacen.sobrante>=paquetes[i].peso){
            almacen.sobrante -= paquetes[i].peso;
            almacen.gananciaTotal += paquetes[i].ganancia;
        }
    }
    
    cout << "Peso sobrante: "<<almacen.sobrante<<endl;
    cout << "Ganancia de la exportacion: "<<almacen.gananciaTotal<<endl;
}

bool compara(struct Datos &a, struct Datos&b){
    return a.maximizar > b.maximizar; 
}