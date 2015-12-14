#ifndef EDMONDS_ALGORITHM_H
#define EDMONDS_ALGORITHM_H
#include "Graph.h"

class EdmondsAlgorithm {
    Graph* G;
    int n;
    vector<int> match, p, base, q;
    vector<bool> used, blossom;
    int lca(int a, int b);
    void mark_path(int v, int b, int children);
    int find_path(int root);
public:
    vector<int> get_max_matching(Graph &);
};

vector<int> EdmondsAlgorithm::get_max_matching(Graph &G_) {
    G = &G_;
    n = G->n;
    match.assign(n, -1);
    p.assign(n, 0);
    base.assign(n, 0);
    q.assign(n, 0);
    used.assign(n, 0);
    blossom.assign(n, 0);
    
    for (int i = 0; i < n; ++i)
        if (match[i] == -1) {
            int v = find_path (i);
            while (v != -1) {
                int pv = p[v],  ppv = match[pv];
                match[v] = pv,  match[pv] = v;
                v = ppv;
            }
        }
    return match;
}

int EdmondsAlgorithm::lca(int a, int b) {
    vector<bool> used_(n, 0);
    for (;;) {
        a = base[a];
        used_[a] = true;
        if (match[a] == -1)  break;
        a = p[match[a]];
    }

    for (;;) {
        b = base[b];
        if (used_[b])  return b;
        b = p[match[b]];
    }
}

void EdmondsAlgorithm::mark_path (int v, int b, int children) {
    while (base[v] != b) {
        blossom[base[v]] = blossom[base[match[v]]] = true;
        p[v] = children;
        children = match[v];
        v = p[match[v]];
    }
}

int EdmondsAlgorithm::find_path (int root) {
    used.assign(n, 0);
    p.assign(n, -1);
    for (int i = 0; i < n; ++i)
        base[i] = i;
    
    used[root] = true;
    int qh = 0, qt = 0;
    q[qt++] = root;
    while (qh < qt) {
        int v = q[qh++];
        for (size_t i = 0; i < n; ++i) {
            size_t to = i;
            if (!G->edges[v][i])
                continue;
            if (base[v] == base[to] || match[v] == to)
                continue;
            if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
                int curbase = lca (v, to);
                blossom.assign(n, 0);
                mark_path (v, curbase, to);
                mark_path (to, curbase, v);
                for (int j = 0; j < n; ++j)
                    if (blossom[base[j]]) {
                        base[j] = curbase;
                        if (!used[j]) {
                            used[j] = true;
                            q[qt++] = j;
                        }
                    }
            }
            else if (p[to] == -1) {
                p[to] = v;
                if (match[to] == -1)
                    return to;
                to = match[to];
                used[to] = true;
                q[qt++] = to;
            }
        }
    }
    return -1;
}

#endif
