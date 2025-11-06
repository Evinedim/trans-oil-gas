#include "Pipe.h"
#include "Station.h"
#include "utils.h"
#include <map>
#include <chrono>
#include <format>

int main() {

    redirect_output_wrapper cerr_out(std::cerr);
	std::string time = std::format("{:%d_%m_%Y %H_%M_%OS}", std::chrono::system_clock::now());
	std::ofstream logfile("log_"+ time);
	if (logfile)
		cerr_out.redirect(logfile);

    std::unordered_map<int, Pipe> pipes = {};
    std::unordered_map<int, Station> stations = {};
    system("cls");

    int choice, id, pipe_choice, station_choice;

    do {
        std::cout << std::endl;
        std::cout << "-------------Main menu-------------" << std::endl;
        std::cout << "[1] Create new pipe" << std::endl;
        std::cout << "[2] Create new compressor station" << std::endl;
        std::cout << "[3] Show all objects" << std::endl;
        std::cout << "[4] Pipes manager" << std::endl;
        std::cout << "[5] Compressor stations manager" << std::endl;
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
                if (pipes.empty()) {
                    std::cout << std::endl << "No one pipe was created!" << std::endl; 
                }
                getInfo(pipes);

                if (stations.empty()) {
                    std::cout << std::endl << "No one station was created!" << std::endl; 
                }
                getInfo(stations);

                std::cout << std::endl << "Return to main menu!" << std::endl;
                break;
            }
            case 4: {
                if (pipes.empty()) {
                    std::cout << std::endl << "List of pipes is empty!" << std::endl;
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
                                filterObjectsByName(pipes);
                                break;
                            }
                            case 2: {
                                filterPipesByStatus(pipes);
                                break;
                            }
                            case 3: {
                                changeById(id, pipes);
                                break;
                            }
                            case 4: {
                                deleteObjectById(id, pipes);
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
                if (stations.empty()) {
                    std::cout << std::endl << "List of stations is empty!" << std::endl;
                    break;
                } else {
                    do {
                        std::cout << std::endl;
                        std::cout << "------------------Stations menu-------------------" << std::endl;
                        std::cout << "[1] Filter stations by name" << std::endl;
                        std::cout << "[2] Filter stations by count of shops in work" << std::endl;
                        std::cout << "[3] Change count shops in work of certain station" << std::endl;
                        std::cout << "[4] Delete certain station" << std::endl;
                        std::cout << "[5] Delete all stations" << std::endl;
                        std::cout << "[0] Exit" << std::endl;
                        std::cout << "--------------------------------------------------" << std::endl;

                        while (true) {
                            std::cout << "Choose the option: ";
                            if (validation(station_choice) && station_choice >= 0 && station_choice <= 5) {
                                break;
                            }
                            std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
                        }

                        switch(station_choice) {
                            case 1: {                                
                                filterObjectsByName(stations);
                                break;
                            }
                            case 2: {
                                filterStationsByCountOfWorkingShops(stations);
                                break;
                            }
                            case 3: {
                                changeById(id, stations);
                                break;
                            }
                            case 4: {
                                deleteObjectById(id, stations);
                                break;
                            }
                            case 5: {
                                stations.clear();
                                std::cout << std::endl << "All stations was deleted!" << std::endl;
                                break;
                            }
                            case 0:
                                break;
                        }
                    } while (station_choice != 0);
                std::cout << std::endl << "Return to main menu!" << std::endl;
                }
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