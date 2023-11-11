#ifndef HOW_TO_GET_THERE_MAPNODE_H
#define HOW_TO_GET_THERE_MAPNODE_H

#include "String.h"

class MapNode {

public:
    String key;
    int value;

    explicit MapNode(const String& key, int value) : key(key), value(value) {}

    bool operator==(const MapNode& right) const {
        return key == right.key;
    }
};

#endif //HOW_TO_GET_THERE_MAPNODE_H
