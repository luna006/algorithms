//
// Created by hammer on 28.03.2020.
//

#include <iostream>
#include <stdexcept>
#include <deque>
#include <queue>
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

void Graph::unweighted(const std::string &startVertexName) {
    auto iterator = vertexMap.find(startVertexName);
    if (iterator == vertexMap.cend()) {
        throw std::invalid_argument("Vertex " + startVertexName + " was not found");
    }
    clear();
    Vertex* startVertex = iterator->second;
    startVertex->distance = 0.0;
    std::deque<Vertex*> queue;
    queue.push_back(startVertex);
    while (!queue.empty()) {
        Vertex* currentVertex = queue.front();
        queue.pop_front();
        for (Edge edge: currentVertex->adjacentVertices) {
            Vertex* adjacentVertex = edge.dest;
            if (adjacentVertex->distance == INFINITY) {
                adjacentVertex->distance = currentVertex->distance + 1;
                adjacentVertex->previousVertex = currentVertex;
                queue.push_back(adjacentVertex);
            }
        }
    }
}

void Graph::dijkstra(const std::string &startVertexName) {
    auto iterator = vertexMap.find(startVertexName);
    if (iterator == vertexMap.cend()) {
        throw std::invalid_argument("Vertex " + startVertexName + " was not found");
    }
    clear();
    Vertex* startVertex = iterator->second;
    startVertex->distance = 0;
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pqueue;
    pqueue.push(Edge(startVertex, startVertex->distance));
    Edge currentEdge;
    for (VertexMap::size_type i = 0; i < vertexMap.size(); i++) {
        do {
            if (!pqueue.empty()) {
                currentEdge = pqueue.top();
                pqueue.pop();
            }
        } while (currentEdge.dest->scratch != 0);
        Vertex* currentVertex = currentEdge.dest;
        currentVertex->scratch = 1;
        for (Edge& edge : currentVertex->adjacentVertices) {
            if (edge.cost < 0) {
                throw std::invalid_argument("Negative cost of edge");
            }
            if (edge.dest->distance > currentVertex->distance + edge.cost) {
                edge.dest->distance = currentVertex->distance + edge.cost;
                edge.dest->previousVertex = currentVertex;
                pqueue.push(std::move(edge));
            }
        }
    }
}
