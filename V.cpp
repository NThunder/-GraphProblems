#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <unordered_set>

enum Color {
	White = 0,
	Gray = 1,
	Black = 2
};

template <class T>
class Graph {
	std::vector<std::vector<std::pair<T, T>>> graph;
	std::vector<std::unordered_multiset<T>> fake_graph;
	std::vector<Color> color;
	std::vector<size_t> time_in;
	std::vector<size_t> time_up;
	std::set<T> AP;
	size_t time;
	void DfsVisit(T, T);


public:
	Graph(int&);
	void AppendEdge(std::pair<std::pair<T, T>, T>&);
	void DfsBridge();
	void PrintBridge() const;
	bool Multiadge(const std::pair<T, T>&) const;
};

template <class T>
Graph<T>::Graph(int& count_vertex) : 
	graph(count_vertex + 1, std::vector<std::pair<T, T>>()),
	fake_graph(count_vertex + 1, std::unordered_multiset<T>()),
	color(count_vertex + 1, White),
	time_in(count_vertex + 1, -1),
	time_up(count_vertex + 1, -1) {
}

template <class T>
void Graph<T>::AppendEdge(std::pair<std::pair<T, T>, T>& edge) {
	graph[edge.first.first].emplace_back(edge.first.second, edge.second);
	fake_graph[edge.first.first].insert(edge.first.second);
	graph[edge.first.second].emplace_back(edge.first.first, edge.second);
	fake_graph[edge.first.second].insert(edge.first.first);
}

template <class T>
bool Graph<T>::Multiadge(const std::pair<T, T>& edge) const {
	return fake_graph[edge.first].count(edge.second) > 1 ||
		fake_graph[edge.second].count(edge.first) > 1;
}

template <class T>
void Graph<T>::DfsBridge() {
	for (size_t v = 1; v < color.size(); ++v) {
		color[v] = White;
	}
	AP.clear();
	time = 0;
	for (size_t v = 1; v < graph.size(); ++v) {
		if (color[v] == White) {
			DfsVisit(v, 0);
		}
	}
}

template <class T>
void Graph<T>::DfsVisit(T u, T parent) {
	time_in[u] = time_up[u] = ++time;
	color[u] = Gray;
	for (auto& v: graph[u]) {
		if (v.first == parent) {
			continue;
		}
		if (color[v.first] == Gray) {
			time_up[u] = std::min(time_up[u], time_in[v.first]);
		}
		if (color[v.first] == White) {
			DfsVisit(v.first, u);
			time_up[u] = std::min(time_up[u], time_up[v.first]);
			if (time_in[u] < time_up[v.first]  && !Multiadge({u, v.first})) {
				AP.insert(v.second);
			}
		}
	}
	color[u] = Black;
}

template <class T>
void Graph<T>::PrintBridge() const {
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
	std::pair<std::pair<int, int>, int> edge;
	for (int i = 1; i <= count_edge; ++i) {
		std::cin >> edge.first.first >> edge.first.second;
		edge.second = i;
		graph.AppendEdge(edge);
	}
	graph.DfsBridge();
	graph.PrintBridge();
	return 0;
}