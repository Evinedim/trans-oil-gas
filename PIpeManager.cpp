#include "PipeManager.h"
#include "utils.h"

void filterPipesByName(std::unordered_map<int, Pipe>& pipes) {

    int pipe_choice;
    std::string name;

    std::cout << std::endl << "Name: ";
    std::getline(std::cin >> std::ws, name);

    std::unordered_map<int, Pipe> filtered_pipes;

    for (auto& [id, pipe] : pipes) {
        if (pipe.getName() == name) {
            filtered_pipes[id] = pipe;
        }
    }

    getInfo(filtered_pipes);

    do {
        if (filtered_pipes.empty()) {
            std::cout << "Nothing was found!" << std::endl;
            break;
        }

        std::cout << std::endl << "Do you want to change the current status of all found pipes?" << std::endl;
        std::cout << "[1] Yes" << std::endl;
        std::cout << "[0] No" << std::endl;

        while (true) {
            std::cout << "Your choice: ";
            if (validation(pipe_choice) && pipe_choice >= 0 && pipe_choice <= 1) {
                break;
            }
            std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
        }

        switch (pipe_choice) {
            case 1:
                for (auto& [id, pipe] : pipes) {
                    if (pipe.getName() == name) {
                        std::cout << std::endl << "[" << id << "] ";
                        pipe.changeStatus();
                    }
                }
                pipe_choice = 0;
                break;
            case 0:
                break;
        }
    } while (pipe_choice != 0);
}

void filterPipesByStatus(std::unordered_map<int, Pipe>& pipes) {

    int pipe_choice, status;

    std::unordered_map<int, Pipe> filtered_pipes = {};

    std::cout << std::endl << "Status: ";
    if (validation(status) && status >= 0 && status <= 1) {
        for (auto& [id, pipe] : pipes) {
            if (pipe.getStatus() == status) {
                filtered_pipes[id] = pipe;
            }
        }
    } else {
        std::cout << std::endl << "[Error] Invalid value! Try again!" << std::endl;
    }

    getInfo(filtered_pipes);

    do {
        if (filtered_pipes.empty()) {
            std::cout << "Nothing was found!" << std::endl;
            break;
        }

        std::cout << std::endl << "Do you want to change the current status of all found pipes?" << std::endl;
        std::cout << "[1] Yes" << std::endl;
        std::cout << "[0] No" << std::endl;

        while (true) {
            std::cout << "Your choice: ";
            if (validation(pipe_choice) && pipe_choice >= 0 && pipe_choice <= 1) {
                break;
            }
            std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
        }

        switch (pipe_choice) {
            case 1:
                for (auto& [id, pipe] : pipes) {
                    if (pipe.getStatus() == status) {
                        std::cout << std::endl << "[" << id << "] ";
                        pipe.changeStatus();
                    }
                }
                pipe_choice = 0;
                break;
            case 0:
                break;
        }
    } while (pipe_choice != 0);
}

void changeStatusById(int id, std::unordered_map<int, Pipe>& pipes) {
    getInfo(pipes);
    std::cout << std::endl << "Choose id of pipe: ";
    if (validation(id) && pipes.count(id) != 0) {
        pipes[id].changeStatus();
    } else {
        std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
    }
}

void deletePipeById(int id, std::unordered_map<int, Pipe>& pipes) {
    getInfo(pipes);
    std::cout << std::endl << "Choose id of pipe: ";
    if (validation(id) && pipes.count(id) != 0) {
        pipes.erase(id);
    } else {
        std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
    }
}