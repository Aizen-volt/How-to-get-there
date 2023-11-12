#ifndef HOW_TO_GET_THERE_CONNECTION_H
#define HOW_TO_GET_THERE_CONNECTION_H

#include <iostream>

class Connection {

public:
    int source, destination, distance;

    Connection(int source, int destination, int distance) : source(source), destination(destination), distance(distance) {}

    friend std::ostream& operator<<(std::ostream& os, const Connection& connection) {
        os << "[" << connection.source << " -> " << connection.destination << " in " << connection.distance << "]";
        return os;
    }
};

#endif //HOW_TO_GET_THERE_CONNECTION_H
