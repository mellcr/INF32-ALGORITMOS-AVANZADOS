
/* 
 * File:   main.cpp
 * Author: cueva
 *
 * Created on 19 de septiembre de 2024, 10:21 AM
 */

#include <iostream>
#include <algorithm>

using namespace std;

// retorna un indcice
int conflictos(int ini[],int fin[], int i)
{
	//retrocede , desde ahi hacia atras hay una solucion
	// 
	for (int j = i - 1; j >= 0; j--) 
		//fin[ant] <= ini[actual]          -> verifica si una de las presentaciones entra
		if (fin[j] <= ini[i])	return j;

	return -1;
	//solo da el primero que cumpla -> arreglos ordenados 
}

int maxbeneficio(int ini[],int fin[],int ben[], int n)
{   int temp;

	// intercambio de tp c: 
	for (int i=0; i < n; i++) 
        for(int j=i+1;j<n;j++)
           if (fin[i]>fin[j])
           {
               temp=fin[i];
               fin[i]=fin[j];
               fin[j]=temp;
			   
               temp=ini[i];
               ini[i]=ini[j];
               ini[j]=temp;    
			   
               temp=ben[i];
               ben[i]=ben[j];
               ben[j]=temp;              
           } 
    
	int dp[n];
	dp[0] = ben[0];

	//PROGRAMACION DINAMICA 
	for (int i = 1; i < n; i++) {
		int beneficioActual = ben[i];       // el beneficio actual u.u
		int l = conflictos(ini,fin, i);			//
		//Si no hay conflicto -> añado beneficio al dp		beneficioActual + beneficio en ese indice
		if (l != -1) beneficioActual = beneficioActual + dp[l]; 
		dp[i] = max(beneficioActual, dp[i - 1]);
		
		for(int j=0;j<i;j++)
            cout << dp[j] <<" ";
        cout << endl;    
	}
	int result = dp[n - 1];
        
        for(int i=0;i<n;i++)
            cout << dp[i] <<" ";
        
	return result;
}

int main()
{
    int ini[]={4,5,2,6};
    int fin[]={15,10,4,12};
    int ben[]={100,30,40,80};

    int n = sizeof(ini) / sizeof(ini[0]);
    cout << endl<<"El beneficio es: "	<< maxbeneficio(ini,fin,ben, 4);
	return 0;
}

