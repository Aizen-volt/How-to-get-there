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


    void addCellToQueue(Queue<std::pair<Position, int>>& queue, std::pair<Position, int>& p, bool** visited, int x, int y) {
        if (!map->isOutOfBound(p.first.x + x, p.first.y + y) && !visited[p.first.x + x][p.first.y + y]) {
            visited[p.first.x + x][p.first.y + y] = true;
            std::pair<Position, int> temp = {Position(p.first.x + x, p.first.y + y), p.second + 1};
            queue.push(temp);
        }
    }


    // BFS from every city to every other city
    void bfs() {
        bool** visited = new bool*[map->width];
        for (int i = 0; i < map->width; i++) {
            visited[i] = new bool[map->height];
        }

        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                // no need to check path to itself
                if (i == j) {
                    continue;
                }

                // represents source city and distance to it
                std::pair<Position, int> source = {Position(map->cityPositions[i].x, map->cityPositions[i].y), 0};

                // reset visited array, only roads and target city should be visitable
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

                // represents cell and its distance to source
                Queue<std::pair<Position, int>> queue;
                queue.push(source);

                // mark source as visited to avoid infinite loop
                visited[source.first.x][source.first.y] = true;

                while (!queue.empty()) {
                    // pick path
                    std::pair<Position, int> p = queue.peek();
                    queue.pop();

                    // check if target city is reached
                    if (p.first.x == map->cityPositions[j].x && p.first.y == map->cityPositions[j].y) {
                        adjacencyList[i].pushBack(Connection(i, j, p.second));
                        break;
                    }

                    // check all 4 directions for possible path

                    // up
                    addCellToQueue(queue, p, visited, 0, -1);

                    // down
                    addCellToQueue(queue, p, visited, 0, 1);

                    // left
                    addCellToQueue(queue, p, visited, -1, 0);

                    // right
                    addCellToQueue(queue, p, visited, 1, 0);
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
        vertices = map->cityPositions.getSize();

        createAdjacencyList();

        // no need to find road connections if there are no roads
        if (map->roadCount > 0) {
            bfs();
        }
    }


    // read flight connection and add it to adjacency list
    void readFlightConnection() {
        String source, destination;
        int distance;
        std::cin >> source >> destination >> distance;

        // convert city names to ids
        int sourceIndex = map->cityNameToId.find(source);
        int destinationIndex = map->cityNameToId.find(destination);

        adjacencyList[sourceIndex].pushBack(Connection(sourceIndex, destinationIndex, distance));
    }


    void printShortestPath() {
        String source, destination;
        bool showPath;

        std::cin >> source >> destination >> showPath;

        // convert city names to ids
        int sourceIndex = map->cityNameToId.find(source);
        int destinationIndex = map->cityNameToId.find(destination);

        // no need to find path if source and destination are the same
        if (sourceIndex == destinationIndex) {
            std::cout<< "0\n";
            return;
        }

        // pair represents distance and vertex
        PriorityQueue<std::pair<int, int>> priorityQueue;

        Vector<int> distances(vertices); // distance from source to every other vertex
        Vector<int> prev(vertices); // previous vertex in path, used to print path
        Vector<bool> visited(vertices); // visited vertices

        // mark initial distances as infinity and visited as false
        for (int i = 0; i < vertices; i++) {
            distances[i] = INT_MAX;
            visited[i] = false;
        }

        // set distance to source as 0 and mark it as visited
        distances[sourceIndex] = 0;
        visited[sourceIndex] = true;
        priorityQueue.push({ 0, sourceIndex });

        // Dijkstra's algorithm
        while (!priorityQueue.empty()) {
            // pick vertex with the smallest distance
            int u = priorityQueue.peek().second;
            priorityQueue.pop();

            // check if destination is reached
            if (u == destinationIndex) {
                // print distance from source to destination
                std::cout << distances[u];

                // print path if needed
                if (showPath) {
                    // begin from destination
                    int i = prev[u];
                    Vector<int> trace;

                    // backtrack to source
                    while (i != sourceIndex) {
                        trace.pushBack(i);
                        i = prev[i];
                    }

                    // print trace in reverse order to get path from source
                    for (int j = trace.getSize() - 1; j >= 0; j--) {
                        std::cout << " " << map->cityNames[trace[j]];
                    }
                }

                std::cout << "\n";
                break;
            }

            for (int i = 0; i < adjacencyList[u].getSize(); i++) {
                // get adjacent vertex and distance to it
                ListNode<Connection>* temp = adjacencyList[u][i];
                int v = temp->data.destination;
                int distance = temp->data.distance;

                // check if vertex is not visited and if distance can be updated
                if (!visited[v] && distances[v] > distances[u] + distance) {
                    prev[v] = u;
                    distances[v] = distances[u] + distance;

                    // add vertex to priority queue only if distance is smaller
                    priorityQueue.push({ distances[v], v });
                }
            }
            visited[u] = true;
        }
    }
};

#endif //HOW_TO_GET_THERE_GRAPH_H
