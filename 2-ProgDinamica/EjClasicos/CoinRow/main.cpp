/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: alulab14
 *
 * Created on 19 de septiembre de 2024, 11:39 AM
 */

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;
int coinrow(vector<int> &monedas,int c);
/*
 * 
 */
int main(int argc, char** argv) {
    vector<int> monedas = {5,1,2,10,6,2};
    int n=6;
    
    cout << coinrow(monedas,n); 
    
    
    return 0;
}

/*tablero solucion -> Fn */
int coinrow(vector<int> &monedas,int c){
	//arreglo debe ser tam= c+1 para guardar 
	//el ant del primero -> 0
	int Fn[c+1]; 
	
	Fn[0]=0;        //ant de la 1ra 
	Fn[1] = monedas[0]; //la 1ra moneda

    //el i se trabaja sobre Fn 
    //empieza en el primer vacio

    for (int i = 2; i < c + 1; i++) {
        int maxAnt = Fn[i - 1]; //max valor ant
        int maxNuevo = monedas[i - 1] + Fn[i - 2]; //moneda act + max no ady
        int max;
        if (maxAnt > maxNuevo) {
            max = maxAnt;
        } else {
            max = maxNuevo;
        }
        Fn[i] = max;
    }

    cout << "F(n) :";
    for (int i = 0; i <= c; i++) {
        cout << setw(3) << Fn[i];
    }
    cout << endl; 
    
    return Fn[c]; 
	 
}