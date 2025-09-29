#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>

template<typename T> bool validation(T& value) {
    if (std::cin >> value) {
        return true;
    }
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    return false;
}

class Pipeline {
    double length;
    int diameter;

public:    
    std::string name;
    bool status;

    void getInfo() {
        if (name == "Undefined" || length == 0.0 || diameter == 0) {
            std::cout << "Pipeline has not been created yet or created with incorrect parameters!" << std::endl;
        } else {
            std::cout << std::endl << "-------------Pipeline--------------" << std::endl;
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

    void readFromConsole() {
        std::cout << std::endl << "Name: "; 
        std::cin.ignore(); 
        std::getline(std::cin, name);

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

    void saveToFile(std::string filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << "P," << name << "," << length << "," << diameter << "," << status << std::endl;
        }
        file.close();
        std::cout << "Pipeline was successfully saved!" << std::endl;
    }

    void loadFromFile(std::string filename) {
        std::ifstream file("save-load-file.txt");
        std::vector<std::string> lines;
        std::string line;
        int current_line = 1;
        if (file.is_open()) {
            while (std::getline(file, line, ',')) {
                if (current_line >= 2 && current_line <= 4) {
                    lines.push_back(line);
                }
                current_line++;
            }
        }
        name = lines[0]; length = std::stod(lines[1]); diameter = std::stoi(lines[2]);
        file.close();
        std::cout << "Pipeline was successfully loaded!" << std::endl;
    }

    Pipeline(std::string p_name = "Undefined", double p_length = 0.0, int p_diameter = 0, bool p_status = false) {
        name = p_name; length = p_length; diameter = p_diameter; status = p_status;
    }
};

class CompressorStation {
    int shops_count;
    int station_class;

public:
    std::string name;
    int shops_in_work;

    int getShopsCount() { return shops_count; }

    void getInfo() {
        if (name == "Undefined" || shops_count == 0 || shops_in_work == 0 || station_class == 0) {
            std::cout << "Compressor station has not been created yet or created with incorrect parameters!" << std::endl;
        } else {
            std::cout << std::endl << "--------Compressor station---------" << std::endl;
            std::cout << "Name: " << name << std::endl;
            std::cout << "Shops count: " << shops_count << std::endl;
            std::cout << "Shops in work: " << shops_in_work << std::endl;
            std::cout << "Station class: " << station_class << std::endl;
            std::cout << "-----------------------------------" << std::endl;
        }
    }

    void readFromConsole() {
        std::cout << std::endl << "Name: "; 
        std::cin.ignore(); 
        std::getline(std::cin, name);

        while (true) {
            std::cout << "Count of shops: ";
            if (validation(shops_count) && shops_count >= 0) {
                break;
            }
            std::cout << std::endl << "[Error] Count of shops must be integer and more than zero! Try again!" << std::endl;
        }

        while (true) {
            std::cout << "Count of working shops: ";
            if (validation(shops_in_work) && (shops_in_work >= 0 && shops_in_work <= shops_count)) {
                break;
            }
            std::cout << std::endl << "[Error] Count of working shops must be integer and less then count of shops! Try again!" << std::endl;
        }

        while (true) {
            std::cout << "Class of compressor station [1-10]: ";
            if (validation(station_class) && (station_class >= 1 && station_class <= 10)) {
                break;
            }
            std::cout << std::endl << "[Error] Class of compressor station must be integer in range [1-10]! Return to main menu!" << std::endl;
        }
    }

    void saveToFile(std::string filename) {
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << "CS," << name << "," << shops_count << "," << shops_in_work << "," << station_class << std::endl;
        }
        file.close();
        std::cout << "Compressor station was successfully saved!" << std::endl;
    }

    void loadFromFile(std::string filename) {
        std::ifstream file(filename);
        std::vector<std::string> lines;
        std::string line;
        int current_line = 1;
        if (file.is_open()) {
            while (std::getline(file, line, ',')) {
                if (current_line >= 6 && current_line <= 9) {
                    lines.push_back(line);
                }
                current_line++;
            }
        }
        name = lines[0]; shops_count = std::stoi(lines[1]); shops_in_work = std::stoi(lines[2]); station_class = std::stoi(lines[3]);
        file.close();
        std::cout << "Compressor station was successfully loaded!" << std::endl;
    }

    CompressorStation(std::string p_name = "Undefined", int p_shops_count = 0, int p_shops_in_work = 0, int p_station_class = 0) {
        name = p_name; shops_count = p_shops_count; shops_in_work = p_shops_in_work; station_class = p_station_class;
    }
};

int main()
{
    Pipeline pipeline = Pipeline();
    CompressorStation compressorstation = CompressorStation();
    system("cls");

    int choice;
    do {
        std::cout << std::endl;
        std::cout << "-------------Main menu-------------" << std::endl;
        std::cout << "[1] Create new pipeline" << std::endl;
        std::cout << "[2] Create new compressor station" << std::endl;
        std::cout << "[3] Show all objects" << std::endl;
        std::cout << "[4] Edit pipeline" << std::endl;
        std::cout << "[5] Edit compressor station" << std::endl;
        std::cout << "[6] Save to file" << std::endl;
        std::cout << "[7] Load from file" << std::endl;
        std::cout << "[0] Exit" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "Choose the option: ";

        std::cin >> choice;

        switch(choice) {
            case 1:
                system("cls");
                pipeline.readFromConsole();
                std::cout << std::endl << "Successful creation! Return to main menu!" << std::endl;
                break;
            case 2:
                system("cls");
                compressorstation.readFromConsole();
                std::cout << std::endl << "Successful creation! Return to main menu!" << std::endl;
                break;
            case 3:
                system("cls");
                pipeline.getInfo();
                compressorstation.getInfo();
                std::cout << std::endl << "Return to main menu!" << std::endl;
                break;
            case 4:
                system("cls");
                if (pipeline.name == "Undefined") {
                    std::cout << "There is nothing to change!" << std::endl;
                    std::cout << "Pipeline has not been created yet or created with incorrect parameters!" << std::endl;
                    std::cout << "Return to main menu!" << std::endl;
                } else {
                    system("cls");
                    pipeline.status = !pipeline.status;
                    std::cout << "Pipeline status has been changed! Return to edit menu!" << std::endl;
                }
                break;
            case 5:
                system("cls");
                if (compressorstation.name == "Undefined") {
                    std::cout << "There is nothing to change!" << std::endl;
                    std::cout << "Compressor station has not been created yet or created with incorrect parameters!" << std::endl;
                    std::cout << "Return to main menu!" << std::endl;
                } else {                        
                    system("cls");
                    int shops_in_work;
                    std::cout << std::endl << "New count: "; std::cin >> shops_in_work;
                    if (shops_in_work < compressorstation.getShopsCount()) {
                        compressorstation.shops_in_work = shops_in_work;
                        std::cout << "Count of working shops has been changed! Return to main menu!" << std::endl;
                    } else {
                        std::cout << "[Error] Count of working shops must be less then count of shops! Return to main menu!" << std::endl;
                    }
                }
                break;
            case 6: {
                system("cls");
                pipeline.saveToFile("save-load-file.txt");
                compressorstation.saveToFile("save-load-file.txt");
                std::cout << std::endl << "Return to main menu!" << std::endl;
                break;
            }
            case 7:
                system("cls");
                pipeline.loadFromFile("save-load-file.txt");
                compressorstation.loadFromFile("save-load-file.txt");
                std::cout<< std::endl << "Return to main menu!" << std::endl;
                break;
            case 0:
                system("cls");
                break;
            default:
                std::cout << std::endl << "Invalid! Try again!" << std::endl;
        }   
    } while (choice != 0);

    return 0;
}