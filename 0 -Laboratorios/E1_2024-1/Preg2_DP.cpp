/* 
 * File:   Preg2_DP.cpp
 * Author: BlueCod 
 *
 * Created on 14 de octubre de 2024, 4:23 p. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
#include "Preguntas.h" 


void pregunta2(){
    vector<int > monedas = {2,5,10,20};
    vector<int > monedas2 = {1, 2, 10, 20};
    int monto=7;
    int nFormas = contarFormas(monedas2,monto,monedas2.size());
    cout << "Numero de formas de obtener el monto "<<monto<<" es: "<<nFormas<<endl;
    
}

int contarFormas(vector<int>&monedas,int monto, int nMonedas){
    int dp[nMonedas+1][monto+1]{};
    
    /*Inicializamos*/
    for(int i=0;i<=monto;i++) dp[0][i] = 0;
    for(int i=0;i<=nMonedas;i++) dp[i][0] = 1;
    
    for(int i=1;i<=nMonedas;i++){
        for(int j=1;j<=monto;j++){
            dp[i][j] = dp[i-1][j]; //anterior
            /*Si la moneda entra en esa "capacidad" (monto)*/
            if(j>=monedas[i-1]){   
                /*Acumulo la cantidad de formas para alcanzar ese monto j*/
                dp[i][j] += dp[i][j - monedas[i - 1]];
            }
        }
    }
    
    
    /*Impresion*/
    for(int i=0;i<=nMonedas;i++){
        for(int j=0; j<=monto;j++){
            cout<<setw(3)<<dp[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    
    return dp[nMonedas][monto];
}
