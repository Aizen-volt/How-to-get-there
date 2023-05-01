#ifndef NEWMAPPER_GRAPH_H
#define NEWMAPPER_GRAPH_H


#include "List.h"
#include "Vector.h"
#include "CityNameToPositionHash.h"

typedef struct Connection {
    int source, destination, distance;
    Connection(int source, int destination, int distance) : source(source), destination(destination), distance(distance) {}
    Connection() : source(-1), destination(-1), distance(-1) {}
} Connection;

typedef struct Position {
    int x, y;
    Position(): x(-1), y(-1) {}
    Position(int x, int y): x(x), y(y) {}
} Position;


typedef struct {
    char** array;
    int width, height, roadCount;
} Map;


typedef struct QueueItem {
    int x, y, distance;
} QueueItem;



class Graph {
private:
    Map* map;
    int verticesCount;
    Vector<List<Connection>> adjacencyList;

    //returns city position and id in adjacency list based on its name
    CityNameToPositionHash* cities;
    Vector<String> cityNames;

    //starting points for BFS
    Vector<Position> cityPositions;
    int excessFactor;

    void InitAdjacencyList();
    void FindCityConnections();
    static bool IsCityName(char letter);
    void FindCityName(int x, int y, String& cityName);
    void ReadMap();
public:
    explicit Graph(Map* map);

    void ReadFlightConnection();
    void Dijkstra(const String& source, const String& destination, int output);
};


#endif //NEWMAPPER_GRAPH_H