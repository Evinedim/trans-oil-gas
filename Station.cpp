#include "Station.h"
#include "utils.h"
#include <fstream>

void Station::getInfo() {
    if (name == "Undefined" || shops_count == 0 || shops_in_work == 0 || station_class == 0) {
        std::cout << std::endl <<  "Compressor station has not been created yet or created with incorrect parameters!" << std::endl;
    } else {
        std::cout << std::endl << "--------Compressor station---------" << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Shops count: " << shops_count << std::endl;
        std::cout << "Shops in work: " << shops_in_work << std::endl;
        std::cout << "Station class: " << station_class << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }
}

void Station::readFromConsole() {
    std::cout << std::endl << "Name: "; 
    INPUT_LINE(std::cin>>std::ws, name);

    while (true) {
        std::cout << "Count of shops: ";
        if (validation(shops_count) && shops_count >= 0) {
            break;
        }
        std::cout << std::endl << "[Error] Count of shops must be integer and more than zero! Try again!" << std::endl;
    }

    while (true) {
        std::cout << "Count of working shops: ";
        if (validation(shops_in_work) && (shops_in_work >= 0 && shops_in_work <= shops_count)) {
            break;
        }
        std::cout << std::endl << "[Error] Count of working shops must be integer and less then count of shops! Try again!" << std::endl;
    }

    while (true) {
        std::cout << "Class of compressor station [1-10]: ";
        if (validation(station_class) && (station_class >= 1 && station_class <= 10)) {
            break;
        }
        std::cout << std::endl << "[Error] Class of compressor station must be integer in range [1-10]! Return to main menu!" << std::endl;
    }
}

void Station::change() {
    getInfo();
    if (name != "Undefined" || shops_count != 0 || shops_in_work != 0 || station_class != 0) {
        while (true) {
            std::cout << std::endl << "New count of working shops: ";
            if (validation(shops_in_work) && (shops_in_work >= 0 && shops_in_work <= shops_count)) {
                break;
            }
            std::cout << std::endl << "[Error] Count of working shops must be integer and less then count of shops! Try again!" << std::endl;
        }
    }
}

void Station::saveToFile(std::ofstream& file) {
    if (name == "Undefined" || shops_count == 0 || shops_in_work == 0 || station_class == 0) {
        std::cout << "[Compressor Station] There is nothing to save!" << std::endl;
    } else {
        file << name << std::endl;
        file << shops_count << std::endl;
        file << shops_in_work << std::endl; 
        file << station_class << std::endl;
        std::cout << "Compressor station was successfully saved!" << std::endl;
    }
}

void Station::loadFromFile(std::ifstream& file) {
    INPUT_LINE(file >> std::ws, name);
    if (file >> shops_count >> shops_in_work >> station_class) {
        std::cout << "Compressor station was successfully loaded!" << std::endl;
    } else {
        std::cout << std::endl << "[Error] Wrong data in file!" << std::endl;
    }
}
