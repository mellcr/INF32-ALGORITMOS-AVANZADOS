#include <iostream>
#define MAX 10
using namespace std;
int lista[MAX]; //arreglo para almacenar los elementos que forman la soluci�n
int y=0; //variable para hacer el seguimiento a los elementos de lista[];
int x=0; //contador de soluciones encontradas

int valida (int k, int n, int predecesor[], int proyecto[])//funci�n que me indica si mi predecesor est� ya incluido en mi lista soluci�n (lista[])
{
	int contador_predecesores=0; //contador de predecesores encontrados
	if (predecesor[k]==-1){//Si el proyecto que se est� analizando no tiene predecesores
		return 1;//Entonces se puede incluir en la soluci�n
	}
	
	for (int i=0; i<n; i++)
	{
		if (predecesor[k]==lista[i]){//Si encuentro el predecesor en la lista que va teniendo los proyectos de mi soluci�n
			contador_predecesores++;//aumento mi contador de predecesores
		}
	}
	if (contador_predecesores)//Si encontr� el predecesor en la lista de mi soluci�n (lista[])
		return 1;//Entonces se puede adicionar en la soluci�n
	
	return 0;//OJO: si el contador_predecesores es 0, entonces NO SE PUEDE A�ADIR el proyecto.
}

int empaca (int i, int n, int presupuesto, int costo[], int predecesor[], int proyecto[])//Devuelve 1 si pudo armar una soluci�n y 0 en caso contrario.
{
	//CASO BASE
	if (i==n || presupuesto<0){//cuando hemos recorrido todos los elementos O 
					   //cuando el peso es negativo, es decir la suma de los paquetes sobrepasa la capacidad
		return 0;//Retornamos 0, es decir que el camino tomado no es una soluci�n
	}
	if (costo[i]-presupuesto==0 && valida (i,y,predecesor, proyecto)){//--------ENCONTRAMOS UNA SOLUCI�N
		
		lista[y]=proyecto[i];//guardamos el proyecto que forma parte de la soluci�n
		
		//Mostramos la soluci�n encontrada
		int z;
		cout<<"Soluci�n: ";
		for (z=0;z<=y;z++)
			cout<<"P"<<lista[z]<< " ";
		cout<<endl;
		x++;
		//return 1;//se encontr� la soluci�n y terminan las llamadas recursivas.
	}
	lista[y]=proyecto[i];//Como se asume que el camino es el correcto, inclu�mos en la lista soluci�n
	y++;
	if (valida (i,y,predecesor, proyecto) && empaca (i+1, n, presupuesto-costo[i], costo, predecesor, proyecto)){//asumimos que es el camino con una soluci�n
		//OJO: primero se invoca a la funci�n valida(), si es que retorna FALSO, ya no se llama a la funci�n recursiva empaca()
		return 1;
	}
	else{
		y--;//Como empaca()=0, es decir no es una soluci�n, se "borra" el elemento considerado en la soluci�n
		return empaca(i+1, n, presupuesto, costo, predecesor, proyecto);//para probar i+2
	}
}
int main(){
	int proyecto[]={0,1,2,3,4,5,6,7};//seg�n enunciado
	int costo[]={7,1,3,2,4,5,1,5};//seg�n enunciado
	int predecesor[]={-1,-1,1,-1,2,4,-1,6};//seg�n enunciado
	int presupuesto=10;//seg�n enunciado
	int n=8;//seg�n enunciado
	
	empaca (0, n, presupuesto, costo, predecesor, proyecto);
	if (x)
		cout<<"Hay soluci�n"<<endl;
	else 
		cout<<"NO hay soluci�n"<<endl;
		
	
	return 0;
}
