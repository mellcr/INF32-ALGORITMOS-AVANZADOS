/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 2 de setiembre de 2024, 2:20 p. m.
 */

#include <iostream>
#include <iomanip>
using namespace std;
#define N 20
#define MAX_INI  8
int movimientos[8][2]; //matriz global que abarcará los mov 
int cont=0;
void generaMov();
void inicializarTablero(char tablero[N][N]); 
void colocarMinas(char tablero[N][N]); 
void imprime(char terreno[N][N],int n,int m); 
int buscaCamino(char terreno[N][N],int x,int y,int n,int m,char solucion[N][N],char paso); 
int valida(char solu[N][N], int x,int y,int n,int m, char tablero[N][N]);
/*
 * 
 */

int main(int argc, char** argv) {
    char terreno[N][N], solucion[N][N]; 
    int n=9,m=5; 
    char paso= 'A';
    
    generaMov();
    inicializarTablero(terreno); 
    inicializarTablero(solucion); //para la impresion 
    colocarMinas(terreno);
    colocarMinas(solucion); 
    //imprime(solucion,n,m); 
    solucion[0][0] = paso; 
    buscaCamino(terreno,0,0,n,m,solucion,paso); 
    
    return 0;
}
void imprime(char terreno[N][N],int n,int m){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout<<setw(4)<<terreno[i][j];
        }
        cout << endl; 
    }
    cout << endl <<endl;
}
void generaMov(){
    //ABAJO,IZQ,DER,ARRIBA
    movimientos[0][0] = 1; movimientos[0][1] = 0;
    movimientos[1][0] = 0; movimientos[1][1] = -1;
    movimientos[2][0] = 0; movimientos[2][1] = 1;
    movimientos[3][0] = -1; movimientos[3][1] = 0;
	
    /*diagonales: abajDer, ArrIzq, AbajIzq,ArrDer*/
    movimientos[4][0] = 1; movimientos[4][1] = 1;
    movimientos[5][0] = -1; movimientos[5][1] = -1;
    movimientos[6][0] = 1; movimientos[6][1] = -1;
    movimientos[7][0] = -1; movimientos[7][1] = 1;
}
void inicializarTablero(char tablero[N][N]){
	int i, j;
	for (i=0;i<N;i++){
		for (j=0; j<N; j++){
			tablero[i][j] = '0';
		}
	}
}
void colocarMinas(char tablero[N][N]){
	tablero[0][4] = '*';
	tablero[2][2] = '*';
	tablero[4][1] = '*';
	tablero[4][2] = '*';
	tablero[4][4] = '*';
	tablero[5][1] = '*';
	tablero[5][2] = '*';
	tablero[5][4] = '*';
	tablero[6][1] = '*';
	tablero[6][3] = '*';
	tablero[7][0] = '*';
	tablero[7][1] = '*';
	tablero[7][2] = '*';
	tablero[7][3] = '*';
}

//este problema no tiene que pisar, sino simular un peak() -> vista 
int buscaCamino(char terreno[N][N],int x,int y,int n,int m,char solucion[N][N],char paso){
    int nx,ny; 
    //1. condiciones base
    if(x==n or y==m or y<0 or x<0) return 0; 
    //1.2 si ya encontro la solu -> llego al extremo
    if(x==n-1 and y==m-1){
        cont++;
        imprime(solucion,n,m); 
        
        if(cont == 3) return 1; 
        else return 0; 
    }
    
    for (int i = 0; i < MAX_INI; i++) {
        nx = x+movimientos[i][0]; //nuevo x
        ny = y+movimientos[i][1]; //nuevo y 
        
        if(valida(solucion,nx,ny,n,m,terreno)){ //sneakpeak del sgte casillero 
            //es posible solucion
            solucion[nx][ny] = paso+1; //sgte letra 
            //imprime(solucion,n,m); debug
            if(buscaCamino(terreno,nx,ny,n,m,solucion,paso+1)) return 1; 
            // backtracking 
            else solucion[nx][ny] = '0'; 
        }
    }
    
    return 0; 
}

int valida(char solu[N][N], int x,int y,int n,int m, char tablero[N][N]){
    //dentro del tablero && casilla no pintada
    if(x<n and y<m and x>=0 and y>= 0 and solu[x][y]=='0' and
            tablero[x][y]!='*'){
        return 1;
    }
    return 0; 
}

//NOTA: la solucion depende del orden de la matriz de movimientos 
//descubre -> alredor  