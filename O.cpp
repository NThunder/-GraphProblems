#include <iostream>
#include <vector>
#include <utility>
#include <string>

enum Color {
	White = 0,
	Gray = 1,
	Black = 2
};

template <class T>
class Graph {
	std::vector<std::vector<T>> graph;
	std::vector<Color> color;
	bool DfsTopSort(T);

public:
	Graph(int&);
	void AppendEdges(std::pair<int, std::string>);
	bool TopSort();
};

template <class T>
Graph<T>::Graph(int& count_vertex) : 
	graph(count_vertex + 1, std::vector<T>()),
	color(count_vertex + 1, White) {
}

template <class T>
void Graph<T>::AppendEdges(std::pair<int, std::string> edges) {
	for (size_t i = 0; i < edges.second.size(); ++i) {
		if (edges.second[i] == 'R') {
			graph[edges.first].push_back(edges.first + i + 1);
		} else {
			graph[edges.first + i + 1].push_back(edges.first);
		}
	}
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
	return false;
}

int main() {
	std::ios::sync_with_stdio(false); 
	std::cin.tie(nullptr);
	int count_vertex = 0;
	std::cin >> count_vertex;
	Graph<int> graph(count_vertex);
	std::pair<int, std::string> edges;
	for (int i = 1; i < count_vertex; ++i) {
		std::cin >> edges.second;
		edges.first = i;
		graph.AppendEdges(edges);
	}
	if (!graph.TopSort()) {
		std::cout << "YES\n";		
	} else {
		std::cout << "NO\n";
	}
	
	return 0;
}