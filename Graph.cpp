#include <vector>
#include "Graph.h"

using namespace std;

Graph::Graph() { edges = {}, edgesData = {}; }

int Graph::get_degree(int v) {
    int degree = 0;
    for (int i = 0; i < n; ++i) {
        if (edges[v][i])
            degree++;
    }
    return degree;
}

int Graph::get_random_neighbor(int v) {
    for (int i = 0; i < n; ++i) {
        if (edges[v][i])
            return i;
    }
    return v;
}

Graph& Graph::operator=(const Graph& other) {
    n = other.n;
    edges = other.edges;
    edgesData = other.edgesData;
    return *this;
}

Graph::Graph(vector<vector<bool>> &edges_,vector<vector<long>> &edgesData_) {
    edges = edges_;
    edgesData = edgesData_;
    n = edgesData.size();
}