#ifndef NEWMAPPER_CITYNAMETOPOSITIONHASH_H
#define NEWMAPPER_CITYNAMETOPOSITIONHASH_H

#include "String.h"


typedef struct HashPair {
    String name;
    int id;
} HashPair;


class CityNameToPositionHash {
private:
    List<HashPair>* cities;

    static int Hash(const String& name) {
        int index = 0;
        int length = name.GetLength();
        for (int i = 0; i < length; i++) {
            index += (i + 1) * name[i];
        }
        return index;
    }
public:
    CityNameToPositionHash() {
        cities = new List<HashPair>[256 *  30];
    }

    ~CityNameToPositionHash() {
        delete[] cities;
    }

    void AddToMap(const String& name, int x, int y, int id) {
        int index = Hash(name);
        HashPair temp {name, id};
        cities[index].PushBack(temp);
    }

    int Find(const String& name) {
        int index = Hash(name);
        Node<HashPair>* current = cities[index].head;
        while (current != nullptr) {
            if (current->data.name == name)
                return current->data.id;
            current = current->next;
        }
        return 0;
    }
};

#endif //NEWMAPPER_CITYNAMETOPOSITIONHASH_H
