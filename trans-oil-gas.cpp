#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int is_int(std::string str) {
    try {
        int num = std::stoi(str);
        return 1;
    } catch (...) {
        return 0;
    }
}

int is_double(std::string str) {
    try {
        double num = std::stod(str);
        return 1;
    } catch (...) {
        return 0;
    }
}

class Pipeline {
private:
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
                std::cout << "Status: pipeline is not on repair" << std::endl;
            } else {
                std::cout << "Status: pipeline is on repair" << std::endl;
            }
            std::cout << "-----------------------------------" << std::endl;
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
private:
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

class Menu {
public:
    void showMenu() {
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
    }

    void showPipelineEditMenu() {
        std::cout << std::endl;
        std::cout << "---------Edit pipeline menu---------" << std::endl;
        std::cout << "[1] Edit name" << std::endl;
        std::cout << "[2] Edit status" << std::endl;
        std::cout << "[0] Exit" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Choose the option: ";
    }

    void showCompressorStationEditMenu() {
        std::cout << std::endl;
        std::cout << "----Edit compressor station menu----" << std::endl;
        std::cout << "[1] Edit name" << std::endl;
        std::cout << "[2] Edit count of working shops" << std::endl;
        std::cout << "[0] Exit" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Choose the option: ";
    }
};

int main()
{
    system("cls");
    Pipeline pipeline = Pipeline();
    CompressorStation compressorstation = CompressorStation();
    int choice;
    Menu menu;
    
    do {
        menu.showMenu();
        std::cin >> choice;
        
        switch(choice) {
            case 1: {
                system("cls");
                std::string name, str_length, str_diameter;
                double length; int diameter;

                std::cout << std::endl; std::cout << "Name: "; std::cin >> name;

                std::cout << "Length ('km'): "; std::cin >> str_length;
                if (!is_double(str_length)) {
                    std::cout << std::endl << "[Error] Length must be double! Return to main menu!" << std::endl;
                    break;
                }
                length = std::stod(str_length);
                if (length < 0) {
                    std::cout << std::endl << "[Error] Length must be more than zero! Return to main menu!" << std::endl;
                    break;
                }

                std::cout << "Diameter ('mm'): "; std::cin >> str_diameter;
                if (!is_int(str_diameter)) {
                    std::cout << std::endl << "[Error] Diameter must be integer! Return to main menu!" << std::endl;
                    break;
                }
                diameter = std::stoi(str_diameter);
                if (diameter < 0) {
                    std::cout << std::endl << "[Error] Diameter must be more than zero! Return to main menu!" << std::endl;
                    break;
                }

                pipeline = Pipeline(name, length, diameter);
                std::cout << std::endl << "Successful creation! Return to main menu!" << std::endl;
                break;
            }
            case 2: {
                system("cls");
                std::string name, str_shops_count, str_shops_in_work, str_station_class;
                int shops_count, shops_in_work, station_class;

                std::cout << std::endl; std::cout << "Name: "; std::cin >> name;

                std::cout << "Count of shops: "; std::cin >> str_shops_count;
                if (!is_int(str_shops_count)) {
                    std::cout << std::endl << "[Error] Count of shops must be integer! Return to main menu!" << std::endl;
                    break;
                }
                shops_count = std::stoi(str_shops_count);
                if (shops_count < 0) {
                    std::cout << std::endl << "[Error] Count of shops must be more than zero! Return to main menu!" << std::endl;
                    break;
                }

                std::cout << "Count of working shops: "; std::cin >> str_shops_in_work;
                if (!is_int(str_shops_in_work)) {
                    std::cout << std::endl << "[Error] Count of working shops mast be integer! Return to main menu!" << std::endl;
                    break;
                }
                shops_in_work = std::stoi(str_shops_in_work);
                if (shops_in_work < 0) {
                    std::cout << std::endl << "[Error] Count of shops must be more than zero! Return to main menu!" << std::endl;
                    break;
                }
                if (shops_count < shops_in_work) {
                    std::cout << std::endl << "[Error] Count of working shops mast be less then count of shops! Return to main menu!" << std::endl;
                    break;
                }
                
                std::cout << "Class of compressor station [1-10]: "; std::cin >> str_station_class;
                if (!is_int(str_station_class)) {
                    std::cout << std::endl << "[Error] Class of compressor station mast be integer! Return to main menu!" << std::endl;
                    break;
                }
                station_class = std::stoi(str_station_class);

                compressorstation = CompressorStation(name, shops_count, shops_in_work, station_class);
                std::cout << std::endl << "Successful creation! Return to main menu!" << std::endl;
                break;
            }
            case 3: {
                system("cls");
                pipeline.getInfo();
                compressorstation.getInfo();
                std::cout << std::endl << "Return to main menu!" << std::endl;
                break;
            }
            case 4: {
                system("cls");
                int pipeline_choice;

                if (pipeline.name == "Undefined") {
                    std::cout << "There is nothing to change!" << std::endl;
                    std::cout << "Pipeline has not been created yet or created with incorrect parameters!" << std::endl;
                    std::cout << "Return to main menu!" << std::endl;
                    break;
                }
                do {
                    menu.showPipelineEditMenu();
                    std::cin >> pipeline_choice;
                    switch(pipeline_choice) {
                        case 1: {
                            system("cls");
                            std::string name;
                            std::cout << std::endl; std::cout << "New name: "; std::cin >> name;
                            pipeline.name = name;
                            std::cout << "Name has been changed! Return to edit menu!" << std::endl;
                            break;
                        }
                        case 2: {
                            system("cls");
                            pipeline.status = !pipeline.status;
                            std::cout << "Status has been changed! Return to edit menu!" << std::endl;
                            break;
                        }
                        case 0: {
                            system("cls");
                            break;
                        }
                        default:
                            std::cout << std::endl << "Invalid! Try again!" << std::endl;
                    }
                } while (pipeline_choice != 0);
                break;
            }
            case 5: {
                system("cls");
                int cs_choice;

                if (compressorstation.name == "Undefined") {
                    std::cout << "There is nothing to change!" << std::endl;
                    std::cout << "Compressor station has not been created yet or created with incorrect parameters!" << std::endl;
                    std::cout << "Return to main menu!" << std::endl;
                    break;
                }
                do {
                    menu.showCompressorStationEditMenu();
                    std::cin >> cs_choice;
                    switch(cs_choice) {
                        case 1: {
                            system("cls");
                            std::string name;
                            std::cout << std::endl; std::cout << "New name: "; std::cin >> name;
                            compressorstation.name = name;
                            std::cout << "Name has been changed! Return to edit menu!" << std::endl;
                            break;
                        }
                        case 2: {
                            system("cls");
                            int shops_in_work;
                            std::cout << std::endl; std::cout << "New count: "; std::cin >> shops_in_work;
                            if (shops_in_work < compressorstation.getShopsCount()) {
                                compressorstation.shops_in_work = shops_in_work;
                            } else {
                                std::cout << "[Error] Count of working shops must be less then count of shops! Return to edit menu!" << std::endl;
                                break;
                            }
                            std::cout << "Count of working shops has been changed! Return to edit menu!" << std::endl;
                            break;
                        }
                        case 0: {
                            system("cls");
                            break;
                        }
                        default:
                            std::cout << std::endl << "Invalid! Try again!" << std::endl;
                    }
                } while (cs_choice != 0);
                break;
            }
            case 6: {
                system("cls");
                pipeline.saveToFile("save-load-file.txt");
                compressorstation.saveToFile("save-load-file.txt");
                std::cout << std::endl << "Return to main menu!" << std::endl;
                break;
            }
            case 7: {
                system("cls");
                pipeline.loadFromFile("save-load-file.txt");
                compressorstation.loadFromFile("save-load-file.txt");
                std::cout<< std::endl << "Return to main menu!" << std::endl;
                break;
            }
            case 0: {
                system("cls");
                break;
            }
            default:
                std::cout << std::endl << "Invalid! Try again!" << std::endl;
        }   
    } while (choice != 0);

    return 0;
}