#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

using namespace std;

struct Graph {
    int n;
    vector<vector<bool>> edges;
    vector<vector<long>> edgesData;
    Graph();
    Graph(vector<vector<bool>> &edges,vector<vector<long>> &edgesData);
    int get_degree(int v);
    int get_random_neighbor(int v);
    Graph& operator=(const Graph&);
};

#endif