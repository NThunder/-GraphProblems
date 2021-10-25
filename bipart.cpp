#include <iostream>
#include <vector>
#include <utility>
#include <queue>

enum Color {
	White = 0,
	Gray = 1,
	Black = 2
};

template <class T>
class Graph {
	std::vector<std::vector<T>> graph;
	std::vector<T> parent;
	std::vector<Color> color;
	std::vector<ssize_t> dist;
	bool DfsForBipart(T, std::vector<Color>&);
public:
	Graph(int&);
	void AppendEdge(std::pair<T, T>&);
	void BFS(T);
	void PrintfDistAndPath(T);
	bool IsBipartite();
};

template <class T>
Graph<T>::Graph(int& count_vertex) : 
	graph(count_vertex + 1, std::vector<T>()),
	parent(count_vertex + 1, -1),
	color(count_vertex + 1, White),
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
bool Graph<T>::IsBipartite() {
	std::vector<Color> mark(color.size(), Black);
	for (size_t v = 1; v < color.size(); ++v) {
		color[v] = White;
	}
	for (size_t v = 1; v < graph.size(); ++v) {
		if (color[v] == White) {
			mark[v] = White;
			if (!DfsForBipart(v, mark)) {
				return false;
			}
		}
	}
	return true;
}

template <class T>
bool Graph<T>::DfsForBipart(T v, std::vector<Color>& mark) {
	color[v] = Gray;
	for (auto& u: graph[v]) {
		if (mark[u] == Black) {
			mark[u] = static_cast<Color>(mark[v] ^ Gray);
		} else if (mark[u] == mark[v]) {
			return false;
		}
		bool ret = true;
		if (color[u] == White) {
			ret = DfsForBipart(u, mark);
		}
		if (!ret) {
			return false;
		}
	}
	color[v] = Black;
	return true;
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
	Graph<int> graph(count_vertex);
	std::pair<int, int> edge;
	for (int i = 0; i < count_edge; ++i) {
		std::cin >> edge.first >> edge.second;
		graph.AppendEdge(edge);
	}
	if (graph.IsBipartite()) {
		std::cout << "YES\n";
	} else {
		std::cout << "NO\n";
	}
	
	return 0;
}