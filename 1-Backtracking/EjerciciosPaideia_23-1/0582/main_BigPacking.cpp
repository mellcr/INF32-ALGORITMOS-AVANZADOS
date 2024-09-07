#include <iostream>

#define N 5

using namespace std;

int solucion[N];
int k=0;

int buscarSolucion(int pesos[N],int peso,int i,int size){
	if (pesos[i]==peso){
		solucion[k] = peso;
		/*La solucion encontrada es*/
		for (int j=0; j<=k; j++){
			cout << solucion[j] << " ";
		}
		cout << endl;
		//return 1;
		return 0;
	}
	if (i==N || peso<0){
		return 0;
	}
	solucion[k] = pesos[i];
	k++;
	if (buscarSolucion(pesos,peso-pesos[i],i+1,size)){
		return 1;
	}
	k--;
	return buscarSolucion(pesos,peso,i+1,size);
}

int main(){
	int peso = 20, n=5;
	int pesos[N] = {17,2,3,5,12};
	if (buscarSolucion(pesos,peso,0,n)){
		cout << "Hay solucion";
	}
	else {
		cout << "No hay solucion";
	}
	
	return 0;
}
