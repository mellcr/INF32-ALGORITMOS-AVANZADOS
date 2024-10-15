/* 
 * File:   main.cpp
 * Author: Rosa Cristina La Cruz Musayon
 * Codigo: 20213714
 * Created on 14 de octubre de 2024, 16:13
 */

#include <iostream>
#include <climits>
#include <iomanip>
using namespace std;
#define N 5
#define MAX_MOV 4
int MinCosto = INT_MAX;
int Solucion[N][N]{};
int solucionFinal[N][N];
int Movimientos[MAX_MOV][MAX_MOV] ;
void generarMovimientos(){
    Movimientos[0][0] = 1; Movimientos[0][1] = 0;
    Movimientos[1][0] = 0; Movimientos[1][1] = -1;
    Movimientos[2][0] = 0; Movimientos[2][1] = 1;
    Movimientos[3][0] = -1; Movimientos[3][1] = 0;
}
void imprimir(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<setw(2)<<Solucion[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}
void Copiar(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            solucionFinal[i][j] = Solucion[i][j];
        }
    }
}
bool Esvalido(int x, int y,int n, int Tabla[N][N]){
    if(x >=0 and y>=0 and x<n and y<n and Tabla[x][y] != 0 and Solucion[x][y] == 0) return true;
    return false;
}
void Robot(int Tabla[N][N],int x,int y,int n,int &costo){
    if (x == n-1 and y == n-1){ 
        if(costo < MinCosto){
            MinCosto  = costo;
            imprimir();
            return;
        }
    }
    int a,b;
    for(int i=0;i<MAX_MOV;i++){
        int nueva_x = x+ Movimientos[i][0];
        int nueva_y = y+ Movimientos[i][1];
        
        if(Esvalido(nueva_x, nueva_y,n,Tabla)){
            costo += Tabla[nueva_x][nueva_y];
            Solucion[nueva_x][nueva_y] = 1;
            Robot(Tabla,nueva_x,nueva_y,n,costo);
            costo -= Tabla[nueva_x][nueva_y];
            Solucion[nueva_x][nueva_y] = 0;
        }
    }
}
int main(int argc, char** argv) {
    int Tabla[N][N] = {
        {1,2,0,1,0},
        {3,2,3,1,1},
        {0,1,2,0,0},
        {3,1,1,2,3},
        {0,1,3,1,1},
    };
    int costo = Tabla[0][0];
    generarMovimientos();
    Solucion[0][0] =1;
    
    Robot(Tabla,0,0,N,costo);
    cout << MinCosto<<endl;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<setw(2)<<solucionFinal[i][j];
        }
        cout<<endl;
    }
    

    return 0;
}

