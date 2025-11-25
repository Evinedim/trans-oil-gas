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

void Network::initializeNetwork() {
    graph.clear();
    for (auto& [id, pipe] : pipes) {
        if (pipe.cs_in != 0 && pipe.cs_out != 0) {
            if (pipe.cs_in != pipe.cs_out && stations.contains(pipe.cs_in) && stations.contains(pipe.cs_out)) {
                graph[pipe.cs_out];
                graph[pipe.cs_in][pipe.cs_out] = id;
                using_pipes.insert(id);
            } else {
                std::cout << std::endl << "Pipe [" << id << "] will be disabled from network!!!" << std::endl;
                std::cout << "Pipe [" << id << "] has an incorrect input or output compressor station ID!!!" << std::endl;

                pipe.cs_in = 0;
                pipe.cs_out = 0;
            }
        }
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
    } else if (getTopologicalSortedNodes().empty()) {
        std::cout << std::endl << "Topological sorting is impossible! Graph contains cycles!" << std::endl;
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
            if (validation(start_cs) && stations.contains(start_cs)) {
                break;
            } else {
                std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
            }
        }

        while (true) {
            std::cout << "Choose id of end station: ";
            if (validation(end_cs) && stations.contains(end_cs) && end_cs != start_cs) {
                break;
            } else {
                std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
            }
        }

        for (auto& [id, pipe] : pipes) {
            if (!using_pipes.contains(id)) {
                std::cout << std::endl << id;
                pipe.getInfo();
            }
        }

        while (true) {
            std::cout << "Choose id of connection pipe: ";
            if (validation(pipe_id) && pipes.contains(pipe_id) && !using_pipes.contains(pipe_id))  {
                break;
            } else {
                std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
            }
        }

        graph[end_cs];
        graph[start_cs][end_cs] = pipe_id;
        using_pipes.insert(pipe_id);

        pipes[pipe_id].cs_in = start_cs;
        pipes[pipe_id].cs_out = end_cs;
    }
}

void Network::deleteConnection() {
    showNetwork();

    if (!graph.empty()) {
        int start_cs, end_cs;

        while (true) {
            std::cout << "Choose id of start station: ";
            if (validation(start_cs) && graph.contains(start_cs)) {
                break;
            } else {
                std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
            }
        }

        while (true) {
            std::cout << "Choose id of end station: ";
            if (validation(end_cs) && graph.contains(end_cs)) {
                break;
            } else {
                std::cout << std::endl << "[Error] Invalid choice! Try again!" << std::endl;
            }
        }

        if (graph.contains(start_cs)) {
            if (graph[start_cs].contains(end_cs)) {
                pipes[graph[start_cs][end_cs]].cs_in = 0;
                pipes[graph[start_cs][end_cs]].cs_out = 0;

                using_pipes.erase(graph[start_cs][end_cs]);
                graph[start_cs].erase(end_cs);
            }
        }

        deleteZeroDegreeNodes();
    }
}