#ifndef EULERCIRCUIT_H
#define EULERCIRCUIT_H
#include <vector>
#include "Graph.h"

using namespace std;

class EulerCircuit {
    vector<int> vertexes;
    int edgesCount;
    Graph G;
    vector<int> euler(int v);
    void add_cycle();
public:
    vector<int> get_circuit(const Graph &G_);
};

vector<int> EulerCircuit::get_circuit(const Graph &G_) {
    G = G_;
    vertexes = {};
    for (int i = 0; i < G.n; ++i)
        for (int j = 0; j < G.n; ++j)
            if (G.edges[i][j])
                edgesCount++;
    
    while (edgesCount > 0) {
        add_cycle();
    }
    return vertexes;
}

void EulerCircuit::add_cycle() {
    int v, i;
    vector<int> local_circuit;
    
    if (!vertexes.empty()) {
        int circuit_len = vertexes.size();
        for (i = 0; i < circuit_len; ++i) {
            if (G.get_degree(vertexes[i]) > 0) {
                v = vertexes[i];
                break;
            }
        }
    }
    else {
        v = 0;
        vertexes.push_back(v);
        i = 0;
    }
    local_circuit = euler(v);
    for (auto& x: local_circuit) {
        i++;
        vertexes.emplace(vertexes.begin() + i, x);
    }
}

vector<int> EulerCircuit::euler(int v) {
    vector<int> cycle;
    int w;

    while (G.get_degree(v) > 0) {
        w = G.get_random_neighbor(v);
        cycle.push_back(w);
        G.edges[v][w] = 0;
        edgesCount--;
        v = w;
    }
    return cycle;
}

#endif


















