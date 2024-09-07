#include <iostream>
#define MAX 10
using namespace std;
int lista[MAX]; //arreglo para almacenar los elementos que forman la soluci�n
int y=0; //variable para hacer el seguimiento a los elementos de lista[];
int x=0; //contador de soluciones encontradas

int empaca (int i, int n, int peso, int paquete[])//Devuelve 1 si pudo armar una soluci�n y 0 en caso contrario.
{
	cout<<"Llamada recursiva i="<<i<<", n="<<n<<", peso="<<peso<<", paquete[i]="<<paquete[i]<<endl;
	//CASO BASE
	if (i==n || peso<0){//cuando hemos recorrido todos los elementos O 
					   //cuando el peso es negativo, es decir la suma de los paquetes sobrepasa la capacidad
		if (i==n) cout<<"Retorna 0 por recorrer todo el arreglo"<<endl;
		if (peso<0) cout<<"Retorna 0 por sobrepasar la capacidad"<<endl;
		return 0;//Retornamos 0, es decir que el camino tomado no es una soluci�n
	}
	if (paquete[i]-peso==0){//--------ENCONTRAMOS UNA SOLUCI�N
		cout<<"paquete[i="<<i<<"]="<<paquete[i]<<", peso="<<peso<<endl;
		cout<<"Retorna 1"<<endl;
		
		lista[y]=paquete[i];//guardamos el paquete que forma parte de la soluci�n
		
		//Mostramos la soluci�n encontrada
		int k;
		cout<<"Soluci�n: ";
		for (k=0;k<=y;k++)
			cout<<lista[k]<< " ";
		cout<<endl;
		x++;
		//return 1;//se encontr� la soluci�n y terminan las llamadas recursivas.
	}
	lista[y]=paquete[i];//Como se asume que el camino es el correcto, inclu�mos en la lista soluci�n
	y++;
	if (empaca (i+1, n, peso-paquete[i], paquete)){//asumimos que es el camino con una soluci�n
		cout<<"Retorna 1"<<endl;
		return 1;
	}
	else{
		y--;//Como empaca()=0, es decir no es una soluci�n, se "borra" el elemento considerado en la soluci�n
		return empaca(i+1, n, peso, paquete);//para probar i+2
	}
}
int main(){
	int paquete[]={1, 4, 5, 7};
	int peso=12;
	int n=4;
	empaca (0, n, peso, paquete);
	if (x)
		cout<<"Hay soluci�n"<<endl;
	else 
		cout<<"NO hay soluci�n"<<endl;
}
