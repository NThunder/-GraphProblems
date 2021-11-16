#include <iostream>
#include <vector>
#include <utility>
#include <queue>

class Graph {
public:
    enum Color {
        White = 0,
        Gray = 1,
        Black = 2
    };
    typedef ssize_t Vertex;
    const Vertex unat_vert = -1;
    const ssize_t unat_dist = -1;
    virtual void AppendEdge(Vertex, Vertex) = 0;
    virtual std::vector<Vertex> GetNeighbors(Vertex) const = 0;
    size_t GetCountOfVertex() const {
        return count_of_vertex;
    }
    std::vector<Vertex> parent;
    std::vector<Color> color;
    std::vector<ssize_t> dist;
    std::vector<Vertex> ShortestPath(Vertex, Vertex);
    bool IsBipartite();
protected:
    bool IsDirected = false;
    size_t count_of_vertex = 0;
    void BFS(Vertex);
    bool DfsForBipart(Vertex, std::vector<Graph::Color>&);
};

class AdjList : public Graph {
    std::vector<std::vector<Vertex>> adjacency_list;
    std::vector<Vertex> GetNeighbors(Vertex v) const override {
        return adjacency_list[v];
    }

public:
    AdjList(const size_t&);
    void AppendEdge(Vertex, Vertex) override;
};

class AdjMatrix : public Graph {
    std::vector<std::vector<bool>> adjacency_matrix;
    std::vector<Vertex> GetNeighbors(Vertex) const override;

public:
    AdjMatrix(const size_t&);
    void AppendEdge(Vertex, Vertex) override;

};

AdjList::AdjList(const size_t& count_vertex) {
    count_of_vertex = count_vertex;
    adjacency_list.resize(count_vertex + 1, std::vector<Vertex>());
    parent.resize(count_vertex + 1, unat_vert);
    dist.resize(count_vertex + 1, unat_dist);
    color.resize(count_vertex + 1, White);
}

void AdjList::AppendEdge(Vertex first, Vertex second) {
    adjacency_list[first].push_back(second);
    if (!IsDirected) {
        adjacency_list[second].push_back(first);
    }
}

std::vector<Graph::Vertex> AdjMatrix::GetNeighbors(Vertex v) const {
    std::vector<Vertex> nbors;
    for (size_t i = 1; i <= GetCountOfVertex(); ++i) {
        if (adjacency_matrix[v][i]) {
            nbors.push_back(i);
        }
    }
    return nbors;
}

AdjMatrix::AdjMatrix(const size_t& count_vertex) {
    count_of_vertex = count_vertex;
    adjacency_matrix.resize(count_vertex + 1, std::vector<bool>(count_vertex + 1, false));
    parent.resize(count_vertex + 1, unat_vert);
    dist.resize(count_vertex + 1, unat_dist);
    color.resize(count_vertex + 1, White);
}

void AdjMatrix::AppendEdge(Vertex first, Vertex second) {
    adjacency_matrix[first][second] = true;
    if (!IsDirected) {
        adjacency_matrix[second][first] = true;
    }
}

void Graph::BFS(Vertex start_vertex) {
    for (size_t i = 0; i < dist.size(); ++i) {
        dist[i] = unat_dist;
        parent[i] = unat_vert;
    }
    std::queue<Vertex> expectation;
    expectation.push(start_vertex);
    parent[0] = start_vertex;
    dist[start_vertex] = 0;
    parent[start_vertex] = start_vertex;
    Vertex vertex = 0;
    while (!expectation.empty()) {
        vertex = expectation.front();
        expectation.pop();
        for (auto &u : GetNeighbors(vertex)) {
            if (dist[u] == unat_dist) {
                dist[u] = dist[vertex] + 1;
                parent[u] = vertex;
                expectation.push(u);
            }
        }
    }
}

std::vector<Graph::Vertex> Graph::ShortestPath(Vertex start_vertex, Vertex finish_vertex) {
    BFS(start_vertex);
    std::vector<Vertex> shortest_path;
    std::vector<Vertex> ans;
    if (dist[finish_vertex] != unat_dist) {
        Vertex par = parent[finish_vertex];
        while (par != parent[0]) {
            ans.push_back(par);
            par = parent[par];
        }
        shortest_path.push_back(parent[0]);
        for (int i = ans.size() - 1; i >= 0; --i) {
            shortest_path.push_back(ans[i]);
        }
        if (parent[0] != finish_vertex) {
            shortest_path.push_back(finish_vertex);
        }
    }
    return shortest_path;
}

bool Graph::IsBipartite() {
    std::vector<Graph::Color> mark(color.size(), Black);
    for (size_t v = 1; v < color.size(); ++v) {
        color[v] = White;
    }
    for (size_t v = 1; v <= GetCountOfVertex(); ++v) {
        if (color[v] == White) {
            mark[v] = White;
            if (!DfsForBipart(v, mark)) {
                return false;
            }
        }
    }
    return true;
}

bool Graph::DfsForBipart(Vertex v, std::vector<Graph::Color>& mark) {
    color[v] = Gray;
    for (auto& u: GetNeighbors(v)) {
        if (mark[u] == Black) {
            mark[u] = static_cast<Graph::Color>(mark[v] ^ Gray);
        } else if (mark[u] == mark[v]) {
            return false;
        }
        bool ret = true;
        if (color[u] == White) {
            ret = DfsForBipart(u, mark);
        }
        if (!ret) {
            return false;
        }
    }
    color[v] = Black;
    return true;
}

class GraphOnDigits : public Graph {

public:
    GraphOnDigits(const size_t&);
    std::vector<Vertex> GetNeighbors(Vertex) const override;
    void AppendEdge(Vertex, Vertex) override {
    }
    static const ssize_t smallest_possible = 1110;
    static const ssize_t biggest_possible = 9999;
    ssize_t ExtractFirstDigit(ssize_t digit) const {
        return digit % 10;
    }
    ssize_t ExtractFourthDigit(ssize_t digit) const {
        return digit / 1000;
    }
};

GraphOnDigits::GraphOnDigits(const size_t& count_vertex) {
    count_of_vertex = (count_vertex + 1);
    parent.resize(count_of_vertex, unat_vert);
    dist.resize(count_of_vertex, unat_dist);
}


std::vector<Graph::Vertex> GraphOnDigits::GetNeighbors(Graph::Vertex vert) const {
    std::vector<Vertex> nbors;
    if (ExtractFourthDigit(vert + smallest_possible) != 9) {
        nbors.push_back((vert + smallest_possible) + 1000 - smallest_possible);
    }
    if (ExtractFirstDigit(vert + smallest_possible) != 1) {
        nbors.push_back((vert + smallest_possible) - 1 - smallest_possible);
    }
    nbors.push_back(((vert + smallest_possible) % 1000) * 10 + ExtractFourthDigit(vert + smallest_possible) - smallest_possible);
    nbors.push_back(ExtractFirstDigit(vert + smallest_possible) * 1000 + ((vert + smallest_possible) / 10) - smallest_possible);
    return nbors;
}

int main() {
    int f_d = 0;
    int s_d = 0;
    std::cin >> f_d >> s_d;

    GraphOnDigits graph(GraphOnDigits::biggest_possible - GraphOnDigits::smallest_possible);
    auto shortest_path = graph.ShortestPath(f_d - GraphOnDigits::smallest_possible, s_d - GraphOnDigits::smallest_possible);
    if (!shortest_path.size()) {
        std::cout << -1;
    } else {
        std::cout << shortest_path.size() << "\n";
    }
    for (auto &vert : shortest_path) {
        std::cout << vert + GraphOnDigits::smallest_possible << "\n";
    }
    return 0;
}