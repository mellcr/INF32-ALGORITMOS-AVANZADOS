/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 19 de setiembre de 2024, 6:03 p. m.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//
//int minSubsetSumDifference(vector<int>& nums) {
//    int n = nums.size();
//    int sumTotal = 0;
//
//    // Calcular la suma total de los elementos
//    for (int num : nums) {
//        sumTotal += num;
//    }
//
//    // El objetivo es encontrar la suma más cercana a sumTotal/2
//    int target = sumTotal / 2;
//
//    // Crear una tabla de DP para almacenar si una suma es posible
//    vector<bool> dp(target + 1, false);
//    dp[0] = true; // Es posible obtener una suma de 0 con ningún elemento
//
//    // Llenar la tabla de DP
//    for (int num : nums) {
//        for (int j = target; j >= num; --j) {
//            dp[j] = dp[j] || dp[j - num];
//        }
//    }
//
//    // Buscar la suma más cercana a sumTotal/2 que sea alcanzable
//    int closestSum = 0;
//    for (int i = target; i >= 0; --i) {
//        if (dp[i]) {
//            closestSum = i;
//            break;
//        }
//    }
//
//    // La diferencia mínima es: S - 2 * closestSum
//    return sumTotal - 2 * closestSum;
//}
//
//int main() {
//    vector<int> A = {1, 6, 11, 5};
//    
//    cout << "La diferencia mínima es: " << minSubsetSumDifference(A) << endl;
//
//    return 0;
//}



int minSubsetSumDifference(vector<int>& nums) {
    int n = nums.size();
    int sumTotal = 0;

    // Calcular la suma total de los elementos
    for (int num : nums) {
        sumTotal += num;
    }

    // El objetivo es encontrar la suma más cercana a sumTotal/2
    int target = sumTotal / 2;

    // Crear una tabla de DP de tamaño (n+1) x (target+1)
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    // Inicializar la tabla DP: se puede formar la suma 0 con cualquier conjunto
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = true;  // Suma 0 es siempre alcanzable sin elementos
    }

    // Llenar la tabla DP
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= target; ++j) {
            // Si no consideramos el elemento nums[i-1], el resultado es el mismo que sin este elemento
            dp[i][j] = dp[i-1][j];

            // Si consideramos el elemento nums[i-1], vemos si podemos formar la suma j - nums[i-1]
            if (j >= nums[i-1]) {
                dp[i][j] = dp[i][j] || dp[i-1][j - nums[i-1]];
            }
        }
    }

    // Buscar la suma más cercana a sumTotal/2 que sea alcanzable
    int closestSum = 0;
    for (int j = target; j >= 0; --j) {
        if (dp[n][j]) {
            closestSum = j;
            break;
        }
    }

    // La diferencia mínima es: S - 2 * closestSum
    return sumTotal - 2 * closestSum;
}

int main() {
    vector<int> A = {1, 6, 11, 5};
    
    cout << "La diferencia mínima es: " << minSubsetSumDifference(A) << endl;

    return 0;
}
