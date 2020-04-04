//
// Created by hammer on 28.03.2020.
//

#include <iostream>
#include <stdexcept>
#include "graph.h"

Graph::~Graph() {
    for (auto& entry: vertexMap) {
        delete entry.second;
    }
}

Graph::Vertex* Graph::getVertex(const std::string& vertexName) {
    auto iterator = vertexMap.find(vertexName);
    if (iterator == vertexMap.cend()) {
        Vertex* newVertex = new Vertex(vertexName);
        vertexMap.emplace(vertexName, newVertex);
        return newVertex;
    }
    return iterator->second;
}

void Graph::addEdge(const std::string &sourceName, const std::string &destinationName, double cost) {
    Graph::Vertex* sourceVertex = getVertex(sourceName);
    Graph::Vertex* destinationVertex = getVertex(destinationName);
    sourceVertex->adjacentVertices.push_back(Graph::Edge(destinationVertex, cost));
}

void Graph::clear() {
    for (auto& entry: vertexMap) {
        entry.second->reset();
    }
}

void Graph::printPath(const Graph::Vertex& destination) const {
    if (destination.previousVertex) {
        printPath(*destination.previousVertex);
        std::cout << " --> ";
    }
    std::cout << destination.name;
}

void Graph::printPath(const std::string &destinationName) const {
    auto iterator = vertexMap.find(destinationName);
    if (iterator == vertexMap.cend()) {
        throw std::invalid_argument("Destination vertex not found");
    }
    const Vertex& vertex = *(iterator->second);
    if (vertex.distance != INFINITY) {
        std::cout << "(Cost is: " << vertex.distance << ") ";
        printPath(vertex);
    } else {
        std::cout << "Vertex " << destinationName << " is unreachable";
    }
    std::cout << std::endl;
}
