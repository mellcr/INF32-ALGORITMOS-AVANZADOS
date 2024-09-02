
/* 
 * File:   main.cpp
 * Author: BlueCod 
 *
 * Created on 2 de setiembre de 2024, 2:20 p. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define N 4
void impriMatrizSol(int sol[N],int n, int*paq);
int empaca(int i,int n,int peso,int *paq, int sol[N]);
/*
 * 
 */

int main(int argc, char** argv) {
    int n=4,peso=15;
    int paq[]={1,3,12,5};
    int sol[N]{};
    
    empaca(0,n,peso,paq,sol);
    impriMatrizSol(sol,n,paq); 
    
    return 0;
}

void impriMatrizSol(int sol[N],int n, int*paq){
    for(int i = 0; i < n; i++) {
            if(sol[i] == 1) {
                cout << paq[i] << " ";
            }
        }
}

