#include <iostream>
#include <vector>
#include <utility>
#include <queue>

template <class T>
class GraphOnTrack {
    std::vector<std::vector<T>> dist;
    std::vector<std::pair<T, T>> GetNborsTrack(std::pair<T, T>);
    std::vector<std::vector<T>> track;
    std::pair<T, T> start_vertex;
    std::pair<T, T> finish_vertex;
public:
    GraphOnTrack(int&, int&);
    void TrackBFS();
    void PrintfDistTrack();
    void BuildTrack();
};

template <class T>
GraphOnTrack<T>::GraphOnTrack(int& track_heigh, int& track_width) : 
    dist(track_heigh + 2, std::vector<T>(track_width + 2, -1)),
    track(track_heigh + 2, std::vector<T>(track_width + 2, -1)) {
}

template <class T>
void GraphOnTrack<T>::BuildTrack() {
    char track_cell;
    for (size_t i = 0; i < dist.size(); ++i) {
        track[i][0] = -2;
        track[i][dist[0].size() - 1] = -2;
    }
    for (size_t j = 0; j < dist[0].size(); ++j) {
        track[0][j] = -2;
        track[dist.size() - 1][j] = -2;
    }
    for (size_t i = 1; i < dist.size() - 1; ++i) {
        for (size_t j = 1; j < dist[0].size() - 1; ++j) {
            std::cin >> track_cell;
            if (track_cell == 'S') {
                start_vertex = {i, j};
            }
            if (track_cell == 'T') {
                finish_vertex = {i, j};
            }
            if (track_cell == '#') {
                track[i][j] = -2;
            }
        }
    }
}

template <class T>
std::vector<std::pair<T, T>> GraphOnTrack<T>::GetNborsTrack(std::pair<T, T> vert) {
    std::vector<std::pair<T, T>> nbors;
    size_t delta = 0;
    do {
        delta++;
        if (track[vert.first + delta][vert.second] == -2) {
            delta--;
            delta -= delta / 2;
            if (delta != 0) {
                nbors.emplace_back(vert.first + delta, vert.second);
            }
            break;
        }
    } while (true);
    delta = 0;
    do {
        delta++;
        if (track[vert.first - delta][vert.second] == -2) {
            delta--;
            delta -= delta / 2;
            if (delta != 0) {
                nbors.emplace_back(vert.first - delta, vert.second);
            }
            break;
        }
    } while (true);
    delta = 0;
    do {
        delta++;
        if (track[vert.first][vert.second + delta] == -2) {
            delta--;
            delta -= delta / 2;
            if (delta != 0) {
                nbors.emplace_back(vert.first, vert.second + delta);
            }
            break;
        }
    } while (true);
    delta = 0;
    do {
        delta++;
        if (track[vert.first][vert.second - delta] == -2) {
            delta--;
            delta -= delta / 2;
            if (delta != 0) {
                nbors.emplace_back(vert.first, vert.second - delta);
            }
            break;
        }
    } while (true);
    return nbors;
}

template <class T>
void GraphOnTrack<T>::TrackBFS() {
    for (size_t i = 0; i < dist.size(); ++i) {
        for (size_t j = 0; j < dist[0].size(); ++j) {
            dist[i][j] = -1;
        }
    }
    std::queue<std::pair<T, T>> expectation;
    expectation.push(start_vertex);
    dist[start_vertex.first][start_vertex.second] = 0;
    std::pair<T, T> vertex;
    while (!expectation.empty()) {
        vertex = expectation.front();
        expectation.pop();
        auto nbors = GetNborsTrack(vertex);
        for (auto &u : nbors) {
            if (dist[u.first][u.second] == -1) {
                dist[u.first][u.second] = dist[vertex.first][vertex.second] + 1;
                expectation.push(u);
            }
        }
    }
}

template <class T>
void GraphOnTrack<T>::PrintfDistTrack() {
    std::cout << dist[finish_vertex.first][finish_vertex.second] << "\n";
}

int main() {
    int track_heigh = 0;
    int track_width = 0;
    std::cin >> track_heigh >> track_width;
    GraphOnTrack<int> GraphOnTrack(track_heigh, track_width);
    GraphOnTrack.BuildTrack();
    GraphOnTrack.TrackBFS();
    GraphOnTrack.PrintfDistTrack();
    return 0;
}