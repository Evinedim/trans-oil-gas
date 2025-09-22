#include <iostream>
#include <string>


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
        return "Name: " + name; 
    }

    void setName(std::string p_name) {
        name = p_name;
    } 
    
    std::string getLength() const {
        return "Length: " + std::to_string(length) + " km"; 
    }

    std::string getDiameter() const {
        return "Diameter: " + std::to_string(diameter) + " mm"; 
    }

    std::string getStatus() const {
        if (status == false) {
            return "Status: Pipeline is not on repair";
        } else {
            return "Status: Pipeline is on repair";
        }
    }

    void setStatus(bool p_status) {
        if (p_status != true && p_status != false) {
            std::cout << std::endl << "[Error] Wrong status! Return to main menu!" << std::endl;
        } 
        status = p_status;
    } 

    void getInfo() {
        if (name == "Undefined" || length == 0.0 || diameter == 0) {
            std::cout << "Pipeline has not been created yet or created with incorrect parameters!";
        } else {
            std::cout << "-------------Pipeline--------------" << std::endl;
            std::cout << getName() << std::endl;
            std::cout << getLength() << std::endl;
            std::cout << getDiameter() << std::endl;
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
        return "Name: " + name;
    }

    void setName(std::string p_name) {
        name = p_name;
    }

    std::string getShopsCount() const {
        return "Shops count: " + std::to_string(shops_count);
    }

    std::string getShopsInWork() const {
        return "Shops in work: " + std::to_string(shops_in_work);
    }

    std::string getStationClass() const {
        return "Station class: " + std::to_string(station_class);
    }

    void getInfo() {
        if (name == "Undefined" || shops_count == 0 || shops_in_work == 0 || station_class == 0) {
            std::cout << "Compressor station has not been created yet or created with incorrect parameters!";
        } else {
            std::cout << "--------Compressor station---------" << std::endl;
            std::cout << getName() << std::endl;
            std::cout << getShopsCount() << std::endl;
            std::cout << getShopsInWork() << std::endl;
            std::cout << getStationClass() << std::endl;
            std::cout << "-----------------------------------" << std::endl;
        }
    }

    CompressorStation(std::string p_name = "Undefined", 
                      int p_shops_count = 0, 
                      int p_shops_in_work = 0, 
                      int p_station_class = 0) {
        name = p_name;
        shops_count = p_shops_count;
        shops_in_work = p_shops_in_work;
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

    void showEditPipelineMenu() {
        std::cout << std::endl;
        std::cout << "--------Edit pipeline menu--------" << std::endl;
        std::cout << "[1] Edit name" << std::endl;
        std::cout << "[2] Edit status" << std::endl;
        std::cout << "[0] Exit" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
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
                if (shops_in_work < 0) {
                    std::cout << std::endl << "[Error] Count of shops must be more than zero! Return to main menu!" << std::endl;
                    break;
                }
                shops_in_work = std::stoi(str_shops_in_work);
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
                std::cout << std::endl;
                std::cout << "Return to main menu!" << std::endl;
                break;
            }
            case 4: {
                system("cls");
                int pipeline_choice;
                do {
                    menu.showEditPipelineMenu();
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
                            if (pipeline.getStatus() == "Status: Pipeline is not on repair") {
                                pipeline.setStatus(true);
                            } else {
                                pipeline.setStatus(false);
                            }
                            std::cout << "Status has been changed! Return to edit menu!" << std::endl;
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
                std::cout << "[5]" << std::endl;
                break;
            case 6:
                std::cout << "[6]" << std::endl;
                break;
            case 7:
                std::cout << "[7]" << std::endl;
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