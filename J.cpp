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
	void AppendEdge(std::pair<T, T>&);
	void BFS(T);
	void PrintfDist(T);
};

template <class T>
Graph<T>::Graph(int& count_vertex) : 
	graph(count_vertex + 1, std::vector<std::pair<T, T>>()),
	dist(count_vertex + 1, -1) {
}

template <class T>
void Graph<T>::AppendEdge(std::pair<T, T>& edge) {
	graph[edge.first].emplace_back(edge.second, 0);

	graph[edge.second].emplace_back(edge.first, 1);
}

template <class T>
void Graph<T>::BFS(T start_vertex) {
	for (size_t i = 0; i < dist.size(); ++i) {
		dist[i] = -1;
	}
	std::deque<T> expectation;
	expectation.push_back(start_vertex);
	dist[start_vertex] = 0;
	T vertex = 0;
	while (!expectation.empty()) {
		vertex = expectation.front();
		expectation.pop_front();
		for (auto &u : graph[vertex]) {
			if (dist[u.first] == -1 || dist[u.first] > dist[vertex] + u.second) {
				dist[u.first] = dist[vertex] + u.second;
				if (u.second == 0) {
					expectation.push_front(u.first);					
				} else {
					expectation.push_back(u.first);
				}
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
	Graph<int> graph(count_vertex);
	std::pair<int, int> edge;
	for (int i = 0; i < count_edge; ++i) {
		std::cin >> edge.first >> edge.second;
		graph.AppendEdge(edge);
	}
	int request_count = 0;
	std::cin >> request_count;
	int start_vertex = 0;
	int finish_vertex = 0;
	for (int i = 0; i < request_count; ++i) {
		std::cin >> start_vertex >> finish_vertex;
		graph.BFS(start_vertex);
		graph.PrintfDist(finish_vertex);
	}
	return 0;
}