
/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 2 de setiembre de 2024, 2:20 p. m.
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ratio>
using namespace std;

bool compara(int a, int b);
int cargamochila(int *paq, int peso, int n); 

/*
 * HEURISTICA     
 */

int main(int argc, char** argv) {
    int mochila[] = {2,5,10,12};
    int n=4; 
    int peso = 15; 
    
    cout << "Resto: "<<setw(3)<<cargamochila(mochila,peso,n);
    
    return 0;
}


bool compara(int a, int b){
    return a>b;
}

int cargamochila(int *paq, int peso, int n){
    sort(paq,paq+n,compara);//puntero a funcion
    
    int resto = peso; 
    for(int i=0; i<n; i++){
        if(resto-paq[i] >= 0 )
            resto-=paq[i]; 
    }
       
    return resto; 
}