#ifndef NIU_CSCI340_GRAPH_H
#define NIU_CSCI340_GRAPH_H

#include "graph.decl.h"
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>

size_t Graph::nvertices() const {
    return vertices.size();
}

size_t Graph::nedges() const {
    return edges.size();
}

void Graph::assign(const std::vector<std::string> &vertices, const std::vector<GraphEdge> &edges) {
    this->vertices = vertices;
    this->edges = edges;
    v_lut.clear();
    for (size_t i = 0; i < vertices.size(); ++i) {
        v_lut[vertices[i]] = i;
    }
}

bool Graph::edge_exists(size_t origin, size_t destination) const {
    for (const auto &edge : edges) {
        if (edge.origin == origin && edge.destination == destination) {
            return true;
        }
    }
    return false;
}

double Graph::edge_weight(size_t origin, size_t destination) const {
    for (const auto &edge : edges) {
        if (edge.origin == origin && edge.destination == destination) {
            return edge.weight;
        }
    }
    return INFINITY;
}

std::vector<AdjListEdge> Graph::undirected_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> adj_list;
    for (const auto &edge : edges) {
        if (edge.origin == vertex) {
            adj_list.push_back({edge.destination, edge.weight});
        } else if (edge.destination == vertex) {
            adj_list.push_back({edge.origin, edge.weight});
        }
    }
    return adj_list;
}

std::vector<AdjListEdge> Graph::in_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> adj_list;
    for (const auto &edge : edges) {
        if (edge.destination == vertex) {
            adj_list.push_back({edge.origin, edge.weight});
        }
    }
    return adj_list;
}

std::vector<AdjListEdge> Graph::out_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> adj_list;
    for (const auto &edge : edges) {
        if (edge.origin == vertex) {
            adj_list.push_back({edge.destination, edge.weight});
        }
    }
    return adj_list;
}

std::vector<double> Graph::weighted_adjacency_matrix() const {
    size_t n = nvertices();
    std::vector<double> matrix(n * n, INFINITY);

    for (const auto &edge : edges) {
        matrix[edge.origin * n + edge.destination] = edge.weight;
    }

    return matrix;
}

std::vector<bool> Graph::unweighted_adjacency_matrix() const {
    size_t n = nvertices();
    std::vector<bool> matrix(n * n, false);

    for (const auto &edge : edges) {
        matrix[edge.origin * n + edge.destination] = true;
    }

    return matrix;
}

std::string Graph::v_label(size_t vertex) const {
    if (vertex < vertices.size()) {
        return vertices[vertex];
    }
    throw std::out_of_range("Invalid vertex index.");
}

ssize_t Graph::v_index(const std::string &label) const {
    auto it = v_lut.find(label);
    return (it != v_lut.end()) ? it->second : -1;
}

template <typename FN>
void Graph::breadth_first(size_t start, FN visitfn, bool connected_only) {
    std::vector<bool> visited(nvertices(), false);
    std::queue<size_t> queue;
    queue.push(start);
    visited[start] = true;

    while (!queue.empty()) {
        size_t current = queue.front();
        queue.pop();
        visitfn(current);

        // Collect adjacency list and sort it to ensure ascending order of indices
        auto adj_list = out_adjacency_list(current);
        std::sort(adj_list.begin(), adj_list.end(), [](const AdjListEdge &a, const AdjListEdge &b) {
            return a.vertex < b.vertex;
        });

        for (const auto &edge : adj_list) {
            if (!visited[edge.vertex]) {
                visited[edge.vertex] = true;
                queue.push(edge.vertex);
            }
        }
    }

    if (!connected_only) {
        for (size_t i = 0; i < nvertices(); ++i) {
            if (!visited[i]) {
                breadth_first(i, visitfn, true); // Process disconnected components
            }
        }
    }
}


template <typename FN>
void Graph::depth_first(size_t start, FN visitfn, bool connected_only) {
    std::vector<bool> visited(nvertices(), false);

    auto dfs_recursive = [&](auto &self, size_t vertex) -> void {
        visited[vertex] = true;
        visitfn(vertex);

        // Collect adjacency list and sort it to ensure ascending order of indices
        auto adj_list = out_adjacency_list(vertex);
        std::sort(adj_list.begin(), adj_list.end(), [](const AdjListEdge &a, const AdjListEdge &b) {
            return a.vertex < b.vertex;
        });

        for (const auto &edge : adj_list) {
            if (!visited[edge.vertex]) {
                self(self, edge.vertex); // Recurse
            }
        }
    };

    dfs_recursive(dfs_recursive, start);

    if (!connected_only) {
        for (size_t i = 0; i < nvertices(); ++i) {
            if (!visited[i]) {
                dfs_recursive(dfs_recursive, i); // Process disconnected components
            }
        }
    }
}

std::vector<size_t> Graph::toposort() const {
    size_t n = nvertices();
    std::vector<size_t> in_degree(n, 0);

    // Compute in-degrees for all vertices
    for (const auto &edge : edges) {
        in_degree[edge.destination]++;
    }

    // Use a priority queue to process vertices in ascending order
    std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>> zero_in_degree;
    for (size_t i = 0; i < n; ++i) {
        if (in_degree[i] == 0) {
            zero_in_degree.push(i);
        }
    }

    std::vector<size_t> sorted;
    while (!zero_in_degree.empty()) {
        size_t current = zero_in_degree.top();
        zero_in_degree.pop();
        sorted.push_back(current);

        for (const auto &edge : out_adjacency_list(current)) {
            size_t neighbor = edge.vertex;
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) {
                zero_in_degree.push(neighbor);
            }
        }
    }


    return sorted;
}



std::vector<dijkstra_row> Graph::dijkstra(size_t start) const {
    if (std::any_of(edges.begin(), edges.end(), [](const GraphEdge &e) { return e.weight < 0; })) {
        std::cerr << "Error: Dijkstra's algorithm does not support graphs with negative edge weights.\n";
        return {};
    }

    std::vector<dijkstra_row> table(nvertices(), {0, false, INFINITY, -1});
    for (size_t i = 0; i < table.size(); ++i) {
        table[i].vertex = i;
    }
    table[start].shortest_known = 0;

    auto compare = [](const dijkstra_row &a, const dijkstra_row &b) {
        return a.shortest_known > b.shortest_known;
    };
    std::priority_queue<dijkstra_row, std::vector<dijkstra_row>, decltype(compare)> pq(compare);

    pq.push(table[start]);

    while (!pq.empty()) {
        dijkstra_row current = pq.top();
        pq.pop();

        if (table[current.vertex].visited) continue;
        table[current.vertex].visited = true;

        for (const auto &edge : out_adjacency_list(current.vertex)) {
            size_t neighbor = edge.vertex;
            double new_distance = current.shortest_known + edge.weight;

            if (new_distance < table[neighbor].shortest_known) {
                table[neighbor].shortest_known = new_distance;
                table[neighbor].came_from = current.vertex;
                pq.push(table[neighbor]);
            }
        }
    }

    return table;
}



#endif /* NIU_CSCI340_GRAPH_H */
