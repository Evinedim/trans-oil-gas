#include "Network.h"
#include "utils.h"
#include <queue>
#include <limits>

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

std::pair<std::vector<int>, double> Network::getShortestWay(int start, int end) {
    std::unordered_map<int, double> costs;
    std::unordered_map<int, int> parents;

    std::unordered_set<int> processed;

    for (auto& [node, neighbors] : graph) {
        costs[node] = std::numeric_limits<double>::max();
    }
    costs[start] = 0;

    std::function<double()> find_lowest_code_node = [&costs, &processed]() {
        double lowest_cost = std::numeric_limits<double>::max();
        double lowest_cost_node = -1;
        for (auto& [node, cost] : costs) {
            if (cost < lowest_cost && processed.count(node) == 0) {
                lowest_cost = cost;
                lowest_cost_node = node;
            }
        }
        return lowest_cost_node;
    };

    double current_node = find_lowest_code_node();
    while (current_node != -1) {
        double cost = costs[current_node];
        std::unordered_map<int, double> neighbors = graph[current_node];
        for (auto& [neighbor, weight] : neighbors) {
            double new_cost = cost + weight;
            if (costs[neighbor] > new_cost) {
                costs[neighbor] = new_cost;
                parents[neighbor] = current_node;
            }
        }
        processed.insert(current_node);
        current_node = find_lowest_code_node();
    }

    if (costs[end] == std::numeric_limits<double>::max()) {
        return {{}, -1};
    }

    std::vector<int> way;
    int node = end;
    while (node != start) {
        way.push_back(node);
        node = parents[node];
    }
    way.push_back(start);
    std::reverse(way.begin(), way.end());
    
    return {way, costs[end]};
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
                graph[pipe.cs_in][pipe.cs_out] = pipe.getCost();
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

void Network::createConnection() {
    if (pipes.size() == using_pipes.size()) {
        std::cout << "Count of pipes is less than required to create a network!!!";
    } else if (stations.size() < 2) {
        std::cout << "Count of stations is less than required to create a network!!!";
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
            if (!using_pipes.contains(id) && pipe.getStatus() == 0) {
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
        graph[start_cs][end_cs] = pipes[pipe_id].getLength();
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

void Network::showNetwork() {
    if (graph.empty()) {
        std::cout << std::endl << "Network is empty!" << std::endl;
    } else {
        std::cout << std::endl;
        for (auto& [start_cs, neighbors]: graph) {
            std::cout << "" << start_cs << ": ";
            for (auto& [end_cs, pipe_id] : neighbors) {
                std::cout << "(" << end_cs << ", " << pipe_id << ") ";
            }  
            std::cout << std::endl; 
        }
        std::cout << std::endl;
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

void Network::findShortestWay() {
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

        auto [way, length] = getShortestWay(start_cs, end_cs);

        if (length == -1) {
            std::cout << std::endl << "There is no way between these stations on the network!!!" << std::endl;
        } else {
            std::cout << std::endl;
            for (int i = 0; i < way.size(); i++) {
                std::cout << "Station " << i + 1 << " id: " << way[i] << std::endl;
            }
            std::cout << std::endl << "Total length: " << length << std::endl;
        }
    }
        
}