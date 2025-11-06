#include "Pipe.h"
#include "PipeManager.h"
#include "Station.h"
#include "utils.h"
#include <map>

int main() {
    std::unordered_map<int, Pipe> pipes = {};
    std::unordered_map<int, Station> stations = {};
    system("cls");

    int choice, id, pipe_choice;

    do {
        std::cout << std::endl;
        std::cout << "-------------Main menu-------------" << std::endl;
        std::cout << "[1] Create new pipe" << std::endl;
        std::cout << "[2] Create new compressor station" << std::endl;
        std::cout << "[3] Show all objects" << std::endl;
        std::cout << "[4] Pipes manager" << std::endl;
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
            case 4: {
                if (pipes.empty()) {
                    std::cout << "There is nothing to edit!" << std::endl;
                    break;
                } else {
                    do {
                        std::cout << std::endl;
                        std::cout << "-------------Pipes menu-------------" << std::endl;
                        std::cout << "[1] Filter pipes by name" << std::endl;
                        std::cout << "[2] Filter pipes by status" << std::endl;
                        std::cout << "[3] Change status of certain pipe" << std::endl;
                        std::cout << "[4] Delete certain pipe" << std::endl;
                        std::cout << "[5] Delete all pipes" << std::endl;
                        std::cout << "[0] Exit" << std::endl;
                        std::cout << "-----------------------------------" << std::endl;

                        while (true) {
                            std::cout << "Choose the option: ";
                            if (validation(pipe_choice) && pipe_choice >= 0 && pipe_choice <= 5) {
                                break;
                            }
                            std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
                        }

                        switch(pipe_choice) {
                            case 1: {                                
                                filterPipesByName(pipes);
                                break;
                            }
                            case 2: {
                                filterPipesByStatus(pipes);
                                break;
                            }
                            case 3: {
                                changeStatusById(id, pipes);
                                break;
                            }
                            case 4: {
                                deletePipeById(id, pipes);
                                break;
                            }
                            case 5: {
                                pipes.clear();
                                std::cout << std::endl << "All pipes was deleted!" << std::endl;
                                break;
                            }
                            case 0:
                                break;
                        }
                    } while (pipe_choice != 0);
                std::cout << std::endl << "Return to main menu!" << std::endl;
                }
                break;
            }
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
                break;
        }   
    } while (choice != 0);

    return 0;
}