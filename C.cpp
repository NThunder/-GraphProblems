#include <iostream>
#include <vector>
#include <utility>
#include <queue>

enum Color {
    White = 0,
    Gray = 1,
    Black = 2
};

template <class T>
class GraphOnTable {
    std::vector<std::vector<std::pair<T, T>>> parent;
    std::vector<std::vector<T>> dist;
    std::vector<std::pair<T, T>> GetNborsForse(std::pair<T, T>);
public:
    GraphOnTable(int&);
    void HorseBFS(std::pair<T, T>);
    void PrintfDistAndPathHorse(std::pair<T, T>);
};

template <class T>
GraphOnTable<T>::GraphOnTable(int& count_vertex) : 
    parent(count_vertex + 1, std::vector<std::pair<T, T>>(count_vertex + 1, {-1, -1})),
    dist(count_vertex + 1, std::vector<T>(count_vertex + 1, -1)) {
}

template <class T>
std::vector<std::pair<T, T>> GraphOnTable<T>::GetNborsForse(std::pair<T, T> vert) {
    std::vector<std::pair<T, T>> nbors;
    int field_size = dist.size();
    if (vert.first + 2 < field_size) {
        if (vert.second + 1 < field_size) {
            nbors.emplace_back(vert.first + 2, vert.second + 1);        
        }
        if (vert.second - 1 >= 1) {
            nbors.emplace_back(vert.first + 2, vert.second - 1);
        }
    }
    if (vert.first - 2 >= 1) {
        if (vert.second + 1 < field_size) {
            nbors.emplace_back(vert.first - 2, vert.second + 1);        
        }
        if (vert.second - 1 >= 1) {
            nbors.emplace_back(vert.first - 2, vert.second - 1);
        }
    }
    if (vert.second + 2 < field_size) {
        if (vert.first + 1 < field_size) {
            nbors.emplace_back(vert.first + 1, vert.second + 2);        
        }
        if (vert.first - 1 >= 1) {
            nbors.emplace_back(vert.first - 1, vert.second + 2);
        }
    }
    if (vert.second - 2 >= 1) {
        if (vert.first + 1 < field_size) {
            nbors.emplace_back(vert.first + 1, vert.second - 2);        
        }
        if (vert.first - 1 >= 1) {
            nbors.emplace_back(vert.first - 1, vert.second - 2);
        }
    }
    return nbors;
}

template <class T>
void GraphOnTable<T>::HorseBFS(std::pair<T, T> start_vertex) {
    for (size_t i = 0; i < dist.size(); ++i) {
        for (size_t j = 0; j < dist.size(); ++j) {
            dist[i][j] = -1;
            parent[i][j] = {-1, -1};
        }
    }
    std::queue<std::pair<T, T>> expectation;
    expectation.push(start_vertex);
    parent[0][0] = start_vertex;
    dist[start_vertex.first][start_vertex.second] = 0;
    parent[start_vertex.first][start_vertex.second] = start_vertex;
    std::pair<T, T> vertex;
    while (!expectation.empty()) {
        vertex = expectation.front();
        expectation.pop();
        auto nbors = GetNborsForse(vertex);
        for (auto &u : nbors) {
            if (dist[u.first][u.second] == -1) {
                dist[u.first][u.second] = dist[vertex.first][vertex.second] + 1;
                parent[u.first][u.second] = vertex;
                expectation.push(u);
            }
        }
    }
}

template <class T>
void GraphOnTable<T>::PrintfDistAndPathHorse(std::pair<T, T> fin_v) {
    std::cout << dist[fin_v.first][fin_v.second] << "\n";
    std::vector<std::pair<T,T>> ans;
    if (dist[fin_v.first][fin_v.second] != -1) {
        std::pair<T, T> par = parent[fin_v.first][fin_v.second];
        while (par != parent[0][0]) {
            ans.push_back(par);
            par = parent[par.first][par.second];
        }
        std::cout << parent[0][0].first << " " << parent[0][0].second << "\n";
        for (int i = ans.size() - 1; i >= 0; --i) {
            std::cout << ans[i].first << " " << ans[i].second << "\n";
        }
        if (parent[0][0] != fin_v) {
            std::cout << fin_v.first << " " << fin_v.second << "\n";
        }
    }
}

int main() {
    int c_v = 0;
    std::cin >> c_v;
    std::pair<int, int> st_p;
    std::pair<int, int> fin_p;
    std::cin >> st_p.first >> st_p.second;
    std::cin >> fin_p.first >> fin_p.second;
    GraphOnTable<int> GraphOnTable(c_v);
    GraphOnTable.HorseBFS(st_p);
    GraphOnTable.PrintfDistAndPathHorse(fin_p);
    return 0;
}