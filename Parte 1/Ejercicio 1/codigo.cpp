#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void BFS(int inicio, const vector<vector<int>>& grafo, int n) {
    vector<bool> visitado(n, false);
    queue<int> cola;

    visitado[inicio] = true;
    cola.push(inicio);

    cout << "Orden de exploracion desde estacion " << inicio << ": ";

    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();
        cout << actual << " ";

        for (int vecino : grafo[actual]) {
            if (!visitado[vecino]) {
                visitado[vecino] = true;
                cola.push(vecino);
            }
        }
    }
}

int main() {
    int n = 5;
    // 0 = Terminal Central, 1 = Estación Norte, 2 = Estación Sur
    // 3 = Parada A,          4 = Parada B
    vector<vector<int>> grafo(n);

    grafo[0].push_back(1); // Terminal → Estación Norte
    grafo[0].push_back(2); // Terminal → Estación Sur
    grafo[1].push_back(3); // Estación Norte → Parada A
    grafo[2].push_back(4); // Estación Sur → Parada B

    BFS(0, grafo, n);
    // Salida esperada: 0 1 2 3 4

    return 0;
}
