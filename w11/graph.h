/************************************************************************************
 ** NIU CSCI 340 Section 2 * Assignment Graph Kevin Dela Paz - z2017241 *
 **
 * I certify that everything I am submitting is either provided by the professor
 *for use in * the assignment, or work done by me personally. I understand that
 *if I am caught submitting * the work of others (including StackOverflow or
 *ChatGPT) as my own is an act of Academic * Misconduct and will be punished as
 *such. *

 ** This program implements a graph data structure and provides algorithms for querying and analyzing graphs
 ************************************************************************************/


#ifndef NIU_CSCI340_GRAPH_H
#define NIU_CSCI340_GRAPH_H

#include "graph.decl.h"
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>

/**
 * @brief Get the number of vertices in the graph.
 * @return The number of vertices.
 */
size_t Graph::nvertices() const {
    return vertices.size();
}

/**
 * @brief Get the number of edges in the graph.
 * @return The number of edges.
 */
size_t Graph::nedges() const {
    return edges.size();
}

/**
 * @brief Assign vertices and edges to the graph.
 * @param vertices A vector of vertex labels.
 * @param edges A vector of edges.
 */
void Graph::assign(const std::vector<std::string> &vertices, const std::vector<GraphEdge> &edges) {
    this->vertices = vertices;  
    this->edges = edges;        

    // Clear and rebuild the vertex lookup table.
    v_lut.clear();
    for (size_t i = 0; i < vertices.size(); ++i) {
        v_lut[vertices[i]] = i; // Map vertex labels
    }
}

/**
 * @brief Check if an edge exists between two vertices.
 * @param origin The index of the starting vertex.
 * @param destination The index of the destination vertex.
 * @return True if the edge exists, false otherwise.
 */
bool Graph::edge_exists(size_t origin, size_t destination) const {
    for (const auto &edge : edges) {
        if (edge.origin == origin && edge.destination == destination) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Get the weight of the edge between two vertices.
 * @param origin The index of the starting vertex.
 * @param destination The index of the destination vertex.
 * @return The weight of the edge, or INFINITY if the edge does not exist.
 */
double Graph::edge_weight(size_t origin, size_t destination) const {
    for (const auto &edge : edges) {
        if (edge.origin == origin && edge.destination == destination) {
            return edge.weight;
        }
    }
    return INFINITY;
}

/**
 * @brief Get the undirected adjacency list of a vertex.
 * @param vertex The index of the vertex.
 * @return A vector of AdjListEdge objects representing the adjacency list.
 */
std::vector<AdjListEdge> Graph::undirected_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> adj_list; // List to store adjacent vertices.
    for (const auto &edge : edges) {
        if (edge.origin == vertex) {
            adj_list.push_back({edge.destination, edge.weight});
        } else if (edge.destination == vertex) {
            adj_list.push_back({edge.origin, edge.weight});
        }
    }
    return adj_list;
}

/**
 * @brief Get the in-adjacency list of a vertex (edges pointing to the vertex).
 * @param vertex The index of the vertex.
 * @return A vector of AdjListEdge objects representing the in-adjacency list.
 */
std::vector<AdjListEdge> Graph::in_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> adj_list; // List to store incoming edges.
    for (const auto &edge : edges) {
        if (edge.destination == vertex) {
            // Add the origin vertex if it points to the given vertex.
            adj_list.push_back({edge.origin, edge.weight});
        }
    }
    return adj_list;
}

/**
 * @brief Get the out-adjacency list of a vertex (edges starting from the vertex).
 * @param vertex The index of the vertex.
 * @return A vector of AdjListEdge objects representing the out-adjacency list.
 */
std::vector<AdjListEdge> Graph::out_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> adj_list; // List to store outgoing edges.
    for (const auto &edge : edges) {
        if (edge.origin == vertex) {
            // Add the destination vertex if the edge starts from the given vertex.
            adj_list.push_back({edge.destination, edge.weight});
        }
    }
    return adj_list;
}

/**
 * @brief Get the weighted adjacency matrix of the graph.
 * @return A vector of doubles representing the matrix in row-major order.
 */
std::vector<double> Graph::weighted_adjacency_matrix() const {
    size_t n = nvertices();
    std::vector<double> matrix(n * n, INFINITY); // Initialize with INFINITY.

    for (const auto &edge : edges) {
        // Set the weight for the corresponding edge in the matrix.
        matrix[edge.origin * n + edge.destination] = edge.weight;
    }

    return matrix;
}

/**
 * @brief Get the unweighted adjacency matrix of the graph.
 * @return A vector of booleans representing the matrix in row-major order.
 */
std::vector<bool> Graph::unweighted_adjacency_matrix() const {
    size_t n = nvertices();
    std::vector<bool> matrix(n * n, false); 

    for (const auto &edge : edges) {
        matrix[edge.origin * n + edge.destination] = true;
    }

    return matrix;
}

/**
 * @brief Get the label of a vertex by its index.
 * @param vertex The index of the vertex.
 * @return The label of the vertex.
 * @throws std::out_of_range if the vertex index is invalid.
 */
std::string Graph::v_label(size_t vertex) const {
    if (vertex < vertices.size()) {
        return vertices[vertex];
    }
    throw std::out_of_range("Invalid vertex index."); 
}

/**
 * @brief Get the index of a vertex by its label.
 * @param label The label of the vertex.
 * @return The index of the vertex, or -1 if not found.
 */
ssize_t Graph::v_index(const std::string &label) const {
    auto it = v_lut.find(label);
    return (it != v_lut.end()) ? it->second : -1;
}

/**
 * @brief Perform a breadth-first traversal of the graph.
 * @tparam FN The type of the visit function.
 * @param start The index of the starting vertex.
 * @param visitfn The function to call when visiting a vertex.
 * @param connected_only Whether to traverse only the connected component of the start vertex.
 */
template <typename FN>
void Graph::breadth_first(size_t start, FN visitfn, bool connected_only) {
    size_t n = nvertices();
    std::vector<bool> visited(n, false); // Track visited vertices.
    std::queue<size_t> queue;           

    // mark it as visited and enqueue it.
    auto process_vertex = [&](size_t vertex) {
        queue.push(vertex);
        visited[vertex] = true;
    };

    process_vertex(start);

    // Process all vertices in the queue.
    while (!queue.empty()) {
        size_t current = queue.front();
        queue.pop();
        visitfn(current); // Call the visit function for the current vertex.

        // Collect and sort neighbors by vertex index.
        auto adj_list = out_adjacency_list(current);
        std::sort(adj_list.begin(), adj_list.end(), [](const AdjListEdge &a, const AdjListEdge &b) {
            return a.vertex < b.vertex;
        });

        // Visit unvisited neighbors.
        for (const auto &edge : adj_list) {
            if (!visited[edge.vertex]) {
                process_vertex(edge.vertex);
            }
        }
    }

    // disconnected components should also be processed.
    if (!connected_only) {
        for (size_t i = 0; i < n; ++i) {
            if (!visited[i]) {
                process_vertex(i); 
                while (!queue.empty()) {
                    size_t current = queue.front();
                    queue.pop();
                    visitfn(current);

                    // Collect and sort neighbors by vertex index.
                    auto adj_list = out_adjacency_list(current);
                    std::sort(adj_list.begin(), adj_list.end(), [](const AdjListEdge &a, const AdjListEdge &b) {
                        return a.vertex < b.vertex;
                    });

                    // Visit unvisited neighbors.
                    for (const auto &edge : adj_list) {
                        if (!visited[edge.vertex]) {
                            process_vertex(edge.vertex);
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief Perform a depth-first traversal of the graph.
 * @tparam FN The type of the visit function.
 * @param start The index of the starting vertex.
 * @param visitfn The function to call when visiting a vertex.
 * @param connected_only Whether to traverse only the connected component of the start vertex.
 */
template <typename FN>
void Graph::depth_first(size_t start, FN visitfn, bool connected_only) {
    std::vector<bool> visited(nvertices(), false); 

    // Recursive lambda for depth-first traversal.
    auto dfs_recursive = [&](auto &self, size_t vertex) -> void {
        visited[vertex] = true; // Mark the vertex as visited.
        visitfn(vertex);        

        // Collect and sort neighbors by vertex index.
        auto adj_list = out_adjacency_list(vertex);
        std::sort(adj_list.begin(), adj_list.end(), [](const AdjListEdge &a, const AdjListEdge &b) {
            return a.vertex < b.vertex;
        });

        // Recurse into unvisited neighbors.
        for (const auto &edge : adj_list) {
            if (!visited[edge.vertex]) {
                self(self, edge.vertex);
            }
        }
    };

    dfs_recursive(dfs_recursive, start); // Start DFS from the given vertex.

    if (!connected_only) {
        for (size_t i = 0; i < nvertices(); ++i) {
            if (!visited[i]) {
                dfs_recursive(dfs_recursive, i);
            }
        }
    }
}

/**
 * @brief Perform a topological sort on the graph.
 * @return A vector of vertex indices in topological order. May be incomplete if a cycle is detected.
 */
std::vector<size_t> Graph::toposort() const {
    size_t n = nvertices();
    std::vector<size_t> in_degree(n, 0); // Track in-degrees of all vertices.

    // Calculate in-degrees for all vertices.
    for (const auto &edge : edges) {
        in_degree[edge.destination]++;
    }

    std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>> zero_in_degree;
    for (size_t i = 0; i < n; ++i) {
        if (in_degree[i] == 0) {
            zero_in_degree.push(i);
        }
    }

    std::vector<size_t> sorted; // Store the sorted order.

    // Process vertices with zero in-degree.
    while (!zero_in_degree.empty()) {
        size_t current = zero_in_degree.top();
        zero_in_degree.pop();
        sorted.push_back(current); 

        // Decrement in-degrees of neighbors and enqueue
        for (const auto &edge : out_adjacency_list(current)) {
            size_t neighbor = edge.vertex;
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) {
                zero_in_degree.push(neighbor);
            }
        }
    }

    return sorted; // Return the sorted order.
}

/**
 * @brief Perform Dijkstra's shortest path algorithm from a given source vertex.
 * @param start The index of the source vertex.
 * @return A vector of dijkstra_row objects representing the shortest paths to all vertices.
 */
std::vector<dijkstra_row> Graph::dijkstra(size_t start) const {
    // Check for negative edge weights.
    if (std::any_of(edges.begin(), edges.end(), [](const GraphEdge &e) { return e.weight < 0; })) {
        std::cerr << "Error: Dijkstra's algorithm does not support graphs with negative edge weights.\n";
        return {};
    }

    std::vector<dijkstra_row> table(nvertices(), {0, false, INFINITY, -1});

    // Initialize the table for the source vertex.
    for (size_t i = 0; i < table.size(); ++i) {
        table[i].vertex = i;
    }
    table[start].shortest_known = 0; 

    // Priority queue to process vertices by the shortest known distance.
    auto compare = [](const dijkstra_row &a, const dijkstra_row &b) {
        return a.shortest_known > b.shortest_known;
    };
    std::priority_queue<dijkstra_row, std::vector<dijkstra_row>, decltype(compare)> pq(compare);

    pq.push(table[start]); 

    // Process the queue.
    while (!pq.empty()) {
        dijkstra_row current = pq.top();
        pq.pop();

        if (table[current.vertex].visited) continue;
        table[current.vertex].visited = true;       

        // Update distances for neighbors.
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
