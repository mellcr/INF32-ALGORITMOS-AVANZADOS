/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: Rosa Cristina La Cruz Musayon
 * Codigo: 20213714
 * Created on 5 de octubre de 2024, 08:10
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Producto {
    int Req;
    int longitud;
    int altura;
    int area;
};

bool compara(struct Producto &a, struct Producto& b) {
    return a.area > b.area;
}

void cortesPlaca(vector<struct Producto> &Productos, int AreaMax, int &cantLam,
        double &Porcentaje) {
    for (int i = 0; i < Productos.size(); i++) {
        Productos[i].area = Productos[i].altura * Productos[i].longitud;
    }
    sort(Productos.begin(), Productos.end(), compara);
    int cont = 0;
    vector<int> Temp(1, AreaMax);
    for (int i = 0; i < Productos.size(); i++) {
        for (int k = 0; k < Temp.size();) {
            if (Temp[k] - Productos[i].area >= 0) {
                Temp[k] -= Productos[i].area;
                cont++;
            } else {
                int a = Temp[Temp.size() - 1];
                if (Productos[i].area > Temp[Temp.size() - 1]) {
                    Temp.push_back(AreaMax);
                    cantLam++;
                }
                k++;
            }
            if (cont == Productos[i].Req) {
                cont = 0;
                break;
            }
        }
    }
    int suma=0;
    for (int num : Temp) {
        cout << num << " ";
        suma += num;
    }
    cout<<endl;
    Porcentaje = ((suma/(double)(cantLam*AreaMax)))*100;
}

int main(int argc, char** argv) {
    vector<struct Producto> Productos{
        {5, 2, 3},
        {10, 9, 3},
        {15, 14, 7},
        {20, 15, 20},
        {20, 22, 18},};
        //cantLam inicia en 1 por que iniciamos con una lamina
    int AreaMax = 50 * 50, cantLam = 1;
    double Porcentaje = 0;
    cout.precision(2);
    cout<<fixed;
    cortesPlaca(Productos, AreaMax, cantLam, Porcentaje);
    
    cout << "Cantidad de laminas de 50x50 es " << cantLam  << endl;
    ;
    cout << "el Porcentaje de mermas residuales es " << Porcentaje << "%";

    return 0;
}

