#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <unordered_map>

template<typename T>
void hash_combine(std::size_t &seed, T const &key) {
    std::hash<T> hasher;
    seed ^= hasher(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
    template <typename T1, typename T2>
    struct hash<std::pair<T1, T2>> {
        std::size_t operator()(std::pair<T1, T2> const &p) const {
            std::size_t seed(0);
            ::hash_combine(seed, p.first);
            ::hash_combine(seed, p.second);
            return seed;
        }
    };
}

enum Color {
    White = 0,
    Gray = 1,
    Black = 2
};

template <class T>
class GraphOnMap {
    std::vector<std::vector<T>> map;
    std::vector<std::vector<Color>> color;
    std::unordered_map<std::pair<T, T>, std::vector<std::pair<T, T>>> adjacency_list;
    std::vector<std::pair<T, T>> GetNborsMap(std::pair<T, T>, std::vector<std::pair<T, T>>&);
    std::vector<std::pair<T, T>> DfsForBuild(std::pair<T, T>);
    void DFSMap();
    void DfsForAnswer(std::pair<T, T>);
public:
    GraphOnMap(int&, int&);
    void BuildMap();
    T DFS();
};

template <class T>
GraphOnMap<T>::GraphOnMap(int& map_heigh, int& map_width) : 
    map(map_heigh + 2, std::vector<T>(map_width + 2, -1)),
    color(map_heigh + 1, std::vector<Color>(map_width + 1, White)),
    adjacency_list(1) {
}

template <class T>
T GraphOnMap<T>::DFS() {
    map[0][0] = 0;
    for (auto& v: adjacency_list) {
        color[v.first.first][v.first.second] = White;
    }
    for (auto& v: adjacency_list) {
        if (color[v.first.first][v.first.second] == White) {
            DfsForAnswer(v.first);
        }
    }
    return map[0][0];
}

template <class T>
void GraphOnMap<T>::DfsForAnswer(std::pair<T, T> v) {
    color[v.first][v.second] = Gray;
    bool flag = false;
    for (auto& u: adjacency_list[v]) {
        flag = true;
        if (color[u.first][u.second] == White) {
            DfsForAnswer(u);
        }
    }
    if (!flag) {
        map[0][0]++;
    }
    color[v.first][v.second] = Black;
}

template <class T>
void GraphOnMap<T>::DFSMap() {
    for (size_t v = 1; v < color.size(); ++v) {
        for (size_t u = 1; u < color[0].size(); ++u) {
            if (color[v][u] == White) {
                adjacency_list[{v, u}] = DfsForBuild({v, u});

            }
        }
    }
}

template <class T>
std::vector<std::pair<T, T>> GraphOnMap<T>::DfsForBuild(std::pair<T, T> v) {
    std::vector<std::pair<T, T>> nbors;
    color[v.first][v.second] = Gray;
    for (auto& u: GetNborsMap(v, nbors)) {
        if (color[u.first][u.second] == White) {
            for (auto &vert: DfsForBuild(u)) {
                nbors.push_back(vert);
            }
        }
    }
    color[v.first][v.second] = Black;
    return nbors;
}

template <class T>
void GraphOnMap<T>::BuildMap() {
    T map_cell;
    for (size_t i = 0; i < map.size(); ++i) {
        map[i][0] = 10001;
        map[i][map[0].size() - 1] = 10001;
    }
    for (size_t j = 0; j < map[0].size(); ++j) {
        map[0][j] = 10001;
        map[map.size() - 1][j] = 10001;
    }
    for (size_t i = 1; i < map.size() - 1; ++i) {
        for (size_t j = 1; j < map[0].size() - 1; ++j) {
            std::cin >> map_cell;
            map[i][j] = map_cell;
        }
    }
    DFSMap();
}

template <class T>
std::vector<std::pair<T, T>> GraphOnMap<T>::GetNborsMap(std::pair<T, T> v, std::vector<std::pair<T, T>>& nb) {
    std::vector<std::pair<T, T>> nbors;
    if (map[v.first][v.second] == map[v.first + 1][v.second]) {
        nbors.emplace_back(v.first + 1, v.second);
    } else if (map[v.first][v.second] > map[v.first + 1][v.second]) {
        nb.emplace_back(v.first + 1, v.second);
    }
    if (map[v.first][v.second] == map[v.first - 1][v.second]) {
        nbors.emplace_back(v.first - 1, v.second);
    } else if (map[v.first][v.second] > map[v.first - 1][v.second]) {
        nb.emplace_back(v.first - 1, v.second);
    }
    if (map[v.first][v.second] == map[v.first][v.second + 1]) {
        nbors.emplace_back(v.first, v.second + 1);
    } else if (map[v.first][v.second] > map[v.first][v.second + 1]) {
        nb.emplace_back(v.first, v.second + 1);
    }
    if (map[v.first][v.second] == map[v.first][v.second - 1]) {
        nbors.emplace_back(v.first, v.second - 1);
    } else if (map[v.first][v.second] > map[v.first][v.second - 1]) {
        nb.emplace_back(v.first, v.second - 1);
    }
    return nbors;
}

int main() {
    int map_heigh = 0;
    int map_width = 0;
    std::cin >> map_heigh >> map_width;
    GraphOnMap<int> GraphOnMap(map_heigh, map_width);
    GraphOnMap.BuildMap();
    std::cout << GraphOnMap.DFS() << "\n";
    return 0;
}