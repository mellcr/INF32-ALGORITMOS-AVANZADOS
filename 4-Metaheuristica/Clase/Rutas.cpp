/* 
 * File:   main.cpp
 * Author: cueva.r
 *
 * Created on 5 de noviembre de 2024, 02:37 PM
 */

#include <iostream>
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

bool compara(nodo a,nodo b){
    return a.distancia<b.distancia;
}

int verifica(vector<nodo>vaux,int minrcl){
    int cont=0;
    for(int i=0;i<vaux.size();i++)
        if(minrcl>=vaux[i].distancia)
            cont++;
    return cont;
}

int minruta(int ini,int fin,int mapa[][MAX]){
    int min=INT_MAX;
    for(int k=0;k<iteraciones;k++){
        int total=0;
        srand(time(NULL));
        int ciudad=ini;
        while(1){

            vector<nodo>vecinos;
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
                int beta = vecinos[0].distancia;     
                int tau = vecinos[vecinos.size()-1].distancia;
                int minrcl=round(beta+alfa*(tau-beta));
                int indrcl=verifica(vecinos,minrcl);
                int inda=rand()%indrcl;
                ciudad=vecinos[inda].punto;
                total+=vecinos[inda].distancia;
            }
            if(ciudad==fin)break;
            if(vecinos.empty()){
                //cout <<"No se encontro la ciudad fin"<<endl;
                total=INT_MAX;
                break;
            }

        }
        if(total<min)
            min=total;
    }
    
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

