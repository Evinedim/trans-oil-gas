#include <iostream>

class Pipeline {
private:
    std::string name;
    double length;
    int diameter;
    bool is_repair;

public:
    std::string getName() const {
        return "Name: " + name; 
    }
    
    std::string getLength() const {
        return "Length: " + std::to_string(length) + " km"; 
    }

    std::string getDiameter() const {
        return "Diameter: " + std::to_string(diameter) + " mm"; 
    }

    std::string getStatus() const {
        if (is_repair == false) {
            return "Pipeline is not on repair";
        } else {
            return "Pipeline is on repair";
        }
    }

    void getInfo() {
        if (name == "Undefined") {
            std::cout << "Pipeline has not been created yet!" << std::endl;
        } else {
            std::cout << getName() << std::endl;
            std::cout << getLength() << std::endl;
            std::cout << getDiameter() << std::endl;
            std::cout << getStatus() << std::endl;
        }
    }

    Pipeline(std::string p_name = "Undefined", 
             double p_length = 0.0, 
             int p_diametr = 0, 
             bool p_is_repair = false) {
        name = p_name;
        length = p_length;
        diameter = p_diametr;
        is_repair = p_is_repair;
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
        if (name == "Undefined") {
            std::cout << "Pipeline has not been created yet!" << std::endl;
        } else {
            std::cout << getName() << std::endl;
            std::cout << getShopsCount() << std::endl;
            std::cout << getShopsInWork() << std::endl;
            std::cout << getStationClass() << std::endl;
        }
    }

    CompressorStation(std::string p_name, int p_shops_count, int p_shops_in_work, int p_station_class) {
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
        std::cout <<  "Main menu" << std::endl;
        std::cout << "[1] Create new pipeline" << std::endl;
        std::cout << "[2] Create new compressor station" << std::endl;
        std::cout << "[3] Show all objects" << std::endl;
        std::cout << "[4] Edit pipeline" << std::endl;
        std::cout << "[5] Edit compressor station" << std::endl;
        std::cout << "[6] Save to file" << std::endl;
        std::cout << "[7] Load from file" << std::endl;
        std::cout << "[0] Exit" << std::endl;
        std::cout << "Choose the option: ";
    }
};

int main()
{
    Pipeline pipeline = Pipeline();
    pipeline.getInfo();

    // int choice;

    // Menu menu;
    // menu.showMenu();
    
    // do {
    //     std::cin >> choice;
        
    //     switch(choice) {
    //         case 1: {
    //             std::string name;
    //             double length;
    //             int diameter;
                
                
    //             std::cout << std::endl; std::cout << "Name: "; std::cin >> name;

    //             // std::cout << "Length: "; std::cin >> length;
    //             // std::cout << "Diameter: "; std::cin >> diameter;
                
    //             Pipeline pipeline = Pipeline(name, length, diameter);

    //             std::cout << std::endl << "Successful creation! Return to main menu!" << std::endl;
                
    //             menu.showMenu();
    //             break;
    //         }
    //         case 2: 
    //             std::cout << "[2]" << std::endl;
    //             break;
    //         case 3:
    //             std::cout << "[3]" << std::endl;
    //             break;
    //         case 4:
    //             std::cout << "[4]" << std::endl;
    //             break;
    //         case 5:
    //             std::cout << "[5]" << std::endl;
    //             break;
    //         case 6:
    //             std::cout << "[6]" << std::endl;
    //             break;
    //         case 7:
    //             std::cout << "[7]" << std::endl;
    //             break;
    //         default:
    //             std::cout << std::endl << "Invalid! Try again!" << std::endl;
    //             menu.showMenu();
    //     }   
    // } while(choice != 0);
    
    return 0;
}