#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

enum Color {
	White = 0,
	Gray = 1,
	Black = 2
};

template <class T>
class Graph {
	std::vector<std::vector<T>> graph;
	std::vector<Color> color;
	std::vector<size_t> time_in;
	std::vector<size_t> time_up;
	std::set<T> AP;
	size_t time;
	void DfsVisit(T, T);


public:
	Graph(const int&);
	void AppendEdge(T, T);
	void DfsAP();
	void PrintAP(int);
};

template <class T>
Graph<T>::Graph(const int& count_vertex) : 
	graph(count_vertex + 1, std::vector<T>()),
	color(count_vertex + 1, White),
	time_in(count_vertex + 1, -1),
	time_up(count_vertex + 1, -1) {
}

template <class T>
void Graph<T>::AppendEdge(T from, T to) {
	graph[from].push_back(to);
	graph[to].push_back(from);
}

template <class T>
void Graph<T>::DfsAP() {
	time = 1;
	for (size_t v = 1; v < graph.size(); ++v) {
		if (color[v] == White) {
			DfsVisit(-1, v);
		}
	}
}

template <class T>
void Graph<T>::DfsVisit(T parent, T u) {
	time_in[u] = time_up[u] = ++time;
	size_t n_children = 0;
	color[u] = Black;
	for (auto& v: graph[u]) {
		if (v == parent) {
			continue;
		}
		if (color[v] == Black) {
			time_up[u] = std::min(time_up[u], time_in[v]);
		} else {
			DfsVisit(u, v);
			time_up[u] = std::min(time_up[u], time_up[v]);
			if (parent != -1 && time_in[u] <= time_up[v]) {
				AP.insert(u);
			}
			++n_children;
		}
	}
	if (parent == -1  && n_children > 1) {
		AP.insert(u);
	}
}

template <class T>
void Graph<T>::PrintAP(int count_vertex) {
    for (auto it : AP) {
        if (it <= count_vertex) {
            AP.erase(it);
        }
    }
    std::cout << AP.size() << '\n';
    for (auto it : AP) {
        std::cout << it - count_vertex << '\n';
    }
}

int main() {
	int count_vertex = 0;
	int count_edge = 0;
	std::cin >> count_vertex >> count_edge;
	Graph<int> graph(count_vertex + count_edge);
    size_t p = count_vertex + 1;
	int a, b, c;
	for (int i = 0; i < count_edge; ++i) {
		std::cin >> a >> b >> c;
		graph.AppendEdge(p, a);
		graph.AppendEdge(p, b);
		graph.AppendEdge(p, c);
		p++;
	}
	graph.DfsAP();
	graph.PrintAP(count_vertex);
	return 0;
}