#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <vector>
//GRASP
#define maxitera 10000        // Número máximo de iteraciones
#define alfa 0.3              // Parámetro alfa para el RCL
using namespace std;
#include "Mochila.h"


void mochilaGRASP(){
    vector<int> paq = {10, 2, 1, 5, 9, 8}; // paq que puedo meter en la mochila
    int peso = 14;
    cargaMochilaGRASP(paq,peso);
    
    
}

void cargaMochilaGRASP(vector<int> &paq,int peso){
    //1. Variabes para la mejor solucion
    int mejor = 999999;
    vector<int>  maxsol;
    
    //2.Mientras <no se cumpla condicion de parada> 
    for(int i=0;i<maxitera;i++){
        //2. RCL inicializacion
        srand(time(NULL));
        vector<int> solucion;
        sort(paq.begin(),paq.end(),compara); //de mayor a menor
        vector<int> paquetes = paq; //copia de paq para trabajar en esta iteracion
        int residual=peso; //inicializacion de la variable que guarda el resto
        
        //Mientras aun hayan paquetes
        while(!paquetes.empty()){
            //3. Construimos el RCL
            int beta = paquetes[0];
            int tau = paquetes[paquetes.size()-1];
            double rcl = beta - alfa * (beta - tau);
        }
    }
    
}

bool compara(int a, int b){
    return a>b; // 9 4 2 1 (DESC)
}
    

/***************** GENETICO ***********************/
void mochilaGenetica(){
    
    
    
    
}