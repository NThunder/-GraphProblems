#include <iostream>
#include <vector>
#include <utility>

enum Color {
	White = 0,
	Gray = 1,
	Black = 2
};

template <class T>
class Graph {
	std::vector<std::vector<T>> graph;
	std::vector<Color> color;
	std::vector<T> cur_cycle;
	T cycle_start;
	bool DfsForCycle(T);
public:
	Graph(int&);
	void AppendEdge(std::pair<T, T>&);
	void PrintCycle();
	bool IsCycle();
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
bool Graph<T>::IsCycle() {
	for (size_t v = 1; v < color.size(); ++v) {
		color[v] = White;
	}
	for (size_t v = 1; v < graph.size(); ++v) {
		if (color[v] == White) {
			if (DfsForCycle(v)) {
				return true;
			}
		}
	}
	return false;
}

template <class T>
bool Graph<T>::DfsForCycle(T v) {
	color[v] = Gray;
	cur_cycle.push_back(v);
	for (auto& u: graph[v]) {
		bool ret = false;
		if (color[u] == White) {
			ret = DfsForCycle(u);
		} else if (color[u] == Gray) {
			cycle_start = u;
			return true;
		}
		if (ret) {
			return true;
		}
	}
	color[v] = Black;
	cur_cycle.pop_back();
	return false;
}

template <class T>
void Graph<T>::PrintCycle() {
	bool flag = false;
	for (auto& a : cur_cycle) {
		if (a == cycle_start) {
			flag = true;
		}
		if (flag) {
			std::cout << a << " ";
		}
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
	if (graph.IsCycle()) {
		std::cout << "YES\n";
		graph.PrintCycle();
	} else {
		std::cout << "NO\n";
	}
	
	return 0;
}