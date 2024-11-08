/* 
 * File:   Pregunta2.cpp
 * Author: BlueCod 
 *
 * Created on 14 de octubre de 2024, 8:50 a. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
#include "Pregunta2.h"
vector<int> almacenRosita(5,0);

void pregunta2(){
    vector<int> cantidadesProd = {2,3,1,4};
    vector<int> capcidadMochilas = {3,2,5,1,3};
    int cantMochila = capcidadMochilas.size(), cantProd  = cantidadesProd.size();
    vector<vector<int>> almacenSolu(cantMochila);
    
    
    //cout << backMochilaTodo2(0,cantidadesProd,capcidadMochilas,cantMochila,almacenRosita,almacenSolu);
    backMochilaRosa(0,cantidadesProd,capcidadMochilas);
    
}

void backMochilaRosa(int index,vector<int> &cantidadesProd,vector<int> &capcidadMochilas){
    if(index==cantidadesProd.size()){
        /*Imprimimos la solucion encontrada*/
        imprime3(almacenRosita);
        
        return;
    }
    
    
    /*Itero hasta acaabar el vector de los productos*/
    for(int i=0;i<capcidadMochilas.size();i++){
        /*Si el producto entra en la mochila -> lo asigno*/
        if(capcidadMochilas[i] >= cantidadesProd[index]){
            capcidadMochilas[i] -= cantidadesProd[index];
            almacenRosita[i]+=cantidadesProd[index];
            backMochilaRosa(index+1,cantidadesProd,capcidadMochilas);
            /*En caso falle, quito el producto y devuelvo capacidad*/
            almacenRosita[i]-=cantidadesProd[index];
            capcidadMochilas[i]+= cantidadesProd[index];
        }
    }
}




bool backMochilaTodo2(int index,vector<int> &cantidadesProd,vector<int> &capcidadMochilas,
        int cantMochila,int cantProd,vector<vector<int>> &almacenSolu){
    if(index==cantProd){
        /*Imprimimos la solucion encontrada*/
        imprime2(almacenSolu);
        
        return true;
    }
    
    
    /*Itero hasta acaabar el vector de los productos*/
    for(int i=0;i<cantMochila;i++){
        /*Si el producto entra en la mochila -> lo asigno*/
        if(capcidadMochilas[i] >= cantidadesProd[index]){
            capcidadMochilas[i] -= cantidadesProd[index];
            almacenSolu[i].push_back(cantidadesProd[index]);
            if(backMochilaTodo2(index+1,cantidadesProd,capcidadMochilas,cantMochila,cantProd,
                    almacenSolu)) return true;
            /*En caso falle, quito el producto y devuelvo capacidad*/
            almacenSolu[i].pop_back();
            capcidadMochilas[i]+= cantidadesProd[index];
        }
    }
    return false;
}

void backMochilaTodo(int index,vector<int> &cantidadesProd,vector<int> &capcidadMochilas,
        int cantMochila,int cantProd,vector<vector<int>> &almacenSolu){
    if(index==cantProd){
        /*Imprimimos la solucion encontrada*/
        imprime2(almacenSolu);
        
        return;
    }
    
    
    /*Itero hasta acaabar el vector de los productos*/
    for(int i=0;i<cantMochila;i++){
        /*Si el producto entra en la mochila -> lo asigno*/
        if(capcidadMochilas[i] >= cantidadesProd[index]){
            capcidadMochilas[i] -= cantidadesProd[index];
            almacenSolu[i].push_back(cantidadesProd[index]);
            backMochilaTodo(index+1,cantidadesProd,capcidadMochilas,cantMochila,cantProd,
                    almacenSolu);
            /*En caso falle, quito el producto y devuelvo capacidad*/
            almacenSolu[i].pop_back();
            capcidadMochilas[i]+= cantidadesProd[index];
        }
    }
}

void imprime(vector<vector<int>> &almacenSolu){
    for (int i = 0; i < almacenSolu.size(); i++) {
        cout << "Mochila " << i + 1 << ": ";  // Imprime el índice de la mochila (empezando en 1)
        if (almacenSolu[i].empty()) {
            cout << "(vacía)";  // Si no hay productos en la mochila
        } else {
            for (int prod : almacenSolu[i]) {
                cout << prod + 1 << " ";  // Imprime los productos almacenados (sumando 1 si es necesario)
            }
        }
        cout << endl;
    }
    cout << endl<<endl<<endl;
}

void imprime2(vector<vector<int>> &almacenSolu){
    cout << "{";
    for (int i = 0; i < almacenSolu.size(); i++) {
        int suma = 0;
        for (int prod : almacenSolu[i]) {
            //cout<< prod<< " "; 
            suma += prod;  // Sumar todos los productos en la mochila
        }

        // Imprimir la suma de los productos en esa ubicación o 0 si está vacía
        cout << suma;

        if (i != almacenSolu.size() - 1) {
            cout << ", ";  // Separador entre valores
        }
    }
    cout << "}" << endl;
}

void imprime3(vector<int> &almacenRosita){
    cout << "{";
    for (int i = 0; i < almacenRosita.size(); i++) {

        // Imprimir la suma de los productos en esa ubicación o 0 si está vacía
        cout << almacenRosita[i];

        if (i != almacenRosita.size() - 1) {
            cout << ", ";  // Separador entre valores
        }
    }
    cout << "}" << endl;
}
    