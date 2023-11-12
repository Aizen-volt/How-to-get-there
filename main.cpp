#include <iostream>
#include <chrono>

#include "MapASCII.h"
#include "Graph.h"

int main() {
    // for measuring execution time
    auto begin = std::chrono::high_resolution_clock::now();

    // speed up i/o
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // read map dimensions
    int width, height;
    std::cin >> width >> height;

    // read map
    MapASCII mapAscii(width, height);
    mapAscii.formMap();

    // create graph
    Graph graph(&mapAscii);

    // read potential flight connections
    int flightConnections;
    std::cin >> flightConnections;

    for (int i = 0; i < flightConnections; i++) {
        graph.readFlightConnection();
    }

    // handle queries
    int queriesCount;
    std::cin >> queriesCount;

    for (int i = 0; i < queriesCount; i++) {
        graph.printShortestPath();
    }

    // print execution time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "\n" << elapsed.count() * 1e-9;

    return 0;
}
