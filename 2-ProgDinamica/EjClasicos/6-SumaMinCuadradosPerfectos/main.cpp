/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 20 de setiembre de 2024, 10:51 a. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
int menorCantCuadradosPerfParaSumarN(int N);

/*
 * 
 */
int main(int argc, char** argv) {
    int N = 12; // 1 < N <  500
    
    cout << setw(3)<<menorCantCuadradosPerfParaSumarN(N);
    
    return 0;
}

int menorCantCuadradosPerfParaSumarN(int N){
    //arreglo Fn
    vector<int> dp (N+1,INT_MAX); //inicializamos todo en un numero muy grande
    dp[0] = 0; //inicializacion
    dp[1] = 1; 
    
    
    //recorro desde i=1 hasta N y en cada uno calculo cuantos 
    //numeros perfectos como minimo tengo que sumar para que sean igual que i
    for(int i=2; i<=N;  i++){
        //verificamos todos los menores cuadrados perfectos <= i (que sumen i)
        for(int j=1; j*j <= i;j++ ){ //mientras el cuadrado perfecto sea menor que i
            //evalua todos los valores y se queda con el mínimo (los chanca)
            dp[i] = min(dp[i],dp[i-j*j] + 1); 
        }
    }
    
    
    for(int i=0; i<=N; i++){
        cout << setw(3)<< dp[i];
    }
    cout << endl; 
    
    
    //retornamos el ultimo minimo valor 
    return dp[N-1]; //siempre es la capacidad del arreglo -1
}