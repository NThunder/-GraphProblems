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

struct Point {
    ssize_t x = 0;
    ssize_t y = 0;
    Point() = default;
    Point(ssize_t f, ssize_t s) : x(f), y(s) {}
    Point operator+(const Point& point) const {
        Point ans = *this;
        ans.x += point.x;
        ans.y += point.y;
        return ans;
    }
};


class GraphOnTable : public Graph {

public:
    GraphOnTable(const size_t&);
    std::vector<Vertex> GetNeighbors(Vertex) const override;
    void AppendEdge(Vertex, Vertex) override {
    }
    std::vector<Point> ShortPath(Point from, Point to) {
        std::vector<Point> ans;
        for(auto &vert : ShortestPath(FromPointToVert(from), FromPointToVert(to))) {
            ans.push_back(FromVertToPoint(vert));
        }
        return ans;
    }
    Vertex FromPointToVert(Point p) const {
        return p.y * grid_size + p.x;
    }
    Point FromVertToPoint(Vertex v) const {
        return {v % grid_size,
                v / grid_size};
    }
    ssize_t grid_size;
};

GraphOnTable::GraphOnTable(const size_t& count_vertex) {
    grid_size = count_vertex + 1;
    count_of_vertex = (count_vertex + 1) * (count_vertex + 1);
    parent.resize(count_of_vertex, unat_vert);
    dist.resize(count_of_vertex, unat_dist);
    color.resize(count_of_vertex, White);
}

std::vector<Graph::Vertex> GraphOnTable::GetNeighbors(Vertex vert) const {
    std::vector<Vertex> nbors;
    Point point = FromVertToPoint(vert);
    int field_size = grid_size;
    std::vector<Point> moves = {{-2, -1}, {-1, -2}, {-1, 2}, {-2, 1},
                                {1, -2}, {2, -1}, {1, 2}, {2, 1}};
    for (auto& move: moves) {
        if ((point + move).x >= 1 && (point + move).y >= 1 && (point + move).x < field_size && (point + move).y < field_size) {
            nbors.push_back(FromPointToVert(point + move));
        }
    }
    return nbors;
}

int main() {
    int count_vertex = 0;
    std::cin >> count_vertex;
    Point st_p, fin_p;
    std::cin >> st_p.x >> st_p.y;
    std::cin >> fin_p.x >> fin_p.y;
    GraphOnTable graph(count_vertex);
    auto shortest_path = graph.ShortPath(st_p, fin_p);
    if (!shortest_path.size()) {
        std::cout << -1;
    } else {
        std::cout << shortest_path.size() - 1 << "\n";
    }
    for (auto &point : shortest_path) {
        std::cout << point.x << " " << point.y << "\n";
    }
    return 0;
}