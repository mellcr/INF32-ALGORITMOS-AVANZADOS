/* 
 * File:   main.cpp
 * Author: cueva
 *
 * Created on 27 de mayo de 2024, 04:28 PM
 */
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#define Tcasamiento 0.2
#define Pcasamiento 0.5
#define Tmutacion 0.2
#define IND 5

using namespace std;

int calculafitness(vector<int> cromo,int *paq){
    int cont=0;
    
    for(int i=0;i<cromo.size();i++)
        cont+=cromo[i]*paq[i];
    
    return cont;
    
}

bool aberracion(vector<int> cromo,int *paq,int peso){
    if(calculafitness(cromo,paq)>peso)
        return true;
    return false;
    
}


void muestrapoblacion(vector<vector<int>> poblacion,int *paq){
    for(int i=0;i<poblacion.size();i++){
        
        for(int j=0;j<poblacion[i].size();j++){
            cout << poblacion[i][j] << "  ";
        }
        cout <<" fo="<< calculafitness(poblacion[i],paq) <<endl;
    }
}

void muestrasupervivencia(vector<vector<int>> poblacion,vector<double>supervivencia,
        int *paq){
    for(int i=0;i<poblacion.size();i++){
        
        for(int j=0;j<poblacion[i].size();j++){
            cout << poblacion[i][j] << "  ";
        }
        cout <<" fo="<< calculafitness(poblacion[i],paq);
        cout <<" Sup=" << supervivencia[i]<< endl;
    }
}


void generapoblacioninicial(vector<vector<int>> &poblacion,int*paq,int n,int peso){
    int cont=0;
    
    srand (time(NULL));
    while(cont<IND){
        vector<int> v;
        for(int j=0;j<n;j++){
            v.push_back(rand()%2);
        }
        if(!aberracion(v,paq,peso)){
            poblacion.push_back(v);
            cont++;
        }    
    }
}

void calculasupervivencia(vector<vector<int>> &poblacion,vector<double>&supervivencia,
        int*paq,int n,int peso){
    
    int sumafitness=0;
    for(int i=0;i<poblacion.size();i++)
        sumafitness+=calculafitness(poblacion[i],paq);
    for(int i=0;i<poblacion.size();i++){
        double fit=round(100*(double)calculafitness(poblacion[i],paq)/sumafitness);
        
        supervivencia.push_back(fit);
    }
  //  muestrasupervivencia(poblacion,supervivencia,paq);
}
void cargaruleta(vector<double>supervivencia,int *ruleta){
    int ind=0;
    for(int i=0;i<supervivencia.size();i++){
        for(int j=0;j<supervivencia[i];j++){
            ruleta[ind]=i;
            ind++;
        }
    }
//    for(int i=0;i<100;i++)
//        cout <<ruleta[i]  <<" ";
//    cout << endl;
}

void seleccion(vector<vector<int>> poblacion,vector<vector<int>> &padres,
        int*paq,int n,int peso){
    int npadres,cont=0;
    vector<double>supervivencia;      
    int ruleta[100]{-1};
    calculasupervivencia(poblacion,supervivencia,paq,n,peso);
    cargaruleta(supervivencia,ruleta);
    npadres=round(poblacion.size()*Tcasamiento);
    while(1){
        int ind=rand()%100;
        if(ruleta[ind]>-1)
            padres.push_back(poblacion[ruleta[ind]]);
        cont++;
        if(cont>=npadres)break;
    }
  //  muestrapoblacion(padres,paq);
}
void generahijo(vector<int>padre,vector<int>madre,vector<int>&hijo){
    int pos=round(padre.size()*Pcasamiento);
    
    for(int i=0;i<pos;i++)
        hijo.push_back(padre[i]);
    for(int i=pos;i<padre.size();i++)
        hijo.push_back(madre[i]);
    
}


void casamiento(vector<vector<int>> &poblacion,vector<vector<int>> padres){
    
    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++)
            if(i!=j){
                vector<int> cromo;
                generahijo(padres[i],padres[j],cromo);
                poblacion.push_back(cromo);
           }
}

void mutacion(vector<vector<int>> &poblacion,vector<vector<int>> padres){
    int cont=0;
    int nmuta=round(padres[0].size()*Tmutacion);
   // cout << nmuta << endl;
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
        poblacion.push_back(padres[i]);     
    }
}
void inversion(vector<vector<int>> &poblacion,vector<vector<int>> padres){
    
    for(int i=0;i<padres.size();i++){
        for(int j=0;j<padres[i].size();j++){
            if(padres[i][j]==0)
                padres[i][j]=1;
            else
                padres[i][j]=0;
        }
        poblacion.push_back(padres[i]);     
    }    
    
}

void eliminaaberraciones(vector<vector<int>> &poblacion,
        int *paq,int peso){
    
    for(int i=0;i<poblacion.size();i++){
        int fo=calculafitness(poblacion[i],paq);
        if(aberracion(poblacion[i],paq,peso)){
            poblacion.erase(poblacion.begin()+i); 
            i--;
        }
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

void mochilaAG(int *paq,int n,int peso){
    vector<vector<int>> poblacion;
    int cont=0;
    while(1){
        vector<vector<int>> padres;
        generapoblacioninicial(poblacion,paq,n,peso);
        seleccion(poblacion,padres,paq,n,peso);
        casamiento(poblacion,padres);
//        cout <<"Casamiento:"<<endl;
//        muestrapoblacion(poblacion,paq);
        mutacion(poblacion,padres);
//        cout <<"Mutacion:"<<endl;
//        muestrapoblacion(poblacion,paq);
//        cout <<"Inversion:" <<endl;
        inversion(poblacion,padres);
//        muestrapoblacion(poblacion,paq);
//        cout <<"Elimina aberrados:" <<endl;
        eliminaaberraciones(poblacion,paq,peso);
        //muestrapoblacion(poblacion,paq);
        int residuo=muestramejor(poblacion,paq,peso);
        cont++;
        if(cont==5 || residuo==0) break;
    }
}

int main(int argc, char** argv) {
    int paquetes[]={1,2,4,12,1,3,5,10,7};
    int n=sizeof(paquetes)/sizeof(paquetes[0]);
    int peso=25;
    
    mochilaAG(paquetes,n,peso);

    
    return 0;
}

