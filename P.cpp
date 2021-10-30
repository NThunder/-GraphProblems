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
	std::vector<std::vector<T>> reverse_graph;
	std::vector<Color> color;
	std::deque<T> sorted_graph;
	std::vector<T> comp;
	void DfsTopSort(T);
	void ReverseDfsTopSort(T);
	T count_comp;

public:
	Graph(int&);
	void AppendEdge(std::pair<T, T>&);
	void TopSort();
	void ReverseTopSort();
	void PrintAnswer();
};

template <class T>
Graph<T>::Graph(int& count_vertex) : 
	graph(count_vertex + 1, std::vector<T>()),
	reverse_graph(count_vertex + 1, std::vector<T>()),
	color(count_vertex + 1, White),
	comp(count_vertex + 1, -1) {
}

template <class T>
void Graph<T>::AppendEdge(std::pair<T, T>& edge) {
	graph[edge.first].push_back(edge.second);
	reverse_graph[edge.second].push_back(edge.first);
}

template <class T>
void Graph<T>::PrintAnswer() {
	std::cout << count_comp << "\n";
	for (size_t i = 1; i < comp.size(); ++i) {
		std::cout << comp[i] << " ";
	}
	std::cout << "\n";
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

template <class T>
void Graph<T>::ReverseTopSort() {
	count_comp = 0;
	for (size_t v = 1; v < color.size(); ++v) {
		color[v] = White;
	}
	for (auto &v : sorted_graph) {
		if (color[v] == White) {
			count_comp++;
			ReverseDfsTopSort(v);
		}
	}

}

template <class T>
void Graph<T>::ReverseDfsTopSort(T v) {
	color[v] = Gray;
	for (auto& u: reverse_graph[v]) {
		if (color[u] == White) {
			ReverseDfsTopSort(u);
		}
	}
	color[v] = Black;
	comp[v] = count_comp;
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
	graph.ReverseTopSort();
	graph.PrintAnswer();
	return 0;
}