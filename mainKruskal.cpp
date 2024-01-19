#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
 
// Estructura de datos para almacenar un borde de graph
struct Edge {
    int src, dest, weight;
};
 
// Objeto de comparación que se usará para ordenar los bordes
struct compare
{
    bool operator() (Edge const &a, Edge const &b) const {
        return a.weight > b.weight;
    }
};
 
// Una clase para representar un conjunto disjunto
class DisjointSet
{
    unordered_map<int, int> parent;
 
public:
    // realizar la operación MakeSet
    void makeSet(int n)
    {
        // crea `n` conjuntos disjuntos (uno para cada vértice)
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
 
    // Encuentra la raíz del conjunto al que pertenece el elemento `k`
    int Find(int k)
    {
        // si `k` es root
        if (parent[k] == k) {
            return k;
        }
 
        // recurre para el padre hasta que encontramos la raíz
        return Find(parent[k]);
    }
 
    // Realizar Unión de dos subconjuntos
    void Union(int a, int b)
    {
        // encuentra la raíz de los conjuntos en los que se encuentran los elementos
        // Pertenece `x` e `y`
        int x = Find(a);
        int y = Find(b);
 
        parent[x] = y;
    }
};
 
// Función para construir MST usando el algoritmo de Kruskal
vector<Edge> runKruskalAlgorithm(vector<Edge> edges, int n)        // sin referencia, sin constante
{
    // almacena los bordes presentes en MST
    vector<Edge> MST;
 
    // inicializa la clase `DisjointSet`
    DisjointSet ds;
 
    // crea un conjunto singleton para cada elemento del universo
    ds.makeSet(n);
 
    // ordena los bordes aumentando el peso
    sort(edges.begin(), edges.end(), compare());
 
    // MST contiene exactamente los bordes `V-1`
    while (MST.size() != n - 1)
    {
        // considera el siguiente borde con peso mínimo del graph
        Edge next_edge = edges.back();
        edges.pop_back();
 
        // encuentra la raíz de los conjuntos a los que pertenecen dos extremos
        // los vértices de la siguiente arista pertenecen
        int x = ds.Find(next_edge.src);
        int y = ds.Find(next_edge.dest);
 
        // si ambos extremos tienen diferentes padres, pertenecen a
        // diferentes componentes conectados y se pueden incluir en MST
        if (x != y)
        {
            MST.push_back(next_edge);
            ds.Union(x, y);
        }
    }
    return MST;
}
 
int main()
{
    // vector de los bordes del graph según el diagrama anterior.
    vector<Edge> edges =
    {
        // (u, v, w) el triplete representa el borde no dirigido desde
        // vértice `u` a vértice `v` con peso `w`
        {0, 1, 7}, {1, 2, 8}, {0, 3, 5}, {1, 3, 9}, {1, 4, 7}, {2, 4, 5},
        {3, 4, 15}, {3, 5, 6}, {4, 5, 8}, {4, 6, 9}, {5, 6, 11}
    };
 
    // número total de nodos en el graph (etiquetados de 0 a 6)
    int n = 7;
 
    // construir grafo
    vector<Edge> e = runKruskalAlgorithm(edges, n);
 
    for (Edge &edge: e)
    {
        cout << "(" << edge.src << ", " << edge.dest << ", "
             << edge.weight << ")" << endl;
    }
 
    return 0;
}
