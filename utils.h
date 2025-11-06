#pragma once
#include "Pipe.h"
#include "Station.h"
#include <unordered_map>
#include <map>
#include <fstream>

#define INPUT_LINE(in, str) getline(in >> std::ws, str); \
						std::cerr << str << std::endl

class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
    }
	void redirect (std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};

template<typename T> 
bool validation(T& value) {
    if (std::cin >> value && std::cin.peek() == '\n') {
        std::cerr << value << std::endl;
        return 1;
    }
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    return 0;
}

template<typename T>
int generateID(std::unordered_map<int, T> &objects) {
    static int id = 1;
    return id++;
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

inline void loadFromFileTo(std::unordered_map<int, Pipe>& pipes, 
                        std::unordered_map<int, Station>& stations) {

    std::string filename;
    std::cout << std::endl << "Filename: ";
    INPUT_LINE(std::cin >> std::ws, filename);
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
    INPUT_LINE(std::cin >> std::ws, filename);
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

inline void filterPipesByStatus(std::unordered_map<int, Pipe>& pipes) {

    int choice, status;

    std::unordered_map<int, Pipe> filtered_pipes = {};

    std::cout << std::endl << "Status: ";
    if (validation(status) && status >= 0 && status <= 1) {
        for (auto& [id, pipe] : pipes) {
            if (pipe.getStatus() == status) {
                filtered_pipes[id] = pipe;
            }
        }
    } else {
        std::cout << std::endl << "[Error] Invalid value! Try again!" << std::endl;
    }

    getInfo(filtered_pipes);

    do {
        if (filtered_pipes.empty()) {
            std::cout << "Nothing was found!" << std::endl;
            break;
        }

        std::cout << std::endl << "Do you want to change the current status of all found pipes?" << std::endl;
        std::cout << "[1] Yes" << std::endl;
        std::cout << "[0] No" << std::endl;

        while (true) {
            std::cout << "Your choice: ";
            if (validation(choice) && choice >= 0 && choice <= 1) {
                break;
            }
            std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
        }

        switch (choice) {
            case 1:
                for (auto& [id, pipe] : pipes) {
                    if (pipe.getStatus() == status) {
                        std::cout << std::endl << "[" << id << "] ";
                        pipe.change();
                    }
                }
                choice = 0;
                break;
            case 0:
                break;
        }
    } while (choice != 0);
}

inline void filterStationsByCountOfWorkingShops(std::unordered_map<int, Station>& stations) {

    int choice, shops_in_work;

    std::unordered_map<int, Station> filtered_stations = {};

    std::cout << std::endl << "Count of working shops: ";
    if (validation(shops_in_work) && shops_in_work >= 0) {
        for (auto& [id, station] : stations) {
            if (station.getShopsInWork() == shops_in_work) {
                filtered_stations[id] = station;
            }
        }
    } else {
        std::cout << std::endl << "[Error] Invalid value! Try again!" << std::endl;
    }

    getInfo(filtered_stations);

    do {
        if (filtered_stations.empty()) {
            std::cout << "Nothing was found!" << std::endl;
            break;
        }

        std::cout << std::endl << "Do you want to change the current count of working shops of all found pipes?" << std::endl;
        std::cout << "[1] Yes" << std::endl;
        std::cout << "[0] No" << std::endl;

        while (true) {
            std::cout << "Your choice: ";
            if (validation(choice) && choice >= 0 && choice <= 1) {
                break;
            }
            std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
        }

        switch (choice) {
            case 1:
                for (auto& [id, station] : stations) {
                    if (station.getShopsInWork() == shops_in_work) {
                        station.change();
                    }
                }
                choice = 0;
                break;
            case 0:
                break;
        }
    } while (choice != 0);
}

template<typename T>
void filterObjectsByName(std::unordered_map<int, T>& objects) {

    int choice;
    std::string name;

    std::cout << std::endl << "Name: ";
    INPUT_LINE(std::cin >> std::ws, name);

    std::unordered_map<int, T> filtered_objects;

    for (auto& [id, object] : objects) {
        if (object.getName() == name) {
            filtered_objects[id] = object;
        }
    }

    getInfo(filtered_objects);

    do {
        if (filtered_objects.empty()) {
            std::cout << "Nothing was found!" << std::endl;
            break;
        }

        std::cout << std::endl << "Do you want to change all found objects?" << std::endl;
        std::cout << "[1] Yes" << std::endl;
        std::cout << "[0] No" << std::endl;

        while (true) {
            std::cout << "Your choice: ";
            if (validation(choice) && choice >= 0 && choice <= 1) {
                break;
            }
            std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
        }

        switch (choice) {
            case 1:
                for (auto& [id, object] : objects) {
                    if (object.getName() == name) {
                        std::cout << std::endl << "[" << id << "] ";
                        object.change();
                    }
                }
                choice = 0;
                break;
            case 0:
                break;
        }
    } while (choice != 0);
}

template<typename T>
void changeById(std::unordered_map<int, T>& objects) {
    int id;

    getInfo(objects);
    std::cout << std::endl << "Choose id of pipe: ";
    if (validation(id) && objects.count(id) != 0) {
        objects[id].change();
    } else {
        std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
    }
}

template<typename T>
void deleteObjectById(std::unordered_map<int, T>& objects) {
    int id;

    getInfo(objects);
    std::cout << std::endl << "Choose id: ";
    if (validation(id) && objects.count(id) != 0) {
        objects.erase(id);
    } else {
        std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
    }
}