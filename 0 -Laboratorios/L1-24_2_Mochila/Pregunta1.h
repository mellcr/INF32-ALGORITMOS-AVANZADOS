/* 
 * File:   Pregunta1.h
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on 14 de octubre de 2024, 8:50 a. m.
 */
#ifndef PREGUNTA1_H
#define PREGUNTA1_H
#define N 5
#define M 7

void pregunta1();
void encontrarSolucion(int ropa[N][M], int inicio, int capacidad, 
        int matrizRespuesta[N][M]);
bool backLavadora(int ropa[M], int inicio, int capacidad, int capacidadInicio,
        int matrizRespuesta[M], int &totalUsado);

#endif /* PREGUNTA1_H */

