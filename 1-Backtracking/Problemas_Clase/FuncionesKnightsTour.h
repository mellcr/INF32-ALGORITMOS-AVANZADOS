/* 
 * File:   FuncionesKnightsTour.h
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on 6 de setiembre de 2024, 5:20 p. m.
 */
#ifndef FUNCIONESKNIGHTSTOUR_H
#define FUNCIONESKNIGHTSTOUR_H

vector<vector<int>> inicializarMatriz(int numInsertar); 
void iniciaRecorridoCab(); 
int recorridoBack(int x,int y,int numMov,vector<vector<int>> &tablero);
int esMovValido(int x,int y,vector<vector<int>> &tablero);

#endif /* FUNCIONESKNIGHTSTOUR_H */

