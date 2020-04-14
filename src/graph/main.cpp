//
// Created by hammer on 02.04.2020.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "graph.h"

void processRequest(std::istream& inStream, Graph& graph);

int main(int argc, const char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " graphFile" << std::endl;
        std::exit(1);
    }
    std::ifstream inStream(argv[1]);
    if (!inStream) {
        std::cerr << "Cannot open " << argv[1] << std::endl;
        std::exit(1);
    }
    std::cout << "Reading file... " << std::endl;
    std::string line;
    Graph graph;
    std::string source;
    std::string destination;
    double cost;
    while (!std::getline(inStream, line).eof()) {
        std::istringstream stringStream(line);
        stringStream >> source >> destination >> cost;
        if (stringStream.fail()) {
            std::cerr << "Bad line: " << line << std::endl;
        } else {
            graph.addEdge(source, destination, cost);
        }
    }
    std::cout << "File read" << std::endl << std::endl;
    bool isContinue = true;
    std::string userInput;
    do {
        try {
            processRequest(std::cin, graph);
        } catch (std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
        }
        std::cout << R"(Enter 'c' to continue or 'q' for quit: )";
        std::cin >> userInput;
        if (userInput != "c") {
            isContinue = false;
        }
    } while (isContinue);
    return 0;
}

void processRequest(std::istream& inStream, Graph& graph) {
    std::string startVertexName;
    std::string destinationVertexName;
    std::cout << "Enter name of start node: ";
    if (!(inStream >> startVertexName)) {
        throw std::invalid_argument("Cannot read name of start node");
    }
    std::cout << "Enter name of destination node: ";
    if (!(inStream >> destinationVertexName)) {
        throw std::invalid_argument("Cannot read name of destination node");
    }
    //graph.unweighted(startVertexName);
    graph.dijkstra(startVertexName);
    graph.printPath(destinationVertexName);
}