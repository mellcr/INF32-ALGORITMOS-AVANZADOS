/* 
 * File:   Pregunta2.h
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on 14 de octubre de 2024, 8:50 a. m.
 */
#ifndef PREGUNTA2_H
#define PREGUNTA2_H
#include <vector>

void pregunta2();
void backMochilaTodo(int index,vector<int> &cantidadesProd,vector<int> &capcidadMochilas,
        int cantMochila,int cantProd,vector<vector<int>> &almacenSolu);
void imprime(vector<vector<int>> &almacenSolu);
void imprime2(vector<vector<int>> &almacenSolu);
bool backMochilaTodo2(int index,vector<int> &cantidadesProd,vector<int> &capcidadMochilas,
        int cantMochila,int cantProd,vector<vector<int>> &almacenSolu);
void backMochilaRosa(int index,vector<int> &cantidadesProd,vector<int> &capcidadMochilas);
void imprime3(vector<int> &almacenRosita);
#endif /* PREGUNTA2_H */

