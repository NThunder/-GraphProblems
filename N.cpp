#include <iostream>
#include <vector>
#include <utility>
#include <deque>

enum Color {
	White = 0,
	Gray = 1,
	Black = 2
};

template <class T>
class Graph {
	std::vector<std::vector<T>> graph;
	std::vector<Color> color;
	std::deque<T> sorted_graph;
	bool DfsTopSort(T);

public:
	Graph(int&);
	void AppendEdge(std::pair<T, T>&);
	bool TopSort();
	void PrintTopSort();
};

template <class T>
Graph<T>::Graph(int& count_vertex) : 
	graph(count_vertex + 1, std::vector<T>()),
	color(count_vertex + 1, White) {
}

template <class T>
void Graph<T>::AppendEdge(std::pair<T, T>& edge) {
	graph[edge.first].push_back(edge.second);
}

template <class T>
void Graph<T>::PrintTopSort() {
	for (auto& v: sorted_graph) {
		std::cout << v << " ";
	}
	std::cout << "\n";
}

template <class T>
bool Graph<T>::TopSort() {
	for (size_t v = 1; v < color.size(); ++v) {
		color[v] = White;
	}
	for (size_t v = 1; v < graph.size(); ++v) {
		if (color[v] == White) {
			if (DfsTopSort(v)) {
				return true;
			}
		}
	}
	return false;
}

template <class T>
bool Graph<T>::DfsTopSort(T v) {
	color[v] = Gray;
	for (auto& u: graph[v]) {
		bool ret = false;
		if (color[u] == White) {
			ret = DfsTopSort(u);
		} else if (color[u] == Gray) {
			return true;
		}
		if (ret) {
			return true;
		}
	}
	color[v] = Black;
	sorted_graph.push_front(v);
	return false;
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
	if (!graph.TopSort()) {
		graph.PrintTopSort();
	} else {
		std::cout << "-1\n";
	}
	
	return 0;
}