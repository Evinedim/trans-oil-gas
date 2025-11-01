#pragma once
#include "Pipe.h"
#include "Station.h"
#include <unordered_map>
#include <fstream>

template<typename T> 
bool validation(T& value) {
    if (std::cin >> value && std::cin.peek() == '\n') {
        return 1;
    }
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    return 0;
}

template<typename T>
int generateID(std::unordered_map<int, T> &objects) {
    int id = 0;
    while (objects.count(id)) {
        id++;
    }
    return id;
}

inline void loadFromFileTo(std::unordered_map<int, Pipe>& pipes, 
                        std::unordered_map<int, Station>& stations) {

    std::string filename;
    std::cout << std::endl << "Filename: ";
    std::getline(std::cin >> std::ws, filename);
    std::ifstream file(filename);

    std::string line;
    int id;
    if (!file.is_open()) {
        std::cout << std::endl << "[Error] File was not opened!" << std::endl; 
    } else {  
        while (file >> line >> id) {
            if (line == "Pipe") { 
                pipes[id].loadFromFile(file); 
            }
            if (line == "Station") { 
                stations[id].loadFromFile(file); 
            }
        }
    }
}