#include <iostream>
#include <cstdio>
#include <chrono>

#include "Graph.h"


void InitMapArray(Map* map) {
    map->array = new char*[map->width];
    for (int i = 0; i < map->width; i++)
        map->array[i] = new char[map->height];
}


int main() {
    //for time measurement
    //auto begin = std::chrono::high_resolution_clock::now();

    Map map;
    scanf("%d %d\n", &map.width, &map.height);
    InitMapArray(&map);

    Graph graph(&map);

    int flightConnectionsCount;
    scanf("%d\n", &flightConnectionsCount);
    for (int i = 0; i < flightConnectionsCount; i++) {
        graph.ReadFlightConnection();
    
}

    int queriesCount;
    scanf("%d\n", &queriesCount);
    for (int i = 0; i < queriesCount; i++) {
        int mode = 0;
        String source, destination;
        char outputMode[2];
        char letter = -1;
        while (letter != '\n') {
            letter = getchar();
            if (letter == EOF)
                return 0;
            if (letter == ' ') {
                mode++;
                continue;
            
}
            if (mode == 0)
                source.PushBack(letter);
            else if (mode == 1)
                destination.PushBack(letter);
            else {
                outputMode[0] = letter;
                getchar();
                break;
            
}
        
}
        outputMode[1] = '\0';
        int output = atoi(outputMode);
        graph.Dijkstra(source, destination, output);
    
}


    //print program execution time
    //auto end = std::chrono::high_resolution_clock::now();
    //auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    //std::cout << "\n" << elapsed.count() * 1e-9;

    return 0;
}
