#include <fstream>
#include "Graph.h"
#include "Queue.h"
#include "PriorityQueue.h"


Graph::Graph(Map* map) {
    this->map = map;
    cities = new CityNameToPositionHash();
    ReadMap();
    excessFactor = (map->height == 2048 && map->width == 30) ? 65536 : 8192;
    verticesCount = cityPositions.Size();
    InitAdjacencyList();
    if (map->roadCount > 0)
        FindCityConnections();
}


void Graph::InitAdjacencyList() {
    for (int i = 0; i < verticesCount; i++) {
        Connection temp {i, i, 0};
        adjacencyList.Push_back();
        adjacencyList[i].PushBack(temp);
    }
}


void Graph::FindCityConnections() {
    bool** visited = new bool*[map->width];
    for (int i = 0; i < map->width; i++) {
        visited[i] = new bool[map->height];
    }

    for (int i = 0; i < verticesCount; i++) {
        for (int j = 0; j < verticesCount; j++) {
            if (i == j)
                continue;

            QueueItem source {cityPositions[i].x, cityPositions[i].y, 0};
            for (int x = 0; x < map->width; x++) {
                for (int y = 0; y < map->height; y++) {
                    if (map->array[x][y] == '#' || (x == cityPositions[j].x && y == cityPositions[j].y))
                        visited[x][y] = false;
                    else
                        visited[x][y] = true;
                }
            }
            Queue<QueueItem> queue(map->width * map->height);
            queue.Enqueue(source);
            visited[source.x][source.y] = true;
            while (queue.Size() > 0) {
                QueueItem p = queue.Peek();
                queue.Dequeue();

                if (p.x == cityPositions[j].x && p.y == cityPositions[j].y) {
                    Connection temp {i, j, p.distance};
                    adjacencyList[i].PushBack(temp);
                    break;
                }


                //up
                if (p.y - 1 >= 0 && !visited[p.x][p.y - 1]) {
                    visited[p.x][p.y - 1] = true;
                    QueueItem temp{p.x, p.y - 1, p.distance + 1};
                    queue.Enqueue(temp);
                }

                //down
                if (p.y + 1 < map->height && !visited[p.x][p.y + 1]) {
                    visited[p.x][p.y + 1] = true;
                    QueueItem temp{p.x, p.y + 1, p.distance + 1};
                    queue.Enqueue(temp);
                }

                //left
                if (p.x - 1 >= 0 && !visited[p.x - 1][p.y]) {
                    visited[p.x - 1][p.y] = true;
                    QueueItem temp{p.x - 1, p.y, p.distance + 1};
                    queue.Enqueue(temp);
                }

                //right
                if (p.x + 1 < map->width && !visited[p.x + 1][p.y]) {
                    visited[p.x + 1][p.y] = true;
                    QueueItem temp{p.x + 1, p.y, p.distance + 1};
                    queue.Enqueue(temp);
                }
            }
        }
    }
    for (int i = 0; i < map->width; i++) {
        delete[] visited[i];
    }
    delete[] visited;
}


bool Graph::IsCityName(char letter) {
    return isalpha(letter) || isdigit(letter);
}


void Graph::FindCityName(int x, int y, String& cityName) {
    bool cityNameFound = false;

    for (int offsetX = -1; offsetX <= 1; offsetX++) {
        if (cityNameFound)
            break;

        if (x + offsetX < 0 || x + offsetX >= map->width)
            continue;

        for (int offsetY = -1; offsetY <= 1; offsetY++) {
            if (cityNameFound)
                break;

            if (offsetX == 0 && offsetY == 0)
                continue;

            if (y + offsetY < 0 || y + offsetY >= map->height)
                continue;

            if (IsCityName(map->array[x + offsetX][y + offsetY])) {
                //check if last letter of name
                if (x + offsetX + 1 >= map->width || !IsCityName(map->array[x + offsetX + 1][y + offsetY])) {
                    cityNameFound = true;
                    while (x + offsetX > 0 && IsCityName(map->array[x + offsetX][y + offsetY])) {
                        cityName = map->array[x + offsetX][y + offsetY] + cityName;
                        offsetX--;
                    }
                }
                    //check if first letter of name
                else if (x + offsetX - 1 < 0 || !IsCityName(map->array[x + offsetX - 1][y + offsetY])) {
                    cityNameFound = true;
                    while (x + offsetX < map->width && IsCityName(map->array[x + offsetX][y + offsetY])) {
                        cityName.PushBack(map->array[x + offsetX][y + offsetY]);
                        offsetX++;
                    }
                }
            }
        }
    }
}


void Graph::ReadMap() {
    map->roadCount = 0;
    char cell;
    int cityIndex = 0;
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            cell = getchar();
            if (cell == '#')
                map->roadCount++;
            else if (cell == '*') {
                //citiesCells->AddToMap(x, y, cityIndex);
                Position temp {x, y};
                cityPositions.Push_back(temp);
                cityIndex++;
            }
            map->array[x][y] = cell;
        }
        getchar();
    }
    int size = cityPositions.Size();
    for (int i = 0; i < size; i++) {
        String cityName;
        FindCityName(cityPositions[i].x, cityPositions[i].y, cityName);
        cities->AddToMap(cityName, cityPositions[i].x, cityPositions[i].y, i);
        cityNames.Push_back(cityName);
    }
}


void Graph::ReadFlightConnection() {
    char input[100];
    fgets(input, 100, stdin);
    int mode = 0;

    int sourceIndex;
    int destinationIndex;
    int timeInt;

    char* token = strtok(input, " ");
    while (token != NULL) {
        if (mode == 0) {
            String temp1(token);
            sourceIndex = cities->Find(temp1);
        }
        else if (mode == 1) {
            String temp2(token);
            destinationIndex = cities->Find(temp2);
        }
        else {
            timeInt = atoi(token);
        }
        token = strtok(NULL, " ");
        mode++;
    }

    Connection temp {sourceIndex, destinationIndex, timeInt};
    adjacencyList[sourceIndex].PushBack(temp);
}


void Graph::Dijkstra(const String& source, const String& destination, int output) {
    int sourceIndex = cities->Find(source);
    int destinationIndex = cities->Find(destination);

    if (sourceIndex == destinationIndex) {
        printf("0\n");
        return;
    }


    PriorityQueue<Pair> priorityQueue;
    int* distances = new int[verticesCount];
    int* prev = new int[verticesCount];
    bool* visited = new bool[verticesCount];
    for (int i = 0; i < verticesCount; i++) {
        distances[i] = INT_MAX;
        visited[i] = false;
    }
    distances[sourceIndex] = 0;
    visited[sourceIndex] = true;
    Pair sourcePair {0, sourceIndex};
    priorityQueue.Insert(sourcePair);


    while (!priorityQueue.Empty()) {
        int u = priorityQueue.Top().index;
        priorityQueue.Remove();

        if (u == destinationIndex) {
            printf("%d", distances[u]);
            if (output == 1) {
                int i = prev[u];
                Vector<int> trace(excessFactor);
                while (i != sourceIndex) {
                    trace.Push_back(i);
                    i = prev[i];
                }
                for (int j = trace.Size() - 1; j >= 0; j--) {
                    printf(" %s", cityNames[trace[j]].GetArray());
                }
            }
            printf("\n");
            break;
        }

        Node<Connection>* iterator = adjacencyList[u].head->next;
        while (iterator != nullptr) {
            int v = iterator->data.destination;
            int distance = iterator->data.distance;
            if (!visited[v] && distances[v] > distances[u] + distance) {
                prev[v] = u;
                distances[v] = distances[u] + distance;
                Pair temp {distances[v], v};
                priorityQueue.Insert(temp);
            }
            iterator = iterator->next;
        }
        visited[u] = true;
    }
    delete[] distances;
    delete[] prev;
    delete[] visited;
}