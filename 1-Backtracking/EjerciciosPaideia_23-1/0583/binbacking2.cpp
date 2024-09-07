#include <iostream>
#define MAX 10
using namespace std;
int lista[MAX]; //arreglo para almacenar los elementos que forman la solución
int y=0; //variable para hacer el seguimiento a los elementos de lista[];
int x=0; //contador de soluciones encontradas

int empaca (int i, int n, int peso, int paquete[])//Devuelve 1 si pudo armar una solución y 0 en caso contrario.
{
	cout<<"Llamada recursiva i="<<i<<", n="<<n<<", peso="<<peso<<", paquete[i]="<<paquete[i]<<endl;
	//CASO BASE
	if (i==n || peso<0){//cuando hemos recorrido todos los elementos O 
					   //cuando el peso es negativo, es decir la suma de los paquetes sobrepasa la capacidad
		if (i==n) cout<<"Retorna 0 por recorrer todo el arreglo"<<endl;
		if (peso<0) cout<<"Retorna 0 por sobrepasar la capacidad"<<endl;
		return 0;//Retornamos 0, es decir que el camino tomado no es una solución
	}
	if (paquete[i]-peso==0){//--------ENCONTRAMOS UNA SOLUCIÓN
		cout<<"paquete[i="<<i<<"]="<<paquete[i]<<", peso="<<peso<<endl;
		cout<<"Retorna 1"<<endl;
		
		lista[y]=paquete[i];//guardamos el paquete que forma parte de la solución
		
		//Mostramos la solución encontrada
		int k;
		cout<<"Solución: ";
		for (k=0;k<=y;k++)
			cout<<lista[k]<< " ";
		cout<<endl;
		x++;
		//return 1;//se encontró la solución y terminan las llamadas recursivas.
	}
	lista[y]=paquete[i];//Como se asume que el camino es el correcto, incluímos en la lista solución
	y++;
	if (empaca (i+1, n, peso-paquete[i], paquete)){//asumimos que es el camino con una solución
		cout<<"Retorna 1"<<endl;
		return 1;
	}
	else{
		y--;//Como empaca()=0, es decir no es una solución, se "borra" el elemento considerado en la solución
		return empaca(i+1, n, peso, paquete);//para probar i+2
	}
}
int main(){
	int paquete[]={1, 4, 5, 7};
	int peso=12;
	int n=4;
	empaca (0, n, peso, paquete);
	if (x)
		cout<<"Hay solución"<<endl;
	else 
		cout<<"NO hay solución"<<endl;
}
