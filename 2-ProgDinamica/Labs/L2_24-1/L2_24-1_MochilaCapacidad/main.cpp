/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 19 de setiembre de 2024, 3:26 p. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
int billeteraCapacidad(vector<int>&billetes,int capacidad,int n);

/*
 * 
 */
int main(int argc, char** argv) {
    vector<int> billetes = {20,20,50,50,50,100};
    int capacidad = 270; 
    int n = billetes.size(); 
    
    if(billeteraCapacidad(billetes,capacidad,n)){
        cout << "Puede entregar el vuelto"<<endl;
    }else{
        cout << "No se puede entregar el vuelto"<<endl;
    }
    
    return 0;
}

int billeteraCapacidad(vector<int>&billetes,int capacidad,int n){
    
    int dp[n+1][capacidad+1]{};
    
    //inicializaciones 
    for(int i=0; i<=n; i++){
        dp[i][0] = 1; 
    }
    for(int i=1; i<=capacidad; i++){
        dp[0][i] = 0; 
    }
    
    //analizamos
    for(int i=1; i<=n; i++){
        for(int j=1; j<=capacidad; j++){
             
            dp[i][j] = dp[i-1][j]; // cap < peso (no entra)
            
            if(dp[i][j]==0 and capacidad>=billetes[i-1]){  // cap >= peso
                dp[i][j] = dp[i-1][j-billetes[i-1]]; 
            }
            
        }
    }
    
    // IMPRESION DE LA MATRIZ DP
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= capacidad; j++) {
            cout << setw(4)<< dp[i][j];
        }
        cout << endl;
    }
    
    return dp[n][capacidad]; /* SIEMPRE RETORNAR */
}

