#include "Network.h"
#include "utils.h"
#include <queue>

std::vector<int> Network::getTopologicalSortedNodes() {

    std::unordered_map<int, int> in_degrees;

    for (auto& [node, neighbors] : graph) {
        in_degrees[node];
        for (auto& [neighbor, weight] : neighbors) {
            in_degrees[neighbor]++;
        }
    }

    std::queue<int> queue;

    for (auto& [node, in_degree] : in_degrees) {
        if (in_degree == 0) {
            queue.push(node);
        }
    }

    std::vector<int> result;

    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();
        result.push_back(node);

        for (auto& [neigbor, weight] : graph[node]) {
            in_degrees[neigbor]--;
            if (in_degrees[neigbor] == 0) {
                queue.push(neigbor);
            }
        }
    }

    if (result.size() != in_degrees.size()) {
        result.clear();
    }
    
    return result;
}

void Network::deleteZeroDegreeNodes() {
    std::unordered_map<int, int> degrees;

    for (auto& [node, neigbours] : graph) {
        degrees[node] += neigbours.size();

        for (auto& [neigbour, weight] : neigbours) {
            degrees[neigbour]++;
        }
    }

    for (auto& [node, degree] : degrees) {
        if (degree == 0) {
            graph.erase(node);
        }
    }
}

void Network::clear() {
    if (!graph.empty()) {
        std::cout << std::endl << "One of the objects on which the network was based was changed!"; 
        std::cout << std::endl << "To avoid problems, the network will be removed!" << std::endl;
        graph.clear();
    }
}

void Network::showNetwork() {
    if (graph.empty()) {
        std::cout << std::endl << "Network is empty!" << std::endl;
    } else {
        for (auto& [start_cs, neighbors]: graph) {
            std::cout << "" << start_cs << ": ";
            for (auto& [end_cs, pipe_id] : neighbors) {
                std::cout << "(" << end_cs << ", " << pipe_id << ") ";
            }  
            std::cout << std::endl; 
        }  
    }
}

void Network::showTopologicalSortedNetwork() {
    if (graph.empty()) {
        std::cout << std::endl << "Network is empty!" << std::endl;
    } else {
        for (auto& start_cs : getTopologicalSortedNodes()) {
            std::cout << start_cs << ": ";
            for (auto& [end_cs, pipe_id] : graph[start_cs]) {
                std::cout << "(" << end_cs << ", " << pipe_id << ") ";
            }
            std::cout << std::endl; 
        } 
    }
}

void Network::createConnection() {
    if (pipes.size() == using_pipes.size()) {
        std::cout << "Count of pipes is less than required to create a network!!!";
    } else {
        int start_cs, end_cs, pipe_id;

        getInfo(stations);

        while (true) {
            std::cout << "Choose id of start station: ";
            if (validation(start_cs) && stations.count(start_cs) != 0) {
                break;
            } else {
                std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
            }
        }

        while (true) {
            std::cout << "Choose id of end station: ";
            if (validation(end_cs) && stations.count(end_cs) != 0) {
                break;
            } else {
                std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
            }
        }

        for (auto& [id, pipe] : pipes) {
            if (using_pipes.count(id) == 0) {
                std::cout << std::endl << id;
                pipe.getInfo();
            }
        }

        while (true) {
            std::cout << "Choose id of connection pipe: ";
            if (validation(pipe_id) && pipes.count(pipe_id) != 0 && using_pipes.count(pipe_id) == 0)  {
                break;
            } else {
                std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
            }
        }

        graph[start_cs][end_cs] = pipe_id;

        if (getTopologicalSortedNodes().empty()) {
            graph[start_cs].erase(end_cs);
            std::cout << std::endl << "Such connection forms cicle! Try again!" << std::endl;
        } else {
            using_pipes.insert(pipe_id);
        }

        deleteZeroDegreeNodes();
    }
}

void Network::deleteConnection() {
    if (graph.empty()) {
        showNetwork();
    } else {
        int start_cs, end_cs;

        showNetwork();

        while (true) {
            std::cout << "Choose id of start station: ";
            if (validation(start_cs) && graph.count(start_cs) != 0) {
                break;
            } else {
                std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
            }
        }

        while (true) {
            std::cout << "Choose id of end station: ";
            if (validation(end_cs) && graph.count(end_cs) != 0) {
                break;
            } else {
                std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
            }
        }

        if (graph.count(start_cs)) {
            if (graph[start_cs].count(end_cs)) {
                using_pipes.erase(graph[start_cs][end_cs]);
                graph[start_cs].erase(end_cs);
            }
        }

        deleteZeroDegreeNodes();
    }
}