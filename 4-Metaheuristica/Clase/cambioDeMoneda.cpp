#include <iomanip>
#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
#define maxiteraciones 10000
#define alpha 0.2
using namespace std;
bool cmp(int a, int b){
    return a>b;
}
int sumar(vector<int> solucion){
    int s=0;
    for(int i=0; i<solucion.size(); i++)
        s+=solucion[i];
    return s;
}
bool cmpCant(vector<int> mejorSolucion,vector<int> solucion){
    int sumaM=sumar(mejorSolucion), suma=sumar(solucion);
    if(sumaM==0)
        sumaM=9999;
    return suma<sumaM;
}
void cambio(int monto, vector<int> denominaciones, int d){
    int mejorResiduo=999999;
    vector<int> mejorSolucion (d, 0);
    srand(time(NULL));
    for(int i=0; i<maxiteraciones; i++){
        vector<int> solucion (d, 0);
        vector<int> copia;
        sort(denominaciones.begin(), denominaciones.end(), cmp);
        copia.insert(copia.begin(), denominaciones.begin(), denominaciones.end());
        int residuo=monto;
        
        while(not copia.empty()){
            int beta=copia[0];
            int tau=copia[copia.size()-1];
            vector<int> rcl;
            int rangoInf=beta-alpha*(beta-tau);
            for(int j=0; j<copia.size(); j++)
                if(copia[j]>=rangoInf and copia[j]<=beta)
                    rcl.push_back(j);
            int ind=rand()%rcl.size();
            int indA=rcl[ind];
            int S=copia[indA];
            if(S<=residuo){
                int i=0;
                for(int j=0; j<denominaciones.size(); j++)
                    if(denominaciones[j]==S)
                        i=j;
                solucion[i]=residuo/S;
                residuo-=S*solucion[i];
            }
            copia.erase(copia.begin()+indA);
        }
        
        if(residuo<=mejorResiduo and cmpCant(mejorSolucion, solucion)){
            mejorResiduo=residuo;
            mejorSolucion.clear();
            mejorSolucion.insert(mejorSolucion.begin(), solucion.begin(), solucion.begin()+solucion.size());
        }
    }
    for(int i=0; i<d; i++)
        cout<<denominaciones[i]<<'-'<<mejorSolucion[i]<<' ';
}
int main(){
    int monto=181, d=3;
    vector<int> denominaciones={1,90,100};
    //quiero guardar la cantidad utilizada por cada denominacion
    cambio(monto, denominaciones, d);
    return 0;
}