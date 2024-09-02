
/* 
 * File:   main.cpp
 * Author: BlueCod (mell1)
 *
 * Created on 31 de agosto de 2024, 3:08 p. m.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define N 5 //max almacen

int atender(int x,int y,int almacen[N][N],int n,int cantPed,int *pedido,int solucion[N][N]);
int verificaPedido(int *pedido,int cantPed,int numProducto);
void quitoPedido(int *pedido,int numProducto,int cantPed);
int pedidoCompleto(int *pedido,int cantPed);
void recolocoProducto(int *pedido,int cantPed,int numProducto);
/*
 * 
 */
int main(int argc, char** argv) {
    // A -> 1 centena
    // M -> 2 centena
    // V -> 3 centena
    int n=5, c=4,pedido[N] = {105,301,250,108};
    int almacen[N][N] = {{120,310,110,225,210},
			{110,301,210,105,315},
			{301,220,250,205,101},
			{325,110,108,105,315},
			{210,202,208,210,110}}; 
    int solucion[N][N]{},posibleAtencion=0;
    
    cout<<"PARTE A:"<<endl;
    posibleAtencion = atender(0,0,almacen,n,c,pedido,solucion);
    if(posibleAtencion) cout <<"Si es posible atender el pedido"<<endl;
    else cout<<"No es posible atender el pedido"<<endl;
    
    cout<<endl<<"PARTE B:"<<endl;
    for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout<<setw(4)<<solucion[i][j];
		}
		cout<<endl;
	}
    
    return 0;
}

int atender(int x, int y,int almacen[N][N],int n,int cantPed,int *pedido,int solucion[N][N]){
    //CONDICIONES BASE PARA LA RECURSION 
    if(x==N or y==N) return 0; //si se sale del tablero  
    if(pedidoCompleto(pedido,cantPed)) return 1;
    
    //1. verificaPedido
    int numProducto = almacen[x][y];
    bool bandera=false;
    if(verificaPedido(pedido,cantPed,numProducto)){
        //1.1 tacho el pedido
        quitoPedido(pedido,numProducto,cantPed);
        //1.2 pinto en solucion
        solucion[x][y] = numProducto;
        bandera = true;
    }
    //2. Avanzo :)
    if(atender(x+1,y,almacen,n,cantPed,pedido,solucion)) return 1; //2.1 abajo
    if(atender(x,y+1,almacen,n,cantPed,pedido,solucion)) return 1; //2.2 derecha
    
    //3. BACKTRACKING - arreglo mis errores
    if(bandera) recolocoProducto(pedido,cantPed,numProducto);
    solucion[x][y]=0;
    
    return 0;
}

int pedidoCompleto(int *pedido,int cantPed){
    for(int i=0;i<cantPed;i++){
        if(pedido[i]!=0){
            return 0;
        }
    }
    return 1;
}

// verifica si se puede atender el pedido o no 
int verificaPedido(int *pedido,int cantPed,int numProducto){
    for(int i=0;i<cantPed;i++){
        if(pedido[i]==numProducto){
            return 1;
        }
    }
    return 0;
}

void quitoPedido(int *pedido,int numProducto,int cantPed){
    for(int i=0; i<cantPed;i++){
        if(numProducto==pedido[i]){
            pedido[i] = 0;
            return;
        }
    }
}

void recolocoProducto(int *pedido,int cantPed,int numProducto){
    for(int i=0; i<cantPed;i++){
        if(0==pedido[i]){
            pedido[i] = numProducto;
            return;
        }
    }
}