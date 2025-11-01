#pragma once
#include <iostream>
#include <string>

class Station {
    std::string name;
    int shops_count;
    int station_class;
    int shops_in_work;

public:
    void getInfo();

    void readFromConsole();

    void changeCountOfWorkingShops();

    void saveToFile(std::ofstream& file);
    void loadFromFile(std::ifstream& file);

    Station() {
        name = "Undefined"; shops_count = 0; shops_in_work = 0; station_class = 0;
    }
};