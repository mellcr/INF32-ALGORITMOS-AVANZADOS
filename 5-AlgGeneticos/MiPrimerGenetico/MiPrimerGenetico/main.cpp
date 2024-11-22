/* 
 * File:   main.cpp
 * Author: cueva
 *
 * Created on 12 de noviembre de 2024, 03:21 PM
 */

#include <iostream>
#include <ctime>			//para la semilla random
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
//datos que nos da el problema 
#define NITERACIONES 1000
#define NIND 10				//num de individuos de la poblacion
#define Tseleccion 0.3
#define Pcasamiento 0.5
#define Tmutacion 0.5
int *gpaq;

using namespace std;





void muestrapoblacion(vector<vector<int>> poblacion,int *paq){
    for(int i=0;i<poblacion.size();i++){
        for(int j=0;j<poblacion[i].size();j++){
            cout << poblacion[i][j] << "  ";
        }
        cout <<" fo="<< calculafitness(poblacion[i],paq) <<endl;
    }
}


int muestramejor(vector<vector<int>> poblacion,
        int *paq,int peso){
    int mejor=0;
    for(int i=0;i<poblacion.size();i++)
        if(calculafitness(poblacion[mejor],paq)<calculafitness(poblacion[i],paq))
            mejor=i;
    
    cout << endl<<"La mejor solucion es:" << calculafitness(poblacion[mejor],paq)<<endl;
    for(int i=0;i<poblacion[mejor].size();i++){
        cout << poblacion[mejor][i] << "  ";        
    }
    cout << endl;
    return peso-calculafitness(poblacion[mejor],paq);
}

void inversion(vector<vector<int>>&poblacion,
        vector<vector<int>>padres,int *paq,int peso){
    
    for(int i=0;i<padres.size();i++){
        for(int j=0;j<padres[i].size();j++){
            if(padres[i][j]==0)
                padres[i][j]=1;
            else
                padres[i][j]=0;
        }
        if(!aberracion(padres[i],paq,peso))
            poblacion.push_back(padres[i]);
    }
}

void mutacion(vector<vector<int>> &poblacion,vector<vector<int>> padres,
        int *paq,int peso){
    int cont=0;
    int nmuta=round(padres[0].size()*Tmutacion);
    for(int i=0;i<padres.size();i++){
        while(cont<nmuta){
            int ind=rand()%padres[0].size();
            if(padres[i][ind]==0){
                padres[i][ind]=1;
            }
            else
                padres[i][ind]=0;
            cont++;
        }
        if(!aberracion(padres[i],paq,peso))
            poblacion.push_back(padres[i]);     
    }
}

//Como solamente se le pueden pasar 2 parametros, se usa el gpaq global
//si tenemos paq y costo, se tendrian que usar de manera global 
bool compara(vector<int>a,vector<int>b){
    int suma=0,sumb=0;
   
    for(int i=0;i<a.size();i++)
        suma+=calculafitness(a,gpaq);
    for(int i=0;i<b.size();i++)
        sumb+=calculafitness(b,gpaq);
    return suma>sumb;
}
int compacta(vector<int>cromo){
    int num=0;
    for(int i=0;i<cromo.size();i++)
        num+=pow(2,i)*cromo[i];
    
    return num;
    
}

//Quita los duplicados 
void eliminaaberraciones(vector<vector<int>> &poblacion,int *paq){
    map<int,vector<int>> municos;
    
    for(int i=0;i<poblacion.size();i++){
        int num=compacta(poblacion[i]); //pasa el bin a un num entero , se pondra como llave, y el cromosoma será el second
        municos[num]=poblacion[i];
    }
    poblacion.clear(); //limpia el vector de vector
	//recorre el mapa y los vectores (ahora unicos) , los paso al vector de vector
    for(map<int,vector<int>>::iterator it=municos.begin();
            it!=municos.end();it++){
        poblacion.push_back(it->second);
    }   
}

void generarpoblacion(vector<vector<int>> &poblacion,
        int *paq,int peso){
    
    gpaq=paq;
	//la funcion compara 
    sort(poblacion.begin(),poblacion.end(),compara);
	//nos quedamos con la poblacion de 10 elementos 
    poblacion.erase(poblacion.begin()+NIND,poblacion.end());
}


void seleccion(vector<vector<int>>&padres,vector<vector<int>>poblacion,
    int *paq,int n,int peso){
    int ruleta[100]{-1};
    vector<int>supervivencia; //guarda probabilidad de fitness para cada cromosoma
	/*2.1 Mide adaptacion*/
    calculasupervivencia(poblacion,supervivencia,paq);
	
	/*Carga ruleta con la cant dependiendo de su probabilidad
	ruleta = {0, 0,..., 1, 1,..., 2, 2}; // 30 ceros, 50 unos, 20 doses.
	*/
    cargaruleta(supervivencia,ruleta);
	
	/*2.2 Seleccionar mejores adaptados de Pt*/
    int nseleccionados= poblacion.size()*Tseleccion;   //nCromosomas       
    for(int i=0;i<nseleccionados;i++){
        int ind=rand()%100;                            // ruleta tiene 100 elementos
        if(ruleta[ind]>-1)
            padres.push_back(poblacion[ruleta[ind]]);
    } 
}

void cargaruleta(vector<int>supervivencia,int *ruleta){
    int ind=0;
	//recorremos el tamaño de la supervivencia
	//la cual guarda la probabilidad de sobrevivir de cada cromosoma
    for(int i=0;i<supervivencia.size();i++)
        for(int j=0;j<supervivencia[i];j++)
            ruleta[ind++]=i;
}

void calculasupervivencia(vector<vector<int>>poblacion,
    vector<int>&supervivencia, int *paq){
    int suma=0;
    
    for(int i=0;i<poblacion.size();i++)
        suma+=calculafitness(poblacion[i],paq);
    for(int i=0;i<poblacion.size();i++){
        int fit= round(100*(double)calculafitness(poblacion[i],paq)/suma);
        supervivencia.push_back(fit);
    }
}

int calculafitness(vector<int> cromo,int *paq){
    int cont=0;
    
    for(int i=0;i<cromo.size();i++)
        cont+=cromo[i]*paq[i];
    
    return cont; //peso de cromosoa 
    
}

void generapoblacioninicial(vector<vector<int>>&poblacion,int *paq,
        int n,int peso){
    int cont=0;
    
	//Creamos NIND=10 cromosomas 
    while(cont<NIND){ //Tam cromosoma = # paquetes 
        vector <int> vaux;
        for(int i=0;i<n;i++)
            vaux.push_back(rand()%2); //aleatoriamente: 1 o 0 
		//Antes de añadir, verificamos que no sea aberracion
        if(not aberracion(vaux,paq,peso)){
            poblacion.push_back(vaux);
            cont++;
        }
    }
}   

//Aberracion: sobrepasar el peso 
bool aberracion(vector<int>cromo,int *paq,int peso){
    int total=0;
    
    for(int i=0;i<cromo.size();i++)
        total+=cromo[i]*paq[i];
    
    return total>peso;
} 

void mochilaAG(int *paq,int n,int peso){
    int cont=0;
	
	/*1. Generar poblacion inicial Pt*/
    vector<vector<int>> poblacion; //son varios cromosomas,  un cromosoma es un vector
    srand(time(NULL));
    generapoblacioninicial(poblacion,paq,n,peso);
    muestrapoblacion(poblacion,paq);    
    
	/*2. While con condiciones de parada: 
		- Iteraciones, Meseta, Aberraciones
	*/
    while(1){
        vector<vector<int>> padres; //vector para la seleccion de la Pt actual
        seleccion(padres,poblacion,paq,n,peso);
        casamiento(padres,poblacion,paq,peso);
        cout << endl;
        inversion(poblacion,padres,paq,peso);
        mutacion(poblacion,padres,paq,peso);
        eliminaaberraciones(poblacion,paq);
        generarpoblacion(poblacion,paq,peso);
        muestrapoblacion(poblacion,paq); 
        muestramejor(poblacion,paq,peso);
        cont++;
        if(cont==NITERACIONES) break; // Control de iteraciones
    }
}

void casamiento(vector<vector<int>>padres,
        vector<vector<int>>&poblacion,int *paq,int peso){
	//todos se casan con todos, y se agrega TODOS los hijos validos a la Pt
    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++)
            if(i!=j){
                vector<int>cromo;
                generahijo(padres[i],padres[j],cromo);
                if(!aberracion(cromo,paq,peso))
                    poblacion.push_back(cromo);
            }
}
void generahijo(vector<int>padre,vector<int>madre,
        vector<int>&hijo){
    int pos=round(padre.size()*Pcasamiento);
    
    for(int i=0;i<pos;i++)
        hijo.push_back(padre[i]);
    for(int i=pos;i<madre.size();i++)
        hijo.push_back(madre[i]);
}

int main(int argc, char** argv) {
    int paq[]={1,2,4,12,1,3,5,10,7};
    int peso=35;
    int n=sizeof(paq)/sizeof(paq[0]);
    
    mochilaAG(paq,n,peso);

    return 0;
}

