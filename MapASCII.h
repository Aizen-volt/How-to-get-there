#ifndef HOW_TO_GET_THERE_MAPASCII_H
#define HOW_TO_GET_THERE_MAPASCII_H

#include "Position.h"
#include "structures/Vector.h"
#include "structures/String.h"
#include "structures/Map.h"

class MapASCII {

private:
    [[nodiscard]] static bool isCityName(char c) {
        return isalpha(c) || isdigit(c);
    }


    String findCityName(int x, int y) {
        String name;

        for (int offX = -1; offX <= 1; offX++) {
            if (x + offX < 0 || x + offX >= width) {
                continue;
            }

            for (int offY = -1; offY <= 1; offY++) {
                if (y + offY < 0 || y + offY >= height) {
                    continue;
                }
                if (offX == 0 && offY == 0) {
                    continue;
                }

                if (isCityName(array[x + offX][y + offY])) {
                    // last letter
                    if (x + offX + 1 >= width || !isCityName(array[x + offX + 1][y + offY])) {
                        while (x + offX > 0 && isCityName(array[x + offX][y + offY])) {
                            name.pushFront(array[x + offX][y + offY]);
                            offX--;
                        }
                        return name;
                    }

                    // first letter
                    else if (x + offX - 1 < 0 || !isCityName(array[x + offX - 1][y + offY])) {
                        while (x + offX < width && isCityName(array[x + offX][y + offY])) {
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

    char** array;
    int width, height;
    int roadCount;

    Vector<Position> cityPositions;
    Vector<String> cityNames;
    Map cityNameToId;


    MapASCII(int width, int height) : width(width), height(height) {
        array = new char*[width];
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

        for (int y = 0; y < height; y++) {
            std::cin >> line;
            for (int x = 0; x < width; x++) {
                cell = line[x];

                if (cell == ROAD_SYMBOL) {
                    roadCount++;
                }
                else if (cell == CITY_SYMBOL) {
                    cityPositions.pushBack(Position(x, y));
                }
                array[x][y] = cell;
            }
        }

        String cityName;
        for (int i = 0; i < cityPositions.getSize(); i++) {
            cityName = findCityName(cityPositions[i].x, cityPositions[i].y);
            cityNames.pushBack(cityName);
            cityNameToId.add(cityName, i);
        }

    }
};

#endif //HOW_TO_GET_THERE_MAPASCII_H
