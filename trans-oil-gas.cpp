#include "Pipe.h"
#include "Station.h"
#include "utils.h"
#include <map>

int main() {
    std::unordered_map<int, Pipe> pipes = {};
    std::unordered_map<int, Station> stations = {};
    system("cls");

    int choice;
    do {
        std::cout << std::endl;
        std::cout << "-------------Main menu-------------" << std::endl;
        std::cout << "[1] Create new pipe" << std::endl;
        std::cout << "[2] Create new compressor station" << std::endl;
        std::cout << "[3] Show all objects" << std::endl;
        std::cout << "[4] Edit pipes" << std::endl;
        std::cout << "[5] Edit compressor stations" << std::endl;
        std::cout << "[6] Save to file" << std::endl;
        std::cout << "[7] Load from file" << std::endl;
        std::cout << "[0] Exit" << std::endl;
        std::cout << "-----------------------------------" << std::endl;

        while (true) {
            std::cout << "Choose the option: ";
            if (validation(choice) && choice >= 0 && choice <= 7) {
                break;
            }
            std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
        }

        switch(choice) {
            case 1: {
                pipes[generateID(pipes)].readFromConsole();
                std::cout << std::endl << "Successful creation! Return to main menu!" << std::endl;
                break;
            }
            case 2: {
                stations[generateID(stations)].readFromConsole(); 
                std::cout << std::endl << "Successful creation! Return to main menu!" << std::endl;
                break;
            }
            case 3: {
                getInfo(pipes, stations);
                std::cout << std::endl << "Return to main menu!" << std::endl;
                break;
            }
            case 4:

                // pipeline.changeStatus();
                std::cout << std::endl << "Return to main menu!" << std::endl;
                break;
            case 5:
                // compressorstation.changeCountOfWorkingShops();
                // std::cout << std::endl << "Return to main menu!" << std::endl;
                break;
            case 6: {
                saveObjectsFrom(pipes, stations);
                std::cout << std::endl << "Return to main menu!" << std::endl;
                break;
            }
            case 7: {
                loadFromFileTo(pipes, stations);
                std::cout<< std::endl << "Return to main menu!" << std::endl;
                break;
            }
            case 0:
                system("cls");
                break;
        }   
    } while (choice != 0);

    return 0;
}