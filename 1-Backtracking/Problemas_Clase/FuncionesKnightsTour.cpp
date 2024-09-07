/* 
 * File:   FuncionesKnightsTour.cpp
 * Author: BlueCod 
 *
 * Created on 6 de setiembre de 2024, 5:20 p. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
#include "FuncionesKnightsTour.h"
#define N 8
int movX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int movY[8] = {1, 2, 2, 1, -1, -2, -2, -1};

/*
 * PROBLEMA: CABALLO DE AJEDREZ
 *  Este problema usa el método de sneak peak (ver la casilla antes de colocarla) 
 */

vector<vector<int>> inicializarMatriz( int numInsertar) {
    vector<vector<int>> todo; 
    
    for(int i=0;i<N;i++){
        vector<int> actual; 
        for(int k=0; k<N; k++){
            actual.push_back(numInsertar); 
        }
        todo.push_back(actual); 
    }
    return todo; 
}

void iniciaRecorridoCab(){
    vector<vector<int>> tablero = inicializarMatriz(-1);

    tablero[0][0] = 0; //inicia el recorrido 
    int numMov = 0; 
    numMov++;
    if(!recorridoBack(0,0,numMov,tablero)){
        cout << " No se encontro solucion"<<endl;
    }
    else{
        for (const auto& fila : tablero) {
        for (int elemento : fila) {
            cout << setw(4)<<elemento;
        }
        cout << endl;
        }
    }
}

int recorridoBack(int x,int y,int numMov,vector<vector<int>> &tablero){
    //¿Cuando se halla una solucion? 
    //-> el caballo recorre UNA VEZ cada casilla (64 mov) 
    if(numMov ==N*N){
        return 1; //se encontro una solucion
    }
    
    //Verificamos para cada mov posible del caballo en una casilla
    for(int i=0; i<N;i++){
        int nuevoX = x+movX[i];
        int nuevoY = y+movY[i];
        
        //¿Es posible hacer ese movimiento?
        if(esMovValido(nuevoX,nuevoY,tablero)){
            //nos movemos :) 
            tablero[nuevoX][nuevoY] = numMov; 
            if(recorridoBack(nuevoX,nuevoY,numMov+1,tablero)) return true; 
            
            //si no es posible retrocedemos y volvemos poner la casilla como no visitada (-1)
            //despues de la recursion:) 
            tablero[nuevoX][nuevoY] = -1; 
        }
    }
    return 0; 
}

int esMovValido(int x,int y,vector<vector<int>> &tablero){
    // tablero[x][y] = -1 -> casilla no visitada 
    if(x<N and y<N and x>=0 and y>=0 and tablero[x][y]==-1) return 1; 
    return 0;
}