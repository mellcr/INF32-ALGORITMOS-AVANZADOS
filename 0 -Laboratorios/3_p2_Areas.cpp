#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Producto {
    string nombre;
    int req; // Requerimientos (cantidad)
    int longitud;
    int altura;
    int area;  // área del producto
};

// Estructura para la lámina
struct Lamina {
    int ancho = 50;
    int alto = 50;
    int residuoAncho = 50;  // espacio restante en ancho
    int residuoAlto = 50;   // espacio restante en alto
};

bool compara(Producto &a, Producto &b) {
    return a.area > b.area;  // Ordenamos por área de mayor a menor
}

void imprimeProductos(vector<Producto> &productos) {
    for (auto &prod : productos) {
        cout << prod.nombre << ": " << prod.req << " unidades, " 
             << prod.longitud << "x" << prod.altura << " cm, área: " 
             << prod.area << " cm²" << endl;
    }
}

void cortesLaminas(vector<Producto> &productos, int nProd, vector<Lamina> &almacen, Lamina &lamina) {
    /* Calculo el área por producto */
    for (int i = 0; i < nProd; i++) {
        productos[i].area = productos[i].longitud * productos[i].altura;
    }

    /* Ordenamos los productos por área de mayor a menor */
    sort(productos.begin(), productos.end(), compara);

    /* Despachamos los pedidos con mayor área */
    for (int i = 0; i < nProd; i++) {
        vector<Lamina> temp(almacen);
        int req = 0;
        /* Verificamos desde el inicio de las láminas */
        for (int j = 0; j < temp.size();) {
            // Si el producto cabe en la lámina actual
            if (productos[i].longitud <= temp[j].residuoAncho && 
                productos[i].altura <= temp[j].residuoAlto) {
                
                temp[j].residuoAncho -= productos[i].longitud;
                temp[j].residuoAlto -= productos[i].altura;
                req++;
                
                // Si se atendió todo el pedido
                if (req == productos[i].req) {
                    almacen.assign(temp.begin(), temp.end());
                    break;
                }
            } else {
                j++;  // Si no cabe, pasamos a la siguiente lámina
                if (j == temp.size()) {
                    temp.push_back(lamina);  // Añadimos una nueva lámina si no cabe en ninguna existente
                }
            }
        }
    }
}

int main() {
    vector<Producto> productos = {
        {"Latas de mentolato", 5, 2, 3},
        {"Latas de crema Nivea", 10, 9, 3},
        {"Latas de atún", 15, 14, 7},
        {"Latas de conserva", 20, 15, 20},
        {"Latas de aceite industrial", 20, 22, 18}
    };

    int nProd = productos.size();
    vector<Lamina> almacen;
    Lamina lamina;

    cortesLaminas(productos, nProd, almacen, lamina);
    
    cout << "Cortes realizados:" << endl;
    imprimeProductos(productos);

    return 0;
}
