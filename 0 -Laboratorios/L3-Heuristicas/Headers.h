/* 
 * File:   Headers.h
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on 14 de octubre de 2024, 6:44 p. m.
 */
#ifndef HEADERS_H
#define HEADERS_H
#include <vector>

void clasicos();
void mochila();
int cargaMochila(vector<int> &mochila,int n,int capacidad);
bool compara(int a, int b);
void monedero();
void obtieneMonedas(vector<int> &monedero,int n,vector<int> &solucion,int vuelto);

void pregunta1();

void examen1();

#endif /* HEADERS_H */

