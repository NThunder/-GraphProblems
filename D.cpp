#include <iostream>
#include <vector>
#include <utility>
#include <queue>

template <class T>
class GraphOnDigits {
    std::vector<T> parent;
    std::vector<T> dist;
    std::vector<T> GetNborsDigit(T);
public:
    GraphOnDigits(const int&);
    void DigitBFS(T);
    void PrintfDistAndPathDigit(T);
};

template <class T>
GraphOnDigits<T>::GraphOnDigits(const int& count_vertex) : 
    parent(count_vertex + 1, -1),
    dist(count_vertex + 1, -1) {
}

template <class T>
std::vector<T> GraphOnDigits<T>::GetNborsDigit(T vert) {
    std::vector<T> nbors;
    if ((vert / 1000) != 9) {
        nbors.push_back(vert + 1000);
    }
    if ((vert % 10) != 1) {
        nbors.push_back(vert - 1);
    }
    nbors.push_back((vert % 1000) * 10 + (vert / 1000));
    nbors.push_back((vert % 10) * 1000 + (vert / 10));
    return nbors;
}

template <class T>
void GraphOnDigits<T>::DigitBFS(T start_vertex) {
    for (size_t i = 0; i < dist.size(); ++i) {
            dist[i] = parent[i] = -1;
    }
    std::queue<T> expectation;
    expectation.push(start_vertex);
    parent[0] = start_vertex;
    dist[start_vertex - 1110] = 0;
    parent[start_vertex - 1110] = start_vertex;
    T vertex;
    while (!expectation.empty()) {
        vertex = expectation.front();
        expectation.pop();
        auto nbors = GetNborsDigit(vertex);
        for (auto &u : nbors) {
            if (dist[u - 1110] == -1) {
                dist[u - 1110] = dist[vertex - 1110] + 1;
                parent[u - 1110] = vertex;
                expectation.push(u);
            }
        }
    }
}

template <class T>
void GraphOnDigits<T>::PrintfDistAndPathDigit(T fin_v) {
    std::cout << dist[fin_v - 1110] << "\n";
    std::vector<T> ans;
    if (dist[fin_v - 1110] != -1) {
        T par = parent[fin_v - 1110];
        while (par != parent[0]) {
            ans.push_back(par);
            par = parent[par - 1110];
        }
        std::cout << parent[0] << "\n";
        for (int i = ans.size() - 1; i >= 0; --i) {
            std::cout << ans[i] << "\n";
        }
        if (parent[0] != fin_v) {
            std::cout << fin_v << "\n";
        }
    }
}

int main() {
    int f_d = 0;
    int s_d = 0;
    std::cin >> f_d >> s_d;
    GraphOnDigits<int> GraphOnDigits(9999 - 1110);
    GraphOnDigits.DigitBFS(f_d);
    GraphOnDigits.PrintfDistAndPathDigit(s_d);
    return 0;
}