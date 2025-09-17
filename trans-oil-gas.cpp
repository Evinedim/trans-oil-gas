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

    std::string getName() const {
        return "Shops count: " + std::to_string(shops_count);
    }

    std::string getName() const {
        return "Statiob class: " + std::to_string(station_class);
    }

    CompressorStation(std::string p_name, int p_shops_count, int p_station_class) {
        name = p_name;
        shops_count = p_shops_count;
        station_class = p_station_class;
    }
};

int main()
{
    Pipe pipe = Pipe("pipe", 100, 1000);
    std::cout << pipe.getName() << std::endl;
    std::cout << pipe.getLength()<< std::endl;
    std::cout << pipe.getDiameter() << std::endl;
    std::cout << pipe.getStatus() << std::endl;
    return 0;
}