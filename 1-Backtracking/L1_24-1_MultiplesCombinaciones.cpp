
/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 2 de setiembre de 2024, 2:20 p. m.
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
vector<vector<string>> generarCombinaciones(string equipos);
void hallaCombBackTrack(int indice,string equipos,vector<string> &actual,
        vector<vector<string>> &resultados); 

/*
 *      PREGUNTA 2-                  
 */

int main(int argc, char** argv) {
    string equipos = "4292";
    vector<vector<string >> combinaciones = generarCombinaciones(equipos);
    
    cout << "Todas las posibles combinaciones son: "<<endl; 
    for(int i=0; i<combinaciones.size();i++){
        cout << "Combinación: ";
        for(int j=0; j<combinaciones[i].size();j++){
            cout<< combinaciones[i][j] << ""; 
        }
        cout <<endl; 
    }
    
    
    return 0;
}

vector<vector<string>> generarCombinaciones(string equipos){
    vector<vector<string>> resultados;  //matriz
    vector<string> actual;              //arreglos
    
    hallaCombBackTrack(0,equipos,actual,resultados);
    return resultados; 
}

void hallaCombBackTrack(int indice,string equipos,vector<string> &actual,
        vector<vector<string>> &resultados){
    // Si hemos llegado al final del número, añadimos la combinación actual a los resultados
    if (indice == equipos.size()) {
        resultados.push_back(actual);
        return;
    }

    // Generar combinaciones usando dígitos adyacentes
    string aux = " ";
    for (int i = indice; i < equipos.size(); i++) {
        aux += equipos[i];
        actual.push_back(aux);
        hallaCombBackTrack(i + 1,equipos , actual, resultados);
        actual.pop_back(); // Deshacer la última acción
    }
}


/* 
 * File:   main.cpp
 * Author: mellcr 
 *
 * Created on 2 de setiembre de 2024, 2:20 p. m.
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
vector<vector<string>> generarCombinaciones(string equipos);
void hallaCombBackTrack(int indice,string equipos,vector<string> &actual,
        vector<vector<string>> &resultados); 

/*
 *      PREGUNTA 2-                  
 */

int main(int argc, char** argv) {
    string equipos = "4292";
    vector<vector<string >> combinaciones = generarCombinaciones(equipos);
    
    cout << "Todas las posibles combinaciones son: "<<endl; 
    for(int i=0; i<combinaciones.size();i++){
        cout << "Combinación: ";
        for(int j=0; j<combinaciones[i].size();j++){
            cout<< combinaciones[i][j] << ""; 
        }
        cout <<endl; 
    }
    
    
    return 0;
}

vector<vector<string>> generarCombinaciones(string equipos){
    vector<vector<string>> resultados;  //matriz
    vector<string> actual;              //arreglos
    
    hallaCombBackTrack(0,equipos,actual,resultados);
    return resultados; 
}

void hallaCombBackTrack(int indice,string equipos,vector<string> &actual,
        vector<vector<string>> &resultados){
    // Si hemos llegado al final del número, añadimos la combinación actual a los resultados
    if (indice == equipos.size()) {
        resultados.push_back(actual);
        return;
    }

    // Generar combinaciones usando dígitos adyacentes
    string aux = " ";
    for (int i = indice; i < equipos.size(); i++) {
        aux += equipos[i];
        actual.push_back(aux);
        hallaCombBackTrack(i + 1,equipos , actual, resultados);
        actual.pop_back(); // Deshacer la última acción
    }
}


