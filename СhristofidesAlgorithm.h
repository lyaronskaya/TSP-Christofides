#ifndef CHRISTOFIDES_H
#define CHRISTOFIDES_H
#include <vector>
#include "EdmondsAlgorithm.h"
#include "EulerCircuit.h"
#include "PrimAlgorithm.h"

using namespace std;

class ChristofidesAlgorithm {
    int n;
    Graph find_MST(Graph &G);
    Graph get_vertexes_odd_degree(Graph &G);
    vector<int> find_min_perfect_matching(Graph &G);
    void unite(Graph&, vector<int> &);
    vector<int> euler_circuit(Graph &G);
    vector<int> hamiltonian_from_euler(Graph &G, vector<int> &euler, int &cost);
    
public:
    vector<int> find_hamiltonian_cycle(Graph&, int& cost);
};

vector<int> ChristofidesAlgorithm::find_hamiltonian_cycle(Graph &G, int &cost) {
    n = G.n;
    Graph T = find_MST(G);
    Graph N_T = get_vertexes_odd_degree(T);
    vector<int> M = find_min_perfect_matching(N_T);

    unite(T, M);
    vector<int> eulerCircuit = euler_circuit(T);
    return hamiltonian_from_euler(G, eulerCircuit, cost);
}

Graph ChristofidesAlgorithm::get_vertexes_odd_degree(Graph& T) {
    vector<int> vertexes;
    int n = T.n;
    for (int i = 0; i < n; ++i) {
        int neighbor_count = 0;
        for (auto v: T.edges[i]) {
            if (v) {
                neighbor_count++;
            }
        }
        if (neighbor_count % 2) {
            vertexes.push_back(i);
        }
    }
    vector<vector<bool>> edges(n, vector<bool>(n, 0));
    vector<vector<long>> edges_data(T.edgesData);
    for (auto& v: vertexes) {
        for (auto& u: vertexes) {
            edges[v][u] = T.edges[v][u];
        }
    }
    return Graph(edges, edges_data);
}

vector<int> ChristofidesAlgorithm::find_min_perfect_matching(Graph &G) {
    auto EdmAlg = EdmondsAlgorithm();
    auto res = EdmAlg.get_max_matching(G);
    return EdmAlg.get_max_matching(G);
}

Graph ChristofidesAlgorithm::find_MST(Graph &G) {
    vector<int> pred;
    prim(G, pred);
    vector<vector<bool>> edges(G.n, vector<bool>(G.n, 0));
    for (int i = 1; i < G.n; ++i) {
        edges[pred[i]][i] = edges[i][pred[i]] = 1;
    }
    return Graph(edges, G.edgesData);
}

vector<int> ChristofidesAlgorithm::euler_circuit(Graph &G) {
    auto EC = EulerCircuit();
    return EC.get_circuit(G);
}


void ChristofidesAlgorithm::unite(Graph& T, vector<int>& edges) {
    for (int i = 0; i < edges.size(); ++i) {
        if (edges[i] != -1)
            T.edges[i][edges[i]] = 1;
    }
}

vector<int> ChristofidesAlgorithm::hamiltonian_from_euler(Graph &G, vector<int> &euler, int &cost) {
    vector<int> res = {};
    auto visited = vector<bool>(n, false);
    int prev = euler[0];
    visited[0] = true;
    cost = 0;
    for (auto u: euler) {
        if (!visited[u]) {
            res.push_back(u);
            cost += G.edgesData[prev][u];
            prev = u;
            visited[u] = true;
        }
    }
    return res;
}
#endif
