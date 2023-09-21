#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
    public:
        Vertex();
        Vertex(int np, int nr);
        Vertex(const Vertex &v);
        virtual ~Vertex(){}
        int getParent() const { return this->parent; }
        int getRanking() const { return this->ranking; }
        void setParent(int np);
        void setRanking(int nr);
    protected:
        int parent, ranking;
};

#endif // VERTEX_H

// USING -1 AS UNDEFINED PARENT
Vertex::Vertex() {
    this->parent = -1;
    this->ranking = 0;
}

Vertex::Vertex(int np, int nr) {
    this->parent = np;
    this->ranking = nr;
}

Vertex::Vertex(const Vertex &v) {
    this->parent = v.getParent();
    this->ranking = v.getRanking();
}

void Vertex::setParent(int np) {
    this->parent = np;
}

void Vertex::setRanking(int nr) {
    this->ranking = nr;
}

#ifndef EDGE_H
#define EDGE_H


class Edge {
    public:
        Edge();
        Edge(int nv, int na, int nw);
        Edge(const Edge &e);
        virtual ~Edge(){}
        int getVertex() const { return this->vertex; }
        int getAdjacent() const { return this->adjacent; }
        int getWeight() const { return this->weight; }
        void setVertex(int nv);
        void setAdjacent(int na);
        void setWeight(int nw);
    protected:
        int vertex, adjacent, weight;
};

#endif // EDGE_H

Edge::Edge() {
    this->vertex = 0;
    this->adjacent = 0;
    this->weight = 0;
}

Edge::Edge(int nv, int na, int nw) {
    this->vertex = nv;
    this->adjacent = na;
    this->weight = nw;
}

Edge::Edge(const Edge &e) {
    this->vertex = e.getVertex();
    this->adjacent = e.getAdjacent();
    this->weight = e.getWeight();
}

void Edge::setVertex(int nv) {
    this->vertex = nv;
}

void Edge::setAdjacent(int na) {
    this->adjacent = na;
}

void Edge::setWeight(int nw) {
    this->weight = nw;
}

// Função de comparação para ordenar as arestas pelo peso
bool compareWeight(Edge a, Edge b) {
    return a.getWeight() < b.getWeight();
}

// Função para encontrar o conjunto pai de um vértice
int findSet(int x, vector<Vertex> &vertices) {
    if (vertices[x].getParent() != x) {
        vertices[x].setParent(findSet(vertices[x].getParent(), vertices));
    }

    return vertices[x].getParent();
}

// Função para criar um conjunto a partir de um vértice
void makeSet(int x, vector<Vertex> &vertices) {
    vertices[x].setParent(x);
    vertices[x].setRanking(0);
}

// Função para unir dois conjuntos
void unionSets(int x, int y, vector<Vertex> &vertices) {
    int rootX = findSet(x, vertices);
    int rootY = findSet(y, vertices);

    if (rootX == rootY) return;

    if (vertices[rootX].getRanking() < vertices[rootY].getRanking()) {
        vertices[rootX].setParent(rootY);
    } else {
        vertices[rootY].setParent(rootX);
        if (vertices[rootX].getRanking() == vertices[rootY].getRanking()) {
            vertices[rootX].setRanking(vertices[rootX].getRanking() + 1);
        }
    }
}

int getTotalEdgeWeight(vector<Edge> &edges) {
    int maximumWeight = 0;

    for (int i = 0; i < edges.size(); i++) {
        maximumWeight += edges[i].getWeight();
    }

    return maximumWeight;
}

// Função principal para encontrar a Árvore Geradora Mínima de um grafo
int MST_KRUSKAL(int n, int m, vector<Vertex> &vertices, vector<Edge> &edges) {
    vector<Edge> minimalTree; // Armazena as arestas da AGM
    int vertex, adjacent, treeWeight = 0;


    for (int i = 0; i < n; i++) {
        makeSet(i, vertices); // Inicializa cada vértice em um conjunto
    }

    sort(edges.begin(), edges.end(), compareWeight); // Ordena as arestas pelo peso

    for (int i = 0; i < m; i++) {
        vertex = edges[i].getVertex();
        adjacent = edges[i].getAdjacent();

        if (findSet(vertex, vertices) != findSet(adjacent, vertices)) { // Se os vértices estão em conjuntos diferentes
            minimalTree.push_back(edges[i]); // Adiciona a aresta na AGM
            treeWeight += edges[i].getWeight();
            unionSets(vertex, adjacent, vertices); // Une os conjuntos dos vértices
        }
    }

    return treeWeight;
}

int main() {
    int m = 1, n = 1; // Number of vertices and edges, respectively
    int x, y, z; // Vertices in a edge and the weight, respectively

    while ((m != 0) && n != 0) {
        vector<Edge> edgesList; // Lista de arestas
        vector<Vertex> verticesList; // Lista de vértices
        Edge edgeAux;
        int finalCost = 0;

        cin >> m >> n;

        if (m != 0 && n != 0) {
            verticesList.resize(m);
            for (int i = 0; i < n; i++) {
                cin >> x >> y >> z;

                edgeAux.setVertex(x);
                edgeAux.setAdjacent(y);
                edgeAux.setWeight(z);
                edgesList.push_back(edgeAux);
            }
           finalCost = getTotalEdgeWeight(edgesList) - MST_KRUSKAL(m, n, verticesList, edgesList);
           cout << finalCost << endl;
        }
    }
    return 0;
}