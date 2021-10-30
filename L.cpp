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
	void DfsTopSort(T);
	void DfsBanksNumber(T);
public:
	Graph(int&);
	void AppendEdge(std::pair<T, T>&);
	void TopSort();
	int BanksNumber();
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
int Graph<T>::BanksNumber() {
	for (size_t v = 1; v < color.size(); ++v) {
		color[v] = White;
	}
	int banks_number = 0;
	for (auto v : sorted_graph) {
		if (color[v] == White) {
			DfsBanksNumber(v);
			banks_number++;
		}
	}
	return banks_number;
}

template <class T>
void Graph<T>::DfsBanksNumber(T v) {
	color[v] = Gray;
	for (auto& u: graph[v]) {
		if (color[u] == White) {
			DfsTopSort(u);
		}
	}
	color[v] = Black;
}



template <class T>
void Graph<T>::TopSort() {
	for (size_t v = 1; v < color.size(); ++v) {
		color[v] = White;
	}
	for (size_t v = 1; v < graph.size(); ++v) {
		if (color[v] == White) {
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
	sorted_graph.push_front(v);
}

int main() {
	int count_vertex = 0;
	std::cin >> count_vertex;
	Graph<int> graph(count_vertex);
	std::pair<int, int> edge;
	for (int i = 1; i <= count_vertex; ++i) {
		std::cin >> edge.first;
		edge.second = i;
		graph.AppendEdge(edge);
	}
	graph.TopSort();
	std::cout << graph.BanksNumber();
	return 0;
}