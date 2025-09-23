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
    std::string name;
    double length;
    int diameter;
    bool status;

public:
    std::string getName() const {
        return name; 
    }

    void setName(std::string p_name) {
        name = p_name;
    } 
    
    int getLength() const {
        return length; 
    }

    int getDiameter() const {
        return diameter; 
    }

    std::string getStatus() const {
        if (status == false) {
            return "Status: pipeline is not on repair";
        } else {
            return "Status: pipeline is on repair";
        }
    }

    void setStatus(bool p_status) {
        status = p_status;
    } 

    void getInfo() {
        if (name == "Undefined" || length == 0.0 || diameter == 0) {
            std::cout << "Pipeline has not been created yet or created with incorrect parameters!";
        } else {
            std::cout << "-------------Pipeline--------------" << std::endl;
            std::cout << "Name: " << getName() << std::endl;
            std::cout << "Length: " << getLength() << " km" << std::endl;
            std::cout << "Diameter: " << getDiameter() << " mm" << std::endl;
            std::cout << getStatus() << std::endl;
            std::cout << "-----------------------------------" << std::endl;
        }
    }

    Pipeline(std::string p_name = "Undefined", 
             double p_length = 0.0, 
             int p_diameter = 0, 
             bool p_status = false) {
        setName(p_name);
        length = p_length;
        diameter = p_diameter;
        setStatus(p_status);
    }
};

class CompressorStation {
private:
    std::string name;
    int shops_count;
    int shops_in_work;
    int station_class;

public:
    std::string getName() const {
        return name;
    }

    void setName(std::string p_name) {
        name = p_name;
    }

    int getShopsCount() const {
        return shops_count;
    }

    int getShopsInWork() const {
        return shops_in_work;
    }

    void setShopsInWork(int p_shops_in_work) {
        shops_in_work = p_shops_in_work;
    }

    int getStationClass() const {
        return station_class;
    }

    void getInfo() {
        if (name == "Undefined" || shops_count == 0 || shops_in_work == 0 || station_class == 0) {
            std::cout << "Compressor station has not been created yet or created with incorrect parameters!";
        } else {
            std::cout << std::endl << "--------Compressor station---------" << std::endl;
            std::cout << "Name: " << getName() << std::endl;
            std::cout << "Shops count: " << getShopsCount() << std::endl;
            std::cout << "Shops in work: " << getShopsInWork() << std::endl;
            std::cout << "Station class: " << getStationClass() << std::endl;
            std::cout << "-----------------------------------" << std::endl;
        }
    }

    CompressorStation(std::string p_name = "Undefined", 
                      int p_shops_count = 0, 
                      int p_shops_in_work = 0, 
                      int p_station_class = 0) {
        setName(p_name);
        shops_count = p_shops_count;
        setShopsInWork(p_shops_in_work);
        station_class = p_station_class;
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
                diameter = std::stod(str_diameter);
                if (diameter < 0) {
                    std::cout << std::endl << "[Error] Diameter must be more than zero! Return to main menu!" << std::endl;
                    break;
                }

                system("cls");
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

                system("cls");
                compressorstation = CompressorStation(name, shops_count, shops_in_work, station_class);
                std::cout << std::endl << "Successful creation! Return to main menu!" << std::endl;
                break;
            }
            case 3: {
                system("cls");
                std::cout << std::endl;
                pipeline.getInfo();
                std::cout << std::endl;
                compressorstation.getInfo();
                std::cout << std::endl << "Return to main menu!" << std::endl;
                break;
            }
            case 4: {
                system("cls");
                int pipeline_choice;

                if (pipeline.getName() == "Undefined") {
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
                            pipeline.setName(name);
                            std::cout << "Name has been changed! Return to edit menu!" << std::endl;
                            break;
                        }
                        case 2: {
                            system("cls");
                            if (pipeline.getStatus() == "Status: pipeline is not on repair") {
                                pipeline.setStatus(true);
                            } else {
                                pipeline.setStatus(false);
                            }
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
            case 5:
                system("cls");
                int cs_choice;

                if (compressorstation.getName() == "Undefined") {
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
                            compressorstation.setName(name);
                            std::cout << "Name has been changed! Return to edit menu!" << std::endl;
                            break;
                        }
                        case 2: {
                            system("cls");
                            int shops_in_work;
                            std::cout << std::endl; std::cout << "New count: "; std::cin >> shops_in_work;
                            if (shops_in_work < compressorstation.getShopsCount()) {
                                compressorstation.setShopsInWork(shops_in_work);
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
            case 6: {
                system("cls");
                std::ofstream file;
                file.open("save-file.txt");
                if (file.is_open()) {
                    file << "P" << ",";
                    file << pipeline.getName() << ",";
                    file << pipeline.getLength() << ",";
                    file << pipeline.getDiameter() << ",";
                    file << pipeline.getStatus() << std::endl;
                    std::cout << "Pipeline was successfully saved!" << std::endl;

                    file << "Cs" << ",";
                    file << compressorstation.getName() << ",";
                    file << compressorstation.getShopsCount() << ",";
                    file << compressorstation.getShopsInWork() << ",";
                    file << compressorstation.getStationClass();
                    std::cout << "Compressor station was successfully saved!" << std::endl;
                }
                std::cout << "Return to main menu!" << std::endl;
                file.close();
                break;
            }
            case 7: {
                std::ifstream file("save-file.txt");
                int n;
                std::vector<std::string> lines;
                std::string line;
                while (std::getline(file, line, ',')) {
                    lines.push_back(line);
                }
                pipeline = Pipeline(lines[1], std::stod(lines[2]), std::stoi(lines[3]));
                compressorstation = CompressorStation(lines[6], std::stod(lines[7]), std::stod(lines[8]), std::stod(lines[9]));
                file.close();
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