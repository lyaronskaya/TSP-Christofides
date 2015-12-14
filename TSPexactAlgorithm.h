#ifndef TSPexactAlgorithm_h
#define TSPexactAlgorithm_h

#include <vector>
#include <cfloat>
#include "Graph.h"

//Graph G - полный взвешенный граф с метрической функцией весов
vector<int> tsp_dinamic(Graph &G)
{
    int n = G.n;
    long nsub = 1 << n;
    vector<vector<float>> opt(nsub, vector<float>(n));
    
    for (long s = 1; s < nsub; s += 2)
        for (int i = 1; i < n; ++i) {
            vector<int> subset;
            for (int u = 0; u < n; ++u)
                if (s & (1 << u))
                    subset.push_back(u);
            
            if (subset.size() == 2)
                opt[s][i] = G.edgesData[0][i];
            
            else if (subset.size() > 2) {
                float min_subpath = FLT_MAX;
                long t = s & ~(1 << i);
                for (vector<int>::iterator j = subset.begin(); j != subset.end(); ++j)
                    if (*j != i && opt[t][*j] + G.edgesData[*j][i] < min_subpath)
                        min_subpath = opt[t][*j] + G.edgesData[*j][i];
                opt[s][i] = min_subpath;
            }
        }
    
    vector<int> tour;
    tour.push_back(0);
    
    bool selected[n];
    fill(selected, selected + n, false);
    selected[0] = true;
    
    long s = nsub - 1;
    
    for (int i = 0; i < n - 1; ++i) {
        int j = tour.back();
        float min_subpath = FLT_MAX;
        int best_k = 0;
        for (int k = 0; k < n; ++k)
            if (!selected[k] && opt[s][k] + G.edgesData[k][j] < min_subpath) {
                min_subpath = opt[s][k] + G.edgesData[k][j];
                best_k = k;
            }
        tour.push_back(best_k);
        selected[best_k] = true;
        s -= 1 << best_k;
    }
    tour.push_back(0);
    
    return tour;
}

#endif
