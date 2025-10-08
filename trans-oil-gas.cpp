#include <iostream>
#include <string>
#include <fstream>

template<typename T> 
bool validation(std::istream& stream, T& value) {
    if (std::cin >> value && std::cin.peek() == '\n') {
        return 1;
    }
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    return 0;
}

class Pipeline {
    std::string name;
    double length;
    int diameter;
    bool status;

public:    
    void getInfo() {
        if (name == "Undefined" || length == 0.0 || diameter == 0) {
            std::cout << std::endl << "Pipeline has not been created yet or created with incorrect parameters!" << std::endl;
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
        std::getline(std::cin >> std::ws, name);

        while (true) {
            std::cout << "Length ('km'): ";
            if (validation(std::cin, length) && length >= 0) {
                break;
            }
            std::cout << std::endl << "[Error] Length must be double and more than zero! Try again!" << std::endl;
        }

        while (true) {
            std::cout << "Diameter ('mm'): ";
            if (validation(std::cin, diameter) && diameter >= 0) {
                break;
            }
            std::cout << std::endl << "[Error] Diameter must be integer and more than zero! Try again!" << std::endl;
        }

    }

    void changeStatus() {
        getInfo();
        if (name != "Undefined" || length != 0.0 || diameter != 0) {
            std::cout << std::endl << "Change the current status?" << std::endl;
            std::cout << "[1] Yes" << std::endl;
            std::cout << "[0] No" << std::endl;

            int choice;
            while (choice != 0) {
                std::cout << "Your choice: "; std::cin >> choice;

                switch (choice) {
                    case 1:
                        status = !status;
                        std::cout << std::endl << "Pipeline status has been changed!" << std::endl;
                        choice = 0;
                        break;
                    case 0:
                        break;
                    default:
                        std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
                }
            }
        }
    }

    void saveToFile(std::ofstream& file) {
        if (name == "Undefined" || length == 0.0 || diameter == 0) {
            std::cout << std::endl << "[Pipeline] There is nothing to save!" << std::endl;
        } else {
            file << "Pipeline" << std::endl;
            file << name << std::endl; 
            file << length << std::endl;
            file << diameter << std::endl;
            file << status << std::endl;
            std::cout << std::endl << "Pipeline was successfully saved!" << std::endl;
        }
    }

    void loadFromFile(std::ifstream& file) {
        std::getline(file >> std::ws, name);
        if (file >> length >> diameter >> status) {
            std::cout << std::endl << "Pipeline was successfully loaded!" << std::endl;
        } else {
            std::cout << std::endl << "[Error] Wrong data in file!" << std::endl;
        }
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
    void getInfo() {
        if (name == "Undefined" || shops_count == 0 || shops_in_work == 0 || station_class == 0) {
            std::cout << std::endl <<  "Compressor station has not been created yet or created with incorrect parameters!" << std::endl;
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
        std::getline(std::cin>>std::ws, name);

        while (true) {
            std::cout << "Count of shops: ";
            if (validation(std::cin, shops_count) && shops_count >= 0) {
                break;
            }
            std::cout << std::endl << "[Error] Count of shops must be integer and more than zero! Try again!" << std::endl;
        }

        while (true) {
            std::cout << "Count of working shops: ";
            if (validation(std::cin, shops_in_work) && (shops_in_work >= 0 && shops_in_work <= shops_count)) {
                break;
            }
            std::cout << std::endl << "[Error] Count of working shops must be integer and less then count of shops! Try again!" << std::endl;
        }

        while (true) {
            std::cout << "Class of compressor station [1-10]: ";
            if (validation(std::cin, station_class) && (station_class >= 1 && station_class <= 10)) {
                break;
            }
            std::cout << std::endl << "[Error] Class of compressor station must be integer in range [1-10]! Return to main menu!" << std::endl;
        }
    }

    void changeCountOfWorkingShops() {
        getInfo();
        if (name != "Undefined" || shops_count != 0 || shops_in_work != 0 || station_class != 0) {
            while (true) {
                std::cout << std::endl << "New count of working shops: ";
                if (validation(std::cin, shops_in_work) && (shops_in_work >= 0 && shops_in_work <= shops_count)) {
                    break;
                }
                std::cout << std::endl << "[Error] Count of working shops must be integer and less then count of shops! Try again!" << std::endl;
            }
        }
    }

    void saveToFile(std::ofstream& file) {
        if (name == "Undefined" || shops_count == 0 || shops_in_work == 0 || station_class == 0) {
            std::cout << "[Compressor Station] There is nothing to save!" << std::endl;
        } else {
            file << "Station" << std::endl;
            file << name << std::endl;
            file << shops_count << std::endl;
            file << shops_in_work << std::endl; 
            file << station_class << std::endl;
            std::cout << "Compressor station was successfully saved!" << std::endl;
        }
    }

    void loadFromFile(std::ifstream& file) {
        std::getline(file >> std::ws, name);
        if (file >> shops_count >> shops_in_work >> station_class) {
            std::cout << std::endl << "Compressor station was successfully loaded!" << std::endl;
        } else {
            std::cout << std::endl << "[Error] Wrong data in file!" << std::endl;
        }
    }

    CompressorStation() {
        name = "Undefined"; shops_count = 0; shops_in_work = 0; station_class = 0;
    }
};

int main() {
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

        while (true) {
            std::cout << "Choose the option: ";
            if (validation(std::cin, choice)) {
                break;
            }
            std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
        }

        switch(choice) {
            case 1:
                pipeline.readFromConsole();
                std::cout << std::endl << "Successful creation! Return to main menu!" << std::endl;
                break;
            case 2:
                compressorstation.readFromConsole();
                std::cout << std::endl << "Successful creation! Return to main menu!" << std::endl;
                break;
            case 3:
                pipeline.getInfo();
                compressorstation.getInfo();
                std::cout << std::endl << "Return to main menu!" << std::endl;
                break;
            case 4:
                pipeline.changeStatus();
                std::cout << std::endl << "Return to main menu!" << std::endl;
                break;
            case 5:
                compressorstation.changeCountOfWorkingShops();
                std::cout << std::endl << "Return to main menu!" << std::endl;
                break;
            case 6: {
                std::ofstream file("save-load-file.txt");
                if (!file.is_open()) {
                    std::cout << "[Error] File was not opened!" << std::endl;
                }

                pipeline.saveToFile(file);
                compressorstation.saveToFile(file);
                
                std::cout << std::endl << "Return to main menu!" << std::endl;
                break;
            }
            case 7: {
                std::ifstream file("save-load-file.txt");
                if (!file.is_open()) {
                    std::cout << std::endl << "[Error] File was not opened!" << std::endl;
                }
                
                std::string line;
                while (file >> line) {
                    if (line == "Pipeline") {
                        pipeline.loadFromFile(file);
                    }
                    if (line == "Station") {
                        compressorstation.loadFromFile(file);
                    }
                }
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