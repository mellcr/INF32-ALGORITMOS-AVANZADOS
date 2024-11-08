/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 15 de octubre de 2024, 7:15 a. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
struct Producto {
    int Req;
    int longitud;
    int altura;
    int area;
};

struct Lamina{
    int area; 
    int residuo; 
};

bool compara(Producto &a, Producto &b);
void cortesLaminas(vector<Producto> &productos,int nProd,vector<Lamina> &almacen,Lamina &lamina,double &porc);

/*
 * 
 */
int main(int argc, char** argv) {
    vector<struct Producto> productos{
        {5, 2, 3},
        {10, 9, 3},
        {15, 14, 7},
        {20, 15, 20},
        {20, 22, 18}};
    struct Lamina lamina{50*50,50*50}  ;  
    vector<Lamina>almacen(1,lamina);
    double porc=0; 
    
    cortesLaminas(productos,productos.size(),almacen,lamina,porc);
    cout << "Cantidad de laminas de 50x50 es " << almacen.size()  << endl;
    cout << "el Porcentaje de mermas residuales es " << porc << "%";
    
    return 0;
}

void cortesLaminas(vector<Producto> &productos,int nProd,vector<Lamina> &almacen,Lamina &lamina,double &porc){
    /*Calculo el area por producto*/
    for(int i=0; i<nProd; i++){
        productos[i].area = productos[i].longitud * productos[i].altura;
    }
    
    sort(productos.begin(),productos.end(),compara);
    
    /*Despachamos los pedidos con mayor area, sin atender pedidos parcialmente*/
    for(int i=0; i<nProd; i++){
        vector<Lamina> temp(almacen);
        int req=0;
        /*Verifico desde el inicio de mis laminas en el almacen*/
        for(int j=0; j<temp.size(); ){
            if(productos[i].area<= temp[j].residuo){
                temp[j].residuo-=productos[i].area; 
                req++;
                /*Se atendio todo el pedido*/
                if(req==productos[i].Req){
                    almacen.assign(temp.begin(), temp.end());
                    break;
                }
            }
            else{
                j++; 
                if(j==temp.size()){
                    temp.push_back(lamina);
                }
            }
            
        }
    }
    
    int sumaRes=0;
    for (int i=0; i<almacen.size(); i++) {
        cout<<almacen[i].residuo<<" ";
        sumaRes += almacen[i].residuo;
    }
    cout<<endl; 
    porc = ((sumaRes/(double)(almacen.size()*lamina.area)))*100;
}

bool compara(Producto &a, Producto &b){
    return a.area > b.area; 
}