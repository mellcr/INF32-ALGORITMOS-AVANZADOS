#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
#define MAX 10
int contador=0; //cuenta el numero de soluciones :) 
vector<vector<int>> todasSoluciones; 
vector<int> solucion; 

int calcularPosiblesPedidos(int pos,int peso,int *t,int nCarne,int difMaxPeso);
int valida(int difMaxPeso);
void quitar(int *t,int nCarne); 

/*
 *                       
 */

int main(int argc, char** argv) {
    int P = 15, difMaxPeso = 4, n=6,t[MAX] = {2, 8, 9, 6, 7, 6};
    
    calcularPosiblesPedidos(0,P,t,n,difMaxPeso); 
    
    cout<<"Numero de pedidos que se puede atender de "<<P<<" kg: "
            << contador<<endl; 
    cout << "Peso de los cortes de cada pedido: "; 
    
    for (const auto& solucion : todasSoluciones) {
        cout << "{ ";
        for (int num : solucion) {
            cout << num << " ";
        }
        cout << "}";
    }
    
    
    
    
    
    return 0;
}

int calcularPosiblesPedidos(int pos,int peso,int *t,int nCarne,int difMaxPeso){
    if(pos==nCarne or peso<0) return 0;  //salida del arreglo 
    
    if(peso==0 and valida(difMaxPeso)){ //se encuentra una combinacion 
        contador++;
        //validar el peso 
        todasSoluciones.push_back(solucion);
        quitar(t,nCarne);
        //return 1;
    }
    
    solucion.push_back(t[pos]);
    calcularPosiblesPedidos(pos+1,peso-t[pos],t,nCarne,difMaxPeso);
    
    solucion.pop_back(); //deshacer la eleccion baktracking 
    calcularPosiblesPedidos(pos+1,peso,t,nCarne,difMaxPeso); 
    
    return 0; 
}


int valida(int difMaxPeso){
    if(solucion.size()<=1) return 1; 
    
    //recorre el vector solucion y busca al menos uno cumpla 
    for(int i=0; i< solucion.size(); i++){    
        for(int j=0; j<solucion.size(); j++){
            if(i!=j and abs(solucion[i]-solucion[j])<=difMaxPeso){
                return 1;
            }
        }
    }
    
    return 0;
}

void quitar(int *t,int nCarne){
    
    for(int i=0,k=0; i<nCarne and k<solucion.size();i++){
        if(t[i]==solucion[k]){
            t[i] = 0; //borro de T 
            k++; 
        }
    }
}