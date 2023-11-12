#ifndef HOW_TO_GET_THERE_GRAPH_H
#define HOW_TO_GET_THERE_GRAPH_H

#include "MapASCII.h"
#include "Connection.h"
#include "structures/List.h"
#include "structures/Queue.h"
#include "structures/PriorityQueue.h"

class Graph {

private:
    size_t vertices;
    Vector<List<Connection>> adjacencyList;
    MapASCII* map;


    void createAdjacencyList() {
        for (int i = 0; i < vertices; i++) {
            List<Connection> temp;
            temp.pushBack({ i, i, 0 });
            adjacencyList.pushBack(temp);
        }
    }


    void bfs() {
        bool** visited = new bool*[map->width];
        for (int i = 0; i < map->width; i++) {
            visited[i] = new bool[map->height];
        }

        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (i == j) {
                    continue;
                }

                std::pair<Position, int> source = {Position(map->cityPositions[i].x, map->cityPositions[i].y), 0};

                for (int x = 0; x < map->width; x++) {
                    for (int y = 0; y < map->height; y++) {
                        if (map->array[x][y] == MapASCII::ROAD_SYMBOL || (x == map->cityPositions[j].x && y == map->cityPositions[j].y)) {
                            visited[x][y] = false;
                        }
                        else {
                            visited[x][y] = true;
                        }
                    }
                }

                Queue<std::pair<Position, int>> queue;
                queue.push(source);

                visited[source.first.x][source.first.y] = true;

                while (!queue.empty()) {
                    std::pair<Position, int> p = queue.peek();
                    queue.pop();

                    if (p.first.x == map->cityPositions[j].x && p.first.y == map->cityPositions[j].y) {
                        adjacencyList[i].pushBack(Connection(i, j, p.second));
                        break;
                    }

                    //up
                    if (p.first.y - 1 >= 0 && !visited[p.first.x][p.first.y - 1]) {
                        visited[p.first.x][p.first.y - 1] = true;
                        std::pair<Position, int> temp = {Position(p.first.x, p.first.y - 1), p.second + 1};
                        queue.push(temp);
                    }

                    //down
                    if (p.first.y + 1 < map->height && !visited[p.first.x][p.first.y + 1]) {
                        visited[p.first.x][p.first.y + 1] = true;
                        std::pair<Position, int> temp = {Position(p.first.x, p.first.y + 1), p.second + 1};
                        queue.push(temp);
                    }

                    //left
                    if (p.first.x - 1 >= 0 && !visited[p.first.x - 1][p.first.y]) {
                        visited[p.first.x - 1][p.first.y] = true;
                        std::pair<Position, int> temp = {Position(p.first.x - 1, p.first.y), p.second + 1};
                        queue.push(temp);
                    }

                    //right
                    if (p.first.x + 1 < map->width && !visited[p.first.x + 1][p.first.y]) {
                        visited[p.first.x + 1][p.first.y] = true;
                        std::pair<Position, int> temp = {Position(p.first.x + 1, p.first.y), p.second + 1};
                        queue.push(temp);
                    }
                }
            }
        }

        for (int i = 0; i < map->width; i++) {
            delete[] visited[i];
        }
        delete[] visited;
    }

public:
    explicit Graph(MapASCII* mapAscii) : map(mapAscii) {
        vertices = map->cityNames.getSize();

        createAdjacencyList();
        if (map->roadCount > 0) {
            bfs();
        }
    }


    void readFlightConnection() {
        String source, destination;
        int distance;
        std::cin >> source >> destination >> distance;

        int sourceIndex = map->cityNameToId.find(source);
        int destinationIndex = map->cityNameToId.find(destination);
        adjacencyList[sourceIndex].pushBack(Connection(sourceIndex, destinationIndex, distance));
    }


    void printShortestPath() {
        String source, destination;
        bool showPath;

        std::cin >> source >> destination >> showPath;
        int sourceIndex = map->cityNameToId.find(source);
        int destinationIndex = map->cityNameToId.find(destination);

        if (sourceIndex == destinationIndex) {
            std::cout<< "0\n";
            return;
        }

        PriorityQueue<std::pair<int, int>> priorityQueue;
        Vector<int> distances(vertices);
        Vector<int> prev(vertices);
        Vector<bool> visited(vertices);

        for (int i = 0; i < vertices; i++) {
            distances[i] = INT_MAX;
            visited[i] = false;
        }

        distances[sourceIndex] = 0;
        visited[sourceIndex] = true;
        priorityQueue.push({ 0, sourceIndex });

        while (!priorityQueue.empty()) {
            int u = priorityQueue.peek().second;
            priorityQueue.pop();

            if (u == destinationIndex) {
                std::cout << distances[u];

                if (showPath) {
                    int i = prev[u];
                    Vector<int> trace;

                    while (i != sourceIndex) {
                        trace.pushBack(i);
                        i = prev[i];
                    }

                    for (int j = trace.getSize() - 1; j >= 0; j--) {
                        std::cout << " " << map->cityNames[trace[j]];
                    }
                }

                std::cout << "\n";
                break;
            }

            for (int i = 0; i < adjacencyList[u].getSize(); i++) {
                ListNode<Connection>* temp = adjacencyList[u][i];
                int v = temp->data.destination;
                int distance = temp->data.distance;

                if (!visited[v] && distances[v] > distances[u] + distance) {
                    prev[v] = u;
                    distances[v] = distances[u] + distance;
                    priorityQueue.push({ distances[v], v });
                }
            }
            visited[u] = true;
        }
    }
};

#endif //HOW_TO_GET_THERE_GRAPH_H
