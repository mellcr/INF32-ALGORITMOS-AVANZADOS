#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
void buscaCambio(vector<int> &monedero,int monto,int n,vector<int> &vuelto);
bool comparar(int a, int b);

/*
 * HEURISTICA     
 */

int main(int argc, char** argv) {
    vector<int> monedero = {1,2,5,10,20,50,100};  // monedas disponibles
    int n =  monedero.size();
    int monto = 27;
    vector<int> vuelto;                           // vector solucion
    
    buscaCambio(monedero,monto,n,vuelto);
    
    return 0;
}

void buscaCambio(vector<int> &monedero,int monto,int n,vector<int> &vuelto){
    //ordenamos el arreglo 
    sort(monedero.begin(),monedero.end(), comparar);
    
    // bucle que recorre todo el arreglo monedero
    for(int i=0; i<monedero.size();i++){
        // por cada moneda se itera las veces que se necesite usarla 
        // ya que la idea es reducir las monedas 
        
        while(monto>=monedero[i]){
            monto-=monedero[i];
            vuelto.push_back(monedero[i]);
        }
    }
    
    for(int i=0; i<vuelto.size() ; i++){
        cout << setw(3)<< vuelto[i]; 
    }
}

bool comparar(int a, int b){
    return a>b;     // DESCENDENTE: 3 2 1 
    //return a<b;   // ASCENDENTE 1 2 3
}