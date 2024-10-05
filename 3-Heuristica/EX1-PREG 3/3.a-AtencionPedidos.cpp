
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#define MIN 999999
using namespace std;

struct Datos{
    int dimension;
    int cantidad;
    int ganancia;
};

struct Barra{
    int tamanho;        //tam original
    int desperdicio;    //tam desp de sus cortes 
};
void hallaSolu(vector<Datos> &pedidos,int nPed,vector<Barra>&almacen,int nBarras, int &maxGanancia);
bool compara(struct Datos &a, struct Datos &b);

int main() {
    vector<Datos> pedidos = {{10,5,10},{20,10,20}, {1,18,15},{3,1,5},{1,1,2}};  
    int nPed = pedidos.size();
    vector<Barra> almacen;
    for(int i=0;i<20;i++){
        Barra barra = {10,10};
        almacen.push_back(barra);
    }
    int nBarras = almacen.size();
    int maxGanancia=0;
    
    hallaSolu(pedidos,nPed,almacen,nBarras,maxGanancia);
    cout << "Maxima ganancia: "<<maxGanancia<<endl; 
    cout << "Barras:     ";
    for (int i = 0; i < nBarras; i++) {
        cout << setw(4) << i + 1; 
    }
    cout << endl;

    // Imprimimos los desperdicios con setw para alinearlos
    cout << "Desperdicio:";
    for (int i = 0; i < nBarras; i++) {
        cout << setw(4) << almacen[i].desperdicio; 
    }
    cout << endl;

    return 0;
}

void hallaSolu(vector<Datos> &pedidos,int nPed,vector<Barra>&almacen,int nBarras, int &maxGanancia){
    /*Ordeno para maximizar ganancia*/
    sort(pedidos.begin(),pedidos.end(),compara);
    /* Atiendo cada pedido */
    
    for(int i=0; i<nPed;i++){
        /*Analizo las barras disponibles en almacen, minimizando desperdicios*/
		/*NOTA: No se atienden pedidos parciales -> proceso de copia para verificar ello*/
        int cant = 0;                       //cantidad del pedido
        vector<Barra> temp (almacen);       //copia del estado actual de las barras en el almacen 
        for(int j=0; j<nBarras;){
            int corte = temp[j].desperdicio-pedidos[i].dimension ;
            if(corte >= 0){
                temp[j].desperdicio-=pedidos[i].dimension;
                cant++;
            }
            else j++;
            /*El pedido se atendio, se procesa su ganancia y cambios en desperdicio*/
            if(cant == pedidos[i].cantidad){
                almacen.assign(temp.begin(), temp.end());
                maxGanancia+=pedidos[i].ganancia;
                break;
            } 
        }
    }
}

bool compara(struct Datos &a, struct Datos &b){
    return a.ganancia> b.ganancia;
}