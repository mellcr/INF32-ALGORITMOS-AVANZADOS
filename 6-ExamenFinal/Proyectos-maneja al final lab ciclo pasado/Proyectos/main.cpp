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
#define Tcasamiento 0.5
#define Pcasamiento 0.5
#define Tmutacion 0.2
#define IND 5

using namespace std;

struct strproyecto{
    int id;
    int costo;
    int ganancia;
    int prede[3];
};


int calculafitness(vector<int> cromo,strproyecto *paq){
    int cont=0;
    
    for(int i=0;i<cromo.size();i++)
        cont+=cromo[i]*paq[i].ganancia;
    
    return cont;
    
}

bool aberracion(vector<int> cromo,strproyecto *paq,int peso){
    int suma=0;
    
    for(int i=0;i<cromo.size();i++){
        suma+=cromo[i]*paq[i].costo;
        if(cromo[i]==1)
            for(int j=0;j<3;j++){
                int pre=paq[i].prede[j];
                if(pre>0){
                    if(cromo[pre-1]==0)
                        return true;
                }
                else
                    break;
            }
    }
    if(suma>peso)
        return true;
    return false;
}


void muestrapoblacion(vector<vector<int>> poblacion,strproyecto *paq){
    for(int i=0;i<poblacion.size();i++){
        
        for(int j=0;j<poblacion[i].size();j++){
            cout << poblacion[i][j] << "  ";
        }
        cout <<" fo="<< calculafitness(poblacion[i],paq) <<endl;
    }
}

void muestrasupervivencia(vector<vector<int>> poblacion,vector<double>supervivencia,
        strproyecto *paq){
    for(int i=0;i<poblacion.size();i++){
        
        for(int j=0;j<poblacion[i].size();j++){
            cout << poblacion[i][j] << "  ";
        }
        cout <<" fo="<< calculafitness(poblacion[i],paq);
        cout <<" Sup=" << supervivencia[i]<< endl;
    }
}


void generapoblacioninicial(vector<vector<int>> &poblacion,strproyecto*paq,int n,int peso){
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
        strproyecto*paq,int n,int peso){
    
    int sumafitness=0;
    for(int i=0;i<poblacion.size();i++)
        sumafitness+=calculafitness(poblacion[i],paq);
    for(int i=0;i<poblacion.size();i++){
        double fit=round(100*(double)calculafitness(poblacion[i],paq)/sumafitness);
        
        supervivencia.push_back(fit);
    }
    muestrasupervivencia(poblacion,supervivencia,paq);
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
        strproyecto *paq,int n,int peso){
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
//    muestrapoblacion(padres,paq);
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
    cout << nmuta << endl;
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

int compacta(vector<int>cromo){
    int num=0;
    
    for(int i=0;i<cromo.size();i++){
        num+=pow(2,i)*cromo[i];
    }
    return num;
    
}
void muestracromo(vector<int>cromo){
    for(int i=0;i<cromo.size();i++){
         cout << cromo[i] << " ";
    }   
     cout << endl;
}

void eliminaberraciones(vector<vector<int>> &poblacion,strproyecto*paq,int peso){
    for(int i=0;i<poblacion.size();i++){
        int fo=calculafitness(poblacion[i],paq);
        if(aberracion(poblacion[i],paq,peso)){
            poblacion.erase(poblacion.begin()+i); 
            i--;
        }
    }   
    for(int i=0;i<poblacion.size();i++){
        int num1=compacta(poblacion[i]);
        cout << "cromo1:";
        muestracromo(poblacion[i]);
        for(int j=i+1;j<poblacion.size();j++){
            cout << "cromo2:";
            muestracromo(poblacion[j]);
            int num2=compacta(poblacion[j]);
            if(num1==num2){
                poblacion.erase(poblacion.begin()+j);
                j--;
            }    
        }
    }
}




void muestramejor(vector<vector<int>> poblacion,
        strproyecto *paq,int peso){
    int mejor=0;
    for(int i=0;i<poblacion.size();i++)
        if(calculafitness(poblacion[mejor],paq)<calculafitness(poblacion[i],paq))
            mejor=i;
    
    cout << endl<<"La mejor solucion es:" << calculafitness(poblacion[mejor],paq)<<endl;
    for(int i=0;i<poblacion[mejor].size();i++){
        cout << poblacion[mejor][i] << "  ";        
    }
    cout << endl;

}

void mochilaAG(strproyecto *paq,int n,int peso){
    vector<vector<int>> poblacion;
    int cont=0;
    generapoblacioninicial(poblacion,paq,n,peso);
    while(1){
        vector<vector<int>> padres;

      //  muestrapoblacion(poblacion,paq);
        seleccion(poblacion,padres,paq,n,peso);
        casamiento(poblacion,padres);
        cout <<"Casamiento:"<<endl;
        muestrapoblacion(poblacion,paq);
        mutacion(poblacion,padres);
        cout <<"Mutacion:"<<endl;
        muestrapoblacion(poblacion,paq);
        cout <<"Inversion:" <<endl;
        inversion(poblacion,padres);
        muestrapoblacion(poblacion,paq);
        eliminaberraciones(poblacion,paq,peso);
        cout <<endl<<"Luego de control de aberraciones:"<<endl;
        muestrapoblacion(poblacion,paq);
        muestramejor(poblacion,paq,peso);
    
        cont++;
        if(cont==5 ) break;    
        
    }    
}

int main(int argc, char** argv) {
    strproyecto proyectos[]={{1,80,150,{0,0,0}},{2,20,80,{0,0,0}},{3,100,300,{1,2,0}},
    {4,100,150,{0,0,0}},{5,50,80,{0,0,0}},{6,10,50,{2,0,0}},{7,50,120,{6,0,0}},{8,50,150,{6,0,0}}};
    int n=sizeof(proyectos)/sizeof(proyectos[0]);
    int peso=250;
    
    mochilaAG(proyectos,n,peso);

    
    return 0;
}

