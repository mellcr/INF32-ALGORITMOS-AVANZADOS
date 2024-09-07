
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
int cantSol=0; 
vector<vector<ControlSeg>> combinaciones; 
vector<ControlSeg> actual; 
int maximoPresupuesto(int pos,int n,int presupuesto,struct ControlSeg *controles);

typedef struct{
    int id; 
    int inversion; 
    int cantReq; 
    int req[3]; 
    int beneficios;
}ControlSeg;
/*
 *      MOCHILA CON REQUISITOS                
 */

int main(int argc, char** argv) {
    struct ControlSeg controles[8]={
        {1,32,0,{},60},
        {2,8,0,{},60},
        {3,40,2,{1,2},120},
        {4,40,0,{},60},
        {4,40,0,{},60},
        {5,20,0,{},32},
        {6,4,{2},20},
        {7,20,{6},48},
        {8,20,{6},60}
    };
    int P=100,n=8; 
    
    maximoPresupuesto(0,n,P,controles);
    
    
    
    
    return 0;
}

int maximoPresupuesto(int pos,int n,int presupuesto,struct ControlSeg *controles){
    if(pos==n) return 0; 
    if(presupuesto ==0 and valida()){
        //se agrega una nueva solucion :) 
        
    }
    
    actual.push_back(controles[pos]); 
    maximoPresupuesto(pos+1,presupuesto-controles[pos].inversion, controles);
    
    actual.pop_back(); //retrocede
    maximoPresupuesto(pos+1,presupuesto,controles); 
    
    
}
