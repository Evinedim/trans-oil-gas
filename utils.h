#pragma once
#include "Pipe.h"
#include "Station.h"
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <functional>

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

template<typename T>
int generateID(std::unordered_map<int, T> &objects) {
    static int id = 1;
    while (objects.count(id) != 0) {
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

template<typename T>
std::unordered_set<int> getFilteredIds(std::unordered_map<int, T>& objects, std::function<bool(T&)> predicate) {
    
    std::unordered_set<int> ids = {};
    for (auto& [id, object] : objects) {
        if (predicate(object)) {
            std::cout << std::endl << id;
            object.getInfo();
            ids.insert(id);
        }
    }

    return ids;
}

inline void changePipeById(std::unordered_map<int, Pipe>& pipes) {
    int id;

    getInfo(pipes);
    std::cout << std::endl << "Choose id of pipe: ";
    if (validation(id) && pipes.count(id) != 0) {
        std::cout << std::endl << "[" << id << "]" << std::endl;
        pipes[id].changeStatus();
    } else {
        std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
    }
}

inline void changeAllPipes(std::unordered_map<int, Pipe>& pipes) {

    getInfo(pipes);
    for (auto& [id, pipe] : pipes) {
        std::cout << std::endl << "[" << id << "]" << std::endl;
        pipes[id].changeStatus();
    }
}

inline std::unordered_set<int> getNumberSeparatedBySpace() {
    
    std::unordered_set<int> numbers;
    std::string line;
    int number;

    INPUT_LINE(std::cin >> std::ws, line);

    std::stringstream stream(line);

    while (stream >> number) {
        numbers.insert(number);
    }
    
    return numbers;
}

inline void changeAllFoundPipes(std::unordered_map<int, Pipe>& pipes, std::unordered_set<int> ids) {

    int choice;

    std::cout << std::endl << "Do you want to change found pipes?" << std::endl;
    std::cout << "[1] Yes (All)" << std::endl;
    std::cout << "[2] Yes (Certain)" << std::endl;
    std::cout << "[0] No" << std::endl;
    std::cout << "Your choice: ";

    if (validation(choice)) {
        if (choice == 1) {
            for (auto& id : ids) {
                std::cout << std::endl << "[" << id << "]";
                pipes[id].changeStatus();
            }
        }
        if (choice == 2) {
            std::cout << "Enter ids separeted by space: ";
            std::unordered_set<int> subset_ids = getNumberSeparatedBySpace();
            for (auto& id : subset_ids) {
                if (ids.count(id) != 0) {
                    pipes[id].changeStatus();
                }
            }
        }
        if (choice == 0) {
            std::cout << std::endl << "Nothing was changed!" << std::endl;
        }
    } else {
        std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
    }
}

inline void filterPipesByName(std::unordered_map<int, Pipe>& pipes) {

    std::string name;

    std::cout << std::endl << "Name: ";
    INPUT_LINE(std::cin >> std::ws, name);

    std::function<bool(Pipe&)> predicate = [&name](Pipe pipe) { return name == pipe.getName(); };

    std::unordered_set<int> ids = getFilteredIds(pipes, predicate);

    if (ids.empty()) {
        std::cout << std::endl << "Nothing was found!" << std::endl;
    } else {
        changeAllFoundPipes(pipes, ids);
    }
}

inline void filterPipesByStatus(std::unordered_map<int, Pipe>& pipes) {

    int status;
    std::cout << std::endl << "Status: ";

    if (!(validation(status) && status >= 0 && status <= 1)) {
        std::cout << std::endl << "[Error] Invalid value! Try again!" << std::endl;
    }

    std::function<bool(Pipe&)> predicate = [&status](Pipe pipe) { return status == pipe.getStatus(); };
    std::unordered_set<int> ids = getFilteredIds(pipes, predicate);

    if (ids.empty()) {
        std::cout << std::endl << "Nothing was found!" << std::endl;
    } else {
        changeAllFoundPipes(pipes, ids);
    }
}

inline void changeStationsById(std::unordered_map<int, Station>& stations) {
    int id;

    getInfo(stations);
    std::cout << std::endl << "Choose id of station: ";
    if (validation(id) && stations.count(id) != 0) {
        std::cout << std::endl << "[" << id << "]" << std::endl;
        stations[id].changeShopsInWorkCount();
    } else {
        std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
    }
}

inline void changeAllFoundStations(std::unordered_map<int, Station>& stations, std::unordered_set<int> ids) {

    int choice;

    std::cout << std::endl << "Do you want to change all found stations?" << std::endl;
    std::cout << "[1] Yes" << std::endl;
    std::cout << "[0] No" << std::endl;
    std::cout << "Your choice: ";

    if (validation(choice) && choice >= 0 && choice <= 1) {
        if (choice == 1) {
            for (auto& id : ids) {
                std::cout << std::endl << "[" << id << "]" << std::endl;
                stations[id].changeShopsInWorkCount();
            }
        } 
        if (choice == 0) {
            std::cout << std::endl << "Nothing was changed!" << std::endl;
        }
    } else {
        std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
    }
}

inline void filterStationsByName(std::unordered_map<int, Station>& stations) {

    std::string name;

    std::cout << std::endl << "Name: ";
    INPUT_LINE(std::cin >> std::ws, name);

    std::function<bool(Station&)> predicate = [&name](Station station) { return name == station.getName(); };

    std::unordered_set<int> ids = getFilteredIds(stations, predicate);

    if (ids.empty()) {
        std::cout << std::endl << "Nothing was found!" << std::endl;
    } else {
        changeAllFoundStations(stations, ids);
    }
}

inline void filterStationsByShopsInWorkCount(std::unordered_map<int, Station>& stations) {

    int shops_in_work;
    std::cout << std::endl << "Count of shops in work: ";

    if (!(validation(shops_in_work))) {
        std::cout << std::endl << "[Error] Invalid value! Try again!" << std::endl;
    }

    std::function<bool(Station&)> predicate = [&shops_in_work](Station station) { return shops_in_work == station.getShopsInWorkCount(); };
    std::unordered_set<int> ids = getFilteredIds(stations, predicate);

    if (ids.empty()) {
        std::cout << std::endl << "Nothing was found!" << std::endl;
    } else {
        changeAllFoundStations(stations, ids);
    }
}