#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Producto {
    string nombre;
    int stock;
};

// Función para intercambiar productos
void swap(Producto &a, Producto &b) {
    Producto temp = a;
    a = b;
    b = temp;
}

// Heapify (ajusta el heap máximo)
void heapify(vector<Producto> &arr, int n, int i) {
    int mayor = i;        // raíz
    int izq = 2 * i + 1;  // hijo izquierdo
    int der = 2 * i + 2;  // hijo derecho

    // Comparar por stock
    if (izq < n && arr[izq].stock > arr[mayor].stock)
        mayor = izq;

    if (der < n && arr[der].stock > arr[mayor].stock)
        mayor = der;

    // Si el mayor no es la raíz
    if (mayor != i) {
        swap(arr[i], arr[mayor]);
        heapify(arr, n, mayor);
    }
}

// Heap Sort
void heapSort(vector<Producto> &arr) {
    int n = arr.size();

    // Construir heap máximo
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extraer elementos uno por uno
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);   // mover máximo al final
        heapify(arr, i, 0);     // reorganizar heap reducido
    }
}

// Mostrar productos
void mostrar(const vector<Producto> &arr) {
    for (const auto &p : arr) {
        cout << "(" << p.nombre << ", " << p.stock << ") ";
    }
    cout << endl;
}

int main() {
    vector<Producto> inventario = {
        {"Leche", 4},
        {"Pan", 10},
        {"Yogur", 3},
        {"Arroz", 5},
        {"Café", 1}
    };

    cout << "Arreglo inicial:\n";
    mostrar(inventario);

    heapSort(inventario);

    cout << "\nOrdenado por stock ascendente:\n";
    mostrar(inventario);

    return 0;
}