#include <iostream>
#include <chrono>

#include "MapASCII.h"
#include "Graph.h"

int main() {
    auto begin = std::chrono::high_resolution_clock::now();

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int width, height;
    std::cin >> width >> height;

    MapASCII mapAscii(width, height);
    mapAscii.formMap();

    Graph graph(&mapAscii);

    int flightConnections;
    std::cin >> flightConnections;

    for (int i = 0; i < flightConnections; i++) {
        graph.readFlightConnection();
    }

    int queriesCount;
    std::cin >> queriesCount;

    for (int i = 0; i < queriesCount; i++) {
        graph.printShortestPath();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "\n" << elapsed.count() * 1e-9;

    return 0;
}
