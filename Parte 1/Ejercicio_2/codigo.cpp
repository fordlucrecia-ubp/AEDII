#include <iostream>
using namespace std;

const int T = 3; // Grado mínimo

class NodoB {
public:
    int claves[2*T-1];
    NodoB* hijos[2*T];
    int n;
    bool hoja;

    NodoB(bool hoja) {
        this->hoja = hoja;
        n = 0;
        for (int i = 0; i < 2*T; i++)
            hijos[i] = nullptr;
    }

    void recorrer() {
        for (int i = 0; i < n; i++) {
            if (!hoja)
                hijos[i]->recorrer();
            cout << claves[i] << " ";
        }
        if (!hoja)
            hijos[n]->recorrer();
    }

    NodoB* buscar(int k) {
        int i = 0;
        while (i < n && k > claves[i])
            i++;

        if (claves[i] == k)
            return this;

        if (hoja)
            return nullptr;

        return hijos[i]->buscar(k);
    }
};

class ArbolB {
public:
    NodoB* raiz;

    ArbolB() {
        raiz = nullptr;
    }

    void insertar(int k) {
        if (raiz == nullptr) {
            raiz = new NodoB(true);
            raiz->claves[0] = k;
            raiz->n = 1;
        } else {
            insertarNoLleno(raiz, k);
        }
    }

    void insertarNoLleno(NodoB* nodo, int k) {
        int i = nodo->n - 1;

        if (nodo->hoja) {
            while (i >= 0 && nodo->claves[i] > k) {
                nodo->claves[i+1] = nodo->claves[i];
                i--;
            }
            nodo->claves[i+1] = k;
            nodo->n++;
        } else {
            while (i >= 0 && nodo->claves[i] > k)
                i--;

            insertarNoLleno(nodo->hijos[i+1], k);
        }
    }

    void mostrar() {
        if (raiz != nullptr)
            raiz->recorrer();
    }

    bool buscar(int k) {
        return (raiz == nullptr) ? false : (raiz->buscar(k) != nullptr);
    }
};

int main() {
    ArbolB inventario;

    // Simulación: códigos de productos
    inventario.insertar(100);
    inventario.insertar(50);
    inventario.insertar(200);
    inventario.insertar(150);
    inventario.insertar(75);

    cout << "Productos ordenados: ";
    inventario.mostrar();

    cout << "\nBuscar producto 150: ";
    if (inventario.buscar(150))
        cout << "Encontrado";
    else
        cout << "No encontrado";

    return 0;
}
