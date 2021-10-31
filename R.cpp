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
	Graph(int&);
	void AppendEdge(std::pair<T, T>&);
	void DfsAP();
	void PrintAP();
};

template <class T>
Graph<T>::Graph(int& count_vertex) : 
	graph(count_vertex + 1, std::vector<T>()),
	color(count_vertex + 1, White),
	time_in(count_vertex + 1, -1),
	time_up(count_vertex + 1, -1) {
}

template <class T>
void Graph<T>::AppendEdge(std::pair<T, T>& edge) {
	graph[edge.first].push_back(edge.second);
	graph[edge.second].push_back(edge.first);
}

template <class T>
void Graph<T>::DfsAP() {
	for (size_t v = 1; v < color.size(); ++v) {
		color[v] = White;
	}
	AP.clear();
	time = 0;
	for (size_t v = 1; v < graph.size(); ++v) {
		if (color[v] == White) {
			DfsVisit(0, v);
		}
	}
}

template <class T>
void Graph<T>::DfsVisit(T parent, T u) {
	time_in[u] = time_up[u] = ++time;
	bool is_root = (parent == 0);
	size_t n_children = 0;
	color[u] = Gray;
	for (auto& v: graph[u]) {
		if (color[v] == Gray) {
			time_up[u] = std::min(time_up[u], time_in[v]);
		}
		if (color[v] == White) {
			++n_children;
			DfsVisit(u, v);
			time_up[u] = std::min(time_up[u], time_up[v]);
			if (!is_root && time_in[u] <= time_up[v]) {
				AP.insert(u);
			}
		}
	}
	if (is_root && n_children > 1) {
		AP.insert(u);
	}
	color[u] = Black;
}

template <class T>
void Graph<T>::PrintAP() {
	std::cout << AP.size() << "\n";
	for (auto &vert: AP) {
		std::cout << vert << "\n";
	}
}

int main() {
	int count_vertex = 0;
	int count_edge = 0;
	std::cin >> count_vertex >> count_edge;
	Graph<int> graph(count_vertex);
	std::pair<int, int> edge;
	for (int i = 0; i < count_edge; ++i) {
		std::cin >> edge.first >> edge.second;
		graph.AppendEdge(edge);
	}
	graph.DfsAP();
	graph.PrintAP();
	return 0;
}