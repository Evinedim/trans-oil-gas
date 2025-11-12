#pragma once
#include <iostream>
#include <string>

class Pipe {
    std::string name;
    double length;
    int diameter;
    bool status;

public:
    std::string getName() { return name; }

    int getStatus() { return status; }

    void getInfo();

    void readFromConsole();

    void changeStatus();

    void saveToFile(std::ofstream& file);
    void loadFromFile(std::ifstream& file);

    Pipe() {
        name = "Undefined"; length = 0.0; diameter = 0; status = false;
    }
};
