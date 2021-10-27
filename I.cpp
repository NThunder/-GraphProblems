#include <iostream>
#include <vector>
#include <utility>
#include <deque>

template <class T>
class Graph {
	std::vector<std::vector<std::pair<T, T>>> graph;
	std::vector<ssize_t> dist;
public:
	Graph(int&);
	void AppendEdge(std::pair<std::pair<int, int>, int>);
	void BFS(T);
	void PrintfDist(T);
};

template <class T>
Graph<T>::Graph(int& count_vertex) : 
	graph(count_vertex + 1, std::vector<std::pair<T, T>>()),
	dist(count_vertex + 1, -1) {
}

template <class T>
void Graph<T>::AppendEdge(std::pair<std::pair<int, int>, int> edge) {
	graph[edge.first.first].emplace_back(edge.first.second, edge.second);
}

template <class T>
void Graph<T>::BFS(T start_vertex) {
	std::deque<std::vector<T>> expectation(31);
	int counter = 0;
	expectation[0].push_back(start_vertex);
	counter++;
	dist[start_vertex] = 0;
	while (counter) {
		T vertex = 0;
		while (expectation[0].empty()) {
			expectation.pop_front();
			expectation.push_back(std::vector<T>());
		}
		vertex = expectation[0].back();
		expectation[0].pop_back();
		counter--;
		for (auto &u : graph[vertex]) {
			if (dist[u.first] == -1 || dist[u.first] > dist[vertex] + u.second) {
				dist[u.first] = dist[vertex] + u.second;
				expectation[u.second].push_back(u.first);
				counter++;
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