#include <iostream>
#define MAX 10
using namespace std;
int lista[MAX]; //arreglo para almacenar los elementos que forman la solución
int y=0; //variable para hacer el seguimiento a los elementos de lista[];
int x=0; //contador de soluciones encontradas

int valida (int k, int n, int predecesor[], int proyecto[])//función que me indica si mi predecesor está ya incluido en mi lista solución (lista[])
{
	int contador_predecesores=0; //contador de predecesores encontrados
	if (predecesor[k]==-1){//Si el proyecto que se está analizando no tiene predecesores
		return 1;//Entonces se puede incluir en la solución
	}
	
	for (int i=0; i<n; i++)
	{
		if (predecesor[k]==lista[i]){//Si encuentro el predecesor en la lista que va teniendo los proyectos de mi solución
			contador_predecesores++;//aumento mi contador de predecesores
		}
	}
	if (contador_predecesores)//Si encontré el predecesor en la lista de mi solución (lista[])
		return 1;//Entonces se puede adicionar en la solución
	
	return 0;//OJO: si el contador_predecesores es 0, entonces NO SE PUEDE AÑADIR el proyecto.
}

int empaca (int i, int n, int presupuesto, int costo[], int predecesor[], int proyecto[])//Devuelve 1 si pudo armar una solución y 0 en caso contrario.
{
	//CASO BASE
	if (i==n || presupuesto<0){//cuando hemos recorrido todos los elementos O 
					   //cuando el peso es negativo, es decir la suma de los paquetes sobrepasa la capacidad
		return 0;//Retornamos 0, es decir que el camino tomado no es una solución
	}
	if (costo[i]-presupuesto==0 && valida (i,y,predecesor, proyecto)){//--------ENCONTRAMOS UNA SOLUCIÓN
		
		lista[y]=proyecto[i];//guardamos el proyecto que forma parte de la solución
		
		//Mostramos la solución encontrada
		int z;
		cout<<"Solución: ";
		for (z=0;z<=y;z++)
			cout<<"P"<<lista[z]<< " ";
		cout<<endl;
		x++;
		//return 1;//se encontró la solución y terminan las llamadas recursivas.
	}
	lista[y]=proyecto[i];//Como se asume que el camino es el correcto, incluímos en la lista solución
	y++;
	if (valida (i,y,predecesor, proyecto) && empaca (i+1, n, presupuesto-costo[i], costo, predecesor, proyecto)){//asumimos que es el camino con una solución
		//OJO: primero se invoca a la función valida(), si es que retorna FALSO, ya no se llama a la función recursiva empaca()
		return 1;
	}
	else{
		y--;//Como empaca()=0, es decir no es una solución, se "borra" el elemento considerado en la solución
		return empaca(i+1, n, presupuesto, costo, predecesor, proyecto);//para probar i+2
	}
}
int main(){
	int proyecto[]={0,1,2,3,4,5,6,7};//según enunciado
	int costo[]={7,1,3,2,4,5,1,5};//según enunciado
	int predecesor[]={-1,-1,1,-1,2,4,-1,6};//según enunciado
	int presupuesto=10;//según enunciado
	int n=8;//según enunciado
	
	empaca (0, n, presupuesto, costo, predecesor, proyecto);
	if (x)
		cout<<"Hay solución"<<endl;
	else 
		cout<<"NO hay solución"<<endl;
		
	
	return 0;
}
