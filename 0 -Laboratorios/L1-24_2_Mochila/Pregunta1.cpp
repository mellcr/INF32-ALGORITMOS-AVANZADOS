/* 
 * File:   Pregunta1.cpp
 * Author: BlueCod 
 *
 * Created on 14 de octubre de 2024, 8:50 a. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Pregunta1.h"
#define N 5
#define M 7

void pregunta1(){
    //kilos de ropa sucia 
    int ropa[N][M] = {
                    {14, 11, 10, 19, 14, 11, 0},
                    {20, 11 , 11, 10, 15, 17, 8},
                    {15, 16, 15, 16, 0, 0, 0},
                    {11, 4, 19, 12, 10, 0, 0},
                    {18, 12, 0, 0, 0, 0, 0}
                    };
    //
    int matrizRespuesta[N][M] = {
                    {0, 0, 0, 0, 0, 0, -1},
                    {0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, -1, -1, -1},
                    {0, 0, 0, 0, 0, -1, -1},
                    {0, 0, -1, -1, -1, -1, -1}
                    };
    int capacidad = 50;
    encontrarSolucion(ropa, 0, capacidad, matrizRespuesta);  
    
}

void encontrarSolucion(int ropa[N][M], int inicio, int capacidad, int matrizRespuesta[N][M]) {
    int capacidadTotal=capacidad*N, capacidadTotalUsada=0;
    
    //por cada piso :)
    for (int i = 0; i < N; i++) {
        cout << "Piso " << i + 1 << ": " << endl << "Peso Total = ";
        
        int totalUsadoLavadora=0;
        backLavadora(ropa[i], inicio, capacidad, capacidad, matrizRespuesta[i],totalUsadoLavadora);
        capacidadTotalUsada+=totalUsadoLavadora;
                
        cout << "Pacientes que tendrán lavada la ropa = ";
        for (int j = 0; j < M; j++) {
            if (matrizRespuesta[i][j] > 0) {
                cout << "R" << j + 1 << " ";
            }
        }
        cout << endl;
        cout << "Pacientes que NO tendrán lavada la ropa = ";
        for (int j = 0; j < M; j++) {
            if (matrizRespuesta[i][j] == 0) {
                std::cout << "R" << j + 1 << " ";
            }
        }
        cout << endl << std::endl;
    }
    
    cout<<"Porcentaje total de ocupacion de las lavadoras: "<< capacidadTotalUsada/(double)capacidadTotal*100
            <<"%"<<endl<<endl;
}

bool backLavadora(int ropa[M], int inicio, int capacidad, int capacidadInicio, int matrizRespuesta[M], int &totalUsado) {
    
    if (capacidad < 0) {
        return false;
    }
    
    // Cuando llega a la ultima prenda imprime la capacidad total usada 
        if (inicio == M) {
        if (capacidad - ropa[inicio] >= 0) {
            totalUsado = capacidadInicio - (capacidad - ropa[inicio]);
            cout << capacidadInicio - (capacidad - ropa[inicio]) << endl;
            matrizRespuesta[inicio] = 1;
        }
        else {
            totalUsado = capacidadInicio - capacidad;
            cout << capacidadInicio - capacidad << endl;
        }
        return true;
    }
    
    
    if (ropa[inicio + 1] != 0) {
        //Solo lava 1 ciclo -> llena lavadora con prendas mas pesadas 
        if (ropa[inicio] > ropa[inicio + 1]) {
            //prueba la ropa pesada primero-> ropa[inicio]
            if (backLavadora(ropa, inicio + 1, capacidad - ropa[inicio], capacidadInicio, matrizRespuesta,totalUsado) == false) {
                //si falla -> ropa[inicio+1]
                if (backLavadora(ropa, inicio + 2, capacidad - ropa[inicio + 1], capacidadInicio, matrizRespuesta,totalUsado) == false) {
                    return false;
                }
                else {
                    matrizRespuesta[inicio + 1] = 1;
                    return true;
                }
            }
            else {
                matrizRespuesta[inicio] = 1;
                return true;
            }
        }
        else {
            //ropa pesada> ropa[inicio+1]
            if (backLavadora(ropa, inicio + 2, capacidad - ropa[inicio + 1], capacidadInicio, matrizRespuesta,totalUsado) == false) {
                //si falla -> ropa[inicio]
                if (backLavadora(ropa, inicio + 1, capacidad - ropa[inicio], capacidadInicio, matrizRespuesta,totalUsado) == false) {
                    return false;
                }
                else {
                    matrizRespuesta[inicio] = 1;
                    return true;
                }
            }
            else {
                matrizRespuesta[inicio + 1] = 1;
                return true;
            }
        }
    }   //ropa[inicio+1] = 0 -> solo se puede evaluar: ropa[inicio]
    else {
        if (capacidad - ropa[inicio] >= 0) {
            totalUsado = capacidadInicio - (capacidad - ropa[inicio]);
            cout << capacidadInicio - (capacidad - ropa[inicio]) << endl;
            matrizRespuesta[inicio] = 1;
        }
        else {
            totalUsado = capacidadInicio - capacidad;
            cout << capacidadInicio - capacidad << endl;
        }
        return true;
    }
}