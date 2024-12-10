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

struct bloque{
    int id;
    int espacio;
    int inicio_min;
};

bool compara(bloque a,bloque b){
    return a.espacio<b.espacio;
}

int verifica(vector<bloque>bloq,double rcl){
    int cont=0;
    
    for(int i=0;i<bloq.size();i++)
        if(rcl>=bloq[i].espacio)cont++;
    return cont;
}

//void cargamochila(int *paq,int peso,int n){
//    int mejor=999999;
//    vector<int>maxsol;
//    for(int k=0;k<maxitera;k++){
//        //fase construccion
//        srand(time(NULL));
//        vector<int>soluciones;
//        //sort(paq,paq+n,compara);
//        vector<int>paquetes;
//        paquetes.insert(paquetes.begin(),paq,paq+n);
//        int residual = peso;
//        while(not paquetes.empty()){
//            int beta=paquetes[0];
//            int tau=paquetes[paquetes.size()-1];
//            double rcl=beta-alfa*(beta-tau);
//            int ind=verifica(paquetes,rcl);
//            int inda = rand()%ind;
//            if(residual-paquetes[inda]>=0){
//                soluciones.push_back(paquetes[inda]);
//                residual-=paquetes[inda];
//            }
//            paquetes.erase(paquetes.begin()+inda);
//        }
//        if(residual<mejor){
//            mejor=residual;
//            maxsol.erase(maxsol.begin(),maxsol.begin()+maxsol.size());
//            maxsol.insert(maxsol.begin(),soluciones.begin(),soluciones.begin()+soluciones.size());
//        }   
//    }
//    cout << mejor<< endl;
//    for(int i=0;i<maxsol.size();i++)
//        cout << maxsol[i] << " ";
//    
//}

bool entra(bloque elegido, int *arr,int cantEspacioTotal){
    if(elegido.inicio_min+elegido.espacio>cantEspacioTotal+1) return false;
    int inicio = elegido.inicio_min-1;
    for(int i=inicio;i<inicio+elegido.espacio;i++){
        if(arr[i]!=0) return false;
    }
    return true;
}

void coloca(bloque elegido, int *arr,int cantEspacioTotal){
    int inicio = elegido.inicio_min-1;
    for(int i=inicio;i<inicio+elegido.espacio;i++){
        arr[i]=elegido.id;
    }
}

void eligeBloques(bloque *bloq, int n,int cantEspacioTotal){
    int mejorCant = -9999;
    vector<bloque> mejorv;
    for(int k=0;k<maxitera;k++){
        //fase construccion
        srand(time(NULL));
        vector<bloque>soluciones;
        vector<bloque>bloques;
        sort(bloq,bloq+n,compara); // cambio
        bloques.insert(bloques.begin(),bloq,bloq+n);
        int cant=0;
        int arr[cantEspacioTotal]{};
        while(not bloques.empty()){
            int beta=bloques[0].espacio;
            int tau=bloques[bloques.size()-1].espacio;
            double rcl=beta+alfa*(tau-beta);
            int ind=verifica(bloques,rcl);
            int inda = rand()%ind;
            if(entra(bloques[inda],arr,cantEspacioTotal)){
                soluciones.push_back(bloques[inda]);
                coloca(bloques[inda],arr,cantEspacioTotal);
                cant++;
            }
            bloques.erase(bloques.begin()+inda);
        }
        if(cant>mejorCant){
            mejorCant = cant;
            mejorv.clear();
            mejorv = soluciones;
        }
    }
    
    cout << mejorCant<< endl;
    for(int i=0;i<mejorv.size();i++)
        cout << mejorv[i].id << " ";
}


int main(int argc, char** argv) {
    int cantEspacioTotal=7;
    bloque bloques[]={{1,2,2},{2,3,3},{3,1,6},{4,3,4}};
    int n=sizeof(bloques)/sizeof(bloques[0]);
    
    //se ordena por menor cantidad de espacio que ocupa el bloque
    //sort(bloques,bloques+n,compara);// (externo)
    
    eligeBloques(bloques,n,cantEspacioTotal);
    return 0;
}

