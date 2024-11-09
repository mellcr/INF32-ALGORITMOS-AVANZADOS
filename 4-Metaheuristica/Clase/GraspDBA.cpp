#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <limits.h>
#define iteraciones 10000
#define alfa 0.3

struct tobjeto {
    int cod;
    int capacidad;
    int rendimiento;
};

struct tresult {
    int disco;
    int tabla;
};

using namespace std;

/*DESCENDENTE: 5 4 3 2 1*/
bool compara(tobjeto a, tobjeto b) {
    return a.rendimiento > b.rendimiento;
}

int verifica(vector<tobjeto> dato, int maxrcl) {
    int cont = 0;
    for (int i = 0; i < dato.size(); i++)
        if (maxrcl <= dato[i].rendimiento) cont++;
    return cont;
}

int cargadiscos(vector<tobjeto>& tabla, vector<tobjeto>& disco, int n, int m) {
    int mejoriop = INT_MIN; //Mejor Iteracion Optima
    vector<tresult> mejorv;

    for (int k = 0; k < iteraciones; k++) {
        vector<tobjeto> vtabla; //Ntabla
        vector<tobjeto> vdisco; //Ndiscos
        vector<tresult> vresultado; //S

        vtabla.insert(vtabla.begin(), tabla.begin(), tabla.end());
        vdisco.insert(vdisco.begin(), disco.begin(), disco.end());
        // similar a ordenar los pesos
        sort(vtabla.begin(), vtabla.begin() + n, compara);
        srand(time(NULL));
        //Condicion de parada: cuando has recorrido todos los elementos
        while (not vtabla.empty()) {
            //Para que siempre asigna al disco con mayor velocidad en ese instante
            sort(vdisco.begin(), vdisco.begin() + m, compara);
            /*RCL para tabla*/
            int beta1 = vtabla[0].rendimiento;
            int tau1 = vtabla[vtabla.size() - 1].rendimiento;
            int maxrcl1 = round(beta1 - alfa * (beta1 - tau1));
            int indrcl1 = verifica(vtabla, maxrcl1);
            int indtabla = rand() % indrcl1;
            /*RCL para disco*/
            int beta2 = vdisco[0].rendimiento;
            int tau2 = vdisco[vdisco.size() - 1].rendimiento;
            int maxrcl2 = round(beta2 - alfa * (beta2 - tau2));
            int indrcl2 = verifica(vdisco, maxrcl2);
            int inddisco = rand() % indrcl2;
            /*Verifica si es una solucion posible*/
            if (vdisco[inddisco].rendimiento >= vtabla[indtabla].rendimiento) {
                vresultado.push_back({vdisco[inddisco].cod, vtabla[indtabla].cod});
                //disminuye el rendimiento (velocidad) del disco
                vdisco[inddisco].rendimiento -= vtabla[indtabla].rendimiento;
            }
            //descarta el elemento ya seleccionado (sea solución o no) 
            vtabla.erase(vtabla.begin() + indtabla);
        }
        sort(vdisco.begin(), vdisco.begin() + m, compara);
        /*LO RESALTADO EN ROSADO*/
        //busca el disco de menor rendimiento (velocidad) y agarra el valor
        int residual = vdisco[vdisco.size() - 1].rendimiento;
        //me quedo con el residual de rendimiento (velocidad) mayor 
        if (residual > mejoriop) {
            mejoriop = residual;
            mejorv.clear();         //limpio mi tabla intermediaxd
            mejorv = vresultado;    // guardo mi nueva combinacion de respuesta
        }
    }
    for (int i = 0; i < mejorv.size(); i++)
        cout << mejorv[i].disco << " " << mejorv[i].tabla << endl;

    return mejoriop;
}

int main(int argc, char** argv) {
    vector<tobjeto> tabla = {{1, 20, 150}, {2, 10, 100}, {3, 15, 80}, {4, 100, 50}, {5, 50, 120}, {6, 100, 10}};
    vector<tobjeto> disco = {{1, 800, 250}, {2, 750, 200}, {3, 850, 200}};
    
    int n = tabla.size();
    int m = disco.size();
    
    cout << "Residual:" << cargadiscos(tabla, disco, n, m);

    return 0;
}
