/* 
 * File:   main.cpp
 * Author: BlueCod 
 * Created on 2 de setiembre de 2024, 2:20 p. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define N 4
void imprimesol(int sol[N],int n, int*paq);
int empaca(int i,int n,int peso,int *paq, int sol[N]);
/*
 * 
 */

int main(int argc, char** argv) {
    int n=4,peso=15;
    int paq[]={1,3,12,5};
    int sol[N]{};
    
    empaca(0,n,peso,paq,sol);
    imprimesol(sol,n,paq); 
    
    return 0;
}

void imprimesol(int sol[N],int n, int*paq){
    for(int i = 0; i < n; i++) {
            if(sol[i] == 1) {
                cout << paq[i] << " ";
            }
        }
}

int empaca(int i,int n,int peso,int *paq, int sol[N]){
    
    if(i==n or peso<0) return 0;
    int num = paq[i]; 
    
    // encuentra solucion posible
    if(num==peso){
        sol[i] = 1;        
        return 1;
    }

    //peso - paq[i] -> usa el paquete
    if(empaca(i+1,n,peso-paq[i],paq,sol)){
        sol[i] = 1;
        return 1; //es una posible solucion usar este paquete
    }
    else{ 
        //ya no considera el paquete
        sol[i] = 0;
        return(empaca(i+1,n,peso,paq,sol));    
    }
}