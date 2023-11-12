#ifndef HOW_TO_GET_THERE_MAPASCII_H
#define HOW_TO_GET_THERE_MAPASCII_H

#include "Position.h"
#include "structures/Vector.h"
#include "structures/String.h"
#include "structures/Map.h"

class MapASCII {

private:
    [[nodiscard]] static bool isCityName(char c) {
        return std::isalpha(c) || std::isdigit(c);
    }


    [[nodiscard]] String findCityName(int x, int y) const {
        String name;

        // check cells surrounding city entrance for its name
        for (int offX = -1; offX <= 1; offX++) {
            // out of bound
            if (isOutOfBound(x + offX, y)) {
                continue;
            }

            for (int offY = -1; offY <= 1; offY++) {
                if (isOutOfBound(x, y + offY)) {
                    continue;
                }
                // skip city entrance
                if (offX == 0 && offY == 0) {
                    continue;
                }

                // letter found
                if (isCityName(array[x + offX][y + offY])) {
                    // last letter of name
                    if (isOutOfBound(x + offX + 1, y + offY) || !isCityName(array[x + offX + 1][y + offY])) {
                        // start from last letter and go backwards
                        while (!isOutOfBound(x + offX, y + offY) && isCityName(array[x + offX][y + offY])) {
                            name.pushFront(array[x + offX][y + offY]);
                            offX--;
                        }
                        return name;
                    }

                    // first letter of name
                    if (isOutOfBound(x + offX - 1, y + offY) || !isCityName(array[x + offX - 1][y + offY])) {
                        // start from first letter and go forwards
                        while (!isOutOfBound(x + offX, y + offY) && isCityName(array[x + offX][y + offY])) {
                            name.pushBack(array[x + offX][y + offY]);
                            offX++;
                        }
                        return name;
                    }
                }
            }
        }
        return name;
    }

public:
    static const char ROAD_SYMBOL = '#';
    static const char CITY_SYMBOL = '*';

    char **array;
    int width, height;
    int roadCount;

    Vector<Position> cityPositions;
    Vector<String> cityNames;
    Map cityNameToId; // city name -> city id for fast access in queries


    MapASCII(int width, int height) : width(width), height(height) {
        array = new char *[width];
        for (int i = 0; i < width; i++) {
            array[i] = new char[height];
        }

        roadCount = 0;
    }


    ~MapASCII() {
        for (int i = 0; i < width; i++) {
            delete[] array[i];
        }
        delete[] array;
    }


    void formMap() {
        char cell;
        String line;

        // read from input, count roads and mark city entrances
        for (int y = 0; y < height; y++) {
            std::cin >> line;
            for (int x = 0; x < width; x++) {
                cell = line[x];

                if (cell == ROAD_SYMBOL) {
                    roadCount++;
                } else if (cell == CITY_SYMBOL) {
                    cityPositions.pushBack(Position(x, y));
                }
                array[x][y] = cell;
            }
        }

        // for each city entrance find its name
        String cityName;
        for (int i = 0; i < cityPositions.getSize(); i++) {
            cityName = findCityName(cityPositions[i].x, cityPositions[i].y);
            cityNames.pushBack(cityName);
            cityNameToId.add(cityName, i);
        }
    }


    [[nodiscard]] bool isOutOfBound(int x, int y) const {
        return x < 0 || x >= width || y < 0 || y >= height;
    }
};

#endif //HOW_TO_GET_THERE_MAPASCII_H
