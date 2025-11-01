#include <iostream>
#include <unordered_map>

template<typename T> 
bool validation(T& value) {
    if (std::cin >> value && std::cin.peek() == '\n') {
        return 1;
    }
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    return 0;
}

template<typename T>
int generateID(std::unordered_map<int, T> &objects) {
    int id = 0;
    while (objects.count(id)) {
        id++;
    }
    return id;
}