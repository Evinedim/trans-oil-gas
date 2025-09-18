#include <iostream>

class Pipe {
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

    Pipe(std::string p_name, double p_length, double p_diametr, bool p_is_repair = false) {
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
    int station_class;

public:
    std::string getName() const {
        return "Name: " + name;
    }

    std::string getShopsCount() const {
        return "Shops count: " + std::to_string(shops_count);
    }

    std::string getStationClass() const {
        return "Station class: " + std::to_string(station_class);
    }

    CompressorStation(std::string p_name, int p_shops_count, int p_station_class) {
        name = p_name;
        shops_count = p_shops_count;
        station_class = p_station_class;
    }
};

class Menu {
public:
    void showMenu() {
        std::cout << std::endl;
        std::cout <<  "Main menu" << std::endl;
        std::cout << "[1]" << std::endl;
        std::cout << "[2]" << std::endl;
        std::cout << "[3]" << std::endl;
        std::cout << "[4] Exit" << std::endl;
        std::cout << "Choose the option: ";
    }
};

int main()
{
    int choice;
    Menu menu;
    
    do {
        menu.showMenu();
        std::cin >> choice;
        
        switch(choice) {
            case 1:
                std::cout << "[1]" << std::endl;
            case 2:
                std::cout << "[1]" << std::endl;
            case 3:
                std::cout << "[1]" << std::endl;
            case 4:
                std::cout << "[1]" << std::endl;
            default:
                std::cout << "[1]" << std::endl;
        }
        std::cout << std::endl;
        
    } while(choice != 4);
    
    return 0;
}