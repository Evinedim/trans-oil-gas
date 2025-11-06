#pragma once
#include "Pipe.h"
#include "Station.h"
#include <unordered_map>
#include <map>
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

template<typename T>
void getInfo(std::unordered_map<int, T>& objects) {

    std::map<int, T> sorted_objects(
        objects.begin(), objects.end()
    );
    for (auto& [id, object] : objects) {
        std::cout << std::endl << id;
        object.getInfo();
    }
}

template<typename T, typename U>
 void getInfo(std::unordered_map<int, T>& objects1, 
            std::unordered_map<int, U>& objects2) {

    std::map<int, T> sorted_objects1(
        objects1.begin(), objects1.end()
    );
    for (auto& [id, object1] : objects1) {
        std::cout << std::endl << id;
        object1.getInfo();
    }
    std::map<int, U> sorted_objects2(
        objects2.begin(), objects2.end()
    );
    for (auto& [id, object2] : objects2) {
        std::cout << std::endl << id;
        object2.getInfo();
    }
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

inline void saveObjectsFrom(std::unordered_map<int, Pipe>& pipes, 
                        std::unordered_map<int, Station>& stations) {
    
    std::string filename;
    std::cout << std::endl << "Filename: ";
    std::getline(std::cin >> std::ws, filename);
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << std::endl << "[Error] File was not opened!" << std::endl; 
    } else {
        for (auto& [id, pipe] : pipes) {
            file << "Pipe" << std::endl << id << std::endl;
            pipe.saveToFile(file);
        }
        for (auto& [id, station] : stations) {
            file << "Station" << std::endl << id << std::endl;
            station.saveToFile(file);
        } 
    }
}