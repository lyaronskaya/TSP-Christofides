#include <iostream>
#include <vector>
#include "Graph.h"
#include <queue>
#include "СhristofidesAlgorithm.h"
#include "TSPexactAlgorithm.h"
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std;

double distance(int x1, int y1, int x2, int y2) {
    return sqrt( (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) );
}

int main(int argc, const char * argv[]) {
    vector<pair<int, int>> coords = {};
    string file_path("coords.txt");
    ifstream data_txt(file_path);
    string line;
    
    for (int i = 0; getline(data_txt, line); ++i) {
        istringstream iss(line);
        string s;
        int city_id, x, y;
        getline(iss, s, ' ');
        try {
            city_id = stoi(s);
        } catch(...) {
            break;
        }
        getline(iss, s, ' ');
        x = stoi(s);
        getline(iss, s, ' ');
        y = stoi(s);
        coords.emplace_back(x, y);
    }

    int n = coords.size();
    auto edges = vector<vector<bool>>(n, vector<bool>(n, 1));
    auto edges_data = vector<vector<long>>(n, vector<long>(n, LONG_MAX));
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            edges_data[i][j] = edges_data[j][i] = distance(coords[i].first, coords[i].second, coords[j].first, coords[j].second);
        }
        edges[i][i] = 0;
    }
    Graph G(edges, edges_data);
    
    auto start = std::chrono::steady_clock::now();
    ChristofidesAlgorithm ea;
    int total_cost;
    auto res = ea.find_hamiltonian_cycle(G, total_cost);
    for (int i = 0; i < n; ++i) {
        cout << res[i] << " ";
    }
    cout << "\n" << total_cost;
    auto end = std::chrono::steady_clock::now();
    std::cout << "Approximate solution took "
    << std::chrono::duration_cast<std::chrono::minutes>(end - start).count()
    << " us.\n";

//    start = std::chrono::steady_clock::now();
//    //
//    auto opt_tour = tsp_dinamic(G);
//    end = std::chrono::steady_clock::now();
//    std::cout << "Exact solution took "
//    << std::chrono::duration_cast<std::chrono::minutes>(end - start).count()
//    << " us.\n";
    
    return 0;
}
