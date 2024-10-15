/* 
 * File:   P1_Combustible.cpp
 * Author: BlueCod 
 *
 * Created on 14 de octubre de 2024, 3:27 p. m.
 */
#include <iostream>
#include <vector>
#include <climits>  // Para usar INT_MAX
using namespace std;
#include "Preguntas.h"
// Usamos un vector para representar el combustible en cada ciudad
vector<int> arr = {1, 2, 1, 4, 2, 3};
int n = arr.size();  //(número de ciudades)
    
void pregunta1(){
    
    cout<< minimosAterrizajes();
}

int minimosAterrizajes() {
    vector<int> dp(n, INT_MAX);

    // Si no hay ciudades o no hay combustible para partir, no se puede llegar
    if (n == 0 || arr[0] == 0) {
        return INT_MAX;  
    }
    
    dp[0]=0;
    for(int i=1;i<n;i++){   //desde la ciudad 2 -> i=1
        /*Quiero verificar si desde la ciudad j puedo llegar a i*/
        for(int j=0; j<i;j++){
            /* desde ciudad j + combustible para saber a q ciudad llego  && Se tiene que poder llegar a la ciudad j (antes)*/
            if(i<=j+arr[j] and dp[j]!=INT_MAX){
                /*Aterrizajes hasta j + 1 ,  dp[i] que es el min de aterrizajes para llegar a i (valor que se actualiza en el for de j)*/
                dp[i] = min(dp[j]+1,dp[i]);
            }
        }
    }

    // Imprimir el número mínimo de aterrizajes para llegar a cada ciudad
    for (int i = 0; i < n; i++) {
        cout << dp[i] << " ";
    }
    cout << endl;

    return dp[n - 1];  // Retornar el número mínimo de aterrizajes para llegar a la última ciudad
}
