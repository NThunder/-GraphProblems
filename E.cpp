#include <iostream>
#include <vector>
#include <utility>
#include <queue>

template <class T>
class GraphOnTable {
    std::vector<std::vector<T>> dist;
    std::vector<std::pair<T, T>> GetNborsRest(std::pair<T, T>);
public:
    GraphOnTable(const int&, const int&);
    void RestBFS(std::vector<std::pair<T, T>>);
    void PrintfDistAndPathRest();
};

template <class T>
GraphOnTable<T>::GraphOnTable(const int& heigh, const int& width) : 
    dist(heigh + 1, std::vector<T>(width + 1, -1)) {
}

template <class T>
std::vector<std::pair<T, T>> GraphOnTable<T>::GetNborsRest(std::pair<T, T> vert) {
    std::vector<std::pair<T, T>> nbors;
    int heigh = dist.size();
    int width = dist[0].size();
    if (vert.first + 1 < heigh) {
            nbors.emplace_back(vert.first + 1, vert.second);        
    }
    if (vert.first - 1 >= 1) {
            nbors.emplace_back(vert.first - 1, vert.second);        
    }
    if (vert.second + 1 < width) {
            nbors.emplace_back(vert.first, vert.second + 1);        
    }
    if (vert.second - 1 >= 1) {
            nbors.emplace_back(vert.first, vert.second - 1);        
    }
    return nbors;
}

template <class T>
void GraphOnTable<T>::RestBFS(std::vector<std::pair<T, T>> rests) {
    for (size_t i = 0; i < dist.size(); ++i) {
        for (size_t j = 0; j < dist[0].size(); ++j) {
            dist[i][j] = -1;
        }
    }
    std::queue<std::pair<T, T>> expectation;
    for (auto & rest: rests) {
        expectation.push(rest);
        dist[rest.first][rest.second] = 0;
    }
    std::pair<T, T> vertex;
    while (!expectation.empty()) {
        vertex = expectation.front();
        expectation.pop();
        auto nbors = GetNborsRest(vertex);
        for (auto &u : nbors) {
            if (dist[u.first][u.second] == -1 || dist[u.first][u.second] > dist[vertex.first][vertex.second] + 1) {
                dist[u.first][u.second] = dist[vertex.first][vertex.second] + 1;
                expectation.push(u);
            }
        }
    }
}

template <class T>
void GraphOnTable<T>::PrintfDistAndPathRest() {
    for (size_t i = 1; i < dist.size(); ++i) {
        for (size_t j = 1; j < dist[0].size(); ++j) {
            std::cout << dist[i][j] << " ";
        }
        std::cout << "\n";       
    }
}

int main() {
    int heigh = 0;
    int width = 0;
    std::cin >> heigh >> width;
    GraphOnTable<int> GraphOnTable(heigh, width);
    int check = 0;
    std::vector<std::pair<int, int>> rest;
    for (int i = 1; i <= heigh; ++i) {
        for (int j = 1; j <= width; ++j) {
            std::cin >> check;
            if (check == 1) {
                rest.emplace_back(i, j);
            }
        }
    }
    GraphOnTable.RestBFS(rest);
    GraphOnTable.PrintfDistAndPathRest();
    return 0;
}

