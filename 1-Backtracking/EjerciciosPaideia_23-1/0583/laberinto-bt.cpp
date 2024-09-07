#include <iostream>
#define N 10
#define verdadero true
#define falso false

using namespace std;

// Funci�n para imprimir la soluci�n del laberinto
void imprimirSolucion(int sol[N][N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            cout << " " << sol[i][j] << " ";  // Imprime el valor de cada celda en la soluci�n
        cout << endl;
    }
}

// Funci�n para verificar si una posici�n en el laberinto es segura
int esSeguro(int laberinto[N][N], int x, int y)
{
    if (x >= 0 && x < N && y >= 0 && y < N && laberinto[x][y] == 1)  // Verifica si la posici�n est� dentro de los l�mites del laberinto y contiene un camino v�lido
        return 1;
    return 0;
}

// Funci�n recursiva para resolver el laberinto
int resolverLaberintoUtil(int laberinto[N][N], int x, int y, int sol[N][N])
{
    if (x == N - 1 && y == N - 1)  // Si se ha llegado a la salida del laberinto
    {
        sol[x][y] = 1;  // Marca la posici�n como parte de la soluci�n
        return verdadero;
    }
    if (esSeguro(laberinto, x, y) == verdadero)  // Verifica si la posici�n actual es segura
    {
        sol[x][y] = 1;  // Marca la posici�n como parte de la soluci�n

        // Llamada recursiva para explorar los movimientos hacia abajo y hacia la derecha
        if (resolverLaberintoUtil(laberinto, x + 1, y, sol) == 1)
            return 1;

        if (resolverLaberintoUtil(laberinto, x, y + 1, sol) == 1)
            return 1;

        sol[x][y] = 0;  // Si ninguno de los movimientos conduce a la soluci�n, desmarca la posici�n
        return 0;
    }

    return 0;
}

// Funci�n principal para resolver el laberinto
int resolverLaberinto(int laberinto[N][N])
{
    int sol[N][N] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};

    if (resolverLaberintoUtil(laberinto, 0, 0, sol) == 0)  // Llamada a la funci�n recursiva para resolver el laberinto
    {
        cout << "No hay solucion" << endl;  // Si no se encontr� una soluci�n, muestra un mensaje
        return 0;
    }

    imprimirSolucion(sol);  // Imprime la soluci�n encontrada
    return verdadero;
}

// Funci�n principal
int main()
{
    int laberinto[N][N] = {
    	/*{1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}*/
    	
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
        {1, 1, 0, 0, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 0, 1}
		};

    resolverLaberinto(laberinto);  // Llamada a la funci�n para resolver el laberinto
    return 0;
}

