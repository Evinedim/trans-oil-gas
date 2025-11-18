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

void Network::createConnection() {
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

    getInfo(pipes);

    while (true) {
        std::cout << "Choose id of connection pipe: ";
        if (validation(pipe_id) && pipes.count(pipe_id) != 0) {
            break;
        } else {
            std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
        }
    }

    graph[start_cs].push_back({end_cs, pipe_id});

    if (getTopologicalSortedNodes().empty()) {
        graph[start_cs].pop_back();
        std::cout << std::endl << "Such connection forms cicle! Try again!" << std::endl;
    }

    for (auto& [start_cs, pair]: graph) {
        if (pair.empty()) {
            graph.erase(start_cs);
        }
    }
}

void Network::showNetwork() {
    if (graph.empty()) {
        std::cout << std::endl << "Network is empty!" << std::endl;
    } else {
        for (auto& [start_cs, pair]: graph) {
            std::cout << "" << start_cs << ": ";
            for (auto& [end_cs, pipe_id] : pair) {
                std::cout << "(" << end_cs << ", " << pipe_id << ") ";
            }  
            std::cout << std::endl; 
        }  
    }
}

void Network::showTopologicalSortedNetwork() {
    for (auto& start_cs : getTopologicalSortedNodes()) {
        std::cout << start_cs << ": ";
        for (auto& [end_cs, pipe_id] : graph[start_cs]) {
            std::cout << "(" << end_cs << ", " << pipe_id << ") ";
        }
        std::cout << std::endl; 
    }  
}