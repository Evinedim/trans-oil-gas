#include <iostream>
#include <string>
#include <fstream>

template<typename T> bool validation(T& value) {
    if (std::cin >> value) {
        return true;
    }
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    return false;
}

class Pipeline {
    std::string name;
    double length;
    int diameter;
    bool status;

public:    
    std::string getName() { return name; }

    void changeStatus() {
        std::cout << "Current pipeline:" << std::endl;
        getInfo();
        status = !status;
        std::cout << "Pipeline status has been changed! Return to edit menu!" << std::endl;
    }

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
            file << name << std::endl; 
            file << length << std::endl;
            file << diameter << std::endl;
            file << status << std::endl;
        }
        file.close();
        std::cout << "Pipeline was successfully saved!" << std::endl;
    }

    void loadFromFile(std::string filename) {
        std::ifstream file("save-load-file.txt");
        
        std::cout << "Pipeline was successfully loaded!" << std::endl;
    }

    Pipeline() {
        name = "Undefined"; length = 0.0; diameter = 0; status = false;
    }
};

class CompressorStation {
    std::string name;
    int shops_count;
    int station_class;
    int shops_in_work;

public:
    std::string getName() { return name; }

    void changeCountOfWorkingShops() {
        getInfo();
        while (true) {
            std::cout << "New count of working shops: ";
            if (validation(shops_in_work) && (shops_in_work >= 0 && shops_in_work <= shops_count)) {
                break;
            }
            std::cout << std::endl << "[Error] Count of working shops must be integer and less then count of shops! Try again!" << std::endl;
        }
    }

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
            file << name << std::endl;
            file << shops_count << std::endl;
            file << shops_in_work << std::endl;
            file << station_class << std::endl;
        }
        file.close();
        std::cout << "Compressor station was successfully saved!" << std::endl;
    }

    void loadFromFile(std::string filename) {
        std::ifstream file(filename);
        
        std::cout << "Compressor station was successfully loaded!" << std::endl;
    }

    CompressorStation() {
        name = "Undefined"; shops_count = 0; shops_in_work = 0; station_class = 0;
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
                if (pipeline.getName() == "Undefined") {
                    std::cout << "There is nothing to change!" << std::endl;
                    std::cout << "Pipeline has not been created yet or created with incorrect parameters!" << std::endl;
                    std::cout << "Return to main menu!" << std::endl;
                } else {
                    system("cls");
                    pipeline.changeStatus();
                }
                break;
            case 5:
                system("cls");
                if (compressorstation.getName() == "Undefined") {
                    std::cout << "There is nothing to change!" << std::endl;
                    std::cout << "Compressor station has not been created yet or created with incorrect parameters!" << std::endl;
                    std::cout << "Return to main menu!" << std::endl;
                } else {                        
                    system("cls");
                    compressorstation.changeCountOfWorkingShops();
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