/* 
 * File:   main.cpp
 * Author: mellcr
 *
 * Created on 5 de noviembre de 2024, 02:37 PM
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <limits.h>
#define iteraciones 1000000
#define alfa 0.6
#define MAX 8

using namespace std;

struct nodo{
    int punto;
    int distancia;
};

//MENOR A MAYOR
bool compara(nodo a,nodo b){
    return a.distancia<b.distancia;
}

int verifica(vector<nodo>vaux,int minrcl){
    int cont=0;
    for(int i=0;i<vaux.size();i++)
		//  c(x) <= minrcl
        if(minrcl>=vaux[i].distancia)
            cont++;
    return cont;
}

int minruta(int ini,int fin,int mapa[][MAX]){
    int min=INT_MAX;
    vector<int> mejorRuta; 
    for(int k=0;k<iteraciones;k++){
        int total=0;		//total distancia 
        srand(time(NULL));
        int ciudad=ini;		//ciudad donde iniciamos 
        
        vector<int> ciudadesRuta; 
        ciudadesRuta.push_back(ciudad); 
        while(1){
			//Guarda los vecinos en esa ciudad
            vector<nodo>vecinos;     //N 
            for(int i=0;i<MAX;i++){
                if(mapa[ciudad][i]>0){
                    nodo aux;
                    aux.distancia=mapa[ciudad][i];
                    aux.punto=i;
                    vecinos.push_back(aux);
                }
            }
            if(not vecinos.empty()){
                sort(vecinos.begin(),vecinos.end(),compara);  
                int beta = vecinos[0].distancia;     //Mejor SOlucion: Distancia menor
                int tau = vecinos[vecinos.size()-1].distancia; //Peor solucion: Distancia mayor
				// CASO: t > B -> B <= f <= B + alfa (t- B )
                int minrcl=round(beta+alfa*(tau-beta));
                int indrcl=verifica(vecinos,minrcl);
                int inda=rand()%indrcl;
				/*NOTA: no se necesita validación de si es una solución válida 
					Ya que es vecino y es corta */
				//Asignamos sgte ciudad y acumulamos valor de distancia 
                ciudad=vecinos[inda].punto;
                total+=vecinos[inda].distancia;
                ciudadesRuta.push_back(ciudad); 
            }
			/*2 posibles casos para parar el while:
			- LLego a la ciudad de fin
			- LLego a una ciudad que no tenga vecinos */
            if(ciudad==fin)break;
            if(vecinos.empty()){
                //cout <<"No se encontro la ciudad fin"<<endl;
                total=INT_MAX;
                break;
            }
        }
		//Guarda la mejor solucion de todas las iteraciones (1000000)
        if(total<min){
            min=total;
            mejorRuta.assign(ciudadesRuta.begin(), ciudadesRuta.end());
        }
        ciudadesRuta.clear(); 
    }
    
    for(int i=0;i<mejorRuta.size();i++ ){
        cout << setw(3)<<mejorRuta[i]+1;
    }
    cout <<endl;
    
    return min;
}


int main(int argc, char** argv) {
    int mapa[][MAX]={   {0,18,10,15,0,0,0,0}, 
                        {0,0,0,0,0,15,0,5},    
                        {0,0,0,0,0,20,0,0},
                        {0,0,0,0,1,0,0,0},
                        {0,0,0,0,0,0,1,0},
                        {0,0,0,0,0,0,5,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}};
    
    
    cout << minruta(0,6,mapa);

    return 0;
}

