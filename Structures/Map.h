#ifndef HOW_TO_GET_THERE_MAP_H
#define HOW_TO_GET_THERE_MAP_H

#include "MapNode.h"
#include "List.h"
#include "Vector.h"

class Map {

private:
    static const size_t DEFAULT_SIZE = 256;
    Vector<List<MapNode>> cities;


    size_t hash(const String& key) {
        size_t index = 0;

        for (size_t i = 0; i < key.getSize(); i++) {
            index += (i + 1) * key[i];
        }
        return index % cities.getSize();
    }

public:
    explicit Map(size_t size = DEFAULT_SIZE) {
        cities = Vector<List<MapNode>>(size);
    }


    void add(const String& key, int value) {
        cities[hash(key)].pushBack(MapNode(key, value));
    }


    int find(const String& key) {
        size_t mapIndex = hash(key);
        size_t dataIndex = cities[mapIndex].find(MapNode(key, 0));
        if (dataIndex == cities[mapIndex].getSize() + 1) {
            return -1;
        }
        return cities[mapIndex][dataIndex]->data.value;
    }
};

#endif //HOW_TO_GET_THERE_MAP_H
