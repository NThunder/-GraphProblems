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
	std::deque<std::vector<T>> connect_comp;
	void DfsTopSort(T);
public:
	Graph(int&);
	void AppendEdge(std::pair<T, T>&);
	void TopSort();
	void ConnectComp();
};

template <class T>
Graph<T>::Graph(int& count_vertex) : 
	graph(count_vertex + 1, std::vector<T>()),
	color(count_vertex + 1, White) {
}

template <class T>
void Graph<T>::AppendEdge(std::pair<T, T>& edge) {
	graph[edge.first].push_back(edge.second);
	graph[edge.second].push_back(edge.first);
}

template <class T>
void Graph<T>::ConnectComp() {
	std::cout << connect_comp.size() << "\n";
	for (auto &u : connect_comp) {
		std::cout << u.size() << "\n";
		for (auto &v : u) {
			std::cout << v << " ";
		}
		std::cout << "\n";
	}
}

template <class T>
void Graph<T>::TopSort() {
	for (size_t v = 1; v < color.size(); ++v) {
		color[v] = White;
	}
	for (size_t v = 1; v < graph.size(); ++v) {
		if (color[v] == White) {
			connect_comp.push_front(std::vector<T>());
			DfsTopSort(v);
		}
	}
}

template <class T>
void Graph<T>::DfsTopSort(T v) {
	color[v] = Gray;
	for (auto& u: graph[v]) {
		if (color[u] == White) {
			DfsTopSort(u);
		}
	}
	color[v] = Black;
	connect_comp[0].push_back(v);
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
	graph.TopSort();
	graph.ConnectComp();
	return 0;
}