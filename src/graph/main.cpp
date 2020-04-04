//
// Created by hammer on 02.04.2020.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "graph.h"

bool processRequest(std::istream& inStream, Graph& graph);

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
    while (processRequest(std::cin, graph)) {
        ;
    }
    return 0;
}

bool processRequest(std::istream& inStream, Graph& graph) {
    return false;
}