/* 
 * File:   Pregunta2.cpp
 * Author: BlueCod 
 *
 * Created on 14 de octubre de 2024, 1:27 p. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
#include "Preguntas.h"

void pregunta2(){
    
    vector<int> longitud = {1,2,3,4};
    vector<int> precio = {2,5,7,8};
    
    //lo que quiero sumarle es el de al costado no el anterior
    //mochilaGanancia(longitud,precio, longitud.size());
    cout <<corteGananciaMax2(longitud,precio,longitud.size(), longitud.size());
}

void mochilaGanancia(vector<int>&longitud,vector<int>&precio, int n){
    int dp[n+1][n+1]{};
    /*Inicializamos valores*/
    for(int i=0; i<=n;i++) dp[0][i] = 0;
    for(int i=0; i<=n;i++) dp[i][0] = 0;
    
    for(int i=1; i<=n;i++){
        for(int j=1;j<=n;j++){  //capacidad
            if(j<longitud[i-1]){
                dp[i][j] = dp[i-1][j]; //anterior
            }
            else{   //j>=longitud
                dp[i][j] = max(dp[i-1][j],precio[i-1]+dp[i][j-longitud[i-1]]);
            }
        }
    }
   
    // IMPRESION DE LA MATRIZ DP
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << setw(5)<< dp[i][j];
        }
        cout << endl;
    }
}

int corteGananciaMax2(vector<int>& longitudes,vector<int>& precios,int n, int longTotal){
    int sumaLong=0; 
    for(int i=0; i<n; i++){
        //suma total de longitudes 
        sumaLong += longitudes[i]; 
    }
    //cout << sumaLong; 
    int dp[n+1][sumaLong+1]{};    

    
//    for(int i=0; i<sumaLong; i++){
//        dp[0][i] = 0; //para 0 cortes hay 0 ganancia
//    }
//    for(int i=0; i<n; i++){
//        dp[i][0] = 0; 
//    }

    
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=sumaLong; j++){
            
            if(j < longitudes[i-1]){
                dp[i][j] = dp[i-1][j];  //el anterior 
            }
            else{
                // si entra el corte en dicha capacidad (long tronco) 
                //analizamos la 
                dp[i][j] = max(precios[i-1]+dp[i][j-longitudes[i-1]], dp[i-1][j]);
            }
        }
    }
    
    //muestra las ganancias maximas hasta la suma maxima que tienen los troncos 
    for (int i = 0; i < n; i++) {
        for(int j=0; j<sumaLong; j++){
            cout << setw(3) << dp[i][j]; 
        }
        cout << endl; 
    }
    
    
    
    //solamente quiero la ganancia maxima cuando la sumaLong = longTotal (de la barra que tengo) 
    return dp[n][longTotal];
}