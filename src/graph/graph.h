//
// Created by hammer on 28.03.2020.
//

#ifndef ALGORITHMS_GRAPH_H
#define ALGORITHMS_GRAPH_H

#include <string>
#include <vector>
#include <map>
#include <limits>


class Graph {
public:
    Graph() = default;
    Graph(const Graph& otherGraph) = delete;
    const Graph& operator=(const Graph& otherGraph) = delete;
    ~Graph();

    void addEdge(const std::string& sourceName, const std::string& destinationName, double cost);
    void printPath(const std::string& destinationName) const;
    void unweighted(const std::string& startName);
    //void dijkstra(const std::string& startName);
    //void negative(const std::string& startName);
    //void acyclic(const std::string& startName);
private:
    struct Vertex;
    struct Edge {
        Vertex *dest;
        double cost;

        explicit Edge(Vertex* dest = nullptr, double cost = 0.0) : dest(dest), cost(cost) {}
    };

    struct Vertex {
        std::string name;
        std::vector<Edge> adjacentVertices;
        double distance = INFINITY;
        Vertex* previousVertex = nullptr;
        int scratch = 0;

        explicit Vertex(const std::string& name) : name(name) {}

        void reset() {
            distance = INFINITY;
            previousVertex = nullptr;
            scratch = 0;
        }
    };

    Vertex* getVertex(const std::string& vertexName);
    void printPath(const Vertex& destination) const;
    void clear();

    constexpr static double INFINITY = std::numeric_limits<double>::infinity();
    using VertexMap = std::map<std::string, Vertex*>;
    VertexMap vertexMap;
};


#endif //ALGORITHMS_GRAPH_H
