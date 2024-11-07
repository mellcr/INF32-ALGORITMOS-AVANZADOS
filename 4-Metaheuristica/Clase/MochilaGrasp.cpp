/* 
 * File:   main.cpp
 * Author: cueva.r
 *
 * Created on 22 de octubre de 2024, 03:03 PM
 */

#include <iostream>
#include <climits>
#include <ctime>
#include <vector>
#include <algorithm>
#define maxitera 10000
#define alfa 0.3

using namespace std;

bool compara(int a,int b){
    return a>b;
}

int verifica(vector<int>paq,double rcl){
    int cont=0;
    
    for(int i=0;i<paq.size();i++)
        if(rcl<=paq[i])cont++;
    return cont;
}

void cargamochila(int *paq,int peso,int n){
    int mejor=999999;
    vector<int>maxsol;
    for(int k=0;k<maxitera;k++){
        //fase construccion
        srand(time(NULL));
        vector<int>soluciones;
        sort(paq,paq+n,compara);
        vector<int>paquetes;
        paquetes.insert(paquetes.begin(),paq,paq+n);
        int residual = peso;
        while(not paquetes.empty()){
            int beta=paquetes[0];
            int tau=paquetes[paquetes.size()-1];
            double rcl=beta-alfa*(beta-tau);
            int ind=verifica(paquetes,rcl);
            int inda = rand()%ind;
            if(residual-paquetes[inda]>=0){
                soluciones.push_back(paquetes[inda]);
                residual-=paquetes[inda];
            }
            paquetes.erase(paquetes.begin()+inda);
        }
        if(residual<mejor){
            mejor=residual;
            maxsol.erase(maxsol.begin(),maxsol.begin()+maxsol.size());
            maxsol.insert(maxsol.begin(),soluciones.begin(),soluciones.begin()+soluciones.size());
        }   
    }
    cout << mejor<< endl;
    for(int i=0;i<maxsol.size();i++)
        cout << maxsol[i] << " ";
    
}


int main(int argc, char** argv) {
    int paq[]={10,2,1,5,9,8};
    int n=sizeof(paq)/sizeof(paq[0]);
    int peso=14;
    cargamochila(paq,peso,n);

    return 0;
}

