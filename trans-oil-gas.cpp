#include "Pipe.h"
#include "Station.h"
#include "Network.h"
#include "utils.h"
#include <map>
#include <chrono>
#include <format>

int main() {

    redirect_output_wrapper cerr_out(std::cerr);

    auto utc0 = std::chrono::system_clock::now();
    auto utc3 = utc0 + std::chrono::hours(3);

	std::string time = std::format("{:%d_%m_%Y %H_%M_%OS}", utc3);

	std::ofstream logfile("logfiles/log " + time + ".txt");
	if (logfile) { 
        cerr_out.redirect(logfile); 
    }

    std::unordered_map<int, Pipe> pipes = {};
    std::unordered_map<int, Station> stations = {};

    Network network = Network(pipes, stations);

    system("cls");

    int choice, pipe_choice, station_choice, network_choice;

    do {
        std::cout << std::endl;
        std::cout << "-------------Main menu-------------" << std::endl;
        std::cout << "[1] Create new pipe" << std::endl;
        std::cout << "[2] Create new compressor station" << std::endl;
        std::cout << "[3] Show all objects" << std::endl;
        std::cout << "[4] Pipes manager" << std::endl;
        std::cout << "[5] Compressor stations manager" << std::endl;
        std::cout << "[6] Transportation network manager" << std::endl;
        std::cout << "[7] Save to file" << std::endl;
        std::cout << "[8] Load from file" << std::endl;
        std::cout << "[0] Exit" << std::endl;
        std::cout << "-----------------------------------" << std::endl;

        while (true) {
            std::cout << "Choose the option: ";
            if (validation(choice) && choice >= 0 && choice <= 8) {
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
                        std::cout << "[4] Change status of all pipes" << std::endl;
                        std::cout << "[5] Delete certain pipe" << std::endl;
                        std::cout << "[6] Delete all pipes" << std::endl;
                        std::cout << "[0] Exit" << std::endl;
                        std::cout << "-----------------------------------" << std::endl;

                        while (true) {
                            std::cout << "Choose the option: ";
                            if (validation(pipe_choice) && pipe_choice >= 0 && pipe_choice <= 6) {
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
                                changePipeById(pipes);
                                break;
                            }
                            case 4: {
                                changeAllObjects(pipes);
                                break;
                            }
                            case 5: {
                                deleteObjectById(pipes);
                                break;
                            }
                            case 6: {
                                pipes.clear();
                                std::cout << std::endl << "All pipes was deleted!" << std::endl;
                                break;
                            }
                            case 0:
                                break;
                        }

                        if (pipe_choice != 0) {
                            std::cout << std::endl << "Return to pipes menu!" << std::endl;
                        }

                    } while (pipe_choice != 0);
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
                        std::cout << "--------------------Stations menu---------------------" << std::endl;
                        std::cout << "[1] Filter stations by name" << std::endl;
                        std::cout << "[2] Filter stations by count of shops in work" << std::endl;
                        std::cout << "[3] Change count of shops in work of certain station" << std::endl;
                        std::cout << "[4] Change count of shops in work of all stations" << std::endl;
                        std::cout << "[5] Delete certain station" << std::endl;
                        std::cout << "[6] Delete all stations" << std::endl;
                        std::cout << "[0] Exit" << std::endl;
                        std::cout << "------------------------------------------------------" << std::endl;

                        while (true) {
                            std::cout << "Choose the option: ";
                            if (validation(station_choice) && station_choice >= 0 && station_choice <= 6) {
                                break;
                            }
                            std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
                        }

                        switch(station_choice) {
                            case 1: {                                
                                filterStationsByName(stations);
                                break;
                            }
                            case 2: {
                                filterStationsByShopsInWorkCount(stations);
                                break;
                            }
                            case 3: {
                                changeStationsById(stations);
                                break;
                            }
                            case 4: {
                                deleteObjectById(stations);
                                break;
                            }
                            case 5: {
                                deleteObjectById(stations);
                                break;
                            }
                            case 6: {
                                stations.clear();
                                std::cout << std::endl << "All stations was deleted!" << std::endl;
                                break;
                            }
                            case 0:
                                break;
                        }

                        if (station_choice != 0) {
                            std::cout << std::endl << "Return to stations menu!" << std::endl;
                        }
                    } while (station_choice != 0);
                }
                break;
            case 6: {
                if (stations.empty() || stations.size() < 2 || pipes.size() < 1) {
                    std::cout << std::endl << "Count of object is less than required to create a network!!!" << std::endl;
                } else {
                    do {
                        std::cout << std::endl;
                        std::cout << "--------------Network menu---------------" << std::endl;
                        std::cout << "[1] Create connection" << std::endl;
                        std::cout << "[2] Delete connection" << std::endl;
                        std::cout << "[3] Show network" << std::endl;
                        std::cout << "[4] Show sorted network" << std::endl;
                        std::cout << "[0] Exit" << std::endl;
                        std::cout << "-----------------------------------------" << std::endl;

                        while (true) {
                            std::cout << "Choose the option: ";
                            if (validation(network_choice) && network_choice >= 0 && network_choice <= 4) {
                                break;
                            }
                            std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
                        }

                        switch(network_choice) {
                            case 1: {
                                network.createConnection();
                                break;
                            }
                            case 2: {
                                network.deleteConnection();
                                break;
                            }
                            case 3: {
                                network.showNetwork();
                                break;
                            }
                            case 4: {
                                network.showTopologicalSortedNetwork();
                                break;
                            }
                            case 0:
                                break;
                        }

                        if (network_choice != 0) {
                            std::cout << std::endl << "Return to network menu!" << std::endl;
                        }
                    } while (network_choice != 0);
                }
                break;
            }
            case 7: {
                saveObjectsFrom(pipes, stations);
                break;
            }
            case 8: {
                loadFromFileTo(pipes, stations);
                break;
            }
            case 0:
                break;
        }

        if (choice != 0) {
            std::cout << std::endl << "Return to main menu!" << std::endl;  
        } 

    } while (choice != 0);

    return 0;
}