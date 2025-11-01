#include "Pipe.h"
#include "utils.h"
#include <fstream>

void Pipe::getInfo() {
    if (name == "Undefined" || length == 0.0 || diameter == 0) {
        std::cout << std::endl << "Pipe has not been created yet or created with incorrect parameters!" << std::endl;
    } else {
        std::cout << std::endl << "---------------Pipe----------------" << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Length: " << length << " km" << std::endl;
        std::cout << "Diameter: " << diameter << " mm" << std::endl;
        if (status == false) {
            std::cout << "Status: not on repair" << std::endl;
        } else {
            std::cout << "Status: on repair" << std::endl;
        }
        std::cout << "-----------------------------------" << std::endl;
    }
}

void Pipe::readFromConsole() {
    std::cout << std::endl << "Name: "; 
    std::getline(std::cin >> std::ws, name);

    while (true) {
        std::cout << "Length ('km'): ";
        if (validation(length) && length >= 0) {
            break;
        }
        std::cout << std::endl << "[Error] Length must be double and more than zero! Try again!" << std::endl;
    }

    while (true) {
        std::cout << "Diameter ('mm'): ";
        if (validation(diameter) && diameter >= 0) {
            break;
        }
        std::cout << std::endl << "[Error] Diameter must be integer and more than zero! Try again!" << std::endl;
    }
}

void Pipe::changeStatus() {
    getInfo();
    if (name != "Undefined" || length != 0.0 || diameter != 0) {
        int choice;
        do {
            std::cout << std::endl << "Change the current status?" << std::endl;
            std::cout << "[1] Yes" << std::endl;
            std::cout << "[0] No" << std::endl;

            while (true) {
                std::cout << "Your choice: ";
                if (validation(choice) && choice >= 1 && choice <= 2) {
                    break;
                }
                std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
            }

            switch (choice) {
                case 1:
                    status = !status;
                    std::cout << std::endl << "Pipe status has been changed!" << std::endl;
                    choice = 0;
                    break;
                case 0:
                    break;
            }
        } while (choice != 0);
    }
}

void Pipe::saveToFile(std::ofstream& file) {
    if (name == "Undefined" || length == 0.0 || diameter == 0) {
        std::cout << std::endl << "[Pipe] There is nothing to save!" << std::endl;
    } else {
        file << "Pipeline" << std::endl;
        file << name << std::endl; 
        file << length << std::endl;
        file << diameter << std::endl;
        file << status << std::endl;
        std::cout << std::endl << "Pipe was successfully saved!" << std::endl;
    }
}

void Pipe::loadFromFile(std::ifstream& file) {
    std::getline(file >> std::ws, name);
    if (file >> length >> diameter >> status) {
        std::cout << std::endl << "Pipe was successfully loaded!" << std::endl;
    } else {
        std::cout << std::endl << "[Error] Wrong data in file!" << std::endl;
    }
}
