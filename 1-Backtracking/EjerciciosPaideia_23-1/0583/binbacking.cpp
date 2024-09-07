#include <iostream>
using namespace std;

int empaca (int i, int n, int peso, int paquete[])//Devuelve 1 si pudo armar una solución y 0 en caso contrario.
{
	//cout<<"Llamada recursiva i="<<i<<", n="<<n<<", peso="<<peso<<", paquete[i]="<<paquete[i]<<endl;
	//CASO BASE
	if (i==n || peso<0){//cuando hemos recorrido todos los elementos O 
					   //cuando el peso es negativo, es decir la suma de los paquetes sobrepasa la capacidad
		//cout<<"Retorna 0"<<endl;
		return 0;//Retornamos
	}
	if (paquete[i]-peso==0){//--------ENCONTRAMOS UNA SOLUCIÓN
		//cout<<"paquete[i="<<i<<"]="<<paquete[i]<<", peso="<<peso<<endl;
		//cout<<"Retorna 1"<<endl;
		return 1;
	}
	if (empaca (i+1, n, peso-paquete[i], paquete)){//asumimos que es el camino con una solución
		//cout<<"Retorna 1"<<endl;
		return 1;
	}
	else 
		return empaca(i+1, n, peso, paquete);//para probar i+2
}
int main(){
	int paquete[]={1, 4, 5, 7};
	int peso=12;
	int n=4;
	
	if (empaca (0, n, peso, paquete))
		cout<<"Se encontró una solución"<<endl;
	else 
		cout<<"NO se encontró una solución"<<endl;
}
