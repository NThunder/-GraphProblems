#include <iostream>
#include <vector>
#include <utility>
#include <deque>

template <class T>
class Graph {
	std::vector<std::vector<T>> graph;
	std::vector<T> deg_in;
	std::vector<T> deg_out;
	std::deque<T> euler_path;
	void DfsEuler(T, T);
	size_t count_edges;

public:
	Graph(int&);
	void AppendEdge(T, T);
	void EulerBuild();
	void PrintEuler() const;
	bool IsEuler();
	std::vector<bool> isolated;
	void dFSVisit(const size_t& vertex, std::vector<bool>& colors);
};

template <class T>
Graph<T>::Graph(int& count_vertex) : 
	graph(count_vertex + 1, std::vector<T>()),
	deg_in(count_vertex + 1, 0),
	deg_out(count_vertex + 1, 0),
	isolated(count_vertex + 1, true)  {
		count_edges = 0;
}

template <class T>
void Graph<T>::AppendEdge(T from, T to) {
	graph[from].push_back(to);
	count_edges++;
	deg_out[from]++;
	deg_in[to]++;
}

template <class T>
void Graph<T>::EulerBuild() {
	euler_path.clear();
	for (size_t v = 1; v < graph.size(); ++v) {
		if (!graph[v].empty()) {
			T u = graph[v].back();
			graph[v].pop_back();
			DfsEuler(v, u);
			euler_path.push_back(v);
			break;
		}
	}
}

template <class T>
void Graph<T>::DfsEuler(T parent, T v) {
	while (!graph[v].empty()) {
		T u = graph[v].back();
		graph[v].pop_back();
		DfsEuler(v , u);
	}
	euler_path.push_front(parent);
}

template <class T>
void Graph<T>::PrintEuler() const {
	std::cout << euler_path.size() << " ";
	for (auto &vert : euler_path) {
		std::cout << vert << " ";
	}
	std::cout << "\n";

}

template <class T>
void Graph<T>::dFSVisit(const size_t& vertex, std::vector<bool>& colors) {
    colors[vertex] = true;
    for (auto& neighbor : graph[vertex]) {
        if (colors[neighbor] == false) {
            dFSVisit(neighbor, colors);
        }
    }
}

template <class T>
bool Graph<T>::IsEuler() {
	if (graph.size() == 1 || count_edges == 0) {
		return false;
	}
	for (size_t i = 1; i < deg_in.size(); ++i) {
		if (deg_in[i] != deg_out[i]) {
			return false;
		}

	}
    std::vector<T> initNumberOfEdges(graph.size());

    std::vector<bool> colors(graph.size(), false);

    for (size_t now_v = 1; now_v < graph.size(); now_v++) {
        if (!graph[now_v].empty()) {
            dFSVisit(now_v, colors);
            break;
        }
    }

    for (size_t now_v = 1; now_v < graph.size(); now_v++) {
        if (deg_in[now_v] != 0 && colors[now_v] == false) {
            return false;
        }
    }
	return true;

}

int main() {
	int path_count;
	std::cin >> path_count;
	int square_count;
	std::cin >> square_count;
	Graph<int> graph(square_count);
	for (int i = 0; i < path_count; ++i) {
		int path_size;
		std::cin >> path_size;
		int from;
		std::cin >> from;
		graph.isolated[from] = false;
		int to;
		for (int j = 0; j < path_size; ++j) {
			std::cin >> to;
			graph.isolated[to] = false;
			graph.AppendEdge(from, to);
			from = to;
		}
	}
	if (graph.IsEuler()) {
		graph.EulerBuild();
		graph.PrintEuler();
	} else {
		std::cout << 0 << "\n";
	}

}