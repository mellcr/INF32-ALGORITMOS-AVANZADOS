/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 19 de setiembre de 2024, 4:10 p. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
bool canPartition(vector<int>& nums) ;

/*
 * 
 */
int main(int argc, char** argv) {
    vector<int> A = {1, 5, 11, 5};
    
    if (canPartition(A))
        cout << "Verdadero" << endl;
    else
        cout << "Falso" << endl;   
    
    
    return 0;
}


bool canPartition(vector<int>& nums) {
    int n = nums.size();
    int sum = 0;

    // Calcular la suma total de los elementos
    for (int num : nums)
        sum += num;

    // Si la suma es impar, no es posible dividir en dos subconjuntos iguales
    if (sum % 2 != 0)
        return false;

    int target = sum / 2;

    // Crear un arreglo de DP donde dp[i] es true si se puede obtener la suma i
    vector<bool> dp(target + 1, false);
    dp[0] = true; // Se puede lograr la suma 0 con ningún elemento

    // Llenar la tabla de DP
    for (int num : nums) {
        for (int j = target; j >= num; --j) {
            dp[j] = dp[j] || dp[j - num];
        }
    }

    // El valor final nos dirá si es posible obtener la suma target
    return dp[target];
}

