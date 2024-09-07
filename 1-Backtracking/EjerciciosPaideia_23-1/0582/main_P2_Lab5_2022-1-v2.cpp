#include <iostream>

#define N 9
#define M 5
#define MAXMOV 8

using namespace std;

int movimientos[2][8];
int cantPasos = 0;

void inicializaTablero(char tablero[N][M],int n,int m){
	for (int i=0; i<n; i++){
		for (int j=0; j<m; j++){
			tablero[i][j] = ' ';
		}
	}
}

void colocaMinas(char tablero[N][M]){
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

void mostrarTablero(char tablero[N][M],int n,int m){
	for (int i=0; i<n; i++){
		for (int j=0; j<m; j++){
			cout << tablero[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int evaluaMovimiento(char tablero[N][M],int n,int m,int x,int y){
	if (tablero[x][y]==' ' && x<n && y<m && x>=0 && y>=0){
		return 1;
	}
	return 0;
}


int encontrarSoluciones(char tablero[N][M],int n,int m,int inicioX, int inicioY,int finX,int finY,char letra, int pasos){
	int nuevoX, nuevoY;
	if (cantPasos>=pasos){
		return 0;
	}
	if (inicioX == finX && inicioY == finY && cantPasos==pasos-1){
		tablero[inicioX][inicioY] = letra;
		mostrarTablero(tablero,n,m);
		return 1;
	}
	for (int i=0; i<MAXMOV; i++){
		nuevoX = inicioX + movimientos[i][0];
		nuevoY = inicioY + movimientos[i][1];
		if (evaluaMovimiento(tablero,n,m,nuevoX,nuevoY)){
			tablero[nuevoX][nuevoY] = letra++;
			cantPasos++;
			if (encontrarSoluciones(tablero,n,m,nuevoX,nuevoY,finX,finY,letra,pasos)){
				return 1;
			}
			tablero[nuevoX][nuevoY] = ' ';
			letra--;
			cantPasos--;
		}
	}
	return 0; /*Esto es para terminar la jugada del ultimo paso y volver al anterior*/
}

void genereMovimientos(){
	movimientos[0][0]= -1;
	movimientos[0][1]= 0;
	movimientos[1][0]= 1;
	movimientos[1][1]= 0;
	movimientos[2][0]= 0;
	movimientos[2][1]= 1;
	movimientos[3][0]= 0;
	movimientos[3][1]= -1;
	movimientos[4][0]= -1;
	movimientos[4][1]= -1;
	movimientos[5][0]= -1;
	movimientos[5][1]= 1;
	movimientos[6][0]= 1;
	movimientos[6][1]= -1;
	movimientos[7][0]= 1;
	movimientos[7][1]= 1;
}

int main(){
	char tablero[N][M], letra='B';
	int n=9, m=5, pasos=12;
	inicializaTablero(tablero,n,m);
	genereMovimientos();
	colocaMinas(tablero);
	tablero[0][0] = 'A';
	encontrarSoluciones(tablero,n,m,0,0,n-1,m-1,letra,pasos);
	return 0;
}
