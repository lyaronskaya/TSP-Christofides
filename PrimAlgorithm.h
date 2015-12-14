#ifndef PRIMALGORITHM_H
#define PRIMALGORITHM_H
#include <vector>
#include <queue>
#include <climits>
#include <iostream>
#include "Graph.h"

using namespace std;

typedef pair<int, int> qitem;

//решает задачу поиска минимального остовного дерева
long long prim(Graph &G, vector<int> &pred) {
    int n = G.n;
    pred.assign(n, -1);
    vector<bool> visited(n);
    vector<long> prio(n, LONG_MAX);
    prio[0] = 0;
    priority_queue<qitem, vector<qitem>, greater<qitem> > q;
    q.push(make_pair(0, 0));
    long long res = 0;
    
    while (!q.empty()) {
        int d = q.top().first;
        int u = q.top().second;
        q.pop();
        if (visited[u])
            continue;
        visited[u] = true;
        res += d;
        for (int i = 0; i < n; i++) {
            if (!G.edges[u][i])
                continue;
            if (visited[i])
                continue;
            int priority = G.edgesData[u][i];
            if (prio[i] > priority) {
                prio[i] = priority;
                pred[i] = u;
                q.push(make_pair(priority, i));
            }
        }
    }
    return res;
}

#endif