#include <iostream>
#include <vector>
#include <utility>
#include <queue>

template <class T>
class Graph {
	std::vector<std::vector<T>> graph;
	std::vector<ssize_t> dist;
public:
	Graph(int&);
	void AppendEdge(std::pair<std::pair<int, int>, int>);
	void BFS(T);
	void PrintfDist(T);
};

template <class T>
Graph<T>::Graph(int& count_vertex) : 
	graph(count_vertex + 1, std::vector<T>()),
	dist(count_vertex + 1, -1) {
}

template <class T>
void Graph<T>::AppendEdge(std::pair<std::pair<int, int>, int> edge) {
	T nbor = edge.first.second;
	while (edge.second > 1) {
		edge.second--;
		graph.push_back(std::vector<T>());
		dist.push_back(-1);
		graph[graph.size() - 1].push_back(nbor);
		nbor = graph.size() - 1;
	}
	graph[edge.first.first].push_back(nbor);
}

template <class T>
void Graph<T>::BFS(T start_vertex) {
	std::queue<T> expectation;
	expectation.push(start_vertex);
	dist[start_vertex] = 0;
	T vertex = 0;
	while (!expectation.empty()) {
		vertex = expectation.front();
		expectation.pop();
		for (auto &u : graph[vertex]) {
			if (dist[u] == -1) {
				dist[u] = dist[vertex] + 1;
				expectation.push(u);
			}
		}
	}
}

template <class T>
void Graph<T>::PrintfDist(T finish_vertex) {
	std::cout << dist[finish_vertex] << "\n";
}

int main() {
	int count_vertex = 0;
	int count_edge = 0;
	std::cin >> count_vertex >> count_edge;
	int start_vertex = 0;
	int finish_vertex = 0;
	std::cin >> start_vertex >> finish_vertex;
	Graph<int> graph(count_vertex);
	std::pair<std::pair<int, int>, int> edge;
	for (int i = 0; i < count_edge; ++i) {
		std::cin >> edge.first.first >> edge.first.second >> edge.second;
		graph.AppendEdge(edge);
	}
	graph.BFS(start_vertex);
	graph.PrintfDist(finish_vertex);
	return 0;
}