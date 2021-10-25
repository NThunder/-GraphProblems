#include <iostream>
#include <vector>
#include <utility>
#include <queue>

template <class T>
class Graph {
	std::vector<std::vector<T>> graph;
	std::vector<T> parent;
	std::vector<ssize_t> dist;
public:
	Graph(int&);
	void AppendEdge(std::pair<T, T>&);
	void BFS(T);
	void PrintfDistAndPath(T);
};

template <class T>
Graph<T>::Graph(int& count_vertex) : 
	graph(count_vertex + 1, std::vector<T>()),
	parent(count_vertex + 1, -1),
	dist(count_vertex + 1, -1) {
}

template <class T>
void Graph<T>::AppendEdge(std::pair<T, T>& edge) {
	graph[edge.first].push_back(edge.second);
	graph[edge.second].push_back(edge.first);
}

template <class T>
void Graph<T>::BFS(T start_vertex) {
	for (size_t i = 0; i < dist.size(); ++i) {
		dist[i] = parent[i] = -1;
	}
	std::queue<T> expectation;
	expectation.push(start_vertex);
	parent[0] = start_vertex;
	dist[start_vertex] = 0;
	parent[start_vertex] = start_vertex;
	T vertex = 0;
	while (!expectation.empty()) {
		vertex = expectation.front();
		expectation.pop();
		for (auto &u : graph[vertex]) {
			if (dist[u] == -1) {
				dist[u] = dist[vertex] + 1;
				parent[u] = vertex;
				expectation.push(u);
			}
		}
	}
}

template <class T>
void Graph<T>::PrintfDistAndPath(T finish_vertex) {
	std::cout << dist[finish_vertex] << "\n";
	std::vector<T> ans;
	if (dist[finish_vertex] != -1) {
		T par = parent[finish_vertex];
		while (par != parent[0]) {
			ans.push_back(par);
			par = parent[par];
		}
		std::cout << parent[0] << " ";
		for (int i = ans.size() - 1; i >= 0; --i) {
			std::cout << ans[i] << " ";
		}
		if (parent[0] != finish_vertex) {
			std::cout << finish_vertex << "\n";
		}
	}
}

int main() {
	int count_vertex = 0;
	int count_edge = 0;
	std::cin >> count_vertex >> count_edge;
	int start_vertex = 0;
	int finish_vertex = 0;
	std::cin >> start_vertex >> finish_vertex;
	Graph<int> graph(count_vertex);
	std::pair<int, int> edge;
	for (int i = 0; i < count_edge; ++i) {
		std::cin >> edge.first >> edge.second;
		graph.AppendEdge(edge);
	}
	graph.BFS(start_vertex);
	graph.PrintfDistAndPath(finish_vertex);
	return 0;
}