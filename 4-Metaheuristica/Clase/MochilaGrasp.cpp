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
#define maxitera 10000			//numero maximo de iteraciones
#define alfa 0.3

using namespace std;

bool compara(int a,int b){
    return a>b;
}

/* Cuenta cuántos elementos cumplen con la condición de pertenecer al RCL. 
Es decir, cuenta cuántos elementos en paquetes tienen un peso mayor o igual a rcl. */
/*NOTA: 
Solo cuenta, no selecciona aleatoriamente uno del RCL,
 lo cual puede no ser óptimo.
*/
int verifica(vector<int>paq,double rcl){
    int cont=0;
    
    for(int i=0;i<paq.size();i++)
        if(rcl<=paq[i])cont++;
    return cont;
}



void cargamochila(int *paq,int peso,int n){
    int mejor=999999;             	//mejor residuo 
    vector<int>maxsol;
    for(int k=0;k<maxitera;k++){
        //fase construccion
        srand(time(NULL));
        vector<int>soluciones;
        sort(paq,paq+n,compara);   //ordena paquetes
        vector<int>paquetes;
        paquetes.insert(paquetes.begin(),paq,paq+n);   //vector auxiliar, copia de paq
        int residual = peso; //peso disponible restante en la mochila
        while(not paquetes.empty()){
            int beta=paquetes[0];				//mayor valor posible
            int tau=paquetes[paquetes.size()-1];//menor valor posible
            double rcl=beta-alfa*(beta-tau);
            int ind=verifica(paquetes,rcl);
            int inda = rand()%ind;            //no es optimo
			//si no excede la capacidad se selecciona 
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

/*llenar la mochila con la mayor cantidad de peso posible sin sobrepasar el peso lim*/
int main(int argc, char** argv) {
    int paq[]={10,2,1,5,9,8};				//paquetes para llenar la mochila
    int n=sizeof(paq)/sizeof(paq[0]);		//n: numero de paquetes
    int peso=14;							
    cargamochila(paq,peso,n);	


	//B = 10
	//t = 1
	//CASO: B > t ---> RCL = { x 𝜖 N : β - α (β - τ)  ≤ c(x) ≤ β}
	
    return 0;
}

