/* 
 * File:   main.cpp
 * Author: cueva
 *
 * Created on 12 de noviembre de 2024, 03:21 PM
 */

#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#define NITERACIONES 1000
#define NIND 10
#define Tseleccion 0.3
#define Pcasamiento 0.5
#define Tmutacion 0.5

using namespace std;

struct bloque{
    int id;
    int espacio;
    int inicio_min;
};

//Verifica si dicho paquete (tarea) entra en el arreglo auxiliar 
bool entra(bloque elegido, int *arr,int cantEspacioTotal){
    if(elegido.inicio_min+elegido.espacio>cantEspacioTotal+1) return false; // si es mas grande q el arreglo aux 
    int inicio = elegido.inicio_min-1; // - 1 por indice 
    for(int i=inicio;i<inicio+elegido.espacio;i++){
        if(arr[i]!=0) return false;
    }
    return true;
}

/*Coloca el paquete (tarea) en esas horas :)  */
void coloca(bloque elegido, int *arr,int cantEspacioTotal){
    int inicio = elegido.inicio_min-1;
    for(int i=inicio;i<inicio+elegido.espacio;i++){
        arr[i]=elegido.id;
    }
}

bool aberracion(vector<int>cromo,bloque *bloq,int cantEspacioTotal){
    int arr[cantEspacioTotal]{};
    for(int i=0;i<cromo.size();i++){
        if(cromo[i]==1){
            if(entra(bloq[i],arr,cantEspacioTotal)){
                coloca(bloq[i],arr,cantEspacioTotal);
            }else{
                return true;
            }
        }
    }
    
    return false;
}

int calculafitness(vector<int> cromo){
    int cont=0;
    
    for(int i=0;i<cromo.size();i++)
        if(cromo[i]==1)
            cont++;
    
    return cont;
    
}

void muestrapoblacion(vector<vector<int>> poblacion){
    for(int i=0;i<poblacion.size();i++){
        for(int j=0;j<poblacion[i].size();j++){
            cout << poblacion[i][j] << "  ";
        }
        cout <<" fo="<< calculafitness(poblacion[i]) <<endl;
    }
}

void generapoblacioninicial(vector<vector<int>>&poblacion,bloque *bloq,int n,int cantEspacioTotal){
    int cont=0;
    
    while(cont<NIND){
        vector <int> vaux;
        for(int i=0;i<n;i++)
            vaux.push_back(rand()%2);
        if(not aberracion(vaux,bloq,cantEspacioTotal)){
            poblacion.push_back(vaux);
            cont++;
        }
    }
}    

void muestramejor(vector<vector<int>> poblacion,
        bloque *bloq){
    int mejor=0;
    for(int i=0;i<poblacion.size();i++)
        if(calculafitness(poblacion[mejor])<calculafitness(poblacion[i]))
            mejor=i;
    
    cout << endl<<"La mejor solucion es:" << calculafitness(poblacion[mejor])<<endl;
    for(int i=0;i<poblacion[mejor].size();i++){
        cout << poblacion[mejor][i] << "  ";        
    }
    cout << endl;
    for(int i=0;i<poblacion[mejor].size();i++){
        if(poblacion[mejor][i]==1)
            cout << bloq[i].id << "  ";        
    }
    cout << endl;
}

void calculasupervivencia(vector<vector<int>>poblacion,
    vector<int>&supervivencia){
    int suma=0;
    
    for(int i=0;i<poblacion.size();i++)
        suma+=calculafitness(poblacion[i]);
    for(int i=0;i<poblacion.size();i++){
        int fit= round(100*(double)calculafitness(poblacion[i])/suma);
        supervivencia.push_back(fit);
    }

}

void cargaruleta(vector<int>supervivencia,int *ruleta){
    int ind=0;
    for(int i=0;i<supervivencia.size();i++)
        for(int j=0;j<supervivencia[i];j++)
            ruleta[ind++]=i;
}

void generahijo(vector<int>padre,vector<int>madre,
        vector<int>&hijo){
    int pos=round(padre.size()*Pcasamiento);
    
    for(int i=0;i<pos;i++)
        hijo.push_back(padre[i]);
    for(int i=pos;i<madre.size();i++)
        hijo.push_back(madre[i]);
}

void casamiento(vector<vector<int>>padres,
        vector<vector<int>>&poblacion,bloque *bloq,int cantEspacioTotal){
    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++)
            if(i!=j){
                vector<int>cromo;
                generahijo(padres[i],padres[j],cromo);
                if(!aberracion(cromo,bloq,cantEspacioTotal))
                    poblacion.push_back(cromo);
            }
}


void seleccion(vector<vector<int>>&padres,vector<vector<int>>poblacion,
    bloque *bloq,int n,int cantEspacioTotal){
    int ruleta[100]{-1};
    vector<int>supervivencia;
    calculasupervivencia(poblacion,supervivencia);
    cargaruleta(supervivencia,ruleta);
    int nseleccionados= poblacion.size()*Tseleccion;        
    for(int i=0;i<nseleccionados;i++){
        int ind=rand()%100;
        if(ruleta[ind]>-1)
            padres.push_back(poblacion[ruleta[ind]]);
            
    } 

}

void inversion(vector<vector<int>>&poblacion,
        vector<vector<int>>padres,bloque *bloq,int cantEspacioTotal){
    
    for(int i=0;i<padres.size();i++){
        for(int j=0;j<padres[i].size();j++){
            if(padres[i][j]==0)
                padres[i][j]=1;
            else
                padres[i][j]=0;
        }
        if(!aberracion(padres[i],bloq,cantEspacioTotal))
            poblacion.push_back(padres[i]);
    }
    
}

void mutacion(vector<vector<int>> &poblacion,vector<vector<int>> padres,
        bloque *bloq,int cantEspacioTotal){
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
        if(!aberracion(padres[i],bloq,cantEspacioTotal))
            poblacion.push_back(padres[i]);     
    }
}

bool compara(vector<int>a,vector<int>b){
    return calculafitness(a)>calculafitness(b);
}
int compacta(vector<int>cromo){
    int num=0;
    for(int i=0;i<cromo.size();i++)
        num+=pow(2,i)*cromo[i];
    
    return num;
    
}
void eliminaaberraciones(vector<vector<int>> &poblacion){
    map<int,vector<int>> municos;
    
    for(int i=0;i<poblacion.size();i++){
        int num=compacta(poblacion[i]);
        municos[num]=poblacion[i];
    }
    poblacion.clear();
    for(map<int,vector<int>>::iterator it=municos.begin();
            it!=municos.end();it++){
        poblacion.push_back(it->second);
    }
        
    
}


void generarpoblacion(vector<vector<int>> &poblacion){
    
    sort(poblacion.begin(),poblacion.end(),compara);
    if(poblacion.size() > NIND)
        poblacion.erase(poblacion.begin()+NIND,poblacion.end());
    
}

void eligeBloquesAG(bloque *bloq,int n,int cantEspacioTotal){
    int cont=0;
    vector<vector<int>> poblacion;
    srand(time(NULL));
    generapoblacioninicial(poblacion,bloq,n,cantEspacioTotal);
    muestrapoblacion(poblacion);    
    
    while(1){
        vector<vector<int>> padres;
        seleccion(padres,poblacion,bloq,n,cantEspacioTotal);
        casamiento(padres,poblacion,bloq,cantEspacioTotal);
        cout << endl;
        inversion(poblacion,padres,bloq,cantEspacioTotal);
        mutacion(poblacion,padres,bloq,cantEspacioTotal);
        eliminaaberraciones(poblacion);
        generarpoblacion(poblacion);
        muestrapoblacion(poblacion); 
        muestramejor(poblacion,bloq);
        cont++;
        if(cont==NITERACIONES) break;
    }
}

int main(int argc, char** argv) {
    int cantEspacioTotal=7;
    bloque bloques[]={{1,2,2},{2,3,3},{3,1,6},{4,3,4}};
    int n=sizeof(bloques)/sizeof(bloques[0]);
    
    eligeBloquesAG(bloques,n,cantEspacioTotal);

    return 0;
}

