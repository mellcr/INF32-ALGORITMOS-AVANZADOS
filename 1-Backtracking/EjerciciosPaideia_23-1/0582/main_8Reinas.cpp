#include <iostream>
#define N 8

using namespace std;

/*Variable global que me va a permitir contar el # de soluciones que encuentre*/
int cantSoluciones = 0;

/*Vamos a colocar todas las posiciones del tablero en 0 que significa que esta libre*/
void inicializarTablero(int tablero[N][N]){
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			tablero[i][j] = 0;
		}
	}
}

void mostrarSolucion(int tablero[N][N]){
	cout << "Solucion " << cantSoluciones << endl;
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			cout << tablero[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int validarJugada(int tablero[N][N],int columna,int fila){
	/*Buscamos una reina en la misma fila a la izquierda*/
	for (int i=0; i<columna; i++){
		if (tablero[fila][i]==1)
			return 0;
	}
	/*Validamos diagonal izquierda superior*/
	for (int i=fila-1,j=columna-1; i>=0 && j>=0; j--, i--){
		if (tablero[i][j]==1)
			return 0;
	}
	/*Validamos diagonal izquierda inferior*/
	for (int i=fila+1,j=columna-1; i<N && j>=0; j--, i++){
		if (tablero[i][j]==1)
			return 0;
	}
	return 1;
}

int encontrarSoluciones(int tablero[N][N],int columna){
	/* Caso base*/
	if (columna==N){
		cantSoluciones++;
		mostrarSolucion(tablero);
	//	return 1;
		return 0;
	}
	/*Si estoy en una columna, debo probar con esa reina en todas las filas*/
	for (int i=0; i<N; i++){
		if (validarJugada(tablero,columna,i)){
			tablero[i][columna] = 1;
			if (encontrarSoluciones(tablero,columna+1)){
				return 1;
			}
			tablero[i][columna] = 0;
		}
	}
	return 0;
}

int main(){
	int tablero[N][N];
	inicializarTablero(tablero);
	encontrarSoluciones(tablero,0);
	cout << "La cantidad de soluciones es: " << cantSoluciones;
	return 0;
}
