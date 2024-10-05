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

struct Proyecto {
    int id;
    int costo;
    int ganancia;
    int beneficio;
    vector<int>Predecesores;
    int Maximizar;
};

bool compara(struct Proyecto& a, struct Proyecto&b) {
    return a.Maximizar > b.Maximizar;
}

bool CumpleRequisitos(struct Proyecto &Pro, vector<struct Proyecto> &Elegidos) {
    if (Pro.Predecesores.empty()) return true;
    if (Elegidos.empty()) return false;
    int cant = 0;
    for (int i = 0; i < Pro.Predecesores.size(); i++) {
        for (int k = 0; k < Elegidos.size(); k++) {
            if (Pro.Predecesores[i] == Elegidos[k].id) cant++;
        }
    }
    if (cant == Pro.Predecesores.size()) return true;
    else return false;
}
bool NoRepetidos(vector<struct Proyecto> &Elegidos, int id){
    for(int i=0;i<Elegidos.size();i++){
        if(Elegidos[i].id == id) return false;
    }
    return true;
}
int ObtenerLaGanancia(vector<struct Proyecto> &Proyectos, int N, int P) {
    vector<struct Proyecto> Elegidos;
    int ganancia = 0;
    for (int i = 0; i < Proyectos.size(); i++) {
        Proyectos[i].Maximizar = (Proyectos[i].ganancia * Proyectos[i].beneficio) / Proyectos[i].costo;
    }
    sort(Proyectos.begin(), Proyectos.end(), compara);
    int presupuesto = P,i;
    while (true) {
        for (i = 0; i < Proyectos.size(); i++) {
            if (presupuesto - Proyectos[i].costo >= 0) {
                if (CumpleRequisitos(Proyectos[i], Elegidos)) {
                    if (NoRepetidos(Elegidos, Proyectos[i].id)) {
                        Elegidos.push_back(Proyectos[i]);
                        ganancia += Proyectos[i].ganancia;
                        presupuesto -= Proyectos[i].costo;
                        break;
                    }
                }
            }
        }
        if (i == Proyectos.size()) break;
    }
    if (!Elegidos.empty()) {
        for (struct Proyecto pro : Elegidos) {
            cout << pro.id << " ";
        }
        cout << endl;
    }
    return ganancia;
}

int main(int argc, char** argv) {
    vector<struct Proyecto> Proyectos{
        {1, 80, 150, 2},
        {2, 20, 80, 5,
            {4}},
        {3, 100, 300, 1,
            {1, 2}},
        {4, 100, 150, 4},
        {5, 50, 80, 2},
        {6, 10, 50, 1,
            {2}},
        {7, 50, 120, 2,
            {6}},
        {8, 50, 150, 4,
            {6}},};
    int N = 8, P = 250;
    int gananciafinal = ObtenerLaGanancia(Proyectos, N, P);
    cout << "Ganancia: " << gananciafinal;
    return 0;
}

