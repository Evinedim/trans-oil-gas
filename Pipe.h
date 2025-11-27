#pragma once
#include <iostream>
#include <string>
#include <limits>

class Pipe {
    std::string name;
    double length;
    int diameter;
    bool status;

public:
    int cs_in = 0;
    int cs_out = 0;

    std::string getName() { return name; }

    double getLength() { return length; }

    double getCost() {
        if (status == 1) {
            return std::numeric_limits<double>::max();
        }
        return length; 
    }

    bool getStatus() { return status; }

    void getInfo();

    void readFromConsole();

    void changeStatus();

    void saveToFile(std::ofstream& file);
    void loadFromFile(std::ifstream& file);

    Pipe() {
        name = "Undefined"; length = 0.0; diameter = 0; status = false;
    }
};
