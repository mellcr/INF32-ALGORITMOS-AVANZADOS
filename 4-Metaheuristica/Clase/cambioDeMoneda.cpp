#include <iomanip>
#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>

#define maxiteraciones 10000 // Número máximo de iteraciones para encontrar la mejor solución
#define alpha 0.2            // Parámetro alfa para definir el RCL (Restricted Candidate List)

using namespace std;

// Función de comparación para ordenar en orden descendente
bool cmp(int a, int b){
    return a > b;
}

// Función para sumar todos los elementos de un vector `solucion`
int sumar(vector<int> solucion){
    int s = 0;
    for(int i = 0; i < solucion.size(); i++)
        s += solucion[i];
    return s;
}

// Función para comparar dos soluciones basándose en la cantidad total de monedas usadas
bool cmpCant(vector<int> mejorSolucion, vector<int> solucion){
    int sumaM = sumar(mejorSolucion);  // Suma de monedas en la mejor solución
    int suma = sumar(solucion);        // Suma de monedas en la solución actual
    if(sumaM == 0)
        sumaM = 9999;                  // Si la mejor solución no tiene monedas, asignamos un valor alto
    return suma < sumaM;               // Devuelve true si la solución actual usa menos monedas
}

// Función para resolver el problema de cambio utilizando un enfoque probabilístico con RCL
void cambio(int monto, vector<int> denominaciones, int d){
    int mejorResiduo = 999999;         // Inicializa el mejor residuo como un valor alto
    vector<int> mejorSolucion(d, 0);   // Inicializa la mejor solución con `d` elementos en 0 (cantidad por denominación)
    srand(time(NULL));                 // Inicializa la semilla aleatoria

    // Bucle principal de búsqueda para intentar mejorar la solución
    for(int i = 0; i < maxiteraciones; i++){
        vector<int> solucion(d, 0);    // Vector que almacena la cantidad de monedas usadas en la solución actual
        vector<int> copia;             // Vector auxiliar para trabajar con una copia de denominaciones
        sort(denominaciones.begin(), denominaciones.end(), cmp); // Ordena las denominaciones en orden descendente
        copia.insert(copia.begin(), denominaciones.begin(), denominaciones.end()); // Copia `denominaciones` en `copia`
        
        int residuo = monto;           // Inicializa el residuo con el monto objetivo

        // Bucle que continúa hasta que no haya más denominaciones en `copia`
        while(!copia.empty()){
            int beta = copia[0];                       // Mejor solución (denominación más grande)
            int tau = copia[copia.size() - 1];         // Peor solución (denominación más pequeña)
            vector<int> rcl;                           // Lista de candidatos restringida (RCL)
            int rangoInf = beta - alpha * (beta - tau); // Límite inferior para la RCL
            
            // Construcción de la RCL: agrega índices de monedas que cumplen con el rango
            for(int j = 0; j < copia.size(); j++)
                if(copia[j] >= rangoInf && copia[j] <= beta)
                    rcl.push_back(j);
            
            int ind = rand() % rcl.size();             // Selecciona un índice aleatorio dentro de la RCL
            int indA = rcl[ind];                       // Índice en `copia` para el valor seleccionado
            int S = copia[indA];                       // Denominación seleccionada

            // Si la denominación seleccionada no excede el residuo
            if(S <= residuo){
                int i = 0;
                for(int j = 0; j < denominaciones.size(); j++)
                    if(denominaciones[j] == S)
                        i = j;                         // Encuentra el índice de la denominación en `denominaciones`
                
                solucion[i] = residuo / S;             // Almacena cuántas monedas de denominación `S` se usan
                residuo -= S * solucion[i];            // Actualiza el residuo restando el valor total usado
            }
            copia.erase(copia.begin() + indA);         // Elimina la denominación usada de `copia`
        }
        
        // Si la solución actual mejora el residuo y usa menos monedas, actualiza la mejor solución
        if(residuo <= mejorResiduo && cmpCant(mejorSolucion, solucion)){
            mejorResiduo = residuo;
            mejorSolucion.clear();
            mejorSolucion.insert(mejorSolucion.begin(), solucion.begin(), solucion.end());
        }
    }

    // Imprime la mejor solución encontrada
    for(int i = 0; i < d; i++)
        cout << denominaciones[i] << '-' << mejorSolucion[i] << ' ';
}

int main(){
    int monto = 181, d = 3;
    vector<int> denominaciones = {1, 90, 100};  // Denominaciones de las monedas disponibles
    // Quiero guardar la cantidad utilizada por cada denominación
    cambio(monto, denominaciones, d);           // Llama a la función `cambio` con el monto y denominaciones
    return 0;
}
