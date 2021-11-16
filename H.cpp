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
    virtual void AppendWeightedEdge(Vertex, Vertex, ssize_t) = 0;
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
    AdjList(const size_t&, bool);
    void AppendEdge(Vertex, Vertex) override;
    void AppendWeightedEdge(Vertex, Vertex, ssize_t) override;
};

class AdjMatrix : public Graph {
    std::vector<std::vector<bool>> adjacency_matrix;
    std::vector<Vertex> GetNeighbors(Vertex) const override;

public:
    AdjMatrix(const size_t&, bool);
    void AppendEdge(Vertex, Vertex) override;
    void AppendWeightedEdge(Vertex, Vertex, ssize_t) override;
};

AdjList::AdjList(const size_t& count_vertex, bool directed = false) {
    IsDirected = directed;
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

AdjMatrix::AdjMatrix(const size_t& count_vertex, bool directed = false) {
    IsDirected = directed;
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

void AdjList::AppendWeightedEdge(Vertex from, Vertex to, ssize_t weight) {
    Vertex nbor = to;
    while (weight > 1) {
        weight--;
        adjacency_list.push_back(std::vector<Vertex>());
        dist.push_back(unat_dist);
        parent.push_back(unat_vert);
        AppendEdge(adjacency_list.size() - 1, nbor);
        nbor = adjacency_list.size() - 1;
    }
    AppendEdge(from, nbor);
}

void AdjMatrix::AppendWeightedEdge(Vertex from, Vertex to, ssize_t weight) {
    Vertex nbor = to;
    while (weight > 1) {
        weight--;
        adjacency_matrix.push_back(std::vector<bool>(dist.size() + 1));
        dist.push_back(unat_dist);
        parent.push_back(unat_vert);
        AppendEdge(adjacency_matrix.size() - 1, nbor);
        nbor = adjacency_matrix.size() - 1;
    }
    AppendEdge(from, nbor);
}

int main() {
    int count_vertex = 0;
    int count_edge = 0;
    std::cin >> count_vertex >> count_edge;
    int start_vertex = 0;
    int finish_vertex = 0;
    std::cin >> start_vertex >> finish_vertex;
    AdjList graph(count_vertex, true);
    Graph::Vertex from, to;
    ssize_t weight;
    for (int i = 0; i < count_edge; ++i) {
        std::cin >> from >> to >> weight;
        graph.AppendWeightedEdge(from, to, weight);
    }
    auto shortest_path = graph.ShortestPath(start_vertex, finish_vertex);
    if (!shortest_path.size()) {
        std::cout << -1;
    } else {
        std::cout << shortest_path.size() - 1 << "\n";
    }
    return 0;
}